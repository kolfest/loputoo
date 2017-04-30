/*
 * timer.c
 *
 *  Created on: 23. apr 2017
 *      Author: Karl
 */

/*
 * timer.c
 *
 *  Created on: 27. märts 2017
 *      Author: Karl
 */
#include "timer.h"

volatile unsigned long long int time;


void
timer_setTime(unsigned long long int timeE)
/**
** For testing only
**
**
**/
{
  time = timeE;
}

unsigned long long int
timer_getTime()
{
  return time;
}

void
timer_initCount(volatile TimerStruct *timer)
/**
**
**  \return
**/
{
  timer->startTime = time;
}

long long int
timer_getElapsedTime(volatile TimerStruct *timer)
/** Get elapsed time with 150us divisions
**
**  \return negative value when configuration error by timer_initCount
**  \return elapsedTime- time passed since timer_initCount call
**/
{

  timer->endTime = time;
  timer->elapsed = (timer->endTime - timer->startTime);
  return (timer->elapsed);

}

void
timer_init(void)
{

  CCTL0 = CCIE; /* enable CCR0 interrupts, CCTL0 is a substitute to TACCTL0 which in turn is a substitute for  TA0CCTL0  Timer A Capture/Compare Control 0 */
  CCR0 = 150; /* one 150us cycle */
  TACTL = TASSEL_2 + MC_1; /* select SMCLK as source, UP mode */
  _BIS_SR(GIE); /* enable global interrupts, take to somewhere else? */

}

void
timer_stopTimer()
{

  //TACTL = MC_0;

}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{

  time++;

}


