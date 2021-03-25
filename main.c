/**
 * Criado por Jo�o Marcus Soares Callegari
 *            Dayane do Carmo Mendon�a
 *            William Caires Silva Amorim
 * Aquivo: main.c
 */

#include "main.h"


/****************************************************************************************
 *************************      GLOBAL VARIABLES DECLARATION        *********************
 ****************************************************************************************/

int main(void)
{

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

    EALLOW;
    PieVectTable.TIMER0_INT = &isr_cpu_timer0;   // Redirecionar interrup��o do timer para fun��o
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;           // Habilita coluna da interrup��o do timer 0
    EDIS;
    IER |= M_INT1;                              // +M_INT2 Habilita interrup��es da linha 1

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 200, 1000000);
    CpuTimer0Regs.TCR.all = 0x4001;

   EINT;                           //Enable Global interrupt INTM
   ERTM;                           //Enable Global real-time interrupt DBGM

}


