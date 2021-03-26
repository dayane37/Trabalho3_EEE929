/*
 * main.h
 *
 *  Created on: 9 de mar de 2021 *      Author: Dayane do Carmo Mendonça,João Marcus Soares Callegari,William Caires Silva Amorim
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

#define VCC_MAX     60                  //Maximum DC bus voltage (450/HV) _IQ(2.250)
#define VG_RMS_MAX  60                  //Maximum RMS grid voltage (1.1 x Vrms - ABNT 16149) (242/HV) _IQ(1.210)
#define VG_INST_MAX 60                 //Maximum instantaneous grid voltage (400/Hv) _IQ(2.0)
#define IO_MAX      8                      //Maximum output current (20/HI) _IQ(1.0)
#define IO_MAX_OVL  8                  //Maximum output current - overload protection (15/HI) _IQ(0.75)
#define F_MIN       45.5                    //Minimum operating frequency (ABNT 16149)_IQ22(57.5) _IQ22(55.5)
#define F_MAX       55.5                        //Maximum operating frequency (ABNT 16149)_IQ22(62.5) _IQ22(65.5)

typedef enum {
    NO_ERROR,INVERTER_OVERCURRENT_0,INVERTER_OVERCURRENT_1,INVERTER_OVERCURRENT_2, INVERTER_OVERCURRENT_RMS, BOOST_OVERCURRENT, RCMU_LIMIT_EXCEED, VCC_OVERVOLTAGE,
                         TEMP_LIMIT_EXCEED, VGRID_OVERVOLTAGE, VGRID_UNDERVOLTAGE, GRID_FREQUENCY_HIGH,
                         GRID_FREQUENCY_LOW, INIT_FAIL,UNDEFINED_INVERTER_MODE} err_code_t;


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
   err_code_t Error;           //Error Code
}Inverter;

/****************************************************************************************
 *************************      LOCAL FUNCTIONS DECLARATION     *************************
 ****************************************************************************************/
//Initialization
static void Data_Init(void);
static void System_Init(void);

//Protection
__attribute__((always_inline)) void OverCurrent_Protection(void);
__attribute__((always_inline)) void Voltage_Protection(void);
__attribute__((always_inline)) void Frequency_Protection(void);
__attribute__((always_inline)) void Error_Handler(err_code_t error);
static void PWM_Enable(void);
static void PWM_Disable(void);

// Interruptions
__interrupt void isr_cpu_timer0(void);
__interrupt void isr_adc(void);



#endif /* MAIN_H_ */
