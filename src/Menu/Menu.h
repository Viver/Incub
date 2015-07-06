#ifndef __MENU_H_
#define __MENU_H_

#include "../Global.h"

enum {
	SCREEN_1 = 1,
	SCREEN_2
	};

void LCD_BuffLineOut(AT8_Data_t *pDt, uint8_t Mode);


#endif //__MENU_H_