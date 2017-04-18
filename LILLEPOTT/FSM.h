/*
 * FSM.h
 *
 *  Created on: 3. apr 2017
 *      Author: Karl
 */
#ifndef FSM_H_
#define FSM_H_

#include "system.h"
#include "ADC.h"

typedef enum commandType
{

  MEASURE_IDLE = 0,
  MEASURE_TEMP = 1,
  MEASURE_HUMIDITY = 2,
  MEASURE_BATTERY = 3,

  NUMBER_OF_FSM_COMMANDS

}commandType;

#define MEASURE_IDLEE 0
#define MEASURE_TEMPP 1

extern tulis[10];

typedef enum FSM_state
{

  FSM_IDLE = 0,
  FSM_CONFIG = 1,
  FSM_MEASURE = 2,
  NUMBER_OF_FSM_STATES

}FSM_state;


typedef enum commandQueueReturns
{
  COMMAND_QUEUE_EMPTY = 4,
  COMMAND_QUEUE_FULL = 5,
  COMMAND_ADDED = 6,

  NUMBER_OF_COMMAND_QUEUE_RETURNS

}commandQueueReturns;

typedef struct
{

 uint8 sample_size;
 ADC_confType ADC_configuration;

}FSMcmdInfoType;

typedef struct {

    commandType *commands;
    uint8 head;
    uint8 tail;
    uint8 size;

} cmdQueue_t;

uint8
FSM_addCmdToQueue (cmdQueue_t * f, commandType command);

commandType
FSM_readCmdFromQueue(cmdQueue_t * f);

FSM_state
FSM_getState();

void
FSM_setCmd(commandType cmd);

void
FSM_setState(FSM_state state);

commandType
FSM_getCmd();

cmdQueue_t*
FSM_getCmdQueue();

void
FSM_initCmdQueue(cmdQueue_t * f, uint8 size);

void
FSM_init();

void
FSM_cyclic();

#endif /* FSM_H_ */
