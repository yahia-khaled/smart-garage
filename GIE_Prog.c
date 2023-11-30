/*
 * GIE_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#include "GIE_Interface.h"
#include "GIE_Private.h"
#include"bit_math.h"

void M_GIE_Void_GlobalInterruptEnable(void)
{
	SET_BIT(SREG_REG,7);
}
void M_GIE_Void_GlobalInterruptDisable(void)
{
	CLR_BIT(SREG_REG,7);
}
