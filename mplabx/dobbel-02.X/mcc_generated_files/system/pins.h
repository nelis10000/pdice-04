/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.0.0
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

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA0 aliases
#define DAT_TRIS                 TRISAbits.TRISA0
#define DAT_LAT                  LATAbits.LATA0
#define DAT_PORT                 PORTAbits.RA0
#define DAT_WPU                  WPUAbits.WPUA0
#define DAT_OD                   ODCONAbits.ODA0
#define DAT_ANS                  ANSELAbits.ANSA0
#define DAT_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define DAT_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define DAT_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define DAT_GetValue()           PORTAbits.RA0
#define DAT_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define DAT_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define DAT_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define DAT_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define DAT_SetPushPull()        do { ODCONAbits.ODA0 = 0; } while(0)
#define DAT_SetOpenDrain()       do { ODCONAbits.ODA0 = 1; } while(0)
#define DAT_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define DAT_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)
// get/set IO_RA1 aliases
#define CLK_TRIS                 TRISAbits.TRISA1
#define CLK_LAT                  LATAbits.LATA1
#define CLK_PORT                 PORTAbits.RA1
#define CLK_WPU                  WPUAbits.WPUA1
#define CLK_OD                   ODCONAbits.ODA1
#define CLK_ANS                  ANSELAbits.ANSA1
#define CLK_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define CLK_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define CLK_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define CLK_GetValue()           PORTAbits.RA1
#define CLK_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define CLK_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define CLK_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define CLK_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define CLK_SetPushPull()        do { ODCONAbits.ODA1 = 0; } while(0)
#define CLK_SetOpenDrain()       do { ODCONAbits.ODA1 = 1; } while(0)
#define CLK_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define CLK_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)
// get/set IO_RA3 aliases
#define SWITCH_TRIS                 TRISAbits.TRISA3
#define SWITCH_LAT                  LATAbits.
#define SWITCH_PORT                 PORTAbits.RA3
#define SWITCH_WPU                  WPUAbits.WPUA3
#define SWITCH_OD                   ODCONAbits.
#define SWITCH_ANS                  ANSELAbits.
#define SWITCH_SetHigh()            do { LATAbits. = 1; } while(0)
#define SWITCH_SetLow()             do { LATAbits. = 0; } while(0)
#define SWITCH_Toggle()             do { LATAbits. = ~LATAbits.; } while(0)
#define SWITCH_GetValue()           PORTAbits.RA3
#define SWITCH_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define SWITCH_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define SWITCH_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define SWITCH_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define SWITCH_SetPushPull()        do { ODCONAbits. = 0; } while(0)
#define SWITCH_SetOpenDrain()       do { ODCONAbits. = 1; } while(0)
#define SWITCH_SetAnalogMode()      do { ANSELAbits. = 1; } while(0)
#define SWITCH_SetDigitalMode()     do { ANSELAbits. = 0; } while(0)
// get/set IO_RA4 aliases
#define OPT_TRIS                 TRISAbits.TRISA4
#define OPT_LAT                  LATAbits.LATA4
#define OPT_PORT                 PORTAbits.RA4
#define OPT_WPU                  WPUAbits.WPUA4
#define OPT_OD                   ODCONAbits.ODA4
#define OPT_ANS                  ANSELAbits.ANSA4
#define OPT_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define OPT_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define OPT_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define OPT_GetValue()           PORTAbits.RA4
#define OPT_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define OPT_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define OPT_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define OPT_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define OPT_SetPushPull()        do { ODCONAbits.ODA4 = 0; } while(0)
#define OPT_SetOpenDrain()       do { ODCONAbits.ODA4 = 1; } while(0)
#define OPT_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define OPT_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)
// get/set IO_RA5 aliases
#define COM_TRIS                 TRISAbits.TRISA5
#define COM_LAT                  LATAbits.LATA5
#define COM_PORT                 PORTAbits.RA5
#define COM_WPU                  WPUAbits.WPUA5
#define COM_OD                   ODCONAbits.ODA5
#define COM_ANS                  ANSELAbits.
#define COM_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define COM_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define COM_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define COM_GetValue()           PORTAbits.RA5
#define COM_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define COM_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define COM_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define COM_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define COM_SetPushPull()        do { ODCONAbits.ODA5 = 0; } while(0)
#define COM_SetOpenDrain()       do { ODCONAbits.ODA5 = 1; } while(0)
#define COM_SetAnalogMode()      do { ANSELAbits. = 1; } while(0)
#define COM_SetDigitalMode()     do { ANSELAbits. = 0; } while(0)
/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/