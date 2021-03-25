/*
 * Peripheral_Setup.c
 *
 *  Created on: 28 de fev de 2021
 *      Author: Dayane do Carmo Mendonça,João Marcus Soares Callegari,William Caires Silva Amorim
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


void Setup_ADC(void){

    Uint16 acqps; // Determina a janela de aquisição mínima

    EALLOW;

    AdcaRegs.ADCCTL2.bit.PRESCALE = 6;        // Divide por 4
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcbRegs.ADCCTL2.bit.PRESCALE = 6;        // Divide por 4
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdccRegs.ADCCTL2.bit.PRESCALE = 6;        // Divide por 4
    AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;    //ADCINT1 trips after AdcResults latch
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;    //ADCINT1 trips after AdcResults latch
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;    //ADCINT1 trips after AdcResults latch

    if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION) acqps = 14;     // ADC de 12 bits: 25*5 ns
    else acqps = 63;                                                            // ADC de 16 bits: 320 ns


    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 4;       //Set SOC0 channel select to ADCINA4 (Ia)
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 5;       //Set SOC1 channel select to ADCINA5 (Va)
    AdcaRegs.ADCSOC2CTL.bit.CHSEL = 15;       //Set SOC0 channel select to ADCIN15 (Vdc)
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps;   //set SOC0 S/H Window
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps;   //set SOC1 S/H Window
    AdcaRegs.ADCSOC2CTL.bit.ACQPS = acqps;    //set SOC0 S/H Window
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 11;   //SOC Trigger source select ePWM4A
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 11;   //sSOC Trigger source select ePWM4A
    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 11;     //SOC Trigger source select ePWM4A

    AdcbRegs.ADCSOC0CTL.bit.CHSEL = 4;       //Set SOC0 channel select to ADCINB4 (Ib)
    AdcbRegs.ADCSOC1CTL.bit.CHSEL = 5;       //Set SOC1 channel select to ADCINB5 (Vb)
    AdcbRegs.ADCSOC0CTL.bit.ACQPS = acqps;   //set SOC0 S/H Window
    AdcbRegs.ADCSOC1CTL.bit.ACQPS = acqps;   //set SOC1 S/H Window
    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 11;   //SOC Trigger source select ePWM4A
    AdcbRegs.ADCSOC1CTL.bit.TRIGSEL = 11;   //SOC Trigger source select ePWM4A

    AdccRegs.ADCSOC0CTL.bit.CHSEL = 4;       //Set SOC0 channel select to ADCINC4 (Ic)
    AdccRegs.ADCSOC1CTL.bit.CHSEL = 5;       //Set SOC1 channel select to ADCINC5 (Vc)
    AdccRegs.ADCSOC0CTL.bit.ACQPS = acqps;   //set SOC0 S/H Window
    AdccRegs.ADCSOC1CTL.bit.ACQPS = acqps;   //set SOC1 S/H Window
    AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 11;   //SOC Trigger source select ePWM4A
    AdccRegs.ADCSOC1CTL.bit.TRIGSEL = 11;   //SOC Trigger source select ePWM4A

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 2;      //setup EOC6 to trigger ADCINT1 to fire
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;        //Enabled ADCINT1
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;     //Disable ADCINT1 Continuous mode

    AdcbRegs.ADCINTSEL1N2.bit.INT1SEL = 1;      //setup EOC6 to trigger ADCINT1 to fire
    AdcbRegs.ADCINTSEL1N2.bit.INT1E = 1;        //Enabled ADCINT1
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;     //Disable ADCINT1 Continuous mode

    AdccRegs.ADCINTSEL1N2.bit.INT1SEL = 1;      //setup EOC6 to trigger ADCINT1 to fire
    AdccRegs.ADCINTSEL1N2.bit.INT1E = 1;        //Enabled ADCINT1
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;     //Disable ADCINT1 Continuous mode

    //AdcRegs.ADCINTSEL1N2.bit.INT1SEL = 0;      //setup EOC6 to trigger ADCINT1 to fire
    //AdcRegs.ADCINTSEL1N2.bit.INT1E = 1;        //Enabled ADCINT1
   // AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;     //Disable ADCINT1 Continuous mode
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;       // Power up the adc
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;       // Power up the adc
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;       // Power up the adc


    DELAY_US(1000);                          // Espera 1 ms para o adc ligar

    EDIS;

}


