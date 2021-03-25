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


    //Pinos PWM 4AB
    GpioCtrlRegs.GPAGMUX1.bit.GPIO6 = 0;  // Configura o agrupamento
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;    // Disable pull-up on GPIO06 (EPWM4A)

    GpioCtrlRegs.GPAGMUX1.bit.GPIO7 = 0;  // Configura o agrupamento
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;    // Disable pull-up on GPIO07 (EPWM4B)

    //Pinos PWM 5AB
    GpioCtrlRegs.GPAGMUX1.bit.GPIO8 = 0;  // Configura o agrupamento
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO8 as EPWM5A
    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 1;    // Disable pull-up on GPIO08 (EPWM5A)

    GpioCtrlRegs.GPAGMUX1.bit.GPIO9 = 0;  // Configura o agrupamento
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO9 as EPWM5B
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;    // Disable pull-up on GPIO09 (EPWM5B)

    //Pinos PWM 6AB
    GpioCtrlRegs.GPAGMUX1.bit.GPIO10 = 0;  // Configura o agrupamento
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   // Configure GPIO10 as EPWM6A
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;    // Disable pull-up on GPIO010 (EPWM6A)

    GpioCtrlRegs.GPAGMUX1.bit.GPIO11 = 0;  // Configura o agrupamento
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;   // Configure GPIO11 as EPWM6B
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;    // Disable pull-up on GPIO011 (EPWM6B)

    //Pinos PWM 7A e 8A
    GpioCtrlRegs.GPEGMUX2.bit.GPIO157 = 0;  // Configura o agrupamento
    GpioCtrlRegs.GPEMUX2.bit.GPIO157 = 1;   // Configure GPIO157 as EPWM7A
    GpioCtrlRegs.GPEPUD.bit.GPIO157 = 1;    // Disable pull-up on GPIO0157 (EPWM7A)

    GpioCtrlRegs.GPEGMUX2.bit.GPIO159 = 0;  // Configura o agrupamento
    GpioCtrlRegs.GPEMUX2.bit.GPIO159 = 1;   // Configure GPIO159 as EPWM8A
    GpioCtrlRegs.GPEPUD.bit.GPIO159 = 1;    // Disable pull-up on GPIO0159 (EPWM8A)

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


void Setup_ePWM(void){
    ///*
    EALLOW;

    CpuSysRegs.PCLKCR2.bit.EPWM4 = 1;
    CpuSysRegs.PCLKCR2.bit.EPWM5 = 1;
    CpuSysRegs.PCLKCR2.bit.EPWM6 = 1;
    CpuSysRegs.PCLKCR2.bit.EPWM7 = 1;
    CpuSysRegs.PCLKCR2.bit.EPWM8 = 1;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

    // Definição do módulo PWM referente aos timers
    //EPWM4
    EPwm4Regs.TBPRD = PRD_PERIOD;                   // Período da portadora
    EPwm4Regs.CMPA.bit.CMPA = 0;
    EPwm4Regs.TBPHS.bit.TBPHS = 0;                 // Set Phase register to zero
    EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;     // Sync down-stream module
    EPwm4Regs.TBCTR = 0x0000;
    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Symmetrical mode
    EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;         // Master module
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;

    EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;   // load on CTR=Zero
    EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;   // load on CTR=Zero

    EPwm4Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;              // set actions for EPWM4A
    EPwm4Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
    EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;                   // set actions for EPWM4A
    EPwm4Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;      // enable Dead-band module
    EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;           // Active Hi complementary
    EPwm4Regs.DBFED.bit.DBFED = 80;                     // FED = 80 TBCLKs
    EPwm4Regs.DBRED.bit.DBRED = 80;                     // RED = 80 TBCLKs

    //Trigger ADC
    EPwm4Regs.ETSEL.bit.SOCAEN = 1;                     // Habilita SOC no grupo A
    EPwm4Regs.ETSEL.bit.SOCASEL = ET_CTR_PRDZERO;       // Trigga adc no topo e zero
    EPwm4Regs.ETPS.bit.SOCAPRD = ET_1ST;                // Trigga em todo evento

    //EPWM5
    EPwm5Regs.TBPRD = PRD_PERIOD;                   // Period = 2000 TBCLK counts
    EPwm5Regs.CMPA.bit.CMPA = 0;                    // Set CMPA to 0
    EPwm5Regs.TBPHS.bit.TBPHS = 0;                  // Set Phase register to zero
    EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Symmetrical mode
    EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE;          // Slave module
    EPwm5Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;          // sync flow-through
    EPwm5Regs.TBCTR = 0x0000;
    EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;   // load on CTR=Zero and PRD
    EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;   // load on CTR=Zero and PRD
    EPwm5Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;            // set actions for EPWM4A
    EPwm5Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
    EPwm5Regs.AQCTLA.bit.CAU = AQ_SET;                  // set actions for EPWM5A
    EPwm5Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    EPwm5Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;      // enable Dead-band module
    EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;           // Active Hi complementary
    EPwm5Regs.DBFED.bit.DBFED = 80;                     // FED = 80 TBCLKs
    EPwm5Regs.DBRED.bit.DBRED = 80;                     // RED = 80 TBCLKs

    //EPWM6
    EPwm6Regs.TBPRD =  PRD_PERIOD;                      // Period = 2000 TBCLK counts
    EPwm6Regs.CMPA.bit.CMPA = 0;                    // Set CMPA to 0
    EPwm6Regs.TBPHS.bit.TBPHS = 0;                      // Set Phase register to zero
    EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;      // Symmetrical mode
    EPwm6Regs.TBCTL.bit.PHSEN = TB_ENABLE;              // Slave module
    EPwm6Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm6Regs.TBCTR = 0x0000;
    EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;          // sync flow-through
    EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;       // load on CTR=Zero and PRD
    EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;       // load on CTR=Zero and PRD
    EPwm6Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;              // set actions for EPWM4A
    EPwm6Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
    EPwm6Regs.AQCTLA.bit.CAU = AQ_SET;                  // set actions for EPWM3A
    EPwm6Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    EPwm6Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;      // enable Dead-band module
    EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;           // Active Hi complementary
    EPwm6Regs.DBFED.bit.DBFED = 80;                     // FED = 80 TBCLKs
    EPwm6Regs.DBRED.bit.DBRED = 80;                     // RED = 80 TBCLKs

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;

    EDIS;
    //*/
}

