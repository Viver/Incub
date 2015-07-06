#include "LCD.h"

#define LCD_BOOTUP_MS           15
#define LCD_ENABLE_US           20
#define LCD_WRITEDATA_US        46
#define LCD_COMMAND_US          42

#define LCD_SOFT_RESET_MS1      5
#define LCD_SOFT_RESET_MS2      1
#define LCD_SOFT_RESET_MS3      1
#define LCD_SET_4BITMODE_MS     5

#define LCD_CLEAR_DISPLAY_MS    2
#define LCD_CURSOR_HOME_MS      2

#define LCD_DDADR_LINE1         0x00
#define LCD_DDADR_LINE2         0x40
#define LCD_DDADR_LINE3         0x10
#define LCD_DDADR_LINE4         0x50

// HD44780 LCD controller command set (do not modify these)
// Clear Display -------------- 0b00000001
#define LCD_CLEAR_DISPLAY       0x01
// Cursor Home ---------------- 0b0000001x
#define LCD_CURSOR_HOME         0x02
// Set Entry Mode ------------- 0b000001xx
#define LCD_SET_ENTRY           0x04
#define LCD_ENTRY_DECREASE      0x00
#define LCD_ENTRY_INCREASE      0x02
#define LCD_ENTRY_NOSHIFT       0x00
#define LCD_ENTRY_SHIFT         0x01
// Set Display ---------------- 0b00001xxx
#define LCD_SET_DISPLAY         0x08
#define LCD_DISPLAY_OFF         0x00
#define LCD_DISPLAY_ON          0x04
#define LCD_CURSOR_OFF          0x00
#define LCD_CURSOR_ON           0x02
#define LCD_BLINKING_OFF        0x00
#define LCD_BLINKING_ON         0x01
// Set Shift ------------------ 0b0001xxxx
#define LCD_SET_SHIFT           0x10
#define LCD_CURSOR_MOVE         0x00
#define LCD_DISPLAY_SHIFT       0x08
#define LCD_SHIFT_LEFT          0x00
#define LCD_SHIFT_RIGHT         0x04
// Set Function --------------- 0b001xxxxx
#define LCD_SET_FUNCTION        0x20
#define LCD_FUNCTION_4BIT       0x00
#define LCD_FUNCTION_8BIT       0x10
#define LCD_FUNCTION_1LINE      0x00
#define LCD_FUNCTION_2LINE      0x08
#define LCD_FUNCTION_5X7        0x00
#define LCD_FUNCTION_5X10       0x04
#define LCD_SOFT_RESET          0x30
// Set CG RAM Address --------- 0b01xxxxxx  (Character Generator RAM)
#define LCD_SET_CGADR           0x40
#define LCD_GC_CHAR0            0
#define LCD_GC_CHAR1            1
#define LCD_GC_CHAR2            2
#define LCD_GC_CHAR3            3
#define LCD_GC_CHAR4            4
#define LCD_GC_CHAR5            5
#define LCD_GC_CHAR6            6
#define LCD_GC_CHAR7            7
// Set DD RAM Address --------- 0b1xxxxxxx  (Display Data RAM)
#define LCD_SET_DDADR           0x80

const char Dig[] PROGMEM={'0','1','2','3','4','5','6','7','8','9'};

static void lcd_enable(void)
{
	LCD_PORT|=(1<<LCD_EN);
	_delay_us(LCD_ENABLE_US);
	LCD_PORT&=~(1<<LCD_EN);
}

static void lcd_out(uint8_t data)
{
	data&=0xF0;
	
	LCD_PORT &= ~(0xF0>>(4-LCD_DB));
	LCD_PORT |= (data>>(4-LCD_DB));
	lcd_enable();
}

void lcd_command(uint8_t data)
{
	LCD_PORT&=~(1<<LCD_RS);
	lcd_out(data);
	lcd_out(data<<4);
	_delay_us(LCD_COMMAND_US);
}

