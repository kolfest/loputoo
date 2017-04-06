/*
 * FSM.c
 *
 *  Created on: 3. apr 2017
 *      Author: Karl
 */

#include "FSM.h"

unsigned char currentStatus = FSM_IDLE;
uint8
FSM_getStatus ()
{
  return currentStatus;
}

uint8
FSM_initFSM ()
{
  currentStatus = FSM_CONFIG;

  return currentStatus;

}



