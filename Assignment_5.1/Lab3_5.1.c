/*
 * ================================================================
 * File: Lab3_5.1.c
 * Author: Pontus Svensson
 * Date: 2023-09-11
 * Description: Configures TM4C129 to enable and configure UART for
 * communication using a serial terminal
 *
 * License: This code is distributed under the MIT License. visit
 * https://opensource.org/licenses/MIT for more information.
 * ================================================================
 */

/*================================================================*/
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "utils/uartstdio.c"

/*================================================================*/
// Configure the UART.
void ConfigureUART() {
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
int main(int argc, char *argv[]) {

  char uart_string_to_receive[256];

  // Initialize the UART
  ConfigureUART();

  while (1) {
    // Writes a string to the serial terminal
    UARTprintf("Enter a message: ");
    // Waits for input in the serial terminal
    UARTgets(uart_string_to_receive, sizeof(uart_string_to_receive));
    // Writes a string to the serial terminal
    UARTprintf("ECHO: %s\n", uart_string_to_receive);
  }
}
