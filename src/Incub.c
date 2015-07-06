#include <avr/signature.h>

#include "Global.h"
#include "Incub.h"

__fuse_t __fuse __attribute__((section (".fuse"))) =
{
	.low =  ( FUSE_SUT0 
			& FUSE_CKSEL3
			& FUSE_CKSEL2
			& FUSE_CKSEL1),
	.high = ( FUSE_BOOTSZ0
			& FUSE_BOOTSZ1
			& FUSE_EESAVE
			& FUSE_SPIEN
			& FUSE_WDTON),
	//.extended = EFUSE_DEFAULT,
};
unsigned char __lock __attribute__((section (".lock"))) = LOCKBITS_DEFAULT;

AT8_Data_t AT8_Data;

int main(void)
{
	uint8_t i=0;
	
	InitTime();
	
	_ENABLE_INTERRUPTS();
	LCD_Init();

	LCD_Data('T');
	LCD_Data('e');
	LCD_Data('s');
	LCD_Data('t');
	
	LCD_SetCursor(0,2);
	LCD_String("Temp = ");
	LCD_SendUint16(1569, 6, 2);
	
	_delay_ms(1000);
	LCD_Clear();
	LCD_Home();
	
	LCD_BuffLineOut(&AT8_Data, SCREEN_1);
	do 
	{
		LCD_Data(AT8_Data.LCD_ScrBuff.LcdLine1OutBuff[i]);
	} while (++i<17);
	LCD_SetCursor(0,2);
	i=0;
	do
	{
		LCD_Data(AT8_Data.LCD_ScrBuff.LcdLine2OutBuff[i]);
	} while (++i<17);
	
	_delay_ms(1000);
	LCD_Clear();
	LCD_Home();
	LCD_String("break point");
	
    while(1)
    {
		return NULL; //)
    }
}