/*
 * FSM.h
 *
 *  Created on: 3. apr 2017
 *      Author: Karl
 */
#ifndef FSM_H_
#define FSM_H_

#include "system.h"

extern unsigned char currentStatus;
enum
{
  FSM_IDLE = 0, FSM_CONFIG = 1, FSM_CONFIG_ERROR = 2, FSM_SAMPLE = 3, NUMBER_OF_FSM_STATES
} commandType;

uint8
FSM_getStatus ();

uint8
FSM_initFSM (); /* returns FSM_IDLE on success, and FSM_CONFIG_ERROR on failure */


#endif /* FSM_H_ */
