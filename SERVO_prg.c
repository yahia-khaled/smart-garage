/*
 * SERVO_prg.c
 *
 *  Created on: Sep 30, 2022
 *      Author: hp
 */

#include "std_types.h"
#include "Timer_Interface.h"
#include <util/delay.h>
//#include "SERVO1_int.h"


void SERVO_vInit(void)
{
	//TIMER1_vInit();
	M_Timer_Void_PWMInit(TIMER1_CHANNEL);
}

//void SERVO_vRotate180_Back(void)
//{
//	u16 L_u16TempVariable=650;
//	TIMER1_vSetICR1(19999);
//	TIMER1_vTurnOn();
//	for(;L_u16TempVariable<=2500;L_u16TempVariable++)
//		{
//		TIMER1_vSetOcrA1Val(L_u16TempVariable);
//		_delay_ms(10);
//		}
//	TIMER1_vSetOcrA1Val(650);
//}
void SERVO_vAngle(u8 A_u8Angle)
{
	//u16 L_u16OCRA=650+10*A_u8Angle;
	/*if (L_u8OCRA>2500||L_u8OCRA<650)
		L_u8OCRA=650;*/

	//u16 L_u16TempVariable=650;
		//TIMER1_vSetICR1(19999);
		//TIMER1_vTurnOn();

		M_Timer_Void_PWMSetDutyCycle(TIMER1_CHANNEL, A_u8Angle);
		M_Timer_Void_PWMStart(TIMER1_CHANNEL);


}
