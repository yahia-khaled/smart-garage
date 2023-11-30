/*
 * Timer_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#include "Timer_Config.h"
#include "Timer_Interface.h"
#include "Timer_Private.h"
#include"DIO_interface.h"
void(*Timer_CallBack)(void);

u32 Timer_U32_CompareMatchNumber	= 0;
u32 Timer_U32_OverflowNumber	    = 0;
u8 	Timer_U8_RemainderTicks		    = 0;
u8  Duty_Cycle=0;
void Set_Duty_Motor(u8 Copy_DutyCycle){
	Duty_Cycle=Copy_DutyCycle;
}


u32 M_Timer_Void_GetTime(void)
{
	return Timer_U32_OverflowNumber*256;
}
void M_Timer_Void_Timer2Init(void)
{
#if   TIMER2_MODE   ==   NORMAL_MODE
	CLR_BIT(TCCR2_REG,WGM21_BIT);
	CLR_BIT(TCCR2_REG,WGM20_BIT);
	/* TO ENABLE TIMER0 OV INTERRUPT */
	SET_BIT(TIMSK_REG,TOIE2_BIT);
#endif
}
void M_Timer_Void_TimerInit(void)
{
#if   TIMER0_MODE   ==   NORMAL_MODE
	CLR_BIT(TCCR0_REG,WGM00_BIT);
	CLR_BIT(TCCR0_REG,WGM01_BIT);
	/* TO ENABLE TIMER0 OV INTERRUPT */
	SET_BIT(TIMSK_REG,TOIE0_BIT);
#elif TIMER0_MODE   ==   CTC_MODE
	CLR_BIT(TCCR0_REG,WGM00_BIT);
	SET_BIT(TCCR0_REG,WGM01_BIT);
	/* TO ENABLE TIMER0 CM INTERRUPT */
	SET_BIT(TIMSK_REG,OCIE0_BIT);
#endif
}
void M_Timer_Void_TimerSetTime(u32 Copy_U32_DesiredTime)
{
	u32 Local_U32_TickTime   = TIMER0_PRESCALER_DF / F_OSC; /* RESULT WILL BE IN MICRO SECONDS */
	u32 Local_U32_TotalTicks = (Copy_U32_DesiredTime * 1000) / Local_U32_TickTime;

#if   TIMER0_MODE   ==   NORMAL_MODE
	Timer_U32_OverflowNumber	= Local_U32_TotalTicks / 256;
		Timer_U8_RemainderTicks = Timer_U32_OverflowNumber % 256;
		if(Timer_U8_RemainderTicks){
			TCNT0_REG = 256 - Timer_U8_RemainderTicks;
			Timer_U32_OverflowNumber++;
		}
#elif TIMER0_MODE   ==   CTC_MODE
	u8 Local_U8_DivisionValue = 255;
	while(Local_U32_TotalTicks % Local_U8_DivisionValue)
	{
		Local_U8_DivisionValue--;
	}
	OCR0_REG = Local_U8_DivisionValue - 1;
	Timer_U32_NumOfCM = Local_U32_TotalTicks / Local_U8_DivisionValue;
#endif
}
void M_Timer_Void_TimerStart(u8 Copy_U8_TimerChannel)
{
	switch(Copy_U8_TimerChannel)
	{
	case TIMER0_CHANNEL:
#if   TIMER0_PRESCALER_DF   ==   1024
	SET_BIT(TCCR0_REG,CS00_BIT);
	CLR_BIT(TCCR0_REG,CS01_BIT);
	SET_BIT(TCCR0_REG,CS02_BIT);
#elif TIMER0_PRESCALER_DF   ==   256
	CLR_BIT(TCCR0_REG,CS00_BIT);
	CLR_BIT(TCCR0_REG,CS01_BIT);
	SET_BIT(TCCR0_REG,CS02_BIT);
#elif TIMER0_PRESCALER_DF == 1
	SET_BIT(TCCR0_REG, CS00_BIT);
	CLR_BIT(TCCR0_REG, CS01_BIT);
	CLR_BIT(TCCR0_REG, CS02_BIT);
#endif
		break;
	case TIMER1_CHANNEL:
#if   TIMER1_PRESCALER_DF   ==   1024
		SET_BIT(TCCR1B_REG,CS10_BIT);
		CLR_BIT(TCCR1B_REG,CS11_BIT);
		SET_BIT(TCCR1B_REG,CS12_BIT);
#elif TIMER1_PRESCALER_DF   ==   256
		CLR_BIT(TCCR1B_REG,CS10_BIT);
		CLR_BIT(TCCR1B_REG,CS11_BIT);
		SET_BIT(TCCR1B_REG,CS12_BIT);
#elif TIMER1_PRESCALER_DF   ==   8
		CLR_BIT(TCCR1B_REG,CS10_BIT);
		SET_BIT(TCCR1B_REG,CS11_BIT);
		CLR_BIT(TCCR1B_REG,CS12_BIT);
#endif
		break;
	case TIMER2_CHANNEL:
#if   TIMER2_PRESCALER_DF   ==   1024
		SET_BIT(TCCR2_REG,CS20_BIT);
		SET_BIT(TCCR2_REG,CS21_BIT);
		SET_BIT(TCCR2_REG,CS22_BIT);
#elif TIMER2_PRESCALER_DF   ==   256
		CLR_BIT(TCCR2_REG,CS20_BIT);
		SET_BIT(TCCR2_REG,CS21_BIT);
		SET_BIT(TCCR2_REG,CS22_BIT);
#elif TIMER2_PRESCALER_DF   ==   8
		CLR_BIT(TCCR2_REG,CS20_BIT);
		SET_BIT(TCCR2_REG,CS21_BIT);
		CLR_BIT(TCCR2_REG,CS22_BIT);
#endif
		break;
	default: break;
	}
}
void M_Timer_Void_TimerStop(u8 Copy_U8_TimerChannel)
{
	switch(Copy_U8_TimerChannel)
	{
	case TIMER0_CHANNEL:
		CLR_BIT(TCCR0_REG,CS00_BIT);
		CLR_BIT(TCCR0_REG,CS01_BIT);
		CLR_BIT(TCCR0_REG,CS02_BIT);

		break;
	case TIMER1_CHANNEL:
		CLR_BIT(TCCR1B_REG,CS10_BIT);
		CLR_BIT(TCCR1B_REG,CS11_BIT);
		CLR_BIT(TCCR1B_REG,CS12_BIT);
		break;
	case TIMER2_CHANNEL:
		CLR_BIT(TCCR2_REG,CS20_BIT);
		CLR_BIT(TCCR2_REG,CS21_BIT);
		CLR_BIT(TCCR2_REG,CS22_BIT);
		break;
	default: break;
	}
}
void M_Timer_Void_PWMInit(u8 Copy_U8_TimerChannel)
{
	switch(Copy_U8_TimerChannel)
	{
	case TIMER0_CHANNEL:
		//old part
		//M_DIO_Void_SetPinDirection(PB3_PIN,OUTPUT);
		//New part
		DIO_VidSetPinDirection(1,3,1);

	#if TIMER0_MODE   ==   FAST_PWM_MODE
		SET_BIT(TCCR0_REG,WGM00_BIT);
		SET_BIT(TCCR0_REG,WGM01_BIT);
	#elif TIMER0_MODE   ==   PHASE_CORRECT_PWM_MODE
		SET_BIT(TCCR0_REG,WGM00_BIT);
		CLR_BIT(TCCR0_REG,WGM01_BIT);
	#endif
	#if   TIMER0_FAST_PWM_MODE   ==   NON_INVERTED
		CLR_BIT(TCCR0_REG,COM00_BIT);
		SET_BIT(TCCR0_REG,COM01_BIT);
	#elif TIMER0_FAST_PWM_MODE   ==   INVERTED
		SET_BIT(TCCR0_REG,COM00_BIT);
		SET_BIT(TCCR0_REG,COM01_BIT);
	#endif
		break;
	case TIMER1_CHANNEL:
		//old part
		//M_DIO_Void_SetPinDirection(PD4_PIN,OUTPUT);
		//M_DIO_Void_SetPinDirection(PD5_PIN,OUTPUT);
		//new part
		DIO_VidSetPinDirection(3,4,1);
		DIO_VidSetPinDirection(3,5,1);


		/* TO SELECT MODE NO. 14 IN TABLE 47 */
		CLR_BIT(TCCR1A_REG,WGM10_BIT);
		SET_BIT(TCCR1A_REG,WGM11_BIT);
		SET_BIT(TCCR1B_REG,WGM12_BIT);
		SET_BIT(TCCR1B_REG,WGM13_BIT);
		/* TO SELECT NON INVERTED MODE */
		CLR_BIT(TCCR1A_REG,COM1A0_BIT);
		SET_BIT(TCCR1A_REG,COM1A1_BIT);
		CLR_BIT(TCCR1A_REG,COM1B0_BIT);
		SET_BIT(TCCR1A_REG,COM1B1_BIT);
		ICR1_REG =(2*((F_OSC * 1000000) / TIMER1_PRESCALER_DF) / F_PWM1);
		ICR1_REG = 19999;
		break;
	case TIMER2_CHANNEL:
#if TIMER2_MODE   ==   FAST_PWM_MODE
		M_DIO_Void_SetPinDirection(PD7_PIN,OUTPUT);
		SET_BIT(TCCR2_REG,WGM21_BIT);
		SET_BIT(TCCR2_REG,WGM20_BIT);
	#elif TIMER2_MODE   ==   PHASE_CORRECT_PWM_MODE
		SET_BIT(TCCR2_REG,WGM00_BIT);
		CLR_BIT(TCCR2_REG,WGM01_BIT);
	#endif
	#if   TIMER2_FAST_PWM_MODE   ==   NON_INVERTED
		CLR_BIT(TCCR2_REG,COM20_BIT);
		SET_BIT(TCCR2_REG,COM21_BIT);
	#elif TIMER2_FAST_PWM_MODE   ==   INVERTED
		SET_BIT(TCCR2_REG,COM20_BIT);
		SET_BIT(TCCR2_REG,COM21_BIT);
	#endif
		break;
	default: break;
	}
}

