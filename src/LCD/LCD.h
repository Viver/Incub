#ifndef __LCD_H
#define __LCD_H

#include "../Global.h"

#define LCD_PORT      PORTD
#define LCD_DDR       DDRD
#define LCD_DB        PD4

#define LCD_RS        PD0
#define LCD_EN        PD2

void LCD_Init(void);
void LCD_Clear(void);
void LCD_Home(void);
void LCD_SetCursor(uint8_t X, uint8_t Y);
void LCD_Data(uint8_t data);
void LCD_String(const char *data);
void LCD_GenerateChar(uint8_t code, const uint8_t *data);
void LCD_SendUint16(uint16_t data, uint8_t x, uint8_t y);

#endif