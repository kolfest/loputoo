/*
 * applicationl.h
 *
 *  Created on: 3. apr 2017
 *      Author: Karl
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "system.h"
#include "timer.h"
void
APP_cyclic();

/***************************************************************************************************
 *	        Global Variable section  				                            				   *
 ***************************************************************************************************/
uint8 error;
extern uint8 payload_length;
uint8 cntr;
extern TimerStruct esimene;
#endif /* APPLICATION_H_ */