void M_Timer_Void_PWMSetDutyCycle(u8 Copy_U8_TimerChannel,f32 Copy_F32_DutyCycle)
{
	switch(Copy_U8_TimerChannel)
	{
	case TIMER0_CHANNEL:
#if TIMER0_MODE   ==   FAST_PWM_MODE
	OCR0_REG = ((Copy_F32_DutyCycle * 256 ) / 100) - 1;
#elif TIMER0_MODE   ==   PHASE_CORRECT_PWM_MODE
	OCR0_REG = ((Copy_F32_DutyCycle * 255 ) / 100);
	//OCR0_REG = 200;
#endif

		break;
	case TIMER1_CHANNEL:
		//OCR1A_REG = ((Copy_F32_DutyCycle * ICR1_REG ) / 100) - 1;
		//OCR1A_REG =2000 + 3000 * Copy_F32_DutyCycle;
		OCR1A_REG = 650+10*Copy_F32_DutyCycle;
				//((Copy_F32_DutyCycle * ICR1_REG ) / 100) - 1;
		//OCR1A_REG = 2000 + 3000 * Copy_F32_DutyCycle;
		break;
	case TIMER2_CHANNEL:
#if TIMER2_MODE   ==   FAST_PWM_MODE
		//OCR2_REG = ((Copy_F32_DutyCycle * 256 ) / 100) - 1;
		OCR2_REG = 15+15*Copy_F32_DutyCycle;
		//OCR2_REG = 38*Copy_F32_DutyCycle;



#endif
		OCR2_REG = ((Copy_F32_DutyCycle * 255 ) / 100);
		break;
	default: break;

	}
}
void M_Timer1_Void_PWM_OCR(u8 Copy_U8_OCRChannel,f32 Copy_F32_OCRValue){
	switch(Copy_U8_OCRChannel){
	case OCR_CHANNEL_A:
		OCR1A_REG = ((Copy_F32_OCRValue * ICR1_REG ) / 100) - 1;
		break;
	case OCR_CHANNEL_B:
		OCR1B_REG =((Copy_F32_OCRValue * ICR1_REG ) / 100) - 1;
		break;
default:break;
}



}
void M_Timer_Void_PWMStart(u8 Copy_U8_TimerChannel)
{
	M_Timer_Void_TimerStart(Copy_U8_TimerChannel);
}
void M_Timer_Void_PWMStop(u8 Copy_U8_TimerChannel)
{
	M_Timer_Void_TimerStop(Copy_U8_TimerChannel);
}

