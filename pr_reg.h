/*
 * pr_reg.h
 *
 *  Created on: 9 de mar de 2021
 *      Author: Dayane do Carmo Mendonça,João Marcus Soares Callegari,William Caires Silva Amorim
 */
#ifndef _STRING
    #include <string.h>
#endif

#ifndef PR_REG_H_
#define PR_REG_H_

typedef struct {
    float  Err;             // Variable: Error
    float  Err_ant;
    float  Err_ant2;
    float  Kp;              // Parameter: Proportional gain
    float  Out;
    float  OutMax;          // Parameter: Maximum output
    float  OutMin;          // Parameter: Minimum output
    float  Out_ant;
    float  Out_ant2;
    float  ch[4];
} PR;

void pr_reg_init(PR *pr, float *ch, float Kp, float OutMax, float OutMin);
void pr_reg_reset(PR *pr);
void calc_PR(PR *pr, float Err);




#endif /* PR_REG_H_ */
