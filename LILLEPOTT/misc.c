/*
 * misc.c
 *
 *  Created on: 13. apr 2017
 *      Author: Karl
 */
#include "misc.h"

uint8
checkIsBitSet(uint16 registerr, uint16 position)
/*******************************************************
** int position - position of the bit to be checked
** LSB is 0th bit
** Returns 1 if the bit is set
**
**
********************************************************/
{

  uint16 result = (((registerr)>>(position)) & 1);
  return result;

}



