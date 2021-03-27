/*
 * pr_reg.c
 *
 *  Created on: 9 de mar de 2021
 *      Author: Dayane do Carmo Mendonça,João Marcus Soares Callegari,William Caires Silva Amorim
 */

#include "pr_reg.h"

void pr_reg_init(PR *pr,float *ch, float Kp, float OutMax, float OutMin){

    memcpy(pr->ch,ch,sizeof(pr->ch));
    pr->Err = 0;                 // Erro
    pr->Err_ant = 0;             // Erro anterior 1 amostra
    pr->Err_ant2 = 0;            // Erro anterior 2 amostras
    pr->Out = 0;                 // Saída ressonante
    pr->Out_ant = 0;             // Saída anterior 1 amostra
    pr->Out_ant2 = 0;           // Saída anterior 2 amostras
    pr->Kp = Kp;
    pr->OutMax=OutMax;
    pr->OutMin=OutMin;
}

void pr_reg_reset(PR *pr){
    pr->Err = 0;
    pr->Err_ant = 0;
    pr->Err_ant2 = 0;
    pr->Out = 0;
    pr->Out_ant = 0;
    pr->Out_ant2 = 0;
}

void calc_PR(PR *pr, float Err){
    pr->Out = pr->ch[0]*(Err-pr->Err_ant2) - pr->ch[2]*pr->Out_ant- pr->ch[3]*pr->Out_ant2;
    pr->Out_ant2=pr->Out_ant;
    pr->Out_ant=pr->Out;
    pr->Err_ant2 =pr->Err_ant;
    pr->Err_ant = Err;
}
