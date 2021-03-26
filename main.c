/**
 *  Created on: 9 de mar de 2021 
 *      Author: Dayane do Carmo Mendonça,João Marcus Soares Callegari,William Caires Silva Amorim
 * Aquivo: main.c
 */

#include "main.h"

/****************************************************************************************
 ******************************      EXECUTION OPTIONS        ***************************
 ****************************************************************************************/
//#define MODULACAO_SEMCONTROLE    // Comenta para habilitar modulação em malha aberta

/****************************************************************************************
 *************************      GLOBAL VARIABLES DECLARATION        *********************
 ****************************************************************************************/
static Inverter inv;

//Control loop references
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

// Manual command to turn on PWM
int Manual_Start=0;

int main(void)
{

    Data_Init(); // Setup data structure

    System_Init(); // System initialization and setup Peripherals: ADC, GPIO, PWM, interruptions

    while(1){


      if (Manual_Start)
      {
          PWM_Enable();
      }

      if (!Manual_Start)
      {
          PWM_Disable();
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

    //Medições
    inv.Vcc = VDC_SCALE*AdcaResultRegs.ADCRESULT2;
    Msrmt_Update(&inv.Ifa, AdccResultRegs.ADCRESULT0-2252);
    Msrmt_Update(&inv.Ifb, AdcbResultRegs.ADCRESULT0-2252);
    Msrmt_Update(&inv.Ifc, AdcaResultRegs.ADCRESULT0-2252);

   PLL_Loop();

   // PROTECTION ALGORITHM (PWM is disabled if limits are exceeded)
   Voltage_Protection();
   OverCurrent_Protection();
   Frequency_Protection();

   if (Manual_Start)
   {
       Current_Loop();
   }

      Msrmt_Index_Update();

    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;      // Limpa flag INT1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;     // Limpa flag

    GpioDataRegs.GPADAT.bit.GPIO15 = 0; //Change pin state to verify task time consumption

}
//*/


__attribute__((always_inline)) void PLL_Loop()
{
        fo = (NOM_GRID_FREQ);
        theta = (theta > TWO_PI) ? (theta - TWO_PI) : (theta + WT_DELTA);

        cos_a = __cos(theta);
        cos_b = __cos(theta-2.094395102393195);
        cos_c = __cos(theta+2.094395102393195);

}


__attribute__((always_inline)) void Current_Loop()
{

    Vpwm_norm_a = ref_mod*cos_a;
    Vpwm_norm_b = ref_mod*cos_b;
    Vpwm_norm_c = ref_mod*cos_c;


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
    PieVectTable.TIMER0_INT = &isr_cpu_timer0;   // Redirecionar interrupção do timer para função
    PieVectTable.ADCA1_INT = &isr_adc;           // Redirecionar interrupção do adc para função
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;           // Habilita coluna da interrupção do timer 0
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;           // ADC a
    EDIS;
    IER |= M_INT1;                              // +M_INT2 Habilita interrupções da linha 1

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 200, 1000000);
    CpuTimer0Regs.TCR.all = 0x4001;

   EINT;                           //Enable Global interrupt INTM
   ERTM;                           //Enable Global real-time interrupt DBGM

}


