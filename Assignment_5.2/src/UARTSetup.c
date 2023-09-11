/*
 * ================================================================
 * File: UARTSetup.c
 * Author: Pontus Svensson
 * Date: 2023-09-11
 * Description: This file handles functionality for the UART protocol for the
 * stopwatch
 *
 * License: This code is distributed under the MIT License. visit
 * https://opensource.org/licenses/MIT for more information.
 * ================================================================
 */

/*================================================================*/
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

volatile struct tm userInputTime;

uint32_t UARTCheckInput(const char *input) {
  uint32_t hours, minutes, seconds;
  char format[4]; // To store the ":" separators

  // Attempt to parse the input string
  if (sscanf(input, "%2d:%2d:%2d%3s", &hours, &minutes, &seconds, format) !=
      3) {
    return 0; // Parsing failed, invalid format
  }

  // Check that hours, minutes, and seconds are within valid ranges
  if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59 || seconds < 0 ||
      seconds > 59) {
    return 0; // Components out of range, invalid format
  } else {
    // Save the input to the struct
    userInputTime.tm_min = minutes;
    userInputTime.tm_hour = hours;
    userInputTime.tm_sec = seconds;
    return 1;
  }
  if (strcmp(input, "stop") == 1) {
    return 2;
  } else if (strcmp(input, "start") == 1) {
    return 3;

  } else if (strcmp(input, "reset") == 1) {
    return 4;
  }

  return 1; // Input is in "hh:mm:ss" format and valid
}
/*================================================================*/
/*            Initialize the UART communication                   */
/*================================================================*/
void UARTConfigure() {
  /* All system peripherals are disabled on start.
   To read and write to the registers they need to be enabled with
   SysCtlPeripheralEnable */
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  // Enable the UART0 module
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

  // Set the pins for GPIO block A to be receive and transmit
  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);

  // GPIOPinTypeUART configures the pins to work in the correct configuration
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  // Specifies the baudclock source for the UART
  UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

  // Configures the settings for the UART communication,
  // baudrate, frequencu, port.
  UARTStdioConfig(0, 115200, 16000000);
}

/*================================================================*/
/*            Print a string to the serial terminal               */
/*================================================================*/
void UARTPrintToTerminal(char *buf) {
  // Prints the string in buf to the terminal
  UARTprintf(buf);
}

/*================================================================*/
/*            Wait for input in the serial terminal               */
/*================================================================*/
void UARTReceiveInput(char *buf) {
  // Input is in hh:mm:ss, convert this string and place in the time struct
  struct tm time_info;
  UARTgets(buf, sizeof(buf));
  // If inpute is correct
  if (UARTCheckInput(buf) == 1) {
  }

  // implement error checking so that input is in the correct format
}
