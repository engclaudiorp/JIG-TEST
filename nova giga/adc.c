#include "adc.h"

#define ADCON0_MASK 0x41
#define ADCON1_MASK 0xC0
#define TRISA_MASK 0x07

#define ADC_MEAN 0x0F

float16_t Amp = 0;
float16_t Volt = 0;
float16_t Watt = 0;


void ADC_Init(void)
{
    TRISA |= TRISA_MASK;
    ADCON0 = ADCON0_MASK;
    ADCON1 = ADCON1_MASK;
}
 
uint16_t ADC_Read(uint8_t Channel)
{
    ADCON0 &= ADCON0_MASK;                          //Clearing the Channel Selection Bits
    ADCON0 |= (uint8_t)(Channel << 2u);             //Setting the required Bits
    //Timer_Delay(1u);                              //Acquisition time to charge hold capacitor
    GO_nDONE = TRUE;                                //Initializes A/D Conversion
    while(GO_nDONE);                                //Wait for A/D Conversion to complete
    return (uint16_t)((ADRESH << 0x08) + ADRESL);   //Returns Result
}

void ADC_Handler(void)
{
    static float16_t Amp_Temp = 0, Volt_Temp = 0;
    static uint8_t i = 0;
    
    Amp_Temp += ADC_Read(0x00);
    Volt_Temp += ADC_Read(0x01);

    if(++i > ADC_MEAN - 1u)
    {
        Amp_Temp = Amp_Temp/ADC_MEAN;
        Amp_Temp = Amp_Temp * 5u/1023ul;
        Amp_Temp = Amp_Temp * 10u;
        Amp = Amp_Temp;

        Volt_Temp = Volt_Temp/ADC_MEAN;
        Volt_Temp = Volt_Temp * 5u/1023ul;
        Volt_Temp = Volt_Temp * 7.8f;
        Volt = Volt_Temp;

        Volt_Temp = 0;
        Amp_Temp = 0;
        Watt = Amp*Volt;
        i = 0;
    }
}

float16_t Amp_Read(void)
{
    return Amp;
}

float16_t Volt_Read(void)
{
    return Volt;
}

float16_t Watt_Read(void)
{
    return Watt;
}