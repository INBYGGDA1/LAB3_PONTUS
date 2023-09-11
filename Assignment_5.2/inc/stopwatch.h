#ifdef STOPWATCH_H
#define STOPWATCH_H

extern void STOPWATCHStart();
extern void STOPWATCHStop();
extern void STOPWATCHReset();
extern void INTHandler();
extern void SysTick_INIT();

#endif // STOPWATCH
