/*
 * ================================================================
 * File: UARTSetup.h
 * Author: Pontus Svensson, Carl Larsson
 * Email: psn19003@student.mdu.se, cln20001@student.mdu.se
 * Date: 2023-09-11
 * Description: Function definitions for the public stopwatch interface.
 *
 * License: This code is distributed under the MIT License. visit
 * https://opensource.org/licenses/MIT for more information.
 * ================================================================
 */

/*================================================================*/
#ifndef UARTSetup_H
#define UARTSetup_H

/*================================================================*/
#include <stdint.h>

/*================================================================*/
extern void UARTConfigure();
extern void UARTCheckInput(char *input);

/*================================================================*/
#endif
