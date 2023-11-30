#include "std_types.h"

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


void DIO_VidSetPinDirection (u8 Copy_U8Port, u8 Copy_U8Pin, u8 Copy_U8Dir);
void DIO_VidSetPortDirection (u8 Copy_U8Port, u8 Copy_U8Dir);
void DIO_VidSetPinValue (u8 Copy_U8Port, u8 Copy_U8Pin, u8 Copy_U8Val);
void DIO_VidSetPortValue (u8 Copy_U8Port, u8 Copy_U8Val);
void DIO_VidTogglePinValue (u8 Copy_U8Port, u8 Copy_U8Pin);
u8 DIO_U8GetPinValue (u8 Copy_U8Port, u8 Copy_U8Pin );


#endif

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1
