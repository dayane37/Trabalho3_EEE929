/*
 * Measurements.c
 *
 *  Created on: 9 de mar de 2021
 *      Author: Dayane do Carmo Mendonça,João Marcus Soares Callegari,William Caires Silva Amorim
 */
#include "Measurements.h"

int index=0;
int offset_cycles_counter=0;
msrmt_state_t state=OFFSET_CALC;

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

        if(state==OFFSET_CALC)
        {
        //Remove offset
        //M->adc_offset = M->adc_offset - KI_OFFSET*M->avg;
       // M->inst = M->scale*adc_read + M->adc_offset;

        //old_div_n = N_SAMPLES_INV*M->buffer[index];
       // new_div_n =N_SAMPLES_INV* M->inst;

      //  M->avg -= old_div_n;//Remove oldest value
       // M->avg += new_div_n;//Put new value
        }
        else if(M->config.rmv_offset){
        //M->inst = M->scale*adc_read + M->adc_offset;
        M->inst = M->scale*adc_read;
        }
        else {  //Just scale adc read
        M->inst= M->scale*adc_read;
        }
}

__attribute__((always_inline)) void Msrmt_Index_Update(void){
//Pass to next old data
    //index = (index == (N_SAMPLES - 1)) ? 0 : (index+1);
    if(index > (N_SAMPLES - 1))
    {
        index=0;
        if(state==OFFSET_CALC)
        {
            if(offset_cycles_counter<OFFSET_CALC_CYCLES)
            {
                offset_cycles_counter++;
            }
            else
            {
                state=READY;
            }
        }

    }
    else index++;
}

__attribute__((always_inline)) int Msrmt_Index_Get(void){
    return index;
}

msrmt_state_t Msrmt_State_Get(void){
    return state;
}
