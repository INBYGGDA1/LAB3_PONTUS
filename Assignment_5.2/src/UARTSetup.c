/*
 * ================================================================
 * File: UARTSetup.c
 * Author: Pontus Svensson
 * Date: 2023-09-11
 * Description: This file handles functionality for the UART IRS and configuration. 
 * 
 *
 * License: This code is distributed under the MIT License. visit
 * https://opensource.org/licenses/MIT for more information.
 * ================================================================
 */

/*================================================================*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../inc/UARTSetup.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "../inc/sharedVariables.h"
#include "../inc/stopwatch.h"

/*================================================================*/
char inputBuffer[128];

/*================================================================*/
/*              The UART interrupt service routine                */
/*================================================================*/
void UARTIntHandler(void) {
  // Returns the current interrupt status
  uint32_t ui32Status = UARTIntStatus(UART0_BASE, true);

  // Clear the registers to prevent the handler getting called again upon
  // exiting the function
  UARTIntClear(UART0_BASE, ui32Status);

  // This function processes the UART input string
  UARTgets(inputBuffer, sizeof(inputBuffer));

  // Call to check what the input represents, start, stop, reset, or hh_mm_ss
  UARTCheckInput(inputBuffer);
}

/*================================================================*/
/*         Check the string received from UART0                   */
/*================================================================*/
void UARTCheckInput(char *input) {
  // To store the ":" separators
  char format[4];
  int tempHours = 0, tempMinutes = 0, tempSeconds = 0;

  // First check if the UART input is one of the following strings
  if (strcmp(input, "start") == 0) {
    startFlag = 1;

  } else if (strcmp(input, "stop") == 0) {
    stopFlag = 1;

  } else if (strcmp(input, "reset") == 0) {
    resetFlag = 1;

  }
  // sscanf will save values divided by : in each variable
  else if (sscanf(input, "%2d:%2d:%2d%3s", &tempHours, &tempMinutes,
                  &tempSeconds, format) == 3) {
    // Check that hours, minutes, and seconds are within valid ranges
    if (tempHours < 0 || tempHours > 23 || tempMinutes < 0 ||
        tempMinutes > 59 || tempSeconds < 0 || tempSeconds > 59) {
    } else {
      // Set the user defined time
      userHours = tempHours;
      userMinutes = tempMinutes;
      userSeconds = tempSeconds;
      // Update counter
      convertToSeconds();
    }
  }
}

/*================================================================*/
/*            Initialize the UART communication                   */
/*================================================================*/
void UARTConfigure() {
  /* All system peripherals are disabled on start.
   To read and write to the registers they need to be enabled with
   SysCtlPeripheralEnable */
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)) {
  }

  // Enable the UART0 module
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0)) {
  }

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

  // Enables interrupts for UART
  UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

  // Enable the global interrupt and set the IRS
  UARTIntRegister(UART0_BASE, UARTIntHandler);

  // Specify UART0 for interrupts in the interrupt controller
  IntEnable(INT_UART0);
}
