/**********************/
/**********************/
/*******Author: Nada Tharwat*********/
/*******File:DIO_prg.c*********/
/******Date: 2nd sep 2022**********/
/******* Version: V1.0**********/
/*********Desc:************/
/**********************/
/**********************/

#include"std_types.h"
#include"bit_math.h"
#include "DIO_PRIVATE.h"



void DIO_VidSetPinDirection (u8 Copy_U8Port, u8 Copy_U8Pin, u8 Copy_U8Dir)
{
	switch (Copy_U8Port)
	{
		case PORTA :
		{
			if (Copy_U8Dir == INPUT)
				{CLR_BIT(DDRA_REG,Copy_U8Pin);}
			else if (Copy_U8Dir == OUTPUT)
		      {SET_BIT(DDRA_REG,Copy_U8Pin);}
			else
			{/*do nothing*/}
			break;
		}
		case PORTB :
		{
			if (Copy_U8Dir == INPUT)
				{CLR_BIT(DDRB_REG,Copy_U8Pin);}
			else if (Copy_U8Dir == OUTPUT)
				{SET_BIT(DDRB_REG,Copy_U8Pin);}
			else
			{/*do nothing*/}
			break;
		}
		case PORTC :
		{
			if (Copy_U8Dir == INPUT)
				{CLR_BIT(DDRC_REG,Copy_U8Pin);}
			else if (Copy_U8Dir == OUTPUT)
				{SET_BIT(DDRC_REG,Copy_U8Pin);}
			else
			{/*do nothing*/}
			break;
		}
		case PORTD :
		{
			if (Copy_U8Dir == INPUT)
				{ CLR_BIT(DDRD_REG,Copy_U8Pin); }
			else if (Copy_U8Dir == OUTPUT)
				{ SET_BIT(DDRD_REG,Copy_U8Pin); }
			else
			{/*do nothing*/}
			break;
		}

	}
	


}
void DIO_VidSetPortDirection (u8 Copy_U8Port, u8 Copy_U8Dir)
{
	switch(Copy_U8Port)
	{
		case PORTA :
		{
		   DDRA_REG=Copy_U8Dir ;

			break;
		}
		case PORTB :
		{
		   DDRB_REG=Copy_U8Dir ;
			break;
		}
		case PORTC :
		{
		   DDRC_REG=Copy_U8Dir ;

			break;
		}
		case PORTD :
		{
		    DDRD_REG=Copy_U8Dir ;

			break;
		}
		
		
	}


}
void DIO_VidSetPinValue (u8 Copy_U8Port, u8 Copy_U8Pin, u8 Copy_U8Val)
{

	switch (Copy_U8Port)
		{
			case PORTA :
			{
				if (Copy_U8Val == LOW)
					{CLR_BIT(PORTA_REG,Copy_U8Pin);}
				else if (Copy_U8Val == HIGH)
			      {SET_BIT(PORTA_REG,Copy_U8Pin);}
				else
							{/*do nothing*/}
				break;
			}
			case PORTB :
			{
				if (Copy_U8Val == LOW)
					{CLR_BIT(PORTB_REG,Copy_U8Pin);}
				else if (Copy_U8Val == HIGH)
					{SET_BIT(PORTB_REG,Copy_U8Pin);}
				else
				{/*do nothing*/}
				break;
			}
			case PORTC :
			{
				if (Copy_U8Val == LOW)
					{CLR_BIT(PORTC_REG,Copy_U8Pin);}
				else if (Copy_U8Val == HIGH)
					{SET_BIT(PORTC_REG,Copy_U8Pin);}
				else
				{/*do nothing*/}
				break;
			}
			case PORTD:
			{
				if (Copy_U8Val== LOW)
					{CLR_BIT(PORTD_REG,Copy_U8Pin);}
				else if (Copy_U8Val == HIGH)
					{SET_BIT(PORTD_REG,Copy_U8Pin);}
				else
				{/*do nothing*/}
				break;
			}

		}
		
		



}
void DIO_VidSetPortValue (u8 Copy_U8Port, u8 Copy_U8Val)
{
	
	switch(Copy_U8Port)
	{
		case PORTA :
		{
		   PORTA_REG=Copy_U8Val;

			break;
		}
		case PORTB :
		{
		  PORTB_REG=Copy_U8Val;
			break;
		}
		case PORTC :
		{
		   PORTC_REG=Copy_U8Val;

			break;
		}
		case PORTD :
		{
		   PORTD_REG=Copy_U8Val;

			break;
		}
		
		
	}
	
}
void DIO_VidTogglePinValue (u8 Copy_U8Port, u8 Copy_U8Pin)
{
	switch(Copy_U8Port)
	{
		case PORTA :
		{
		 TOGGEL_BIT(PORTA_REG,Copy_U8Pin);

			break;
		}
		case PORTB :
		{
		 TOGGEL_BIT(PORTB_REG,Copy_U8Pin);
			break;
		}
		case PORTC :
		{
		   TOGGEL_BIT(PORTC_REG,Copy_U8Pin);

			break;
		}
		case PORTD :
		{
           TOGGEL_BIT(PORTD_REG,Copy_U8Pin);

			break;
		}
		
	}
}
u8 DIO_U8GetPinValue (u8 Copy_U8Port, u8 Copy_U8Pin )
{
	u8 x;
	switch(Copy_U8Port)
	{
		case PORTA :
		{
		   x=GET_BIT(PINA_REG, Copy_U8Pin);

			break;
		}
		case PORTB :
		{
		   x=GET_BIT(PINB_REG, Copy_U8Pin);
			break;
		}
		case PORTC :
		{
		    x=GET_BIT(PINC_REG, Copy_U8Pin);

			break;
		}
		case PORTD :
		{
            x=GET_BIT(PIND_REG, Copy_U8Pin);

			break;
		}
		
	}
	return x;

}

