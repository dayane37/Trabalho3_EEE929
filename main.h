/*
 * main.h
 *
 *  Created on: 9 de mar de 2021
 *      Author: João Marcus Soares Callegari
 */

#include "Peripheral_Setup.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "string.h"

#ifndef MAIN_H_
#define MAIN_H_


//PWM Carrier peak value
#define PRD 5000            //fsw=20 kHz @ 200MHz clock
#define PRD_div2 2500

#define Ts 5.0e-05                //Sampling time (1/Sampling frequency)
#define wn 3.141592653589793e+02  // Nominal angular frequency rad/s
#define fn 50                     // Nominal frequency Hz
#define TWO_PI 6.283185307179586476925286766559 //2*pi (Numeric Constant)


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
