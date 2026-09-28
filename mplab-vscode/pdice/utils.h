#pragma once
#include "config.mcc/mcc_generated_files/system/system.h"

//
// Variables
//
extern volatile uint16_t ms_ticks;


//
// Prototypes
//
void delay_ms(uint16_t milliseconds);
void Timer1_Tick_Callback(void);
