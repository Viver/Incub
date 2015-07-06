#include "Menu.h"

const char StrI_tC[] PROGMEM = "tC=  \n"; //5 - температура
const char StrI_Ph[] PROGMEM = "Ph%=  \n"; //6 - влажность
const char StrI_tp[] PROGMEM = "tp=11m22\n"; //8 - время до переворота лотка
const char StrI_ts[] PROGMEM = "ts=111m22\n"; //8 - общее время с начала
const char StrI_Pr[] PROGMEM = "Pr=1\n"; //4 - фаза инкубации

const char StrISet[] PROGMEM = "Settings:\n"; //10

const char StrIChck[] PROGMEM = "Chicken\n"; // 7
const char StrIDck[] PROGMEM = "Duck\n"; // 4
const char StrIGs[] PROGMEM = "Geese\n"; // 5
const char StrITrk[] PROGMEM = "Turkeys\n"; // 7

PGM_P const MIPtrs[] PROGMEM = 
{
	StrI_tC, //0
	StrI_Ph, //1
	StrI_tp, //2
	StrI_ts, //3
	StrI_Pr, //4
	StrISet, //5
	StrIChck, //6
	StrIDck, //7
	StrIGs, //8
	StrITrk //9
};

enum {
	tC,
	Ph,
	tp,
	ts,
	Period,
	Settings,
	Chicken,
	Duck,
	Geese,
	Turkeys
};

void LCD_BuffLineOut(AT8_Data_t *pDt, uint8_t Mode)
{
	char Buff[16];
	uint8_t Cnt=0, Pos=0;
	
	switch(Mode)
	{
		case SCREEN_1:
			strcpy_P(Buff, (PGM_P)pgm_read_word(&(MIPtrs[Settings]))); // Line 1
			do 
			{
				pDt->LCD_ScrBuff.LcdLine1OutBuff[Cnt]=Buff[Cnt];
				Cnt++;
			} while (Buff[Cnt]!='\n');
			Pos=Cnt;
			Cnt=0;
			strcpy_P(Buff, (PGM_P)pgm_read_word(&(MIPtrs[Chicken])));
			do
			{
				pDt->LCD_ScrBuff.LcdLine1OutBuff[Cnt+Pos]=Buff[Cnt];
				Cnt++;
			} while (Buff[Cnt]!='\n');
			Pos=Cnt;
			pDt->LCD_ScrBuff.DataLine1Upd = 1;
			Pos=0;
			Cnt=0;
			strcpy_P(Buff, (PGM_P)pgm_read_word(&(MIPtrs[ts]))); // Line 2
			do 
			{
				pDt->LCD_ScrBuff.LcdLine2OutBuff[Cnt]=Buff[Cnt];
				Cnt++;
			} while (Buff[Cnt]!='\n');
			Pos=Cnt;
			Cnt=0;
			strcpy_P(Buff, (PGM_P)pgm_read_word(&(MIPtrs[tp])));
			do
			{
				pDt->LCD_ScrBuff.LcdLine2OutBuff[Cnt+Pos]=Buff[Cnt];
				Cnt++;
			} while (Buff[Cnt]!='\n');
			Pos=Cnt;
			pDt->LCD_ScrBuff.DataLine2Upd = 1;
			Pos=0;
			Cnt=0;
		break;//case SCREEN_1
		case SCREEN_2:

		break;//case SCREEN_2		
	}//switch(Mode)
}


