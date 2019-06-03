
#include "timer.h"

#define TIMER_RESET 6u

#define OSCCON_MASK (0x06 << 4u | 0x01 << 0u)
#define OPTION_REG_MASK 0x01

uint16_t Timer_Counter = 0;
uint8_t Timer_Tick = FALSE;
uint8_t Timer_Flag = 0;

void Timer_Init(void)
{
    //OSCCON = OSCCON_MASK;
    T0CS = FALSE;
    T0SE = FALSE;
    PSA = FALSE;
    PS0 = TRUE;
    PS1 = FALSE;
    PS2 = FALSE;
    TMR0 = TIMER_RESET;
    
    //OPTION_REG |= OPTION_REG_MASK;
    TMR0IF = FALSE;
    TMR0IE = TRUE;
    
    GIE = TRUE;
}

void Timer_Refresh(void)
{
    TMR0IF = FALSE;
    TMR0 = TIMER_RESET;
}

void Timer_Delay(const uint16_t Value)
{
    Timer_Counter = 0;
    while(Timer_Counter < Value);
}

uint8_t Timer_Check(void)
{
    return Timer_Tick;
}

void Timer_Clear(void)
{
    Timer_Tick = FALSE;
}

void __interrupt () tcInt(void)
{
    if(TMR0IE && TMR0IF)
    {
        Timer_Counter++;
        Timer_Tick = TRUE;
        Timer_Refresh();
    }  
}
 