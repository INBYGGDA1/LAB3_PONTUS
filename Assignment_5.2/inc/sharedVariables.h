/*
 * ================================================================
 * File: sharedVariables.h
 * Author: Pontus Svensson, Carl Larsson
 * Email: psn19003@student.mdu.se, cln20001@student.mdu.se
 * Date: 2023-09-11
 * Description: Shared variables for communication with the IRS's implemented in
 * a different location.
 * 
 * License: This code is distributed under the MIT License. visit
 * https://opensource.org/licenses/MIT for more information.
 * ================================================================
 */

/*================================================================*/
#ifndef SHARED_VARIABLES_H
#define SHARED_VARIABLES_H

/*================================================================*/
#include <stdint.h>

/*================================================================*/
extern volatile uint32_t stopwatch_time;
extern char inputBuffer[];
extern volatile uint32_t hours, minutes, seconds;
extern volatile uint32_t userHours, userMinutes, userSeconds;
extern volatile uint32_t startFlag, stopFlag, resetFlag;
extern volatile uint32_t countFlag;
extern volatile uint32_t stopwatch_time;

/*================================================================*/
#endif
