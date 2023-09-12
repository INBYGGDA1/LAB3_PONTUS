/*
 * ================================================================
 * File: stopwatch.c
 * Author: Pontus Svensson
 * Date: 2023-09-11
 * Description: This files handles function to start, stop, reset the stopwatch
 *
 * License: This code is distributed under the MIT License. visit
 * https://opensource.org/licenses/MIT for more information.
 * ================================================================
 */
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "../inc/stopwatch.h"

volatile uint32_t seconds = 0; // Variable to maintain elapsed seconds
/*================================================================*/
/*         Functions to start,stop, and reset the stopwatch       */
/*================================================================*/
void STOPWATCHStart(char *userInput) {}
void STOPWATCHStop(void) {}
void STOPWATCHReset(char *userInput) {}

/*================================================================*/
/*              The stopwatch will count using an IRS             */
/*================================================================*/
void IntHandler(void) {
  // This irs should be called every 1 second and increment the time
  UARTprintf("\033[2J"); // Clear the screen
  seconds++;
  UARTprintf("Time: %d\n", seconds);
  // Clear the interrupt flag
  TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

/*================================================================*/
/*         The stopwatch will count using an IRS                  */
/*================================================================*/
void SysTick_INIT(uint32_t loadTime) {

  // // Do a complete reset of the timer to avoid errors
  // SysCtlPeripheralDisable(SYSCTL_PERIPH_TIMER0);
  // SysCtlPeripheralReset(SYSCTL_PERIPH_TIMER0);
  // Enable the timer which should be used for interrupts
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

  while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)) {
  }
  // TIMER0 configured to be periodic
  // TIMER_CFG_A_PERIODIC is used to keep the interrupts recurring and not
  // stopping after first interrupt
  TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC);
  TimerLoadSet(TIMER0_BASE, TIMER_A, loadTime);

  // Enable the timers.
  TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  TimerEnable(TIMER0_BASE, TIMER_A);

  // Register the timer interrupt handler
  TimerIntRegister(TIMER0_BASE, TIMER_A, &IntHandler);

  // // Enable the interrupts
  IntMasterEnable();
}
