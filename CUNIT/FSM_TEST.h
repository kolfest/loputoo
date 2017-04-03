/*
 * FSM_TEST.h
 *
 *  Created on: 3. apr 2017
 *      Author: Karl
 */

#ifndef FSM_TEST_H_
#define FSM_TEST_H_
#include "CUnit.h"
enum
{
  FSM_IDLE = 0, FSM_CONFIG = 1, NUMBER_OF_FSM_STATES
} commandType;
enum
{
  ADC_CONFIG_FAILURE = 0, ADC_CONFIG_SUCCESS = 1, NUMBER_OF_ADC_CONFIG_STATES
} commandType2;


unsigned char
ADC_configureADC (unsigned char configuration);

unsigned char
FSM_getStatus ();

unsigned char
FSM_confFSM ();

unsigned char
FSM_initFSM ();

int
init_FSMsuite (void);

int
clean_FSMsuite (void);

void
test_FSM_getStatus ();

void
test_ADC_configureADC ();

#endif /* FSM_TEST_H_ */
