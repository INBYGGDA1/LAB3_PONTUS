#ifdef STOPWATCH_H
#define STOPWATCH_H

extern void STOPWATCHStart(char *userInput);
extern void STOPWATCHStop();
extern void STOPWATCHReset(char *userInput);
extern void *INTHandler();
extern void SysTick_INIT();

#endif // STOPWATCH_H
