/*
 * Timer_Interface.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef MCAL_TIMER_TIMER_INTERFACE_H_
#define MCAL_TIMER_TIMER_INTERFACE_H_

#include "std_types.h"
#include "bit_math.h"
#include "Timer_Config.h"
#include <avr/interrupt.h>
#include "DIO_Interface2.h"

#define  TIMER0_CHANNEL         0
#define  TIMER1_CHANNEL         1
#define  TIMER2_CHANNEL         2


void M_Timer_Void_TimerInit(void);
u32 M_Timer_Void_GetTime(void);
void M_Timer_Void_TimerSetTime(u32);
void M_Timer_Void_TimerStart(u8);
void M_Timer_Void_TimerStop(u8);

void M_Timer_Void_PWMInit(u8);
void M_Timer_Void_PWMSetDutyCycle(u8,f32);
void M_Timer_Void_PWMStart(u8);
void M_Timer_Void_PWMStop(u8);
void M_Timer1_Void_PWM_OCR(u8 ,f32);
void M_Timer_Void_SetCallBack(void(*)(void));

#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
