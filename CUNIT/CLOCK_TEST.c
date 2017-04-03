/*
 * CLOCK_TEST.c
 *
 *  Created on: 3. apr 2017
 *      Author: Karl
 */
#include "CLOCK_TEST.h"


void
test_initClk (void)
{

  CU_ASSERT_EQUAL(SR, E_SR);
  CU_ASSERT_EQUAL(DCOCTL, E_DCOCTL);
  CU_ASSERT_EQUAL(BCSCTL1, E_BCSCTL1);
  CU_ASSERT_EQUAL(BCSCTL2, E_BCSCTL2);
  CU_ASSERT_EQUAL(BCSCTL3, E_BCSCTL3);
  CU_ASSERT_EQUAL(IFG1, E_IFG1);

}

