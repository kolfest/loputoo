/*
 * WATCHDOG_TEST.c
 *
 *  Created on: 13. apr 2017
 *      Author: Karl
 */

#include "watchdog.h"
#include "CUnit/Basic.h"

void
test_WDT_setWatchdog()
{

  /*valid input */
  CU_ASSERT(WDT_SUCCESS == WDT_setWatchdog(400));
  CU_ASSERT(WDT_SUCCESS == WDT_setWatchdog(2));
  CU_ASSERT(WDT_SUCCESS == WDT_setWatchdog(31536000));


  /* out of bounds */
  CU_ASSERT(WDT_ERR == WDT_setWatchdog(0));
  CU_ASSERT(WDT_ERR == WDT_setWatchdog(-1));
  CU_ASSERT(WDT_ERR == WDT_setWatchdog(1));
  CU_ASSERT(WDT_ERR == WDT_setWatchdog(-31536001));
  CU_ASSERT(WDT_ERR == WDT_setWatchdog(31536001));
  CU_ASSERT(WDT_ERR == WDT_setWatchdog(31536552));


  WDT_setWatchdog(400);
  CU_ASSERT(WDT_getCurrentPeriod() == 400);


}

int
init_WDTsuite (void)
{
  return 0;
}

int
clean_WDTsuite (void)
{
  return 0;
}

