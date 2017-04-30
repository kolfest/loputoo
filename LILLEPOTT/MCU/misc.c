/*
 * misc.c
 *
 *  Created on: 13. apr 2017
 *      Author: Karl
 */

/** @file
**	\brief
**
**
**
**/
#include "misc.h"

uint8
checkIsBitSet(
				uint16 registerr, /**< System register to be checked*/
				uint16 position) /**< bit to be checked, LSB is 0th bit*/
/*!******************************************************
** int position - position of the bit to be checked
** LSB is 0th bit
** Returns 1 if the bit is set
**
**\return 1 when set, 0 otherwise
********************************************************/
{

  uint16 result = (((registerr)>>(position)) & 1);
  return result;

}
