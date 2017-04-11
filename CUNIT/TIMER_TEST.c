/*
 * timer_TEST.c
 *
 *  Created on: 7. apr 2017
 *      Author: Karl
 */
#include "timer.h"
#include "CUnit/Basic.h"
TimerStruct refSettle = {0,250};
unsigned long long int timeT;
void
test_timer_getElapsedTime()
{

  /* start time < end time */
  timer_setTime(10);
  timer_initCount(&refSettle);
  timer_setTime(100);

  CU_ASSERT( 0 < timer_getElapsedTime(&refSettle));

  /*start time = end time, 5us not passed*/
  timer_setTime(10);
  CU_ASSERT(0 == timer_getElapsedTime(&refSettle));

  /*start time > end time */
  timer_setTime(0);
  CU_ASSERT(0 > timer_getElapsedTime(&refSettle));

}

void
test_timer_initCount()
{

  /* */
  timer_setTime(10);
  timer_initCount(&refSettle);
  CU_ASSERT(10 == refSettle.startTime);

}

void
test_timer_init()
{

}


int
init_timerSuite()
{
  return 0;
}

int
clean_timerSuite()
{
  return 0;
}
