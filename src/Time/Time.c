#include "Time.h"

typedef struct{
	uint8_t Sec;
	uint8_t Min;
	uint8_t Hr;
	uint8_t Dt;
}Time_t;

Time_t Tm;

inline void InitTime(void)
{
    // ��������� ���������� ������� 2.
    TIMSK &= ~(_BV(TOIE2) | _BV(OCIE2));

    // ��������� ������ 2 � ����������� ����� (������������ ��
    // �������� ���������� ����������).
    ASSR |= _BV(AS2);

    TCNT2 = 0x00;
    TCCR2 = 0x05; //������������� ����������� ������� ������ 128.
    OCR2  = 0x00;

    // ���� ���������� �������.
    while (ASSR & (_BV(TCN2UB) | _BV(OCR2UB) | _BV(TCR2UB)));

    // ��������� ���������� �� ������� 2.
    TIMSK |= _BV(TOIE2);
}

uint8_t GetTime(uint8_t t)
{
	switch(t)
	{
		case R_SEC: return Tm.Sec;
		case R_MIN: return Tm.Min;
		case R_Hr: return Tm.Hr;
		case R_Dt: return Tm.Dt;
		default: return -1;		
	}
}

ISR(TIMER2_OVF_vect)
{
	if (++Tm.Sec==60)
	{
		Tm.Sec=0;
		
		if (++Tm.Min==60)
		{
			Tm.Min=0;
			if (++Tm.Hr==24)
			{
				Tm.Hr=0;
				Tm.Dt++;
			}
		}
	}
}