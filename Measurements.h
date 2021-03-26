/*
 * Measurements.h
 *
 *  Created on: 9 de mar de 2021
 *      Author: Dayane do Carmo Mendonça,João Marcus Soares Callegari,William Caires Silva Amorim
 */

#ifndef _STRING
    #include <string.h>
#endif

#ifndef MEASUREMENTS_H_
#define MEASUREMENTS_H_

#define N_SAMPLES 400 //Number of samples per period
#define OFFSET_CALC_CYCLES 10
#define KI_OFFSET  (0.002) //ADC offset integral controller
#define SQRT_2_INV (0.707106781186548) //Inverse of sqrt(2)
#define N_SAMPLES 400                   // Numero de pontos da fundamental N = fs/fn;
#define N_SAMPLES_2 200                 // Numero de pontos da fundamental N = fs/fn;
#define N_SAMPLES_INV (1.0/N_SAMPLES) //Inverse of N_SAMPLES
#define NOM_GRID_FREQ 50

typedef enum{
    OFFSET_CALC,
    READY
}msrmt_state_t;

typedef struct{
    int rmv_offset;
    int rms_calc;
    int thd_calc;
}CONFIG_CALC;


typedef struct{
    //float buffer[N_SAMPLES];    //Sample buffer
    CONFIG_CALC config;        //Configuration values
    float scale;                   //ADC Scale factor
    float adc_read;            //ADC reading
    float adc_offset;              //ADC Offset
    float inst;                   //Instantaneous value (after scale and offset)
    float avg;                    //Average value
    float THD;                    //Total Harmonic Distortion
    float RMS;                    //RMS
    float RMS2;                   //Squared RMS value
}MEASUREMENT;

void Msrmt_Init(MEASUREMENT *M, float scale, int rmv_offset, int rms_calc, int thd_calc);
__attribute__((always_inline)) void Msrmt_Update(MEASUREMENT *M, int adc_read);
__attribute__((always_inline)) void Msrmt_Index_Update(void);
__attribute__((always_inline)) int Msrmt_Index_Get(void);
msrmt_state_t Msrmt_State_Get(void);

#endif /* MEASUREMENTS_H_ */
