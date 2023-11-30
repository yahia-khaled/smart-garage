#include"std_types.h"
#include"bit_math.h"
#include"K_PRIVATE.H"
#include"DIO_interface.h"
#include"K_CFG.h"
#include"avr/delay.h"

u8 GETPRESSED_VALUE(){
	u8 key=50;
			u8 pressed;
	for(u8 c=4;c<7;c++){
		DIO_VidSetPinValue(KBD_PORT,c,LOW);
		for(u8 r=0;r<4;r++){
			pressed=DIO_U8GetPinValue(KBD_PORT,r);
		if(pressed==LOW){
			key= (r*3)+(c-3);
			if(r==3 && c==5)
				key=0;
			while(LOW==pressed)
			{
				pressed=DIO_U8GetPinValue(KBD_PORT,r);
			}
			_delay_ms(5);
		}


		}
		DIO_VidSetPinValue(KBD_PORT,c,HIGH);
	}
	return key;
}
void KBD(){
	DIO_VidSetPortDirection(KBD_PORT,0b11110000);
	 DIO_VidSetPortValue(KBD_PORT,0b11111111);
}
