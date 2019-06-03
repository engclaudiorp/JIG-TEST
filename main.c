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

void Teste(int pos, int linha, int valor){
    
    int parte_inteira = valor;
//float parte_decimal = valor - parte_inteira;

int digito_centena = parte_inteira / 100;
int digito_dezena = parte_inteira % 100 / 10;
int digito_unidade = parte_inteira % 10;

//float num_invertido = (digito_unidade*100) + (digito_dezena*10) + digito_centena + parte_decimal;
//printf("%0.3f\n", num_invertido);
char texto[3];
texto[0] = digito_centena+0x30;
texto[1] = digito_dezena+0x30;
texto[2] = '.';
texto[3] = digito_unidade+0x30;

Lcd_PosStr(pos, linha, texto);
//Lcd_PosStr(pos, linha, unidade);
}
/*
float16_t Medida(float16_t *current,float16_t *tension,float16_t *wattage)
{
    
  float16_t Amp = 0, Volt = 0, Watt = 0;
    Amp = Amp_Read() *10;
    Volt = Volt_Read()*10;
    Watt = Watt_Read(); 
    
    Teste(1,1,Volt);
    Teste(8,1,Amp);
    Teste(1,2, Watt);
    *current = Amp;
    *tension = Volt;
    *wattage = Watt;
  //  return Amp, Volt, Watt;
    
}
*/
void main(void) {
   // OSCCON = 0x76;
    ANSELH = 0;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB4 = 0;   
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB5 = 0;   
    TRISBbits.TRISB6 = 0;   
    ADC_Init();
    Lcd_Init();
  // TRISB = 0x0F;
  //  PORTB = 0x00;
    int a, b , c, d;
    char flag;
    
    while(TRUE)
    {
        ADC_Handler();
        CLRWDT();
        
        a = Volt_Read() *10;
        d = Amp_Read()  *10;
      
      //  Medida(&a,&b,&c);
       Teste(1,1, a);
       Teste(9,1, d);
       Lcd_PosStr( 6, 1, "V" );
       Lcd_PosStr( 14, 1, "A" );
       Lcd_PosStr( 1, 3, "      GIGA     " );
       Lcd_PosStr( 1, 4, "TESTE DE PLACAS" );
      
       
       if(PORTBbits.RB0 == 0 ) {
            flag =1; 
       }
       if(PORTBbits.RB0 == 1 && flag == 1 )     
       {
           b++;
           flag = 0;
           PORTBbits.RB4 = 1;
           Lcd_PosChr( 1, 2, '>' );
           Lcd_PosChr( 6, 2, ' ' );
           Teste( 2, 2, b );
       }
       
   
       
       
         if(PORTBbits.RB1 == 0 ) {
            flag =1; 
       }
       if(PORTBbits.RB1 == 1 && flag == 1)     
       {
           c++;
           flag = 0;
           PORTBbits.RB5 = 1;
           Lcd_PosChr( 6, 2, '>' );
           Lcd_PosChr( 1, 2, ' ' );
           Teste( 7, 2, c );
       }
       
       
           else if( b < d && c > d) 
       {
           PORTBbits.RB6 = 1;   
       }
       
       
       else{
           PORTBbits.RB4 = 0;
           PORTBbits.RB5 = 0;
           PORTBbits.RB6 = 0;   
       }
       
      // Teste(6,1, 'V' );
       // Lcd_PosChr(6, 1, Amp);
    //    Lcd_PosChr(5, 1, 'V');
    }
}
