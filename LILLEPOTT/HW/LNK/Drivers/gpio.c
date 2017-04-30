/*
 * gpio.c
 *
 *  Created on: 18. märts 2017
 *      Author: Karl
 */

/** @file
**	\brief
**
**
**
**/
#include "gpio.h"

void GPIO_setup()
/*!Configuring pins for minimal current consumption, for more info see family guide section 8.2.8
 * Used by RF module: P1.3 - P1.7, P2.0-P2.1, P2.5
 * Unused: P1.0, P2.2-P2.4, P2.6-P2.7
 *
 */
{
	 P3DIR = 0xFF; /* set all of the ports pins to output direction */
	 P3OUT = 0x00; /* pin outputs to low */

	//P1DIR =
	//P2SEL =
	//P2SEL2 =

	//P2DIR =
	//P2SEL =
	//P2SEL2 =
}


