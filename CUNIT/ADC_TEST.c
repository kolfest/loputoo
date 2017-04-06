/*
 * ADC_TEST.c
 *
 *  Created on: 5. apr 2017
 *      Author: Karl
 */

#include "ADC.h"
#include "CUnit/Basic.h"

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

   configuration = ADC_TEMP;
   CU_ASSERT(ADC_CONFIG_SUCCESS == ADC_configureADC(configuration));

   configuration = ADC_HUMIDITY;
   CU_ASSERT(ADC_CONFIG_SUCCESS == ADC_configureADC(configuration));

   configuration = ADC_BATTERY;
   CU_ASSERT(ADC_CONFIG_SUCCESS == ADC_configureADC(configuration));

  /* VALID CONFIGURATION, REFRENCE DOES NOT SETTLE*/
  c_ADC_REF_SETTLE = 0; /* 1 for success, 0 for failure of the settling*/
  c_INVALID_CONFIGURATION = 0; /* 1:invalid, 0:valid */


  configuration = ADC_TEMP;
  CU_ASSERT(ADC_CONFIG_FAILURE == ADC_configureADC(configuration));

  configuration = ADC_HUMIDITY;
  CU_ASSERT(ADC_CONFIG_FAILURE == ADC_configureADC(configuration));

  configuration = ADC_BATTERY;
  CU_ASSERT(ADC_CONFIG_FAILURE == ADC_configureADC(configuration));


  /* INVALID CONFIGURATION, REFRENCE DOES NOT SETTLE */
  c_ADC_REF_SETTLE = 0; /* 1 for success, 0 for failure of the settling*/
  c_INVALID_CONFIGURATION = 1; /* 1:invalid, 0:valid */

  CU_ASSERT(ADC_CONFIG_FAILURE == ADC_configureADC(configuration));


  /* INVALID CONFIGURATION, REFRENCE SETTLES */

  c_ADC_REF_SETTLE = 1; /* 1 for success, 0 for failure of the settling*/
  c_INVALID_CONFIGURATION = 1; /* 1:invalid, 0:valid */

  CU_ASSERT(ADC_CONFIG_FAILURE == ADC_configureADC(configuration));
}


int
init_ADCsuite (void)
{
  return 0;
}

int
clean_ADCsuite (void)
{
  return 0;
}


