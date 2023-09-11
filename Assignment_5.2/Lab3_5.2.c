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
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"
#include "inc/UARTSetup.h"
#include "inc/stopwatch.h"
/*================================================================*/
int main(int argc, char *argv[]) {
  char *default_time = "00:00:00";
  volatile uint32_t systemclock_scaled = 0;
  volatile uint32_t systemClock = 0;
  uint32_t userInput = 0;
  // systemClock initialized to 120Mhz
  systemClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                    SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                                   16000);
  uint32_t loadValue = systemClock / 1 - 1;

  // Initialize UART since we need to communicate using the serial terminal
  // I want to implement the UART interrupt, and simultaneosly have a clock
  // ticking Depending on the UART input the interrupt will perform different
  // tasks Functions to implement in the IRS, START, STOP, Reset
  UARTConfigure();
  // Initialize the interrupt
  SysTick_INIT(loadValue);
  while (1) {
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
}
