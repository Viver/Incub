#ifndef TIME_H_
#define TIME_H_

#include <avr/io.h>
#include <stdint.h>
#include "../Macros/Interrupt.h"

#define R_SEC 23
#define R_MIN 25
#define R_Hr 27
#define R_Dt 29


void InitTime(void);
uint8_t GetTime(uint8_t t);


#endif /* TIME_H_ */