/*
 * main.c
 *
 *  Created on: Mar 8, 2023
 *      Author: Marim Khaled
 */




#include"std_types.h"
#include"bit_math.h"
#include"ADC_interface.h"
#include"lcd_interface.h"
#include"K_INTERFACE.h"
#include"DIO_interface.h"
#include "HC_SR04_Interface.h"
#include "SERVO_int.h"
//#include <util/delay.h>
#include<avr/delay.h>
void APP_INIT(void);
void func(){u16 x;
u16 y=0;
u16 z;

	x=ADC_Data(0b00000111);
	y=(x*(u32)5000)/1023;
	z=(5000*10-y*10)/y;

if(z<100)
{

z=100-z;
if((z>90 && z<100)|| z==90){
	DIO_VidSetPinValue(3,6,0);
	DIO_VidSetPinValue(3,7,0);

			for(int i=2;i<4;i++)
			DIO_VidSetPinValue(3,i,0);}

if(z>75 && z<90){

			DIO_VidSetPinValue(3,6,1);
				DIO_VidSetPinValue(3,7,0);
			for(int i=2;i<4;i++)
			DIO_VidSetPinValue(3,i,0);}
if((z>50 && z<75) || z==75)
{
	for(int i=6;i<8;i++)
				DIO_VidSetPinValue(3,i,1);
	for(int i=2;i<4;i++)
				DIO_VidSetPinValue(3,i ,0);
}
if((z>25 && z<50) || z==50)
		{
			for(int i=6;i<8;i++)
						DIO_VidSetPinValue(3,i,1);
			DIO_VidSetPinValue(3,2,1);
						DIO_VidSetPinValue(3,3 ,0);
		}
if((z>0 && z<25) || (z==25))
		{DIO_VidSetPinValue(3,6,1);
		DIO_VidSetPinValue(3,7,1);
			for(int i=2;i<4;i++)
						DIO_VidSetPinValue(3,i,1);

		}
}
else if(z>100 || z==100){
z=0;
for(int i=0;i<4;i++)
						DIO_VidSetPinValue(3,i,1);
}

x=0;}
func1(){
	GoToPos(1,0);
	u16 x;
u16 y=0;
x=ADC_Data(0b00000110);

													y=(x*(u32)5000)/1023;
		y=y/10;
		if(y>95){
									DIO_VidSetPinValue(0,5,1);
															  // SERVO_vAngle(100);

																 }
		else
							{DIO_VidSetPinValue(0,5,0);
							//if(y<23)
								//SERVO_vAngle(0);
							}
							lcd_number(y);

}
void main (void){
	DIO_VidSetPinDirection(0,7,0);
	DIO_VidSetPinDirection(3,6,1);
	DIO_VidSetPinDirection(3,7,1);
	DIO_VidSetPinDirection(3,2,1);
	DIO_VidSetPinDirection(3,3,1);
	DIO_VidSetPinDirection(0,6,0);
	DIO_VidSetPinDirection(0,5,1);




	ADC_VidInit();
	lcd_initialisation();
	KBD();
		u8 pass[50][4]={ {0,1,1,1},{1,2,3,4},{3,4,5,6}};
		u8 empty[3]={0,0,0};
		u8 c=2;
		u8 e=3;//counter for entering car
		u8 urpass[4];
		GoToPos(0,0);
		u8 compare=0;
		u8 j;
		u8 i;
		u8 k;
		float APP_UltrasonicRead_2;
		float APP_UltrasonicRead;
		u8 s=0;

		GoToPos(0,0);
		APP_INIT();
while(1)
{
	_delay_ms(300);
	APP_UltrasonicRead = H_HC_SR04_GetDistance(1);
	_delay_ms(50);
	 APP_UltrasonicRead_2 = H_HC_SR04_GetDistance(2);


	if(APP_UltrasonicRead<APP_UltrasonicRead_2 ){
			       lcd_sendcommand(0b00000001);
			       lcd_number(APP_UltrasonicRead);
	}
	else if(APP_UltrasonicRead_2<APP_UltrasonicRead){
				       lcd_sendcommand(0b00000001);
				       lcd_number(APP_UltrasonicRead_2);
		}
	func();
func1();
if((APP_UltrasonicRead<=5)||(APP_UltrasonicRead_2<=5))
{
lcd_sendcommand(0b00000001);
GoToPos(0,0);
lcd_string("enter ur id:");

		for( i=0;i<4;i++)
		{
			urpass[i]=GETPRESSED_VALUE();
			while(urpass[i]==50){
				urpass[i]=GETPRESSED_VALUE();
			func();
			func1();}
			GoToPos(0,i+12);
			lcd_number(urpass[i]);
		}
		_delay_ms(500);
		lcd_sendcommand(0b00000001);
		for(j=0;j<(c+1);j++)
		{
					for(k=0;k<4;k++){
						if(urpass[k]==pass[j][k])
							compare++;
					}
					if(compare==4){
						empty[j]+=1;
																			if(empty[j]==1)
																				e--;
																			if(empty[j]==2)
																			{e++;
																			empty[j]=0;}
						lcd_string("welcome");
						GoToPos(1,0);
						lcd_number(e);
						lcd_string("empty");
						for(u8 i=0;i<=100;i+=5)
						 {
						   SERVO_vAngle(i);
						   func();
							_delay_ms(250);
										   }

						if(APP_UltrasonicRead<=5)
						{

								APP_UltrasonicRead_2 = H_HC_SR04_GetDistance(2);
								while(APP_UltrasonicRead_2>4){APP_UltrasonicRead_2 = H_HC_SR04_GetDistance(2);
								func();}
								for(u8 i=100;i>0;i-=5)
																	   {
																		   SERVO_vAngle(i);
																		   func();
																			_delay_ms(250);
																						   }
																		  SERVO_vAngle(0);
						}
						else if(APP_UltrasonicRead_2<=5){
							APP_UltrasonicRead = H_HC_SR04_GetDistance(1);
							func();
						    while(APP_UltrasonicRead>4)
						    {
						    	APP_UltrasonicRead = H_HC_SR04_GetDistance(1);
						    	func();
						     }
						    for(u8 i=100;i>0;i-=5)
						    									   {
						    										   SERVO_vAngle(i);
						    										   func();
						    											_delay_ms(250);
						    														   }
						    										  SERVO_vAngle(0);
						}

						_delay_ms(1000);
						lcd_sendcommand(0b00000001);
						compare=0;
					break;}
					else
						compare=0;

				}
				if(j==(c+1)){
					lcd_sendcommand(0b00000001);
					lcd_string("not valid");
					_delay_ms(2000);
					lcd_sendcommand(0b00000001);}

}

}


}
void APP_INIT()
{
ADC_VidInit();
lcd_initialisation();
M_GIE_Void_GlobalInterruptEnable();
SERVO_vInit();
H_HC_SR04_Init(1);
H_HC_SR04_Init(2);

}
