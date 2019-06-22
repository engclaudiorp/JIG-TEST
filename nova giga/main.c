/*
 * File:   main.c
 * Author: claudio.paula
 *
 * Created on 24 de Maio de 2019, 10:14
 */

#include <xc.h>
#include <stdio.h>
#include "defs.h"
#include "adc.h"
#include "delay.h"
#include "types.h"
#include "timer.h"
#include "defines.h"
#include "lcd.h"
#include "uart.h"

#define ESQUERDA_MAIS               PORTBbits.RB0
#define ESQUERDA_MENOS              PORTBbits.RB2 
#define DIREITA_MAIS                PORTBbits.RB1
#define DIREITA_MENOS               PORTBbits.RB3
#define OK                          PORTBbits.RB4
#define LED_VERDE                   PORTBbits.RB6 
#define LED_VERMELHO                PORTBbits.RB7 

void Teste(int pos, int linha, int valor){
    
int parte_inteira = valor;
int digito_centena = parte_inteira / 100;
int digito_dezena = parte_inteira % 100 / 10;
int digito_unidade = parte_inteira % 10;

char texto[3];
texto[0] = digito_centena+0x30;
texto[1] = digito_dezena+0x30;
texto[2] = '.';
texto[3] = digito_unidade+0x30;

Lcd_PosStr(pos, linha, texto);

}

unsigned char Pattern5[] =              // Matriz do caracter especial 
{
  0b01000,
  0b01100,
  0b01110,
  0b01111,
  0b01110,
  0b01100,
  0b01000,
  0b00000
};

unsigned char Pattern1[]= {0x0e,0x0e,0x04,0x04,0x1f,0x04,0x0a,0x0a}; 
unsigned char Pattern2[]= {0x0e,0x0e,0x15,0x0e,0x04,0x04,0x0a,0x11};
unsigned char Pattern3[]= {0x00,0x00,0x0a,0x15,0x11,0x0a,0x04,0x00};
unsigned char Pattern4[]= {0x00,0x00,0x0a,0x1f,0x1f,0x0e,0x04,0x00};

void main(void) {
   // OSCCON = 0x76;
    ANSELH = 0;
    TRISB = 0x0F;   // portb 00001111;
    ADC_Init();
    Lcd_Init();
   // Timer_Init();
    UART_Init(9600);
    unsigned int tensao, b , c , corrente;
    unsigned int i = 0;
    int flag, flag1, flag2;
    Teste( 2, 2, b );
    Teste( 7, 2, c );
   
    CreateCustomCharacter(Pattern1,1); /*Create Man pattern at location 1 of CGRAM*/
    CreateCustomCharacter(Pattern2,3); 
    CreateCustomCharacter(Pattern3,0); 
    CreateCustomCharacter(Pattern4,2);
    CreateCustomCharacter(Pattern5,4);
    
    while(TRUE)
    {
       // if(Timer_Check()) {
         
       UART_Write('A');
       __delay_ms(100);
        if(UART_Data_Ready())
        PORTB = UART_Read();
       ADC_Handler();
       CLRWDT();
       
       tensao = Volt_Read() *10;    //Lê o AD canal 1
       corrente = Amp_Read()  *10;  //Lê o AD canal 2

       Teste(1,1, tensao);
       Teste(9,1, corrente);
       Lcd_PosStr( 6, 1, "V" );
       Lcd_PosStr( 14, 1, "A" );
       Lcd_PosStr( 1, 3, "      GIGA     " );
       Lcd_PosStr( 1, 4, "TESTE DE PLACAS" );
      
      
       if(ESQUERDA_MAIS == 0 && flag == 0) {
           flag = 1;
                                           }
  
       if(ESQUERDA_MAIS == 1 && flag == 1) {
           flag = 0; 
           b++;
           PORTBbits.RB4 = 1;
           Lcd_PosChr( 1, 2,  4 );
           Lcd_PosChr( 6, 2, ' ' );
           Teste( 2, 2, b );
                                           }
       
        if(ESQUERDA_MENOS == 0 && flag == 0 ) {
           flag = 1; 
                                              }
       
       if(ESQUERDA_MENOS == 1 && flag == 1)     
       {
           if(b>0)
            b--;
           flag = 0;
           PORTBbits.RB4 = 1;
           Lcd_PosChr( 1, 2,  4  );
           Lcd_PosChr( 6, 2, ' ' );
           Teste( 2, 2, b );
       }
 
      
         if(DIREITA_MAIS == 0 && flag == 0 ) {
            flag = 1; 
                                             }
       if(DIREITA_MAIS == 1 && flag == 1)     
       {
           c++;
           flag = 0;
           PORTBbits.RB5 = 1;
           Lcd_PosChr( 6, 2,  4  );
           Lcd_PosChr( 1, 2, ' ' );
           Teste( 7, 2, c );
       }
       
      
       
            if(DIREITA_MENOS == 0 && flag == 0 ) {
            flag = 1; 
                                                 }
       if(DIREITA_MENOS == 1 && flag == 1)     
       {
           if(c>0)
           c--;
           flag = 0;
           PORTBbits.RB5 = 1;
           Lcd_PosChr( 6, 2,  4  );
           Lcd_PosChr( 1, 2, ' ' );
           Teste( 7, 2, c );
       }
       
       
       else if( b < corrente && c > corrente) 
       {
            LED_VERDE = 1; // EQUIPAMENTO PASS
            Lcd_PosStr( 11, 2, "<PASS>" );
       }
       
       else if( corrente == 0 ) {
           LED_VERMELHO = 1;    // EQUIPAMENTO DESLIGADO
                                }
       else{
           PORTBbits.RB4 = 0;
           PORTBbits.RB5 = 0;
           LED_VERDE = 0;  
           LED_VERMELHO = 0;
           Lcd_PosStr( 11, 2, "      " );
           }
    //   Timer_Clear();
               //             } //fecha funçao if do timer check
    }
}


