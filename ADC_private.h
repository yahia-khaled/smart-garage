#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_



#define ADMUX  *((u8 volatile*) 0x27)
#define ADCSRA *((u8 volatile*) 0x26)
#define ADCL   *((u8 volatile*) 0x24)
#define ADCH   *((u8 volatile*) 0x25)
#define ADCLH  *((u16 volatile*) 0x24)
#define SFIOR  *((u8 volatile*) 0x50)

#define RIGHT_ADJ_RES 0
#define LEFT_ADJ_RES 1
#define null '\0'




#endif
