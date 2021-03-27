/**
 * Criado por Dayane do Carmo Mendon�a,Jo�o Marcus Soares Callegari,William Caires Silva Amorim
 * Aquivo: main.c
 */

#include "main.h"

/****************************************************************************************
 ******************************      EXECUTION OPTIONS        ***************************
 ****************************************************************************************/
//#define MODULACAO_SEMCONTROLE    // Comenta para habilitar modula��o em malha aberta

/****************************************************************************************
 *************************      GLOBAL VARIABLES DECLARATION        *********************
 ****************************************************************************************/
static Inverter inv;
static PR PR_ialfa;             //Alfa current controller
static PR PR_ibeta;             //Beta current controller

//Control loop references
float Io_ref = 0;   //Peak
float Io_ref_in = 0;
float ia_inst = 0;
float ib_inst = 0;
float ic_inst = 0;
float cos_a = 0;
float cos_b = 0;
float cos_c = 0;
float ref_mod = 0;
float fo = 0;
float theta = 0;
float Vpwm_norm_a = 0;
float Vpwm_norm_b = 0;
float Vpwm_norm_c = 0;
uint16_t dutya = 0, dutyb = 0, dutyc = 0;

#define PLOT_SAMPLES 400
float Channel_1[PLOT_SAMPLES];
float *p_Channel1 = &(inv.Ifa.inst);
float Channel_2[PLOT_SAMPLES];
float *p_Channel2 = &(inv.Ifb.inst);

// Manual command to pass from presync to connected state
int Manual_Presync=0;

// Manual command to turn on PWM
int Manual_Start=0;

int main(void)
{

    Data_Init(); // Setup data structure

    System_Init(); // System initialization and setup Peripherals: ADC, GPIO, PWM, interruptions

    Operation_Mode();  //Check the inverter operating mode

    Setup_Controllers();  //Setup current and voltage controllers


    //GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
   // GpioDataRegs.GPADAT.bit.GPIO31 = 1;

    while(1){

// State Machine---------------------------------------------------------
        switch (inv.State)
        {
        case TURNED_ON:
            if(inv.Mode==Undefined_Mode)
            {
                Error_Handler(UNDEFINED_INVERTER_MODE);
            }
            else if(Msrmt_State_Get()==READY)
            {
                inv.State = START_UP_COMPLETE;
            }
            break;
        case START_UP_COMPLETE:
            if (Pre_Sync())
            {
                inv.State = PRE_SYNC_COMPLETE;
            }
            break;
        case PRE_SYNC_COMPLETE:
            inv.State = CONNECTED;
            break;
        case CONNECTED:
            inv.ioref_alfa=0;
            inv.ioref_beta=0;
            Io_ref=0;
            pr_reg_reset(&PR_ialfa);
            pr_reg_reset(&PR_ibeta);

            if(!Pre_Sync()) inv.State = START_UP_COMPLETE;
            else if (Manual_Start) {
                inv.State = PWM_ON;
                PWM_Enable();
            }
            break;
        case PWM_ON:
            if (!Manual_Start)
            {
                PWM_Disable();
                inv.State = CONNECTED;
            }
            break;
        case HAVE_ERROR:
            //Do nothing
            break;
        }
    }

}


/********************************************************************************
 *****************************   INTERRUPTIONS      *****************************
 *********************************************************************************/

__interrupt void isr_cpu_timer0(void){
    GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;     // Limpa flag
}


__interrupt void isr_adc(void){
    GpioDataRegs.GPADAT.bit.GPIO15 = 1;    //Change pin state to verify task time consumption

    //Medi��es
    inv.Vcc = VDC_SCALE*AdcaResultRegs.ADCRESULT2;
    Msrmt_Update(&inv.Ifa, AdccResultRegs.ADCRESULT0-2252);
    Msrmt_Update(&inv.Ifb, AdcbResultRegs.ADCRESULT0-2252);
    Msrmt_Update(&inv.Ifc, AdcaResultRegs.ADCRESULT0-2252);

   if(inv.State >= START_UP_COMPLETE) PLL_Loop();
   if(inv.State >= PRE_SYNC_COMPLETE) inv.freq = fo; //Get Grid frequency for protection routine

   // PROTECTION ALGORITHM (PWM is disabled if limits are exceeded)
   Voltage_Protection();
   OverCurrent_Protection();
   Frequency_Protection();

   if (inv.State == PWM_ON)
      {
          if (inv.Mode == Grid_Feeding) Feeding_Loop();
          Current_Loop();
      }

      Msrmt_Index_Update();



    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;      // Limpa flag INT1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;     // Limpa flag

    GpioDataRegs.GPADAT.bit.GPIO15 = 0; //Change pin state to verify task time consumption

    Plot();

}
//*/

