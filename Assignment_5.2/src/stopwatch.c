/*
 * ================================================================
 * File: stopwatch.c
 * Author: Pontus Svensson, Carl Larsson
 * Email: psn19003@student.mdu.se, cln20001@student.mdu.se
 * Date: 2023-09-11
 * Description: This files handles functionality to start, stop and reset the
 * stopwatch
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
  // Clear the interrupt flag to let the timer interrupt again
  TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  // To prevent race condition we disable the interrupts while increasing the
  // timer. I note that
  IntMasterDisable();
  if (startFlag == 1) {
    STOPWATCHStart();
  }
  if (stopFlag == 1) {
    STOPWATCHStop();
  }
  if (resetFlag == 1) {
    STOPWATCHReset();
  }

  // Clear the screen to prevent scrolling
  UARTprintf("\033[2J");

  // Update the clock
  seconds = stopwatch_time % 60;
  minutes = (stopwatch_time / 60) % 60;
  hours = (stopwatch_time / 3600) % 24;

  UARTprintf("Stopwatch time: %02u:%02u:%02u\nInput: ", hours, minutes,
             seconds);
  if (countFlag == 1) {
    stopwatch_time++;
  }
  IntMasterEnable();
}

/*================================================================*/
/*         Initialization of the timer module and IRS             */
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
  TimerIntRegister(TIMER0_BASE, TIMER_A, IntHandler);

  // // Enable the interrupts
  IntMasterEnable();
}
