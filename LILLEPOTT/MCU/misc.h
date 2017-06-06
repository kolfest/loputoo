/*
 * misc.h
 *
 *  Created on: 13. apr 2017
 *      Author: Karl
 */

#ifndef MISC_H_
#define MISC_H_

//#include "LNK/Drivers/system.h"
#include "system.h"
typedef uint16 crc;
uint8 MISC_checkIsBitSet(uint16 registerr, uint16 position);
crc MISC_crc(uint8 const message[], int nBytes);

#endif /* _MISC_H_ */
