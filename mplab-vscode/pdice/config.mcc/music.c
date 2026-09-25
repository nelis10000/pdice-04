//#include "mcc_generated_files/system/system.h"
#include "music.h"
#include "utils.h"



void introMusic_01(void)
{
    const uint16_t l1 = 100;     // Short note duration in ms
    const uint16_t l2 = 200;     // Long note duration in ms

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

void introMusic_02(void)
{
    const uint16_t l1 = 100;     // Short note duration in ms
    const uint16_t l2 = 200;     // Long note duration in ms

    playNote(NOTE_E6,  l1);

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
}


uint16_t freqToPwm(uint16_t freq)
{
    return 0;       // TODO FIXME
}
