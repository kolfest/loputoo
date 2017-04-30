/*
 * timer.h
 *
 *  Created on: 23. apr 2017
 *      Author: Karl
 */
/*
 * timer.h
 *
 *  Created on: 27. märts 2017
 *      Author: Karl
 */
#include "system.h"
#ifndef TIMER_H_
#define TIMER_H_


typedef struct {unsigned long long int startTime;
		unsigned long long int endTime;
		unsigned long long int elapsed;} TimerStruct;

void
timer_init(void);

void
timer_initCount(volatile TimerStruct *timer);

void
timer_setTime(unsigned long long int timeE);

long long int
timer_getElapsedTime(volatile TimerStruct *timer);

unsigned long long int
timer_getTime();

extern TimerStruct esimenee;
#endif /* TIMER_H_ */
