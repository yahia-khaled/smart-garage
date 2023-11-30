/*
 * HC_SR04_prog.c
 *
 *  Created on: Feb 6, 2023
 *      Author: abdal
 */


#include <avr/io.h>
#include<avr/delay.h>
#include <DIO_Interface2.h>
//#include <util/delay.h>
#include "Timer_Interface.h"
#include "HC_SR04_interface.h"
#include "std_types.h"
#include "bit_math.h"
#include "GIE_Interface.h"
//#include "lcd_interface.h"


void H_HC_SR04_Init(int choice)
{

	M_GIE_Void_GlobalInterruptEnable();
	switch (choice)
	{

	case 1: 	{M_DIO_Void_SetPinDirection(TRIGGER_PIN1, OUTPUT);
	             M_DIO_Void_SetPinDirection(ECHO_PIN1, INPUT);
	                       break;                                  }

	case 2: 	{M_DIO_Void_SetPinDirection(TRIGGER_PIN2, OUTPUT);
	             M_DIO_Void_SetPinDirection(ECHO_PIN2, INPUT);
	                       break;
	}

     	default:    break;
	}


	M_Timer_Void_TimerInit();
}

//Function to generate trigger pulse on Trigger pin
void H_HC_SR04_SendTriggerPulse(int choice) {
	 //Set trigger pin high
	switch(choice)
	{
	case 1: {
		 M_DIO_Void_SetPinValue(TRIGGER_PIN1, HIGH);
		 //Wait for 10us
		 _delay_us(10);
		 //Set trigger pin low
		 M_DIO_Void_SetPinValue(TRIGGER_PIN1, LOW);
		 break;
	}

	case 2: {
		 M_DIO_Void_SetPinValue(TRIGGER_PIN2, HIGH);
		 //Wait for 10us
		 _delay_ms(0.1);
		 //Set trigger pin low
		 M_DIO_Void_SetPinValue(TRIGGER_PIN2, LOW);
		 break;
	}

	default:    break;

	}


}


//Function to calculate and return the distance in cm
float H_HC_SR04_GetDistance(int choice) {

	switch(choice)
	{

	case 1: {

		//Variable to store the duration of echo pulse
			float duration;

			//Generate trigger pulse
			H_HC_SR04_SendTriggerPulse(1);

			//Wait for the rising edge of echo pulse
			//while((PIND & (1 << ECHO_PIN)) == 0);
			u32 x = 0;
			while(M_DIO_U8_GetPinValue(ECHO_PIN1) == 0)
			{
				if(++x >= 1000)
					break;
			}
			x = 0;
			//Record the start time of echo pulse
			M_Timer_Void_TimerStart(TIMER0_CHANNEL);
			unsigned long startTime = M_Timer_Void_GetTime();

			//Wait for the falling edge of echo pulse
			while(M_DIO_U8_GetPinValue(ECHO_PIN1) > 0)
			{
				if(++x >= 1000)
					break;
			}

			//Record the end time of echo pulse
			unsigned long endTime = M_Timer_Void_GetTime();
			M_Timer_Void_TimerStop(TIMER0_CHANNEL);

			 //Calculate duration of echo pulse
			duration = endTime - startTime;

			//Calculate distance in cm   using speed = 343m/s and divide by 2 as sound travels back and forth
			return ((duration*34300)/(2*F_OSC*1000000));
			//return startTime;

	}


	case 2: {


		//Variable to store the duration of echo pulse
			float duration;

			//Generate trigger pulse
			H_HC_SR04_SendTriggerPulse(2);

			//Wait for the rising edge of echo pulse
			//while((PIND & (1 << ECHO_PIN)) == 0);
			u32 x = 0;
			while(M_DIO_U8_GetPinValue(ECHO_PIN2) == 0)
			{
				if(++x >= 1000)
					break;
			}
			x = 0;
			//Record the start time of echo pulse
			M_Timer_Void_TimerStart(TIMER0_CHANNEL);
			unsigned long startTime = M_Timer_Void_GetTime();

			//Wait for the falling edge of echo pulse
			while(M_DIO_U8_GetPinValue(ECHO_PIN2) > 0)
			{
				if(++x >= 1000)
					break;
			}

			//Record the end time of echo pulse
			unsigned long endTime = M_Timer_Void_GetTime();
			M_Timer_Void_TimerStop(TIMER0_CHANNEL);

			 //Calculate duration of echo pulse
			duration = endTime - startTime;

			//Calculate distance in cm   using speed = 343m/s and divide by 2 as sound travels back and forth
			return ((duration*34300)/(2*F_OSC*1000000));
			//return startTime;
	}

	default:    break;
	}




}


