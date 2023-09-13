/*
 * ================================================================
 * File: Lab3_5.2.c
 * Author: Pontus Svensson
 * Date: 2023-09-11
 * Description: Using the serial terminal as a user interface, the program can
 * set initial time, start, stop, update and reset the clock via the keyboard on
 * the serial terminal. The updated time should be displayed on the terminal
 * screen. A hardware timer to update the time value periodically when the timer
 * is running.
 * Time format should be in “hh:mm:ss” format, e.g., 23:01:59.
 *
 * License: This code is distributed under the MIT License. visit
 * https://opensource.org/licenses/MIT for more information.
 * ================================================================
 */

/*================================================================*/
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include "utils/uartstdio.h"
#include "utils/uartstdio.c"

#include "inc/UARTSetup.h"
#include "inc/stopwatch.h"
#include "inc/sharedVariables.h"

/*================================================================*/
#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ui32Line) {
  while (1)
    ;
}
#endif

/*================================================================*/
/*         Set the initial values for the stopwatch               */
/*================================================================*/
volatile uint32_t hours = 0, minutes = 0, seconds = 0;
volatile uint32_t userHours = 0, userMinutes = 0, userSeconds = 0;
volatile uint32_t stopwatch_time = 0;
volatile uint32_t startFlag = 0, stopFlag = 0, resetFlag = 0, countFlag = 0;

/*================================================================*/
int main(void) {
  // Initialize UART since we need to communicate using the serial terminal
  UARTConfigure();

  // Initialize the interrupt and set the clock frequency to 16kHz
  SysTick_INIT(SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                   SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                                  16000) -
               1);
  while (1) {
  }
}
