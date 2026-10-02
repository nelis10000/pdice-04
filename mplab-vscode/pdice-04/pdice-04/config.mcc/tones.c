//#include "mcc_generated_files/system/system.h"
#include "tones.h"
#include "utils.h"
#include "interrupts.h"

//
// See tones.h for available notes and note lengths, you can also add notes there.
//

// Fur Elise: E6 DS6 E6 DS6 E6 B5 D6 C6 A5
void tune_01(void)
{
    playNote(NOTE_E6,  NOTE_L1);
    playNote(NOTE_DS6, NOTE_L1);
    playNote(NOTE_E6,  NOTE_L1);
    playNote(NOTE_DS6, NOTE_L1);
    playNote(NOTE_E6,  NOTE_L1);
    playNote(NOTE_B5,  NOTE_L1);
    playNote(NOTE_D6,  NOTE_L1);
    playNote(NOTE_C6,  NOTE_L1);
    playNote(NOTE_A5,  NOTE_L1);
}


// Starwars: A6 A6 A6 F6 CS6 A6 F6 CS6 A6
void tune_02(void)
{
    playNote(NOTE_A5, NOTE_L1);         // 500
    playNote(NOTE_A5, NOTE_L1);         // 500
    playNote(NOTE_A5, NOTE_L1);         // 500
    playNote(NOTE_F5, (uint16_t)(NOTE_L1*0.7));     // 350
    playNote(NOTE_C6, (uint16_t)(NOTE_L1*0.3));     // 150
    playNote(NOTE_A5, NOTE_L1);         // 500
    playNote(NOTE_F5, (uint16_t)(NOTE_L1*0.7));     // 350
    playNote(NOTE_C6, (uint16_t)(NOTE_L1*0.3));     // 150
    playNote(NOTE_A5, NOTE_L1);         // 500
}


// Seven Nation Army
void tune_03(void)
{
    playNote(NOTE_G4, NOTE_L1);
    playNote(NOTE_G4, NOTE_L2);
    playNote(NOTE_A4, NOTE_L2);
    playNote(NOTE_G4, NOTE_L1);
    playNote(NOTE_E4, NOTE_L2);
    playNote(NOTE_D4, NOTE_L2);
    playNote(NOTE_C4, NOTE_L1);
}


// Whoop Up
void tune_04(void)
{
    uint16_t freq = 500;
    uint16_t reload = 500;
    
    buzzSetFreq(freq);
    do {
        PWM3_Stop();
        buzzSetFreq(freq);
        PWM3_Start();
        __delay_ms(8);
        freq += 10;
    } while (freq < 3000);
    PWM3_Stop();
}


// Random
void tune_05(void)
{
    uint16_t i;

    for (i=0; i<75; i++) {
        PWM3_Stop();
        buzzSetFreq((uint16_t)(500+rand()%3000));
        PWM3_Start();
        __delay_ms(25);
    }
    PWM3_Stop();
}


// RandomLow
void tune_06(void)
{
    uint16_t i;

    for (i=0; i<75; i++) {
        PWM3_Stop();
        buzzSetFreq((uint16_t)(100+rand()%1000));
        PWM3_Start();
        __delay_ms(25);
    }
    PWM3_Stop();
}


// RandomHigh
void tune_07(void)
{
    uint16_t i;

    for (i=0; i<75; i++) {
        PWM3_Stop();
        buzzSetFreq((uint16_t)(2000+rand()%4000));
        PWM3_Start();
        __delay_ms(25);
    }
    PWM3_Stop();
}


// Sound to play for a dice value
void dicePlaySound(uint8_t val)
{
    switch (val) {
        case 1:
            break;      // Nothing
        case 2:
            break;      // Nothing
        case 3:
            break;      // Nothing
        case 4:
            break;      // Nothing
        case 5:
            break;      // Nothing
        case 6: 
            buzzFreq(2000,100);
            buzzFreq(2400,200);
            break;
        default: 
            break;
    }
}


// Play a note (macros for period and duration are in music.h)
void playNote(uint16_t period, uint16_t duration_ms)
{
    // Set PWM reload timer period for this frequency
    PWM3_PeriodSet(period);

    // Enable PWM output (tone starts)
    PWM3_Start();

    // Wait while the tone is playing
    delay_ms(duration_ms);

    // Disable PWM output (tone stops)
    PWM3_Stop();

    // Small delay between notes
    __delay_ms(25);
}


// Convert a frequency to PWM reload value
uint16_t freqToPwmPeriod(uint16_t freq)
{
    const uint8_t prescale = 1;

    return (uint16_t) ((_XTAL_FREQ / (freq * prescale)) - 1);
}


// Just buzz for .. ms
inline void buzz(uint16_t duration_ms)
{
    buzzFreq(BUZZFREQ_DEFAULT, duration_ms);

}


// Buzz at given freq for .. ms
void buzzFreq(uint16_t freq, uint16_t duration_ms)
{
    // Set buzzer frequency (if we played music or other tones, the frequency may be changed)
    buzzSetFreq(freq);

    // PWM on
    PWM3_Start();

    // Wait
    delay_ms(duration_ms);

    // PWM off
    PWM3_Stop();

}


// Set PWM frequency for buzzer
inline void buzzSetFreq(uint16_t freq)
{
    PWM3_PeriodSet(freqToPwmPeriod(freq));
}
