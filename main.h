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



/****************************************************************************************
 *************************      LOCAL FUNCTIONS DECLARATION     *************************
 ****************************************************************************************/
//Initialization
static void System_Init(void);

// Interruptions
__interrupt void isr_cpu_timer0(void);



#endif /* MAIN_H_ */
