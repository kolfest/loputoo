/*
 * FSM_TEST.c
 *
 *  Created on: 3. apr 2017
 *      Author: Karl
 */
#include "FSM_TEST.h"


#define ADC_TEMP 1
#define ADC_HUMIDITY 2
#define ADC_BATTERY 3
/* #define FAIL_TESTS */
unsigned char c_ADC_REF_SETTLE = 0; /* 1:settled, 0:unsettled, test double for refrence settling checking */
unsigned char c_INVALID_CONFIGURATION = 1; /* 1:invalid conf, 0:valid conf,  test double for valid input configuration checking*/
unsigned char currentStatus = FSM_IDLE;
unsigned char configuration = ADC_TEMP;
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


void
test_ADC_configureADC ()
/** Test for ADC configuration
 **
 **
 **
 ********************************************************/
{

  /* VALID CONFIGURATION, REFRENCE SETTLES */

  c_INVALID_CONFIGURATION = 0; /* 1:invalid, 0:valid */
  c_ADC_REF_SETTLE = 1; /* 1 for success, 0 for failure of the settling*/

  #ifdef FAIL_TESTS /* trying to FAIL asserts*/
    configuration = ADC_TEMP;
    CU_ASSERT(ADC_CONFIG_FAILURE == ADC_configureADC(configuration));

    configuration = ADC_HUMIDITY;
    CU_ASSERT(ADC_CONFIG_FAILURE == ADC_configureADC(configuration));

    configuration = ADC_BATTERY;
    CU_ASSERT(ADC_CONFIG_FAILURE == ADC_configureADC(configuration));

  #else/* trying to PASS asserts*/

    configuration = ADC_TEMP;
    CU_ASSERT(ADC_CONFIG_SUCCESS == ADC_configureADC(configuration));

    configuration = ADC_HUMIDITY;
    CU_ASSERT(ADC_CONFIG_SUCCESS == ADC_configureADC(configuration));

    configuration = ADC_BATTERY;
    CU_ASSERT(ADC_CONFIG_SUCCESS == ADC_configureADC(configuration));
  #endif


  /* VALID CONFIGURATION, REFRENCE DOES NOT SETTLE*/
  c_ADC_REF_SETTLE = 0; /* 1 for success, 0 for failure of the settling*/
  c_INVALID_CONFIGURATION = 0; /* 1:invalid, 0:valid */

  #ifdef FAIL_TESTS/* trying to FAIL asserts*/

  configuration = ADC_TEMP;
  CU_ASSERT(ADC_CONFIG_SUCCESS == ADC_configureADC(configuration));

  configuration = ADC_HUMIDITY;
  CU_ASSERT(ADC_CONFIG_SUCCESS == ADC_configureADC(configuration));

  configuration = ADC_BATTERY;
  CU_ASSERT(ADC_CONFIG_SUCCESS == ADC_configureADC(configuration));

  #else/* trying to PASS asserts*/

    configuration = ADC_TEMP;
    CU_ASSERT(ADC_CONFIG_FAILURE == ADC_configureADC(configuration));

    configuration = ADC_HUMIDITY;
    CU_ASSERT(ADC_CONFIG_FAILURE == ADC_configureADC(configuration));

    configuration = ADC_BATTERY;
    CU_ASSERT(ADC_CONFIG_FAILURE == ADC_configureADC(configuration));
  #endif

  /* INVALID CONFIGURATION, REFRENCE DOES NOT SETTLE */
  c_ADC_REF_SETTLE = 0; /* 1 for success, 0 for failure of the settling*/
  c_INVALID_CONFIGURATION = 1; /* 1:invalid, 0:valid */

  #ifdef FAIL_TESTS/* trying to FAIL asserts*/

  CU_ASSERT(ADC_CONFIG_SUCCESS == ADC_configureADC(configuration));

  #else /* trying to PASS asserts*/

    CU_ASSERT(ADC_CONFIG_FAILURE == ADC_configureADC(configuration));

  #endif


  /* INVALID CONFIGURATION, REFRENCE SETTLES */

  c_ADC_REF_SETTLE = 1; /* 1 for success, 0 for failure of the settling*/
  c_INVALID_CONFIGURATION = 1; /* 1:invalid, 0:valid */

  #ifdef FAIL_TESTS/* trying to FAIL asserts*/

    CU_ASSERT(ADC_CONFIG_SUCCESS == ADC_configureADC(configuration));

  #else /* trying to PASS asserts*/

    CU_ASSERT(ADC_CONFIG_FAILURE == ADC_configureADC(configuration));

  #endif

}

/* public functions*/
unsigned char
FSM_getStatus ()
{
  return currentStatus;
}

/*internal fuctions */
unsigned char
ADC_configureADC (unsigned char configuration)
{

  if (c_INVALID_CONFIGURATION) /* configuration checking test double, needs proper implementation */
    {
      return ADC_CONFIG_FAILURE;
    }

  if (c_ADC_REF_SETTLE)/* adc refrence settle test double, needs proper implementation */
   {
     switch(configuration)
     {
      case ADC_TEMP:
	/* implementation */
	return ADC_CONFIG_SUCCESS;
      case ADC_HUMIDITY:
	/* implementation */
	return ADC_CONFIG_SUCCESS;
      case ADC_BATTERY:
	/* implementation */
	return ADC_CONFIG_SUCCESS;
     }
   }
  return ADC_CONFIG_FAILURE;
}

unsigned char
FSM_initFSM ()
{
  currentStatus = FSM_CONFIG;

  return currentStatus;

}

unsigned char
FSM_confFSM ()
{

  if(ADC_configureADC(configuration) == ADC_CONFIG_FAILURE)
   {
     currentStatus = FSM_CONFIG;
     /* init FSM again, refrence settling failed */
   }
  currentStatus = FSM_IDLE; /*successful configuration*/

  return currentStatus;

}

int
init_FSMsuite (void)
{
  c_ADC_REF_SETTLE = 0;
  c_INVALID_CONFIGURATION = 1;
  return 0;
}

int
clean_FSMsuite (void)
{
  c_ADC_REF_SETTLE = 0;
  c_INVALID_CONFIGURATION = 1;

  return 0;
}
