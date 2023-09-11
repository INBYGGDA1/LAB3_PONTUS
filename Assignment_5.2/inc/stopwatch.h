#ifdef STOPWATCH_H
#define STOPWATCH_H

extern void STOPWATCHStart(char *userInput);
extern void STOPWATCHStop(void);
extern void STOPWATCHReset(char *userInput);
extern void *INTHandler(void);
extern void SysTick_INIT(uint32_t loadValue);

#endif // STOPWATCH_H
