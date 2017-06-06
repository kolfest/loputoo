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
#define WIDTH  (8 * sizeof(crc))
#define TOPBIT (1 << (WIDTH - 1))
#define POLYNOMIAL 0xBAAD
uint8
MISC_checkIsBitSet(
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

crc
MISC_crc(uint8 const message[], int nBytes)
{
    crc  remainder = 0;	

    for (int byte = 0; byte < nBytes; ++byte)
    {

        remainder ^= (message[byte] << (WIDTH - 8));
        for (uint8 bit = 8; bit > 0; --bit)
        {

            if (remainder & TOPBIT)
            {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }
    return (remainder);
}

