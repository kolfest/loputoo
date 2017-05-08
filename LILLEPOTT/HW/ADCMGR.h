/*
 * ADCMGR.h
 *
 *  Created on: 3. apr 2017
 *      Author: Karl
 */
#ifndef ADCMGR_H_
#define ADCMGR_H_

#include "LNK/Drivers/system.h"
#include "ADC.h"

typedef enum commandType
{

  MEASURE_IDLE = 0,
  MEASURE_TEMP = 1,
  MEASURE_HUMIDITY = 2,
  MEASURE_BATTERY = 3,

  NUMBER_OF_ADCMGR_COMMANDS

}commandType;

#define MEASURE_IDLEE 0
#define MEASURE_TEMPP 1

extern uint16 TEMP_BUF[10];
extern uint16 HUM_BUF[10];
extern uint16 BATTERY_BUF[10];


typedef enum ADCMGR_state
{

  ADCMGR_IDLE = 0,
  ADCMGR_CONFIG = 1,
  ADCMGR_MEASURE = 2,
  NUMBER_OF_ADCMGR_STATES

}ADCMGR_state;


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
 ADC_ConfType ADC_configuration;

}ADCMGRcmdInfoType;


typedef struct {

    commandType *commands;
    uint8 head;
    uint8 tail;
    uint8 size;

} cmdQueue_t;

uint16
ADCMGR_getTemp();

uint16
ADCMGR_getHum();

uint16
ADCMGR_getBattery();

uint8
ADCMGR_addCmdToQueue (cmdQueue_t * f, commandType command);

ADCMGR_state
ADCMGR_getState();

void
ADCMGR_setCmd(commandType cmd);

void
ADCMGR_setState(ADCMGR_state state);

commandType
ADCMGR_getCmd();

cmdQueue_t*
ADCMGR_getCmdQueue();

void
ADCMGR_init();

void
ADCMGR_cyclic();

#endif /* ADCMGR_H_ */
