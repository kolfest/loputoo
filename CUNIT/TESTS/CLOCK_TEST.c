/*
 * CLOCK_TEST.c
 *
 *  Created on: 3. apr 2017
 *      Author: Karl
 */

#include "clock.h"
#include "CUnit/Basic.h"
uint16 E_DCOCTL = 0xC0;
uint16 E_BCSCTL1 = 0x86;
uint16 E_BCSCTL2 = 0x00;
uint16 E_BCSCTL3 = 0x05;
uint16 E_SR = 0x0080;
uint16 E_IFG1 = 0x00; /* reset with PUC */

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

