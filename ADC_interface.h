#include"std_types.h"
#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/*typedef enum
{ channel0,
  channel1,
  channel2,
  channel3,
  channel4,
  channel5,
  channel6,
  channel7
}channel_type;*/


void ADC_VidInit();
/*void ADC_VidStartConversion(channel_type x);
u16 ADC_ReadData();*/
u16 ADC_Data(u8 x);




#endif
