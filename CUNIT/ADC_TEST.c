/*
 * ADC_TEST.c
 *
 *  Created on: 5. apr 2017
 *      Author: Karl
 */

#include "ADC.h"
#include "CUnit/Basic.h"

void
test_ADC_measure()
{

  ADC10CTL1 |= ADC10BUSY; /*set ADC10 BUSY flag */
  CU_ASSERT(ADC_MEASURE_TIMEOUT == ADC_measure(configuration));

}

void
test_ADC_startConversion()
{

  /* ADC10 IS BUSY */

  ADC10CTL1 |= ADC10BUSY; /*set ADC10 BUSY flag */
  CU_ASSERT(ADC_BUSY == ADC_startConversion());

  /* successful */
  ADC10CTL1 &= ~(1<<0); /* clear ADC10 BUSY flag */
  CU_ASSERT(ADC_INIT_SUCCESS == ADC_startConversion());


}

void
test_checkIsBitSet()
/*******************************************************
** Border cases not analysed
**
********************************************************/
{

  /**/

  uint16 registerrr = 0x00;
  uint8 position = 0x04;
  uint16 registerr = registerrr | position;
  CU_ASSERT( 1 == checkIsBitSet(registerr,  2));

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

  c_ADC_REF_SETTLE = 1; /* 1 for success, 0 for failure of the settling*/
  c_INVALID_CONFIGURATION = 0; /* 1:invalid, 0:valid */

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

  CU_ASSERT(ADC_INVALID_INPUT == ADC_configureADC(configuration));


  /* INVALID CONFIGURATION, REFRENCE SETTLES */

  c_ADC_REF_SETTLE = 1; /* 1 for success, 0 for failure of the settling*/
  c_INVALID_CONFIGURATION = 1; /* 1:invalid, 0:valid */

  CU_ASSERT(ADC_INVALID_INPUT == ADC_configureADC(configuration));

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


