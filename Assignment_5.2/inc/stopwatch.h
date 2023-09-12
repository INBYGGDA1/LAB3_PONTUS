#ifdef STOPWATCH_H

#include <stdint.h>
void STOPWATCHStart(char *userInput);
void STOPWATCHStop(void);
void STOPWATCHReset(char *userInput);
void INTHandler(void);
void SysTick_INIT();

#endif // STOPWATCH_H
