#ifndef _ADC_H_
#define _ADC_H_

#include <xc.h>
#include "defs.h"
//#include "timer.h"

void ADC_Init(void);
uint16_t ADC_Read(uint8_t Channel);

void ADC_Handler(void);

float16_t Amp_Read(void);
float16_t Volt_Read(void);
float16_t Watt_Read(void);

#endif /* _ADC_H_ */