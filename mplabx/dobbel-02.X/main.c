 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include <stdlib.h>

/* Pin functions
 * See "Header Files/MCC Generated Files/system/pins.h" for pin macro functions
 * 
 * RA0: DAT    - Shift Register Data  / PGD
 * RA1: CLK    - Shift Register Clock / PGC
 * RA2: BUZZ   - Buzzer / PWM3
 * RA3: SWITCH - Switch / VPP
 * RA4: OPT    - Optional / PWM2 / AN3
 * RA5: COM    - Led Common (cathode) / PWM1
 */

// Prototypes
void selftest_1(void);
void initRandomSeed(void);
void shiftOutByte(uint8_t val);
void gooi_dobbelsteen(void);
void buzz(void);

// Global variables
uint8_t dobbelsteen_waarde = 0;
const uint8_t patroon[7] = {
        0b00000000,     // 0
        0b00001000,     // 1
        0b01000100,     // 2
        0b01001100,     // 3
        0b01010101,     // 4
        0b01011101,     // 5
        0b01110111 };   // 6




#if(0)
void MyTimer1Isr(void)
{
    // Laat de waarde van de dobbelstenen afwisselend op de linker en rechter dobbelsteen zien.
    // Dit doen we zo snel dat je het niet meer kan zien.
    
    // Eerst zetten we beide dobbelstenen uit
    COM1_SetHigh();
    COM2_SetHigh();
    
    if (dobbelsteen_show == links) {
        dobbelsteen_show = rechts; 
        // Schrijf waarde naar rechter dobbelsteen
        shiftOutByte(dobbelsteen_patroon_links);
        // Zet de rechter dobbelsteen aan
        COM2_SetLow();
    } else {
        dobbelsteen_show = links;
        // Schrijf waarde naar linker dobbelsteen
        shiftOutByte(dobbelsteen_patroon_rechts);
        // Zet de linker dobbelsteen aan 
        COM1_SetLow();
    }
}
#endif


/*
    Main application
*/
int main(void)
{
    uint8_t num; 
    
    SYSTEM_Initialize();


    COM_SetLow();
    OPT_SetLow();
    shiftOutByte(0b11111111);
    
    while(1) {

    }
    
    
    

/*  
//    TMR1_OverflowCallbackRegister(MyTimer1Isr);
    selftest_1();
    
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 
   
    // Enable the Peripheral Interrupts 
//    INTERRUPT_PeripheralInterruptEnable(); 
    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 

    // Enable the Global Interrupts 
//    INTERRUPT_GlobalInterruptEnable(); 
    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 


    COM_SetLow();
    OPT_SetHigh();
    shiftOutByte(0);

    shiftOutByte(0b11111111);
    while(1) {
        // 
    }
    
    while(1)
    {
        gooi_dobbelsteen();
        buzz();
        __delay_ms(1000);
        
        shiftOutByte(0b00000000);
        __delay_ms(100);
    }    
*/
    
}




void initRandomSeed(void)
{
    // Probeer een willekeurige ADC waarde in te lezen door een pin (RA4, OPT) in analoge mode te zetten en dan de waarde ervan te lezen.
    
    uint16_t adcResult;
    
    TRISAbits.TRISA4 = 1;       // RA4 input
    ANSELAbits.ANSA4 = 1;       // RA4 analog mode
    
    ADCON0 = 0b00001101;        // Select channel 3 (bit 6...2) and enable ADC (bit 0))
    ADCON0bits.GO_nDONE = 1;    // Start an analog-to-digital conversion
    
    while(ADCON0bits.GO_nDONE == 1);    // Wait for the conversion to end
    
    adcResult = (uint16_t)((ADRESH<<8) | ADRESL);   // Save the conversion value

    srand(adcResult);   // Use adc result to seed the random number generator
    
    ANSELAbits.ANSA4 = 0;   // RA0 digital mode
    TRISAbits.TRISA4 = 0;   // RA0 output
}



void shiftOutByte(uint8_t val)
{
    const uint16_t delay_us=1;
    
    uint8_t bit;
    
    for (bit=0; bit < 8; ++bit)
    {
        DAT_LAT = val & 1;
        val >>= 1;
        
        CLK_SetHigh();
        __delay_us(delay_us);
        CLK_SetLow();
        __delay_us(delay_us);
    }
}


void gooi_dobbelsteen(void)
{
    dobbelsteen_waarde = (rand() % 6) + 1;
    shiftOutByte(patroon[dobbelsteen_waarde]);
}


void selftest_1(void)
{
    __delay_ms(100);
    
    COM_SetHigh();
    
    shiftOutByte(0b11111111);
    __delay_ms(1000);

    shiftOutByte(0b00000000);
    __delay_ms(1000);
    buzz();
}

void buzz(void)
{
    // PWM on
    PWM3_Start();
    __delay_ms(50);
    // PWM off
    PWM3_Stop();
    __delay_ms(50);
}