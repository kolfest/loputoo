/*
 * ADC_TEST.c
 *
 *  Created on: 5. apr 2017
 *      Author: Karl
 */

#include "ADC.h"
#include "CUnit/Basic.h"
uint16 ADC10CTL00 = 0x0000;
void
test_ADC_measure()
{

  configuration = 0; /*invalid conf */
  CU_ASSERT(ADC_INVALID_CONVERSION_RESULT == ADC_measure(configuration));

  ADC10CTL1 |= ADC10BUSY; /*set ADC10 BUSY flag */
  configuration = ADC_TEMP; /*invalid conf */

  CU_ASSERT(ADC_INVALID_CONVERSION_RESULT == ADC_measure(configuration));
}

void
test_ADC_startConversion()
{

  /* ADC10 IS BUSY */
  ADC10CTL1 |= ADC10BUSY; /*set ADC10 BUSY flag */
  CU_ASSERT(ADC_BUSY == ADC_startConversion());

  /* ADC10 IS NOT BUSY */

  ADC10CTL1 &= ~(1<<0); /* clear ADC10 BUSY flag */
  CU_ASSERT(ADC_INIT_SUCCESS == ADC_startConversion());

}

void
test_ADC_configureADC ()
/** Test for ADC configuration
 **
 **
 **
 ********************************************************/
{

  /* VALID CONFIGURATION */

   configuration = ADC_TEMP;
   CU_ASSERT(ADC_CONFIG_SUCCESS == ADC_configureADC(configuration));

   configuration = ADC_HUMIDITY;
   CU_ASSERT(ADC_CONFIG_SUCCESS == ADC_configureADC(configuration));

   configuration = ADC_BATTERY;
   CU_ASSERT(ADC_CONFIG_SUCCESS == ADC_configureADC(configuration));

   /* INVALID CONFIGURATION */
   configuration = ADC_BUSY;
   CU_ASSERT(ADC_CONFIG_FAILURE == ADC_configureADC(configuration));



}

void
test_ADC_stopConversion()
{

  ADC10CTL00 &= ~ENC; /* Stop conversion */
  ADC10CTL00 &= ~(REFON + ADC10ON); /* Disable voltage refrence generator and ADC core */
  ADC_stopConversion();
  CU_ASSERT(ADC10CTL0 == ADC10CTL00);

}

void
test_ADC_getConversionResult()
{
  ADC10MEM = 0x11;
  CU_ASSERT(ADC_getConversionResult() == ADC10MEM);
}

void
test_checkIfADCBusy()
{

  ADC10CTL1 |= ADC10BUSY; /*set ADC10 BUSY flag */
  CU_ASSERT(1 == checkIfADCBusy());

  ADC10CTL1 &= ~(1<<0); /*clear ADC10 BUSY flag */
   CU_ASSERT(0 == checkIfADCBusy());

   ADC10CTL1 = INCH_10 + ADC10DIV_0;
   ADC10CTL1 |= ADC10BUSY; /*set ADC10 BUSY flag */
   CU_ASSERT(1 == checkIfADCBusy());

}


void
test_checkIfADCON()
{

  ADC10CTL0 |= ADC10ON; /*set ADC10 BUSY flag */
  CU_ASSERT(1 == checkIfADCON());
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


