/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 3.0.0
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

#include "../pins.h"

void (*SWITCH_InterruptHandler)(void);

void PIN_MANAGER_Initialize(void)
{
   /**
    LATx registers
    */
    LATA = 0x0;

    /**
    TRISx registers
    */
    TRISA = 0x8;

    /**
    ANSELx registers
    */
    ANSELA = 0x0;

    /**
    WPUx registers
    */
    WPUA = 0x8;
    OPTION_REGbits.nWPUEN = 0x0;
  
    /**
    ODx registers
    */
   
    ODCONA = 0x0;
    /**
    SLRCONx registers
    */
    SLRCONA = 0x37;
    /**
    INLVLx registers
    */
    INLVLA = 0x3F;

    /**
    PPS registers
    */

    /**
    APFCON registers
    */

   /**
    IOCx registers 
    */
    IOCAP = 0x0;
    IOCAN = 0x8;
    IOCAF = 0x0;

    SWITCH_SetInterruptHandler(SWITCH_DefaultInterruptHandler);

    // Enable INTCONbits.IOCIE interrupt 
    INTCONbits.IOCIE = 1; 
}
  
void PIN_MANAGER_IOC(void)
{
    // interrupt on change for pin SWITCH}
    if(IOCAFbits.IOCAF3 == 1)
    {
        SWITCH_ISR();  
    }
}
   
/**
   SWITCH Interrupt Service Routine
*/
void SWITCH_ISR(void) {

    // Add custom IOCAF3 code

    // Call the interrupt handler for the callback registered at runtime
    if(SWITCH_InterruptHandler)
    {
        SWITCH_InterruptHandler();
    }
    IOCAFbits.IOCAF3 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF3 at application runtime
*/
void SWITCH_SetInterruptHandler(void (* InterruptHandler)(void)){
    SWITCH_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF3
*/
void SWITCH_DefaultInterruptHandler(void){
    // add your SWITCH interrupt custom code
    // or set custom function using SWITCH_SetInterruptHandler()
}
/**
 End of File
*/