void M_Timer_Void_SetCallBack(void(*Copy_Ptr)(void))
{
	Timer_CallBack = Copy_Ptr;
}
#if TIMER0_MODE == NORMAL_MODE

ISR(TIMER0_OVF_vect)
{
//	static u32 Local_U32_Counter = 0;

//	if(++Local_U32_Counter == Timer_U32_OverflowNumber)
//	{
//		Timer_CallBack();
//		Local_U32_Counter = 0;
//		TCNT0_REG = 256 - Timer_U8_RemainderTicks;
//	}
	Timer_U32_OverflowNumber++;
	if(Timer_U32_OverflowNumber > 2000)
		Timer_U32_OverflowNumber = 0;
}
#elif   TIMER0_MODE   ==   CTC_MODE

ISR(TIMER0_COMP_vect)
{
	static u32 Local_U32_Counter = 0;
	Local_U32_Counter++;
	if(Local_U32_Counter == Timer_U32_NumOfCM)
	{
		Timer_CallBack();
		Local_U32_Counter = 0;
	}
}
#endif
//ISR(TIMER2_OVF_vect)
//{
//	static u32 Local_U32_Counter = 0;
//		Local_U32_Counter++;
//		if(Local_U32_Counter==Duty_Cycle){
//			M_DIO_Void_SetPinValue(PD4_PIN,LOW);
//			M_DIO_Void_SetPinValue(PD5_PIN,LOW);
//
//		}
//		if(Local_U32_Counter==100){
//				M_DIO_Void_SetPinValue(PD4_PIN,HIGH);
//				M_DIO_Void_SetPinValue(PD5_PIN,HIGH);
//
//				Local_U32_Counter=0;
//
//			}
//}
