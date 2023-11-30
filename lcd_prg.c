#include"std_types.h"
#include"bit_math.h"
#include"lcd_private.h"
#include"lcd_cfg.h"
#include"util/delay.h"
#include "DIO_Interface2.h"

void lcd_writedata(u8 data){
	DIO_VidSetPinValue(CONTROL_PORT,EN,LOW);
    DIO_VidSetPinValue(CONTROL_PORT,RS,HIGH);
	DIO_VidSetPinValue(CONTROL_PORT,RW,LOW);
	DIO_VidSetPortValue (DATA_PORT,data);
	DIO_VidSetPinValue(CONTROL_PORT,EN,HIGH);
	_delay_ms(1);
	DIO_VidSetPinValue(CONTROL_PORT,EN,LOW);
	_delay_ms(2);
}

void lcd_sendcommand(u8 inst){
	DIO_VidSetPinValue(CONTROL_PORT,EN,LOW);
	DIO_VidSetPinValue(CONTROL_PORT,RS,LOW);
	DIO_VidSetPinValue(CONTROL_PORT,RW,LOW);
    DIO_VidSetPortValue(DATA_PORT,inst);
	DIO_VidSetPinValue(CONTROL_PORT,EN,HIGH);
	_delay_ms(1);
	DIO_VidSetPinValue(CONTROL_PORT,EN,LOW);
	_delay_ms(2);
}

void lcd_initialisation(){ 
  DIO_VidSetPortDirection(DATA_PORT,0xFF);
  DIO_VidSetPinDirection(CONTROL_PORT,RS,HIGH);
  DIO_VidSetPinDirection(CONTROL_PORT,RW,HIGH);
  DIO_VidSetPinDirection(CONTROL_PORT,EN,HIGH);
	_delay_ms(35);
	lcd_sendcommand(FUNSET);
		_delay_ms(1);
	lcd_sendcommand(ON_OFF);
	_delay_ms(1);
	lcd_sendcommand(CLEAR);
	_delay_ms(2);
	}

void lcd_string(char name[]){
	char *p=name;
	u8 c=0;
	while(*p!=null){

		lcd_writedata(name[c]);
		c++;
		p++;
	}
	}
void lcd_number(int x){
	u8 y[100];
	int r=0;
	if(x==0)
		lcd_writedata(48);
	else{
	while(x!=0){
		{y[r]=x%10;
		x=x/10;
		r++;}
	}
	for(int i=r-1;i>=0;i--){
		lcd_writedata(y[i]+48);
	}}
}
void Lcd8_Set_Cursor(char line, char col)
{
    if(line == 1)
    	lcd_sendcommand(0x80 + col);
    else if(line == 2)
    	lcd_sendcommand(0xC0 + col);
}
void GoToPos(u8 row ,u8 col)
  {
 	 u8 address;
 	if (row <2 && col <16)
 	{
 		address= (row* 0x40)+ col ;
 		address = SET_BIT(address,7);
 		lcd_sendcommand(address);
 	}
  }

 u8 StrLen (u8*arr)
 {
    u8 i = 0;
    while (arr[i]!=null)
      i++;
     return i ;

 }

