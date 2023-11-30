#include"std_types.h"
#include"bit_math.h"
#include"ADC_private.h"
#include"ADC_cfg.h"
#include"DIO_interface.h"
#include"lcd_interface.h"

typedef enum
{ channel0,
  channel1,
  channel2,
  channel3,
  channel4,
  channel5,
  channel6,
  channel7
}channel_type;

void ADC_VidInit(void)
{    /* setting volt ref --> VCC with external cap=5v */
    #if VREF==1
	    CLR_BIT(ADMUX,7);
	    SET_BIT(ADMUX,6);
    #elif VREF==0
	     CLR_BIT(ADMUX,7);
	     CLR_BIT(ADMUX,6);
    #elif VREF==2
	     SET_BIT(ADMUX,7);
	     SET_BIT(ADMUX,6);
    #else
         #error "wrong input!"
    #endif

	/*disable auto trigger */
	    CLR_BIT(ADCSRA,5);

	/* setting the adjustment --> right  */
		CLR_BIT(ADMUX,5);

	/*single ended on portA0*/
	/*
	  CLR_BIT(ADMUX,0);
	  CLR_BIT(ADMUX,1);
	  CLR_BIT(ADMUX,2);
	  CLR_BIT(ADMUX,3);
	  CLR_BIT(ADMUX,4); */

	  /*FLAF IS ALREADY 0 AT FIRST*/


	/*set the prescaler to be --> divide by 64 */
	 SET_BIT(ADCSRA,2);
	 SET_BIT(ADCSRA,1);
	 CLR_BIT(ADCSRA,0);

	/*ENABLE ADC*/
	 SET_BIT(ADCSRA,7);
	 /*disable interrupt*/
	 CLR_BIT(ADCSRA,3);



}

/*void ADC_VidStartConversion(channel_type x)
{
	  CLR_BIT(ADMUX,0);
	  CLR_BIT(ADMUX,1);
	  CLR_BIT(ADMUX,2);
	  CLR_BIT(ADMUX,3);
	  CLR_BIT(ADMUX,4);

	  if (x==channel1)
      	  SET_BIT(ADMUX,0);
      else if (x==channel2)
      	  SET_BIT(ADMUX,1);
	  else if (x==channel3)
	  {
		  SET_BIT(ADMUX,0);
		  SET_BIT(ADMUX,1);
	  }
	  else if (x==channel4)
      	  SET_BIT(ADMUX,2);
	  else if (x==channel5)
      {
	  SET_BIT(ADMUX,0);
	  SET_BIT(ADMUX,2);
	  }
	  else if (x==channel6)
	  {
		  SET_BIT(ADMUX,1);
		  SET_BIT(ADMUX,2);
	  }
	  else if (x==channel7)
	  {
		  SET_BIT(ADMUX,0);
		  SET_BIT(ADMUX,1);
		  SET_BIT(ADMUX,2);
	  }
	  else
	  { }

	/SET_BIT(ADCSRA,6);
}*/

/*u16 ADC_ReadData()
{
	while (GET_BIT(ADCSRA,4)==0);
	return ADCLH;

}*/
u16 ADC_Data(u8 x)
{


	ADMUX&=0b11100000;
	ADMUX|=(x&0b00011111);
	SET_BIT(ADCSRA,6);
	while (GET_BIT(ADCSRA,4)==0)
	{

	}

	 SET_BIT(ADCSRA,4);
	 return ADCLH;


}

