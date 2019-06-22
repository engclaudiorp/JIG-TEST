#ifndef MAIN_H
#define	MAIN_H

#pragma config FOSC     =  INTRC_NOCLKOUT
#pragma config WDTE     =  OFF	// Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE    =  OFF	// Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN    =  OFF	// Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP      =  OFF	// Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD      =  OFF	// Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT      =  OFF	// Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP       =  OFF	// Flash Program Memory Code Protection bit (Code protection off)

#endif	/* MAIN_H */

