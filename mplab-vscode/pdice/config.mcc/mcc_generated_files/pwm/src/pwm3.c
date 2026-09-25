/**
 * PWM3 Generated Driver File
 * 
 * @file pwm3.c
 * 
 * @ingroup pwm3
 * 
 * @brief This is the generated driver implementation file for the PWM3 driver.
 *
 * @version PWM3 Driver Version 1.0.0
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "../pwm3.h"
static void (*PWM3_Callback)(void);

/**
  Section: PWM3 APIs
*/

void PWM3_Initialize(void)
{
  //PRIE disabled; DCIE disabled; PHIE disabled; OFIE disabled; 
  PWM3INTE = 0x0;

  // PRIF cleared; DCIF cleared; PHIF cleared; OFIF cleared; 
  PWM3INTF = 0x0;

  // CLKSEL FOSC; PRESC No_Prescalar; 
  PWM3CLKCON = 0x0;

  // LDMOD disabled; LD do_not_load; LDSRC reserved; 
  PWM3LDCON = 0x0;

  // OFTOUTMC match_decrementing; OFTMOD independent_run; OFTSEL reserved; 
  PWM3OFCON = 0x0;

  // PWMPHH 0; 
  PWM3PHH = 0x0;

  // PWMPHL 11; 
  PWM3PHL = 0xB;

  // PWMDCH 7; 
  PWM3DCH = 0x7;

  // PWMDCL 224; 
  PWM3DCL = 0xE0;

  // PWMPRH 15; 
  PWM3PRH = 0xF;

  // PWMPRL 192; 
  PWM3PRL = 0xC0;

  // PWMOFH 126; 
  PWM3OFH = 0x7E;

  // PWMOFL 2; 
  PWM3OFL = 0x2;

  // PWMTMRH 0x0; 
  PWM3TMRH = 0x0;

  // PWMTMRL 0x0; 
  PWM3TMRL = 0x0;

  //Clear interrupt flag


  //PWMEN disabled; PWMMODE standard_PWM; PWMPOL active_hi; PWMOE disabled; 
  PWM3CON = 0x0;
}

void PWM3_Start(void)
{
  PWM3CONbits.EN = 1;
}

void PWM3_Stop(void)
{
  PWM3CONbits.EN = 0;
}

bool PWM3_CheckOutputStatus(void)
{
  return (PWM3CONbits.OUT);
}

void PWM3_LoadBufferSet(void)
{
  PWM3LDCONbits.LDA=1;
}

void PWM3_PhaseSet(uint16_t phaseCount)
{
  PWM3PHH = (uint8_t)(phaseCount>>8);
  PWM3PHL = (uint8_t)(phaseCount);
}

void PWM3_DutyCycleSet(uint16_t dutyCycleCount)
{
  PWM3DCH = (uint8_t)(dutyCycleCount>>8);
  PWM3DCL = (uint8_t)(dutyCycleCount);
}

void PWM3_PeriodSet(uint16_t periodCount)
{
  PWM3PRH = (uint8_t)(periodCount>>8);
  PWM3PRL = (uint8_t)(periodCount);
}

void PWM3_OffsetSet(uint16_t offsetCount)
{
  PWM3OFH = (uint8_t)(offsetCount>>8);
  PWM3OFL = (uint8_t)(offsetCount);
}

uint16_t PWM3_timerCountGet(void)
{
  return (((uint16_t) (PWM3TMRH<<8)| PWM3TMRL));
}

bool PWM3_IsOffsetMatchOccured(void)
{
  return (PWM3INTFbits.OFIF);
}

bool PWM3_IsPhaseMatchOccured(void)
{
  return (PWM3INTFbits.PHIF);
}

bool PWM3_IsDutyCycleMatchOccured(void)
{
  return (PWM3INTFbits.DCIF);
}

bool PWM3_IsPeriodMatchOccured(void)
{
  return (PWM3INTFbits.PRIF);
}


/**
 End of File
*/