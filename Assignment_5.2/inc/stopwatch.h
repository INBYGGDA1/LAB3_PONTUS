#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <stdint.h>
extern void STOPWATCHStart(void);
extern void STOPWATCHStop(void);
extern void STOPWATCHReset(void);
extern void convertToSeconds(void);
extern void INTHandler(void);
extern void SysTick_INIT(uint32_t loadValue);

#endif // STOPWATCH_H