void LCD_Init(void)
{
	uint8_t pins=	(0x0F<<LCD_DB)
					|(1<<LCD_RS)
					|(1<<LCD_EN);
	LCD_DDR |= pins;
	LCD_PORT &= ~pins;
	_delay_ms(LCD_BOOTUP_MS);
	
	lcd_out(LCD_SOFT_RESET);
	_delay_ms(LCD_SOFT_RESET_MS1);
	
	lcd_enable();
	_delay_ms(LCD_SOFT_RESET_MS2);
	
	lcd_enable();
	_delay_ms(LCD_SOFT_RESET_MS3);
	
	lcd_out(LCD_SET_FUNCTION|LCD_FUNCTION_4BIT);
	_delay_ms(LCD_SET_4BITMODE_MS);
	lcd_command(LCD_SET_FUNCTION|LCD_FUNCTION_4BIT|LCD_FUNCTION_2LINE|LCD_FUNCTION_5X7);
	lcd_command(LCD_SET_DISPLAY|LCD_DISPLAY_ON|LCD_CURSOR_OFF|LCD_BLINKING_OFF);
	lcd_command(LCD_SET_ENTRY|LCD_ENTRY_INCREASE|LCD_ENTRY_NOSHIFT);
	
	LCD_Clear();
}

void LCD_Clear(void)
{
	lcd_command(LCD_CLEAR_DISPLAY);
	_delay_ms(LCD_CLEAR_DISPLAY_MS);
}

void LCD_Home(void)
{
	lcd_command(LCD_CURSOR_HOME);
	_delay_ms(LCD_CURSOR_HOME_MS);
}

void LCD_SetCursor(uint8_t X, uint8_t Y)
{
	uint8_t data;
	switch (Y)
	{
		case 1: data=LCD_SET_DDADR+LCD_DDADR_LINE1+X; break;
		case 2: data=LCD_SET_DDADR+LCD_DDADR_LINE2+X; break;
		case 3: data=LCD_SET_DDADR+LCD_DDADR_LINE3+X; break;
		case 4: data=LCD_SET_DDADR+LCD_DDADR_LINE4+X; break;
		default: return;
	}
	lcd_command(data);
}

void LCD_Data(uint8_t data)
{
	LCD_PORT|=(1<<LCD_RS);
	lcd_out(data);
	lcd_out(data<<4);
	_delay_us(LCD_WRITEDATA_US);
}

void LCD_String(const char *data)
{
	while( *data != '\0' )
	LCD_Data( *data++ );
}

void LCD_GenerateChar(uint8_t code, const uint8_t *data)
{
	lcd_command(LCD_SET_CGADR|(code<<3));
	for (uint8_t i=0; i<8; i++)
	{
		LCD_Data(data[i]);
	}
}

void LCD_SendUint16(uint16_t data, uint8_t x, uint8_t y)
{
	uint16_t Temp = 0;
	uint8_t *buf;
	uint8_t LCD_Buff[5];
	uint8_t Flag = 0;

	buf = &LCD_Buff[0];
	Temp = data;
	*buf = Temp/10000;
	Temp = Temp%10000;
	++buf;
	*buf = Temp/1000;
	Temp = Temp%1000;
	++buf;
	*buf = Temp/100;
	Temp = Temp%100;
	++buf;
	*buf = Temp/10;
	Temp = Temp%10;
	++buf;
	*buf = Temp;
	LCD_SetCursor(x, y);
	for (uint8_t i=0; i<5; i++)
	{
		switch(Flag)
		{
			case 0:
			{
				if(LCD_Buff[i]==0)
				{
					if (i!=4) {LCD_Data(' ');}
					else {LCD_Data('0');};
					
				}
				else
				{
					LCD_Data((uint8_t)pgm_read_word(&Dig[LCD_Buff[i]]));
					Flag = 1;
				};
			};
			break;
			case 1:
			{
				LCD_Data((uint8_t)pgm_read_word(&Dig[LCD_Buff[i]]));
			};
			break;
		};
	};
}


