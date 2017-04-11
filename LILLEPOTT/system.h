/*
 * system.h
 *
 *  Created on: 27. märts 2017
 *      Author: Karl
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_
//#define TEST

#ifdef TEST
#include "device.h"
#else
#include "msp430g2553.h"
#endif

typedef unsigned long  uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;

typedef signed long    int32;
typedef signed short   int16;
typedef signed char    int8;



#endif /* SYSTEM_H_ */
