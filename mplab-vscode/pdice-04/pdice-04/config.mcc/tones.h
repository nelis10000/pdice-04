#pragma once
#include "mcc_generated_files/system/system.h"


// Select which introduction music we want to play at poweron
#define introTune()         tune_02()

// Full note length in milliseconds. Fractional note lengths are calculated from this value. 
#define NOTE_L1     300             // Semibreve / Full note 
#define NOTE_L2     (NOTE_L1 / 2)   // Minum     / Half note
#define NOTE_L4     (NOTE_L1 / 4)   // Crotchet  / Quarter note
#define NOTE_L8     (NOTE_L1 / 8)   // Quaver    / Eighth note

// Set buzzer frequency and delay for dice rolls
#define BUZZFREQ_DICEROLLS  500
#define BUZZDELAY_DICEROLLS 20

// Buzzer frequency for the boring standard buzz() function
#define BUZZFREQ_DEFAULT    4000

/* 
    Musical notes to frequency table: https://www.liutaiomottola.com/formulae/freqtab.htm
    The compiler calculates the formulas below in the preprocessor stage.
    
    For better power consumption, the XTAL_FREQ set in MCC config should be low, but too low will create inaccurate tones.
    When changing the XTAL_FREQ, check if the calculated output of the lowest and highest note below is still between 0 and 65535.
    An XTAL_FREQ of 4MHz seems to be a good tradeoff (range is 31.5kHz to 32MHz). 
    Prescaler is typically just 1, no prescaler.
    
    PeriodCount = Fosc / (freq*prescaler) - 1 
    
    NOTE_C5 = 4000000/(523.25*1) - 1 = 7645
    ...
    NOTE_B7 = 4000000/(3951.066*1) - 1 = 1012
*/
#define NOTE_C5     (uint16_t)((_XTAL_FREQ / (523.250 * 1)) - 1)
#define NOTE_C5  	(uint16_t)((_XTAL_FREQ / (523.250 * 1)) - 1)
#define NOTE_CS5	(uint16_t)((_XTAL_FREQ / (554.370 * 1)) - 1)
#define NOTE_D5  	(uint16_t)((_XTAL_FREQ / (587.330 * 1)) - 1)
#define NOTE_DS5	(uint16_t)((_XTAL_FREQ / (622.250 * 1)) - 1)
#define NOTE_E5  	(uint16_t)((_XTAL_FREQ / (659.250 * 1)) - 1)
#define NOTE_F5  	(uint16_t)((_XTAL_FREQ / (698.460 * 1)) - 1)
#define NOTE_FS5	(uint16_t)((_XTAL_FREQ / (739.990 * 1)) - 1)
#define NOTE_G5  	(uint16_t)((_XTAL_FREQ / (783.990 * 1)) - 1)
#define NOTE_GS5	(uint16_t)((_XTAL_FREQ / (830.610 * 1)) - 1)
#define NOTE_A5  	(uint16_t)((_XTAL_FREQ / (880.000 * 1)) - 1)
#define NOTE_AS5	(uint16_t)((_XTAL_FREQ / (932.330 * 1)) - 1)
#define NOTE_B5  	(uint16_t)((_XTAL_FREQ / (987.770 * 1)) - 1)

#define NOTE_C6  	(uint16_t)((_XTAL_FREQ / (1046.502 * 1)) - 1)
#define NOTE_CS6	(uint16_t)((_XTAL_FREQ / (1108.731 * 1)) - 1)
#define NOTE_D6  	(uint16_t)((_XTAL_FREQ / (1174.659 * 1)) - 1)
#define NOTE_DS6	(uint16_t)((_XTAL_FREQ / (1244.508 * 1)) - 1)
#define NOTE_E6  	(uint16_t)((_XTAL_FREQ / (1318.510 * 1)) - 1)
#define NOTE_F6  	(uint16_t)((_XTAL_FREQ / (1396.913 * 1)) - 1)
#define NOTE_FS6	(uint16_t)((_XTAL_FREQ / (1479.978 * 1)) - 1)
#define NOTE_G6  	(uint16_t)((_XTAL_FREQ / (1567.982 * 1)) - 1)
#define NOTE_GS6	(uint16_t)((_XTAL_FREQ / (1661.219 * 1)) - 1)
#define NOTE_A6  	(uint16_t)((_XTAL_FREQ / (1760.000 * 1)) - 1)
#define NOTE_AS6	(uint16_t)((_XTAL_FREQ / (1864.655 * 1)) - 1)
#define NOTE_B6  	(uint16_t)((_XTAL_FREQ / (1975.533 * 1)) - 1)
								
#define NOTE_C7  	(uint16_t)((_XTAL_FREQ / (2093.005 * 1)) - 1)
#define NOTE_CS7	(uint16_t)((_XTAL_FREQ / (2217.461 * 1)) - 1)
#define NOTE_D7  	(uint16_t)((_XTAL_FREQ / (2349.318 * 1)) - 1)
#define NOTE_DS7	(uint16_t)((_XTAL_FREQ / (2489.016 * 1)) - 1)
#define NOTE_E7  	(uint16_t)((_XTAL_FREQ / (2637.021 * 1)) - 1)
#define NOTE_F7  	(uint16_t)((_XTAL_FREQ / (2793.826 * 1)) - 1)
#define NOTE_FS7	(uint16_t)((_XTAL_FREQ / (2959.955 * 1)) - 1)
#define NOTE_G7  	(uint16_t)((_XTAL_FREQ / (3135.964 * 1)) - 1)
#define NOTE_GS7	(uint16_t)((_XTAL_FREQ / (3322.438 * 1)) - 1)
#define NOTE_A7  	(uint16_t)((_XTAL_FREQ / (3520.000 * 1)) - 1)
#define NOTE_AS7	(uint16_t)((_XTAL_FREQ / (3729.310 * 1)) - 1)
#define NOTE_B7  	(uint16_t)((_XTAL_FREQ / (3951.066 * 1)) - 1)


//
// Prototypes
//
void playNote(uint16_t period, uint16_t duration_ms);   // Play a note (see above for macros for period and duration)
void buzzFreq(uint16_t freq, uint16_t duration_ms);     // Buzz at given freq for .. ms
uint16_t freqToPwmPeriod(uint16_t freq);                // Convert a frequency to PWM reload value
inline void buzz(uint16_t duration_ms);                 // Just buzz for .. ms
inline void buzzSetFreq(uint16_t freq);                 // Set PWM frequency for buzzer

void dicePlaySound(uint8_t val);        // Play a sound after dice roll, depending on dice value.

void tune_01(void);               // Plays a melody (Beethoven)
void tune_02(void);               // Plays a melody (Star Wars)
void tune_03(void);               // Whoop up
void tune_04(void);               // Random
void tune_05(void);               // ?
void tune_06(void);               // ?
void tune_07(void);               // ?
void tune_08(void);               // ?
void tune_09(void);               // ?
void tune_10(void);               // ?
