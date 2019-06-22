#ifndef _TIMER_H_
#define _TIMER_H_

#include <xc.h>
#include "defs.h"

void Timer_Init(void);
void Timer_Refresh(void);
void Timer_Delay(const uint16_t Value);

uint8_t Timer_Check(void);
void Timer_Clear(void);

#endif /* _TIMER_H_ */