__attribute__((always_inline)) void abc2alfabeta(MEASUREMENT *A, MEASUREMENT *B,MEASUREMENT *C, ALFABETA *alfabeta)
{
    // Invariante em amplitude
    alfabeta->alfa = 0.66666666666667*(A->inst - 0.5*B->inst - 0.5*C->inst);
    alfabeta->beta = 0.5773502692*(B->inst - C->inst);

    // Invariante em pot�ncia
   //p_alfabeta->alfa = 0.816496580927726*(p_abc->a - 0.5*p_abc->b - 0.5*p_abc->c);
   //p_alfabeta->beta = 0.816496580927726*(0.866025403784439*p_abc->b - 0.866025403784439*p_abc->c);
}

__attribute__((always_inline)) void alfabeta2abc(Inverter* alfabeta, ABC* abc)
{
    // Invariante em amplitude
    abc->a = alfabeta->alfa;
    abc->b = -0.5*alfabeta->alfa + 0.866025403784439*alfabeta->beta;
    abc->c = -0.5*alfabeta->alfa - 0.866025403784439*alfabeta->beta;

    // Invariante em pot�ncia
    //p_ABC->a = 0.816496580927726*p_alfabeta->alfa;
    //p_ABC->b = 0.816496580927726*(-0.5*p_alfabeta->alfa + 0.866025403784439*p_alfabeta->beta);
    //p_ABC->c = 0.816496580927726*(-0.5*p_alfabeta->alfa - 0.866025403784439*p_alfabeta->beta);
}

__attribute__((always_inline)) void PLL_Loop()
{
        fo = (NOM_GRID_FREQ);
        theta = (theta > TWO_PI) ? (theta - TWO_PI) : (theta + WT_DELTA);

        cos_a = __cos(theta);
        cos_b = __cos(theta-2.094395102393195);
        cos_c = __cos(theta+2.094395102393195);

}

__attribute__((always_inline)) void Feeding_Loop()
{


        Io_ref = Io_ref + (0.01)*(Io_ref_in - Io_ref); //  Current reference calculation

        ia_inst = Io_ref*cos_a;
        ib_inst = Io_ref*cos_b;
        ic_inst = Io_ref*cos_c;

        inv.ioref_alfa = 0.66666666666667*(ia_inst - 0.5*ib_inst - 0.5*ic_inst);  //  alpha-current reference calculation
        inv.ioref_beta = 0.5773502692*(ib_inst - ic_inst); //  beta-current reference calculation
        //inv.ioref_alfa = Io_ref*cos_;
        //inv.ioref_beta = Io_ref*sin_;
}

__attribute__((always_inline)) void Current_Loop()
{

    #ifdef MODULACAO_SEMCONTROLE

    vsa_svpwm = ref_mod*cos_a;
    vsb_svpwm = ref_mod*cos_b;
    vsc_svpwm = ref_mod*cos_c;

    #else

    abc2alfabeta(&inv.Ifa, &inv.Ifb, &inv.Ifc, &inv.Ialfabeta);

    //Current controller
    PR_ialfa.Err = inv.ioref_alfa - inv.Ialfabeta.alfa;
    calc_PR(&PR_ialfa, PR_ialfa.Err);

    PR_ibeta.Err = inv.ioref_beta - inv.Ialfabeta.beta;
    calc_PR(&PR_ibeta, PR_ibeta.Err);

    inv.alfa = PR_ialfa.Kp*PR_ialfa.Err+PR_ialfa.Out;
    inv.beta = PR_ibeta.Kp*PR_ibeta.Err+PR_ibeta.Out;

    alfabeta2abc(&inv, &inv.Vabc);

    Vpwm_norm_a = __divf32(inv.Vabc.a*1.732050807568877,inv.Vcc);
    Vpwm_norm_b =  __divf32(inv.Vabc.b*1.732050807568877,inv.Vcc);
    Vpwm_norm_c =  __divf32(inv.Vabc.c*1.732050807568877,inv.Vcc);

    if(Vpwm_norm_a > 1) Vpwm_norm_a = 1;
    if(Vpwm_norm_a < -1) Vpwm_norm_a = -1;
    if(Vpwm_norm_b > 1) Vpwm_norm_b = 1;
    if(Vpwm_norm_b < -1) Vpwm_norm_b = -1;
    if(Vpwm_norm_c > 1) Vpwm_norm_c = 1;
    if(Vpwm_norm_c < -1) Vpwm_norm_c = -1;

   #endif


    dutya = PRD_div2 + Vpwm_norm_a*PRD_div2;
    dutyb = PRD_div2 + Vpwm_norm_b*PRD_div2;
    dutyc = PRD_div2 + Vpwm_norm_c*PRD_div2;

    // duty cycle
    EPwm4Regs.CMPA.bit.CMPA = dutya;
    EPwm5Regs.CMPA.bit.CMPA =  dutyb;
    EPwm6Regs.CMPA.bit.CMPA =  dutyc;

}


