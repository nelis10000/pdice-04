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

// Disable the "warning: (520) Function xxx is never called" warnings, all those warnings make the compiler output messages hard to read.
#pragma warning disable 520

#include "mcc_generated_files/system/system.h"
#include "utils.h"
#include "music.h"

//
// Macros
//
#define Switch_IsPressed()    !(SWITCH_GetValue())
#define Switch_IsNotPressed() SWITCH_GetValue()

// Dice LED layout
// 
// a-f is segment name, 0-7 is the shift register Q.. output
// 
//    7  _           _  1
//    a |_|    4    |_| e
//             d   
//    6  _     _     _  2
//    b |_|   |_|   |_| f
//                 
//    5  _           _  3
//    c |_|         |_| g
//                 
//                 
//    0            
//    x (not connected)
// 
//              Q 76543210
#define dot_a   0b00000001
#define dot_b   0b00000010
#define dot_c   0b00000100
#define dot_d   0b00001000
#define dot_e   0b01000000
#define dot_f   0b00100000
#define dot_g   0b00010000

// LED control macro. COM pin needs to be pulled LOW for LEDs to be on, and HIGH for LEDs off.
#define LedsOn()        COM_SetLow()
#define LedsOff()       COM_SetHigh()


//
// Global variables
//
uint8_t runMode;                    // Selects which program mode we run in. Selected by pressing SWITCH at poweron
const uint8_t pattern[7] = {
    0,
    dot_d,
    dot_c + dot_e,
    dot_c + dot_d + dot_e,
    dot_a + dot_c + dot_e + dot_g,
    dot_a + dot_c + dot_d + dot_e + dot_g,
    dot_a + dot_b + dot_c + dot_e + dot_f + dot_g };    // LED pattern


//
// Prototypes
//
void initRandomSeed(void);          // Initialize the Pseudo Random Number Generator (PRNG)
void selftest_1(void);              // Test LEDs and buzzer at poweron
void shiftOutByte(uint8_t val);     // Write LED pattern to shift register
void buzz_short(void);              // Simple short buzzer
uint8_t roll_dice(void);            // Roll the dice and return the number


/*
    Main application
*/
int main(void)
{
    uint8_t nrolls;     // Number of rolls
    uint8_t dice_val;   // Dice value
    uint8_t i;
    int j;

    SYSTEM_Initialize();
    TMR1_OverflowCallbackRegister(Timer1_Tick_Callback);

    // Bug: It seems that MCC does not enable the PWM Output Enable bit on the 12F157x series. 
    // Without this bit set, the PWM pin is not active, so we have to enable it ourselves.
    PWM1CONbits.OE = 1;     // LEDs COM PWM
    PWM3CONbits.OE = 1;     // Buzzer PWM

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 
    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 
    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Disable the LEDs
    LedsOff();
    OPT_SetHigh();  // OPT pin is only used on the prototype with 2 dices

    // Seed the pseudo random number generator with a random value, taken from a floating analog input. 
    // It's probably the best we can do. Also the PRNG is reseeded with the TMR0 count at every keypress.
    initRandomSeed();

    // Run a quick selftest, all LEDs on and a short beep
    selftest_1();
    delay_ms(1000);

    // Play an intro tune
    introMusic();
    delay_ms(1000);

    // Set the buzzer frequency for dice rolls
    BuzzSetFreq(BUZZ_4000HZ);

    // Check the button. If not pressed, runMode=1, else it's 2
    if (Switch_IsNotPressed()) {
        runMode = 1;
    } else {
        runMode = 2;
    }
    // Wait until switch is released
    while (Switch_IsPressed()) {
        __delay_ms(10);
    }

    // Flash an pattern to signal we're ready for the first dice roll
    if (runMode == 1) {
        shiftOutByte(dot_a);
    } else {
        shiftOutByte(dot_b);       
    }

    while( Switch_IsNotPressed())
    {
        LedsOn();
        delay_ms(100);
        LedsOff();
        delay_ms(100);
    }    

    while(1)
    {
        // Roll 15 times, plus a another 0-9 times
        nrolls = (uint8_t)(15+(rand() % 10));
        for (i=1; i<nrolls; i++) {
            // Get a number from a dice roll
            dice_val = roll_dice();

            // Show dice value on the LEDs
            LedsOff();                          // Disable LEDs
            __delay_ms(50);
            shiftOutByte(pattern[dice_val]);    // Write pattern to LED shift register
            LedsOn();                           // Enable LEDs

            // Short beep
            PWM3_Start();
            __delay_ms(20);
            PWM3_Stop();


            if (runMode == 1) {
                // RunMode 1
                if (i<10) {
                    __delay_ms(10);
                } else {
                    //__delay_ms(nrolls*10);              // Delay 10ms     ---> Inline delay argument must be constant
                    for (j=nrolls; j>0; j--) {
                        __delay_ms(10);
                    }
                }
            } else {
                // RunMode 2
                for (j=nrolls; j>0; j--) {
                    //__delay_ms(nrolls*10);              // Delay 10ms     ---> Inline delay argument must be constant
                    __delay_ms(10);
                }
            }
        }

        while( Switch_IsPressed()) {         // If the key is still pressed, we wait here until it is released
            __delay_ms(10);
        }
        while( Switch_IsNotPressed()) {         // Wait for the next keypress...
            __delay_ms(10);
        }
        
        // ... and repeat everything for the next roll
    }
}


// Try to seed the pseudo random number generator with a random value, taken from a floating analog input
void initRandomSeed(void)
{
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
    uint8_t bit;
    const uint16_t delay_us=10;

    for (bit=0; bit < 8; ++bit)
    {
        DAT_LAT = val & 1;
        //val >>= 1;
        val = val >> 1;

        CLK_SetHigh();
        __delay_us(delay_us);
        CLK_SetLow();
        __delay_us(delay_us);
    }
}


uint8_t roll_dice(void)
{
    uint8_t roll_value; 

    // Get random number, reseed the pseudo random number generator with the value of the free-running TMR0
    srand(TMR0_CounterGet());
    roll_value = (uint8_t) ( (rand() % 6) + 1);

    return roll_value;
}


void selftest_1(void)
{
    // shiftOutByte(0b11111111);       // All LED outputs on
    // COM_SetLow();                       // Enable LEDs
    // buzz_short();                       // Short buzzer
    // __delay_ms(1000);

    // COM_SetLow();                       // Disable LEDs
    // shiftOutByte(0b00000000);       // All LED outputs off
    // __delay_ms(1000);
    COM_SetLow();
    shiftOutByte(dot_a);
    delay_ms(1000);
    shiftOutByte(dot_b);
    delay_ms(1000);
    shiftOutByte(dot_c);
    delay_ms(1000);
    shiftOutByte(dot_d);
    delay_ms(1000);
    shiftOutByte(dot_e);
    delay_ms(1000);
    shiftOutByte(dot_f);
    delay_ms(1000);
    shiftOutByte(dot_g);
    delay_ms(1000);
    COM_SetHigh();
}

void buzz_short(void)
{
    // PWM on
    PWM3_Start();
    __delay_ms(50);
    // PWM off
    PWM3_Stop();
    __delay_ms(50);
}


