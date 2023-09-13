/*
 * ================================================================
 * File: stopwatch.c
 * Author: Pontus Svensson
 * Date: 2023-09-11
 * Description: This files handles functionality to start, stop, reset the stopwatch
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
#include "inc/hw_ints.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "../inc/stopwatch.h"
#include "../inc/sharedVariables.h"

/*================================================================*/
/*         Functions to convert the input to seconds              */
/*================================================================*/
void convertToSeconds(void) {
  stopwatch_time = (userHours * 3600) + (userMinutes * 60) + userSeconds;
}

/*================================================================*/
/*         Functions to start,stop, and reset the stopwatch       */
/*================================================================*/
void STOPWATCHStart(void) {
  countFlag = 1;
  startFlag = 0;
}

/*================================================================*/
void STOPWATCHStop(void) {
  convertToSeconds();
  countFlag = 0;
  stopwatch_time = 0;
  stopFlag = 0;
  startFlag = 0;
}

/*================================================================*/
void STOPWATCHReset(void) {
  // Reset to user defined input
  convertToSeconds();
  hours = userHours;
  minutes = userMinutes;
  seconds = userSeconds;
  countFlag = 1;
  resetFlag = 0;
}

/*================================================================*/
/*                       The stopwatch IRS                        */
/*================================================================*/
void IntHandler(void) {
  if (startFlag == 1) {
    STOPWATCHStart();
  }
  if (stopFlag == 1) {
    STOPWATCHStop();
  }
  if (resetFlag == 1) {
    STOPWATCHReset();
  }
  if (countFlag == 1) {
    stopwatch_time++;
  }
  // Clear the screen to prevent scrolling
  UARTprintf("\033[2J");

  // Update the clock
  seconds = stopwatch_time % 60;
  minutes = (stopwatch_time / 60) % 60;
  hours = (stopwatch_time / 3600) % 24;

  UARTprintf("\rStopwatch time: %02u:%02u:%02u\nInput: ", hours, minutes,
             seconds);
  // Clear the interrupt flag to let the timer interrupt again
  TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

/*================================================================*/
/*         The stopwatch will count using an IRS                  */
/*================================================================*/
void TIMERInit(uint32_t loadTime) {

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
