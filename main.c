/**
 * Criado por Dayane do Carmo Mendonça
 * Aquivo: main.c
 */


#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "F28x_Project.h"

//Initialization
static void System_Init(void);

// Interruptions
__interrupt void isr_cpu_timer0(void);


int main(void)
{
    EALLOW;
    // Leds
    GpioCtrlRegs.GPAGMUX2.bit.GPIO31 = 0;  // Configura o agrupamento como GPIO
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;   // Configura o periférico como GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;    //Configure GPIO as output pin (LED AZUL)
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 1;    // Disable pull-up on GPIO31
    GpioCtrlRegs.GPACSEL4.bit.GPIO31 = GPIO_MUX_CPU1;    // Passa controle do pino para CPU1

    GpioCtrlRegs.GPBGMUX1.bit.GPIO34 = 0;               // Configura o agrupamento como GPIO
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;                // Configura o periférico como GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;                 //Configure GPIO as output pin (LED vermelho)
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;                 // Disable pull-up on GPIO34
    GpioCtrlRegs.GPBCSEL1.bit.GPIO34 = GPIO_MUX_CPU1;    // Passa controle do pino para CPU1
    EDIS;

    System_Init();

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


    EALLOW;
    PieVectTable.TIMER0_INT = &isr_cpu_timer0;   // Redirecionar interrupção do timer para função
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;           // Habilita coluna da interrupção do timer 0
    EDIS;
    IER |= M_INT1;                              // +M_INT2 Habilita interrupções da linha 1

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 200, 1000000);
    CpuTimer0Regs.TCR.all = 0x4001;

   EINT;                           //Enable Global interrupt INTM
   ERTM;                           //Enable Global real-time interrupt DBGM

}


