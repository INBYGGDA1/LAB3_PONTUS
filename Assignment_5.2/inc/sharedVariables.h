#ifndef SHARED_VARIABLES_H
#define SHARED_VARIABLES_H

#include <stdint.h>

extern volatile uint32_t stopwatch_time;
extern char inputBuffer[];
extern volatile uint32_t hours, minutes, seconds;
extern volatile uint32_t userHours, userMinutes, userSeconds;
extern volatile uint32_t startFlag, stopFlag, resetFlag;
extern volatile uint32_t countFlag;
extern volatile uint32_t stopwatch_time;

#endif
