#ifndef UARTSetup_H
#define UARTSetup_H

#include <stdint.h>
extern void UARTConfigure();
extern uint32_t UARTCheckInput(char *buf);
extern void UARTReceiveInput(char *buf);

#endif
