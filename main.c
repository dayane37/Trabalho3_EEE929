/**
 * Criado por Dayane do Carmo Mendonça,João Marcus Soares Callegari,William Caires Silva Amorim
 * Aquivo: main.c
 */

#include "main.h"


/****************************************************************************************
 *************************      GLOBAL VARIABLES DECLARATION        *********************
 ****************************************************************************************/
static Inverter inv;

int main(void)
{

    Data_Init(); // Setup data structure

    System_Init(); // System initialization and setup Peripherals: ADC, GPIO, PWM, interruptions

    while(1){


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

    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;      // Limpa flag INT1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;     // Limpa flag

    GpioDataRegs.GPADAT.bit.GPIO15 = 0; //Change pin state to verify task time consumption

    EPwm4Regs.CMPA.bit.CMPA = 1500;
    EPwm5Regs.CMPA.bit.CMPA = 1500;
    EPwm6Regs.CMPA.bit.CMPA = 1500;

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


