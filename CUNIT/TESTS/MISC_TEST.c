/*
 * MISC_TEST.c
 *
 *  Created on: 13. apr 2017
 *      Author: Karl
 */


#include "misc.h"
#include "CUnit/Basic.h"
void
test_checkIsBitSet()
/*******************************************************
** Border cases not analysed
**
********************************************************/
{

  /**/

  uint16 registerrr = 0x00;
  uint8 position = 0x01;
  uint16 registerr = registerrr | position;
  CU_ASSERT( 1 == checkIsBitSet(registerr,  0));

}