__attribute__((always_inline)) void OverCurrent_Protection(void)
{
    if (inv.Ifa.inst > IO_MAX || inv.Ifb.inst > IO_MAX || inv.Ifc.inst > IO_MAX) //Instantaneous overcurrent (short-circuit protection)
    {
        Error_Handler(INVERTER_OVERCURRENT_2);
    }
}

__attribute__((always_inline)) void Voltage_Protection(void)
{
    if (inv.Vcc > VCC_MAX)
    {
        Error_Handler(VCC_OVERVOLTAGE);
    }
}

__attribute__((always_inline)) void Frequency_Protection(void)
{
    if (inv.freq > F_MAX)
    {
        Error_Handler(GRID_FREQUENCY_HIGH);
    }
    else if (inv.freq < F_MIN)
    {
        Error_Handler(GRID_FREQUENCY_LOW);
    }
}


__attribute__((always_inline)) void Error_Handler(err_code_t errorCode)
{
    PWM_Disable();
    inv.State = HAVE_ERROR;
    inv.Error = errorCode;
}

static void PWM_Enable(void)
{
    GpioDataRegs.GPADAT.bit.GPIO26 = 0; //Enable PWM
}

//-----------------------------------------------------------------------------
static void PWM_Disable(void)
{
    GpioDataRegs.GPADAT.bit.GPIO26 = 1; //Disable PWM
}



__attribute__((always_inline)) int Pre_Sync(void)
{
   return Manual_Presync;
}

__attribute__((always_inline)) void Plot(void)
{
    static unsigned int plot_ind_vetor = 0;
    Channel_1[plot_ind_vetor] = *p_Channel1;
    Channel_2[plot_ind_vetor] = *p_Channel2;
    plot_ind_vetor = (plot_ind_vetor == (PLOT_SAMPLES - 1)) ? 0 : (plot_ind_vetor + 1);
}

static void Data_Init(void)
{
    memset(&inv, 0, sizeof(Inverter));

    //Variables initialization
    Msrmt_Init(&inv.Ifa,IO_SCALE, 1, 0, 0);
    Msrmt_Init(&inv.Ifb,IO_SCALE, 1, 0, 0);
    Msrmt_Init(&inv.Ifc,IO_SCALE, 1, 0, 0);
    inv.freq = fn;
}


static void System_Init(void)
{
    InitSysCtrl();                  //Initialize System Control

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.CPUTIMER0 = 1;
    EDIS;

    DINT;                           //Disable CPU interrupts
    InitPieCtrl();                  //Initialize the PIE control registers to their default state
    IER = 0x0000;                   //Disable CPU interrupts
    IFR = 0x0000;                   //Clear all CPU interrupt flags
    InitPieVectTable();             //Initialize the PIE vector table

    Setup_GPIO();
    Setup_ePWM();
    Setup_ADC();

    EALLOW;
    PieVectTable.TIMER0_INT = &isr_cpu_timer0;   // Redirecionar interrup��o do timer para fun��o
    PieVectTable.ADCA1_INT = &isr_adc;           // Redirecionar interrup��o do adc para fun��o
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;           // Habilita coluna da interrup��o do timer 0
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;           // ADC a
    EDIS;
    IER |= M_INT1;                              // +M_INT2 Habilita interrup��es da linha 1

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 200, 1000000);
    CpuTimer0Regs.TCR.all = 0x4001;

   EINT;                           //Enable Global interrupt INTM
   ERTM;                           //Enable Global real-time interrupt DBGM

}

static void Operation_Mode(void)
{
    inv.Mode=Grid_Feeding;
}

static void Setup_Controllers(void)
{
    PR_ialfa.ch[0] = 0.157068238876871;
    PR_ialfa.ch[1] =  -0.157068238876871;
    PR_ialfa.ch[2] =   -1.999690445418618;
    PR_ialfa.ch[3] = 0.999937172704449;

    PR_ibeta.ch[0] = 0.157068238876871;
    PR_ibeta.ch[1] =  -0.157068238876871;
    PR_ibeta.ch[2] =   -1.999690445418618;
    PR_ibeta.ch[3] = 0.999937172704449;

    PR_ialfa.Kp =  24.9813;
    PR_ibeta.Kp =  24.9813;
}
