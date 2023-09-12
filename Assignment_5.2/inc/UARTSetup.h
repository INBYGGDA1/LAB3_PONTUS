#ifdef UARTSetup_H

#include <stdint.h>
void UARTConfigure();
uint32_t UARTCheckInput(char *buf);
void UARTReceiveInput(char *buf);

#endif
