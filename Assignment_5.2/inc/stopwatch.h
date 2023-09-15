/*
 * ================================================================
 * File: stopwatch.h
 * Author: Pontus Svensson, Carl Larsson
 * Email: psn19003@student.mdu.se, cln20001@student.mdu.se
 * Date: 2023-09-11
 * Description: Function definitions for the stopwatch interface.
 *
 * License: This code is distributed under the MIT License. visit
 * https://opensource.org/licenses/MIT for more information.
 * ================================================================
 */

/*================================================================*/
#ifndef STOPWATCH_H
#define STOPWATCH_H

/*================================================================*/
#include <stdint.h>

/*================================================================*/
extern void STOPWATCHStart(void);
extern void STOPWATCHStop(void);
extern void STOPWATCHReset(void);
extern void convertToSeconds(void);
extern void INTHandler(void);
extern void TIMERInit(uint32_t loadValue);

/*================================================================*/
#endif // STOPWATCH_H
