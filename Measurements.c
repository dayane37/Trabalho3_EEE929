/*
 * Measurements.c
 *
 *  Created on: 9 de mar de 2021
 *      Author: Dayane do Carmo Mendonça,João Marcus Soares Callegari,William Caires Silva Amorim
 */
#include "Measurements.h"

int index=0;
int offset_cycles_counter=0;


void Msrmt_Init(MEASUREMENT *M, float scale, int rmv_offset, int rms_calc, int thd_calc)
{
    memset(M,0,sizeof(MEASUREMENT));
    M->scale=scale;
    M->config.rmv_offset=rmv_offset;
    M->config.rms_calc=rms_calc;
    M->config.thd_calc=thd_calc;
}

__attribute__((always_inline)) void Msrmt_Update(MEASUREMENT *M, int adc_read)
{
        float old_div_n,new_div_n;

        M->adc_read = adc_read;

        M->inst = M->scale*adc_read;

}

__attribute__((always_inline)) void Msrmt_Index_Update(void){
//Pass to next old data
    index = (index == (N_SAMPLES - 1)) ? 0 : (index+1);
}

__attribute__((always_inline)) int Msrmt_Index_Get(void){
    return index;
}

