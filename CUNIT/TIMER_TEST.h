/*
 * timer_TEST.h
 *
 *  Created on: 7. apr 2017
 *      Author: Karl
 */

#ifndef TIMER_TEST_H_
#define TIMER_TEST_H_
#include "CUnit.h"

void
test_timer_getElapsedTime();

void
test_timer_initCount();

void
test_timer_init();

int
init_timerSuite();

int
clean_timerSuite();



#endif /* TIMER_TEST_H_ */
