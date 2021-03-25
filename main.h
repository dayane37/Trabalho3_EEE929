/*
 * main.h
 *
 *  Created on: 9 de mar de 2021
 *      Author: Dayane do Carmo Mendonça,João Marcus Soares Callegari,William Caires Silva Amorim
 */

#include "Peripheral_Setup.h"
#include "Measurements.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "string.h"

#ifndef MAIN_H_
#define MAIN_H_

//Scale Factors
#define VDC_ANG_GAIN 0.040491268470543     //Analog gain of input DC bus voltage sense
#define VG_ANG_GAIN 0.040491268470543      //Analog gain of grid voltage sense
#define IO_ANG_GAIN 0.1000                 //Analog gain of grid current sense

//Ganho do ADC
#define ADC_VOLTAGE_REFERENCE 3.0 // VDDA voltage
#define ADC_GAIN (4095.0/(double)ADC_VOLTAGE_REFERENCE) // 12bit ADC

#define VG_SCALE (1.0/((double)ADC_GAIN*VG_ANG_GAIN))
#define VDC_SCALE (1.0/((double)ADC_GAIN*VDC_ANG_GAIN))
#define IO_SCALE (1.0/((double)ADC_GAIN*IO_ANG_GAIN))

#define DUTY_MAX  1
#define DUTY_MIN  -1

//PWM Carrier peak value
#define PRD 5000            //fsw=20 kHz @ 200MHz clock
#define PRD_div2 2500

#define Ts 5.0e-05                //Sampling time (1/Sampling frequency)
#define wn 3.141592653589793e+02  // Nominal angular frequency rad/s
#define fn 50                     // Nominal frequency Hz
#define TWO_PI 6.283185307179586476925286766559 //2*pi (Numeric Constant)
#define WT_DELTA (0.01570796)    //Angle step for internal reference generation


typedef struct{
   MEASUREMENT Ifa;        //Analog filtered Output Current
   MEASUREMENT Ifb;        //Analog filtered Output Current
   MEASUREMENT Ifc;        //Analog filtered Output Current
   float Vcc;              //Voltage on DC bus (regulated by boost)
   float freq;             //Measured Frequency
   float temp;             //Inverter temperature
   float Duty;
   float alfa;
   float beta;
   float ioref_alfa;
   float ioref_beta;
   float voref;
}Inverter;

/****************************************************************************************
 *************************      LOCAL FUNCTIONS DECLARATION     *************************
 ****************************************************************************************/
//Initialization
static void Data_Init(void);
static void System_Init(void);

// Interruptions
__interrupt void isr_cpu_timer0(void);
__interrupt void isr_adc(void);



#endif /* MAIN_H_ */
