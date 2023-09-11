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
#include <time.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"

volatile uint32_t seconds = 0; // Variable to maintain elapsed seconds
/*================================================================*/
/*         Functions to start,stop, and reset the stopwatch       */
/*================================================================*/
void STOPWATCHStart() {}
void STOPWATCHStop() {}
void STOPWATCHReset() {}
/*================================================================*/
/*         The stopwatch will count using an IRS                  */
/*================================================================*/
void *IntHandler() {
  // This irs should be called every 1 second and increment the time
  seconds++;
  // Clear the interrupt flag
  TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

/*================================================================*/
/*         The stopwatch will count using an IRS                  */
/*================================================================*/
void SysTick_INIT() {

  // Enable the timer which should be used for interrupts
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

  // Wait for the timer to be enabled
  while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)) {
  }

  // TIMER0 configured to be periodic
  TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

  // This will interrupt every 1 second.
  TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet());

  // Enable the timers.
  TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  TimerEnable(TIMER0_BASE, TIMER_A);

  // Register the timer interrupt handler
  TimerIntRegister(TIMER0_BASE, TIMER_A, IntHandler());

  // Enable the interrupts
  IntMasterEnable();
}
