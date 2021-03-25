/*
 * Peripheral_Setup.c
 *
 *  Created on: 28 de fev de 2021
 * Criado por João Marcus Soares Callegari
 *            Dayane do Carmo Mendonça
 *            William Caires Silva Amorim
 */

#include "Peripheral_Setup.h"
#include "F28x_Project.h"

void Setup_GPIO(void){
    EALLOW;

    // PWM Reset
    GpioCtrlRegs.GPAGMUX2.bit.GPIO26 = 0;  // Configura o agrupamento
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;   // Configure GPI26 as GPIO
    GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;    // Enable pull-up on GPIO06
    GpioCtrlRegs.GPADIR.bit.GPIO26 = 1;     // GPIO Output
    GpioCtrlRegs.GPACSEL4.bit.GPIO26 = GPIO_MUX_CPU1;    // Passa controle do pino para CPU1

    //Pino 15
    GpioCtrlRegs.GPAGMUX1.bit.GPIO15 = 0;  // Configura o agrupamento
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;   // Configure GPI15 as GPIO
    GpioCtrlRegs.GPAPUD.bit.GPIO15 = 1;    // Disable pull-up on GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;
    GpioCtrlRegs.GPACSEL2.bit.GPIO15 = GPIO_MUX_CPU1;    // Passa controle do pino para CPU1


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
}


