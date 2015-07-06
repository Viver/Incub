#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>

#include <stdint.h>

#define F_CPU 10000000UL
#include <util/delay.h>

#include "Macros/BitMask.h"

typedef struct //LCD_ScrBuff_t
{
	char LcdLine1OutBuff[16];
	uint8_t DataLine1Upd;
	char LcdLine2OutBuff[16];
	uint8_t DataLine2Upd;
}LCD_ScrBuff_t;

typedef struct //AT16_Data_t
{
	uint8_t Descriptor;
	LCD_ScrBuff_t LCD_ScrBuff;
	
}AT8_Data_t;


#endif /* GLOBAL_H_ */