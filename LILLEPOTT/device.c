/*
 * device.c
 *
 *  Created on: 5. apr 2017
 *      Author: Karl
 */

#include "device.h"

/* init */
uint16 DCOCTL  = 0x60;
uint16 BCSCTL1  = 0x87;
uint16 BCSCTL2  = 0x00;
uint16 BCSCTL3 = 0x05;
uint16 SR = 0x00;
uint16 IFG1 = 0x02; /* reset with PUC */

void _bis_SR_register_double( uint16 SCG1)
{

  SR |= SCG1;

}

