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
#include "inc/stopwatch.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
// #include "inc/tm4c129encpdt.h"
#include "inc/UARTSetup.h"
#include "src/stopwatch.c"

/*================================================================*/
int main(int argc, char *argv[]) {
  char *default_time = "00:00:00";

  // Initialize the interrupt
  SysTick_INIT();
  INTInit();
  // Initialize UART since we need to communicate using the serial terminal
  // I want to implement the UART interrupt, and simultaneosly have a clock ticking
  // Depending on the UART input the interrupt will perform different tasks
  // Functions to implement in the IRS, START, STOP, Reset
  UARTConfigure();
  while (1) {
    UARTPrintToTerminal(default_time);
  }
  return 0;
}
