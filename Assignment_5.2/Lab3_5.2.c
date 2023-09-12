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
/*         Define MACROS to include correct header definitions    */
/*================================================================*/
#define UARTSetup_H
#define STOPWATCH_H
#define UART_BUFFERED

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

#ifdef DEBUG
void __error__(char *pcFilename, uint32_t ui32Line) {
  while (1)
    ;
}
#endif
/*================================================================*/
int main(void) {
  uint32_t systemClock = 0;
  uint32_t systemClockScaled = 0;
  uint32_t userInput = 0;
  systemClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                    SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                                   16000);

  systemClockScaled = systemClock - 1;
  // Initialize UART since we need to communicate using the serial terminal
  // I want to implement the UART interrupt, and simultaneously have a clock
  // ticking Depending on the UART input the interrupt will perform
  // different tasks Functions to implement in the IRS, START, STOP, Reset
  // Initialize the interrupt
  UARTConfigure();
  UARTprintf("%d\n", systemClockScaled);
  SysTick_INIT(systemClockScaled);

  IntMasterEnable();
  TimerEnable(TIMER0_BASE, TIMER_A);
  UARTprintf("INIT\n");
  while (1) {
    // if (UARTPeek(ucChar) > 0) {

    UARTReceiveInput(default_time);

    // If input is correct
    userInput = UARTCheckInput(default_time);
    if (userInput == 2) {

      STOPWATCHStop();
    } else if (userInput == 1) {

      STOPWATCHStart(default_time);
    } else {

      STOPWATCHReset(default_time);
    }
  }
  // }
}
