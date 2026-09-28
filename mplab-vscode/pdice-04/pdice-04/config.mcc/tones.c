//#include "mcc_generated_files/system/system.h"
#include "tones.h"
#include "utils.h"
#include "interrupts.h"


// Fur Elise: E6 DS6 E6 DS6 E6 B5 D6 C6 A5
void introMusic_01(void)
{
    const uint16_t l1 = 50;     // Short note duration in ms
    const uint16_t l2 = 100;     // Long note duration in ms

    playNote(NOTE_E6,  l1);
    playNote(NOTE_DS6, l1);
    playNote(NOTE_E6,  l1);
    playNote(NOTE_DS6, l1);
    playNote(NOTE_E6,  l1);
    playNote(NOTE_B5,  l1);
    playNote(NOTE_D6,  l1);
    playNote(NOTE_C6,  l1);
    playNote(NOTE_A5,  l1);
}

// Starwars: A6 A6 A6 F6 CS6 A6 F6 CS6 A6
void introMusic_02(void)
{
    playNote(NOTE_A5, 500/3);
    playNote(NOTE_A5, 500/3);
    playNote(NOTE_A5, 500/3);
    playNote(NOTE_F5, 350/3);
    playNote(NOTE_C6, 150/3);
    playNote(NOTE_A5, 500/3);
    playNote(NOTE_F5, 350/3);
    playNote(NOTE_C6, 150/3);
    playNote(NOTE_A5, 500/3);
}

// Whoop Up
void introMusic_03(void)
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
void introMusic_04(void)
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
void introMusic_05(void)
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
void introMusic_06(void)
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

void diceSound_None(void)
{
    // Nothing to play
}

void diceSound_Play1(void)
{
    buzzNr(1);
}

void diceSound_Play2(void)
{
    buzzNr(2);
}

void diceSound_Play3(void)
{
    buzzNr(3);
}

void diceSound_Play4(void)
{
    buzzNr(4);
}

void diceSound_Play5(void)
{
    buzzNr(5);
}

void diceSound_Play6(void)
{
    buzzNr(6);
}


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


uint16_t freqToPwmPeriod(uint16_t freq)
{
    const uint8_t prescale = 1;

    return (uint16_t) ((_XTAL_FREQ / (freq * prescale)) - 1);
}

inline void buzz(uint16_t duration_ms)
{
    buzzFreq(BUZZFREQ_DEFAULT, duration_ms);

}

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

void buzzNr(uint16_t nr)
{
    uint16_t i;

    for (i=0; i<nr; i++)
    {
        buzz(50);
        delay_ms(50);
    }
}
