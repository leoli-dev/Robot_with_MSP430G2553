#include "io430.h"
#include "adc.h"
#include "intrinsics.h"

/*............................................*/
/* Fonction d'initialisation de l'ADC         */
/*............................................*/
void init_ADC_Infrarouge(void)
{  
   ADC10AE0 = BIT0;  // Exemple pour le bit0 (A0) doit etre a 1 : ADC10AE0 : 00000001(2)
   ADC10CTL1 = INCH_0 + ADC10DIV_0;  // Exemple Channel 0 : INCHx : 0000(2) channel 0(10) 
   ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
   //ADC10CTL0 = SREF_1 + ADC10SHT_2 + REF2_5V + REFON + ADC10ON;  // Wait for ADC Ref to settle   
   __delay_cycles(500); // 100 ms de delai
}

void init_ADC_P1_1(void)
{  
   ADC10AE0 = BIT1;
   ADC10CTL1 = INCH_1 + ADC10DIV_0;
   ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
   //ADC10CTL0 = SREF_1 + ADC10SHT_2 + REF2_5V + REFON + ADC10ON;
   __delay_cycles(500);
}

void init_ADC_P1_2(void)
{  
   ADC10AE0 = BIT2;
   ADC10CTL1 = INCH_2 + ADC10DIV_0;
   ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
   //ADC10CTL0 = SREF_1 + ADC10SHT_2 + REF2_5V + REFON + ADC10ON;
   __delay_cycles(500);
}

void init_ADC_LigneDetecteurA(void)
{  
   ADC10AE0 = BIT4;
   ADC10CTL1 = INCH_4 + ADC10DIV_0;
   ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
   //ADC10CTL0 = SREF_1 + ADC10SHT_2 + REF2_5V + REFON + ADC10ON;
   __delay_cycles(500);
}

void init_ADC_LigneDetecteurB(void)
{  
   ADC10AE0 = BIT5;
   ADC10CTL1 = INCH_5 + ADC10DIV_0;
   ADC10CTL0 = SREF_0 + ADC10SHT_2 + ADC10ON;
   //ADC10CTL0 = SREF_1 + ADC10SHT_2 + REF2_5V + REFON + ADC10ON;
   __delay_cycles(500);
}


/*............................................*/
/* Fonction lecture de la valeur ADC convertie*/
/*............................................*/
unsigned int ReadAdc(void)
{
    ADC10CTL0 |= ENC + ADC10SC;     // Sampling and conversion start
    __delay_cycles(500);
    ADC10CTL0 &= ~ENC;		    // Disable ADC conversion
    return ADC10MEM;	            // Return Conversion value
}