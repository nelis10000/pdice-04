/*
    pdice-04 - Dice rolling machine with PIC12F1572 microprocessor, designed for the "Weekend van de wetenschap 2026"

    Niels Althuisius 
    Elektronica Bèta VU
    Vrije Universiteit Amsterdam
    n.althuisius@beta.vu.nl
*/


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
#include "interrupts.h"
#include "utils.h"
#include "tones.h"


//
// Macros
//
#define Switch_IsPressed()    (SWITCH_GetValue()==0)
#define Switch_IsNotPressed() (SWITCH_GetValue()==1)

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


//
// Global variables
//
bool prng_needs_seeding;            // Signals that we need to seed the pseudo random number generator (on powerup, after sleep)
const uint8_t pattern[7] = {        // LED patterns
    0,
    dot_d,
    dot_c + dot_e,
    dot_c + dot_d + dot_e,
    dot_a + dot_c + dot_e + dot_g,
    dot_a + dot_c + dot_d + dot_e + dot_g,
    dot_a + dot_b + dot_c + dot_e + dot_f + dot_g };    


//
// Prototypes
//
void selftest(void);                // Test LEDs and buzzer at poweron
void diceShow(uint8_t dice_val);   // Show dice value on LEDs
uint8_t diceRoll(void);            // Roll the dice and return the number


//
//  Main program
//
int main(void)
{
    uint8_t nrolls;     // Number of rolls
    uint8_t dice_val;   // Dice value
    uint8_t i;

    SYSTEM_Initialize();
    TMR1_OverflowCallbackRegister(Timer1_Tick_Callback);        // TMR1 is used for the delay_ms() function
    TMR2_PeriodMatchCallbackRegister(Timer2_Period_Callback);   // TMR2 is used for auto-power off after about 5 minutes
    SWITCH_SetInterruptHandler(Switch_Interrupt_Callback);      // Switch (RA3) Interrupt-on-change 

    // Bug: It seems that MCC does not enable the PWM Output Enable bit on the 12F157x series. (only PWM2?)
    // Without this bit set, the PWM pin is not active, so we have to enable it ourselves.
    PWM3CONbits.OE = 1;

    // Enable low-power sleep mode
    VREGCONbits.VREGPM = 1;

    // Disable the LEDs
    LedsOff();
    OPT_SetHigh();  // OPT pin is only used on the prototype with 2 dices, setting it as output will save power in sleep mode

    // Enable the Peripheral Interrupts and Global Interrupts
    INTERRUPT_PeripheralInterruptEnable(); 
    INTERRUPT_GlobalInterruptEnable(); 

    // Seed the pseudo random number generator with a random value, taken from a floating analog input. 
    // It's probably the best we can do. Also the PRNG is reseeded with the TMR0 count at every keypress.
    initRandomSeed();
    prng_needs_seeding = true;

    // Run a quick selftest
    selftest();

    // Play an intro tune 
    shiftOutByte(0xff);     // All LEDs on
    LedsOn();
    introTune();


    // Set the buzzer frequency for dice rolls
    buzzSetFreq(BUZZFREQ_DICEROLLS);

    // Start the power-off timeout timer
    run_state = INTRO;
    TMR2_Start();


    //
    // Start of main loop
    // 
    while(1)
    {
        if (run_state == INTRO) {
            // Flash an LED to indicate we're ready for the first dice roll
            shiftOutByte(dot_d);
            {
                LedsOn();
                __delay_ms(250);
                LedsOff();
                __delay_ms(250);
            }
            if (sw_status == PRESSED) {
                // change status to running
                run_state = ACTIVE;
            }
        }

        if( run_state == ACTIVE && sw_status == PRESSED) {

            // Roll 15 times, plus a another 0-9 times
            nrolls = (uint8_t)(15+(rand() % 10));
            for (i=1; i<nrolls; i++) {
                // Get a number from a dice roll
                dice_val = diceRoll();

                // LEDs off between dice values
                LedsOff();                          
                delay_ms(50);

                // Show dice value on LEDs
                diceShow(dice_val);                
                LedsOn();

                // Short beep
                buzzFreq(BUZZFREQ_DICEROLLS, BUZZDELAY_DICEROLLS);

                // Roll delay
                delay_ms(i*10);
            }

            // Play a sound after dice roll 
            dicePlaySound(dice_val);

            sw_status = OFF;
            while(SWITCH_GetValue()==0);
            delay_ms(10);
        }

        if( run_state == SHUTDOWN )
        {
            // Shutdown sound
            buzzFreq(2000,50);
            buzzFreq(1500,50);
        
            // Leds off, stop Timers, disable interrupts, disable brown-out reset (saves power)
            LedsOff();
            TMR1_Stop();
            TMR2_Stop();
            INTERRUPT_GlobalInterruptDisable();
            INTERRUPT_PeripheralInterruptDisable(); 
            BORCONbits.SBOREN = 0;
            SLEEP();
            NOP();

            // Zzzzzzzzzzzz - sleep until an interrupt-on-change from the switch
            
            // Waking up - re-enable everything we shut off 
            BORCONbits.SBOREN = 1;
            INTERRUPT_PeripheralInterruptEnable();
            INTERRUPT_GlobalInterruptEnable(); 
            TMR2_Start();
            TMR1_Start();
            LedsOn();

            // Wakeup sound
            buzzFreq(1500,50);
            buzzFreq(2000,50);

            run_state = ACTIVE;
            delay_ms(20);
            sw_status = OFF;
            prng_needs_seeding = true;
        }

        if( run_state == SHUTDOWN_INTRO )
        {
            // Just beep and change runstate back to Intro
            buzzFreq(2000,50);
            run_state = INTRO;
        }
    }   // end while()
} // end main()


// Roll the dice, seed the pseudo-random-number-generator if needed
uint8_t diceRoll(void)
{
    uint8_t roll_value; 

    // Just on the first dice roll, seed the prng with the Timer0 value, which should be random enough (value depends on the number of microseconds between power-on and keypress)
    if (prng_needs_seeding==true) {
        prng_needs_seeding = false;
        srand(TMR0_CounterGet());
    }
    roll_value = (uint8_t) ( (rand() % 6) + 1);

    return roll_value;
}


// Show dice value on LEDs 
void diceShow(uint8_t dice_val)
{
    shiftOutByte(pattern[dice_val]);    // Write pattern to LED shift register
}




void selftest(void)
{
    LedsOn();
    for (uint8_t val = 1; val<=6; val++)
    {
       diceShow(val);
       delay_ms(250);
    }
    LedsOff();
}

