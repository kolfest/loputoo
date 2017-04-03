/*
 * device.h
 *
 *  Created on: 2. apr 2017
 *      Author: Karl
 */

#ifndef DEVICE_H_
#define DEVICE_H_

typedef unsigned long  uint32;
typedef unsigned short uint16;
typedef unsigned char  uint8;

typedef signed long    int32;
typedef signed short   int16;
typedef signed char    int8;

/* system registers */
unsigned int DCOCTL = 0x60;
unsigned int BCSCTL1 = 0x87;
unsigned int BCSCTL2 = 0x00;
unsigned int BCSCTL3 = 0x05;
unsigned int SR = 0x00;
unsigned int IFG1 = 0x02; /* reset with PUC */

/*expected register values */
unsigned int E_DCOCTL = 0xC0;
unsigned int E_BCSCTL1 = 0x86;
unsigned int E_BCSCTL2 = 0x00;
unsigned int E_BCSCTL3 = 0x05;
unsigned int E_SR = 0x0080;
unsigned int E_IFG1 = 0x00; /* reset with PUC */

/* system configuration bits */
unsigned int SCG1 = 0x0080;
unsigned int OFIFG = 0x02;
unsigned int CALBC1_1MHZ = 0x86;
unsigned int CALDCO_1MHZ = 0xC0;
unsigned int SELM_0 = 0x00;
unsigned int LFXT1S_0 = 0x00;
unsigned int DIVA_0 = 0x00;

/*
 * Stub for register setting


void _bis_SR_register( SCG1)
{

  SR |= SCG1;

}
 */
#endif /* DEVICE_H_ */
