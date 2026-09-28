#include "utils.h"

//
// Variables
//
volatile uint16_t ms_ticks = 0;     // Free running millisecond counter. Wraps around at 65.536 seconds since it is just an uint16_t!



// Timer1 callback function. This will increment ms_ticks every millisecond.
void Timer1_Tick_Callback(void)
{
    ms_ticks++;
}


void delay_ms(uint16_t milliseconds)
{
    // Capture the tick count at the start of the delay
    uint16_t start_ticks = ms_ticks;
    
    // Wait until the difference matches the requested milliseconds
    while ((ms_ticks - start_ticks) < milliseconds)
    {
        // Do nothing here, just wait until the time has elapsed
    }
}
