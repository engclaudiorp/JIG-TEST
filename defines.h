#ifndef DEFINES_H
#define	DEFINES_H

//#define FOSC          20000000UL       //oscilador externo 20MHz
#define FOSC            8000000UL        //oscilador interno 8MHz
#define FCY             (FOSC/4)
#define _XTAL_FREQ      FOSC            //para funcoes de __delay_xs()
/*
#define LED0            PORTBbits.RB4
#define LED1            PORTBbits.RB5
#define LED2            PORTBbits.RB6
#define LED3            PORTBbits.RB7
#define ESQ             PORTBbits.RB0
#define DIR             PORTBbits.RB1
#define ESC             PORTBbits.RB2
#define OK              PORTBbits.RB3
*/
#define LIGA            1U
#define DESLIGA         0U


#endif	/* DEFINES_H */

