/*
 * FSM_TEST.c
 *
 *  Created on: 3. apr 2017
 *      Author: Karl
 */
#include "FSM.h"
#include "CUnit/Basic.h"

#define ADC_TEMP 1
#define ADC_HUMIDITY 2
#define ADC_BATTERY 3
/* #define FAIL_TESTS */

//unsigned char c_;

/* public fuction tests*/
void
test_FSM_getStatus ()
{

  /*test the getter for status*/
  CU_ASSERT(FSM_IDLE == FSM_getStatus());

  currentStatus = FSM_CONFIG;
  CU_ASSERT(FSM_CONFIG == FSM_getStatus());
}


/* internal function tests*/
void
test_FSM_intitFSM ()
{
  /*test the getter for status*/
  CU_ASSERT(FSM_IDLE == FSM_getStatus());
}


int
init_FSMsuite (void)
{

  return 0;
}

int
clean_FSMsuite (void)
{


  return 0;
}
