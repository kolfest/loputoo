/*
 * CUnit.c
 *
 *  Created on: 12. dets 2016
 *      Author: Karl
 *      TODO: *proper refactoring of tests to suites
 *      *add usage of suite initializers and cleaners
 */

#include "CUnit/Basic.h"

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */

#include "TESTS/ADC_TEST.h"
#include "TESTS/MISC_TEST.h"
#include "TESTS/WATCHDOG_TEST.h"
#include "TESTS/FSM_TEST.h"

int main()
{

  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry ())
    return CU_get_error ();

  /* add a suite to the registry */
  pSuite = CU_add_suite ("Suite_1", init_ADCsuite, clean_ADCsuite);

  if (NULL == pSuite)
    {
      CU_cleanup_registry ();
      return CU_get_error ();
    }

  /* add the tests to the suite */
  if ((NULL == CU_add_test (pSuite, "test of ADC_measure",  test_ADC_measure)) ||
      (NULL == CU_add_test (pSuite, "test of ADC_startConversion",  test_ADC_startConversion)) ||
      (NULL == CU_add_test (pSuite, "test of ADC_configureADC",  test_ADC_configureADC)) ||
      (NULL == CU_add_test (pSuite, "test of checkIsBitSet",  test_checkIsBitSet)) ||
      (NULL == CU_add_test (pSuite, "test of checkIfADCBusy",  test_checkIfADCBusy)) ||
      (NULL == CU_add_test (pSuite, "test of checkIfADCON",  test_checkIfADCON)) ||
      (NULL == CU_add_test (pSuite, "test of stopConversion",  test_ADC_stopConversion)) ||
      (NULL == CU_add_test (pSuite, "test of getconversionresult",  test_ADC_getConversionResult)) ||
      (NULL == CU_add_test (pSuite, "test of setwatchdog",  test_WDT_setWatchdog)) ||
      (NULL == CU_add_test (pSuite, "test of initCmdQueue",  test_FSM_initCmdQueue)) ||
      (NULL == CU_add_test (pSuite, "test of addcmdtoqueue",  test_FSM_addCmdToQueue)) ||
      (NULL == CU_add_test (pSuite, "test of test_FSM_readCmdFromQueue",  test_FSM_readCmdFromQueue)) ||
      (NULL == CU_add_test (pSuite, "test of test_FSM_getState",  test_FSM_getState)) ||
      (NULL == CU_add_test (pSuite, "test of test_FSM_init",  test_FSM_init)) ||
      (NULL == CU_add_test (pSuite, "test of test_FSM_getCmd",  test_FSM_getCmd)) ||
      (NULL == CU_add_test (pSuite, "test of test_FSM_setCmd",  test_FSM_setCmd)) ||
      (NULL == CU_add_test (pSuite, "test of test_FSM_cyclic",  test_FSM_cyclic)))

    {
      CU_cleanup_registry ();
      return CU_get_error ();
    }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode (CU_BRM_VERBOSE);
  CU_basic_run_tests ();
  CU_cleanup_registry ();
  return CU_get_error ();
}

