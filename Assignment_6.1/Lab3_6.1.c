/*
 * ================================================================
 * File: Lab3_6.1.c
 * Author: Pontus Svensson, Carl Larsson
 * Email: psn19003@student.mdu.se, cln20001@student.mdu.se
 * Date: 2023-09-11
 * Description: The program showcases the functionality of using UART with
 * interrupts instead of polling. Enter a string in the serial terminal and the
 * program will echo it back.
 *
 * License: This code is distributed under the MIT License. visit
 * https://opensource.org/licenses/MIT for more information.
 * ================================================================
 */

/*================================================================*/
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"

volatile char inputBuffer[128];

/*================================================================*/
/*              The UART interrupt service routine                */
/*================================================================*/
void UARTIntHandler(void) {
  // Returns the current interrupt status
  uint32_t ui32Status = UARTIntStatus(UART0_BASE, true);

  // Clear the registers to prevent the handler getting called again upon
  // exiting the function
  UARTIntClear(UART0_BASE, ui32Status);

  // Prevent another interrupt from executing
  IntMasterDisable();
  // This function processes the UART input string
  UARTgets(inputBuffer, sizeof(inputBuffer));
  // Clear the screen to prevent scrolling
  UARTprintf("\033[2J");
  UARTprintf("\rECHO: %s\nInput:", inputBuffer);

  // Call to check what the input represents, start, stop, reset, or hh_mm_ss
  IntMasterEnable();
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
/*================================================================*/
int main(void) {
  // Start that uart module and start the UARTinterrupts module
  UARTConfigure();
  while (1) {
    // Loop to prevent the program from exiting
    // All functionality is handled by interrupt service routine
  }
}
