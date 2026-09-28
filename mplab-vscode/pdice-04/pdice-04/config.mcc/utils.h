#pragma once
#include "mcc_generated_files/system/system.h"

//
// Macros
//

// LED control macro. COM pin needs to be pulled LOW for LEDs to be on, and HIGH for LEDs off.
#define LedsOn()        COM_SetLow()
#define LedsOff()       COM_SetHigh()
// #define LedsOn()        PWM1CONbits.OE=1
// #define LedsOff()       PWM1CONbits.OE=0

// #define LED_DC_100  128
// #define LED_DC_75   95
// #define LED_DC_50   63
// #define LED_DC_25   32
// #define LED_DC_0    0
// #define LedsOn()        PWM1_DutyCycleSet(LED_DC_100)
// #define LedsOff()       PWM1_DutyCycleSet(LED_DC_0)


//
// Variables
//


//
// Prototypes
//
void delay_ms(uint16_t milliseconds);   
void initRandomSeed(void);              // Initialize the Pseudo Random Number Generator (PRNG)
