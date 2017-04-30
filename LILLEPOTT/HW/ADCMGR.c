/*
 * ADCMGR.c
 *
 *  Created on: 3. apr 2017
 *      Author: Karl
 *      TODO:
 *      	fix enums (currently there is comparison between commandType and CommandQueueReturns)
 *			100% code coverage reached
 *			Proper buffer for measured values (for async processing?)
 */

/** @file
**	\brief Documentation for ADCMGR module
@startuml{ADCMGR_STATECHART.png}
	[*] --> ADCMGR_IDLE
	ADCMGR_IDLE-->ADCMGR_IDLE: cmdqueue == EMPTY
	ADCMGR_IDLE --> ADCMGR_CONFIG: cmdqueue != EMPTY
	ADCMGR_CONFIG:ADC_configureADC(c_cmd.configuration); c_command = readCmdFromQueue();
	ADCMGR_CONFIG --> ADCMGR_MEASURE
	ADCMGR_MEASURE: ADC_measure();
	ADCMGR_MEASURE--> ADCMGR_MEASURE:ADC_measure();/ --cmdqueue[n].sample_size;
	ADCMGR_MEASURE--> ADCMGR_IDLE: c_command.sample_size==0 && cmdqueue == EMPTY
	ADCMGR_MEASURE--> ADCMGR_CONFIG: c_command.sample_size==0 && cmdqueue != EMPTY
@enduml
**
**
**/

#include "ADCMGR.h"

const ADCMGRcmdInfoType  priv_commands[] =
{

  /**<           		 sample_size,  	configuration 		*/
  /**< MEASURE_IDLE */ 	{    0,  	ADC_IDLE},
  /**< MEASURE_TEMP */	{    1,   	ADC_TEMP},
  /**< MEASURE_HUMIDITY */{    1,   	ADC_HUMIDITY},
  /**< MEASURE_BATTERY */	{    1,   	ADC_BATTERY},

};


#define ADCMGR_COMMAND_BUFFER_SIZE (sizeof(buf) / sizeof(commandType)) /**< command buffer size */
#define COMMANDS_ARRAY_SIZE sizeof(priv_commands) / sizeof(ADCMGRcmdInfoType) /**< number of commands for ADCMGR */

static commandType currentCommand = MEASURE_IDLE; /**<current command of ADCMGR, used as a index index for priv_commands[] */

static ADCMGR_state currentState = ADCMGR_IDLE; /**< ADCMGR state variable for getter functionality */

static ADCMGRcmdInfoType cmdData; /**< variable for information obtained from priv_commands using the currentCommand index variable */

static commandType buf[4]; /**< command index storage, maximum 5 in queue */

static cmdQueue_t cmdQueue; /**< commandqueue */


void
ADCMGR_initCmdQueue(cmdQueue_t * f, uint8 size);

commandType
ADCMGR_readCmdFromQueue(cmdQueue_t * f);


uint16 o = 0; /**< variable for result buffer */
uint16 h = 0; /**< variable for result buffer */
uint16 b = 0; /**< variable for result buffer */

uint16 TEMP_BUF[10]; /**< result buffer */
uint16 HUM_BUF[10]; /**< result buffer */
uint16 BATTERY_BUF[10]; /**< result buffer */

uint16 battery = 0; /**< currently used result storing variable for battery level measurement */
uint16 temperature = 0; /**< currently used result storing variable for temperature measurement */
uint16 humidity = 0; /**< currently used result storing variable for humidity measurement */

cmdQueue_t*
ADCMGR_getCmdQueue()
{

  cmdQueue_t *cmdQueueptr = &cmdQueue;
  return cmdQueueptr;

}

ADCMGR_state
ADCMGR_getState()
{

  return currentState;

}

void
ADCMGR_setState(ADCMGR_state state)
{

  currentState = state;

}

commandType
ADCMGR_getCmd()
{

  return currentCommand;

}

void
ADCMGR_setCmd(commandType cmd)
{

  currentCommand = cmd;

}

commandType
ADCMGR_readCmdFromQueue(cmdQueue_t * f)
/*******************************************************
** TODO:
**
**
********************************************************/
{

  commandType p;
  if(f->head != f->tail)
    {

      p = f->commands[f->tail];
      f->tail++;

      if(f->size == f->tail ) /*wrap around */
          f->tail = 0;

      return p;
    }
  return COMMAND_QUEUE_EMPTY;
}

uint8
ADCMGR_addCmdToQueue (cmdQueue_t * f, commandType command)
/*******************************************************
** TODO: valid input checking
** Returns COMMAND_QUEUE_FULL when queue maximum size reached
**
********************************************************/
{

  if( (f->head + 1 == f->tail) || /* full, avoid overwriting */
      ( (f->head + 1 == f->size) && (f->tail == 0) ) ) /* full, avoid overwriting*/
	{
	  return COMMAND_QUEUE_FULL;
	}
	else
	{
	  f->commands[f->head] = command;
	  f->head++;
	  if( f->head == f->size ) /* head wraparound */
	    {
	      f->head = 0;
	    }
	    return COMMAND_ADDED;
	}

}

void
ADCMGR_init()
/*******************************************************
 * initilizes command queue and other ADCMGR variables
 *
 *
********************************************************/
{

  currentState = ADCMGR_IDLE;
  cmdData = priv_commands[MEASURE_IDLE];
  ADCMGR_initCmdQueue(&cmdQueue, 4);

}

void
ADCMGR_initCmdQueue(cmdQueue_t *f, uint8 size)
/*******************************************************
** TODO: do proper returns
** initializes simple FIFO queue
**
********************************************************/
{

  if ((size > ADCMGR_COMMAND_BUFFER_SIZE) || size == 0) /* do proper return, currently stalls as no memory is allocated?*/
    return ;

  f->head = 0;
  f->tail = 0;
  f->size = size;
  f->commands = buf;

}

void
ADCMGR_cyclic()
/*******************************************************
** TODO:
**
**
********************************************************/
{

  switch (currentState)
  {

   case ADCMGR_IDLE:

    currentCommand = ADCMGR_readCmdFromQueue(&cmdQueue);
     if(currentCommand != COMMAND_QUEUE_EMPTY)
     {
	 currentState = ADCMGR_CONFIG;
	 break;
     }

    currentState = ADCMGR_IDLE;
    break;

   case ADCMGR_CONFIG:
     cmdData = priv_commands[currentCommand];
     ADC_configureADC(cmdData.ADC_configuration);
     currentState = ADCMGR_MEASURE;
     break;

   case ADCMGR_MEASURE:
	if(cmdData.ADC_configuration == ADC_TEMP)
	{
		temperature = ADC_measure();
    	o++;
	}
	if(cmdData.ADC_configuration == ADC_HUMIDITY)
	{
		humidity = ADC_measure();
    	h++;
	}
	if(cmdData.ADC_configuration == ADC_BATTERY)
	{
		battery = ADC_measure();
    	b++;
	}
    cmdData.sample_size -= 1;
    if (cmdData.sample_size == 0)
       {
	  currentCommand = ADCMGR_readCmdFromQueue(&cmdQueue);
	   if (currentCommand == COMMAND_QUEUE_EMPTY)
	     {
		     currentState = ADCMGR_IDLE;
		     o=0;
		     b=0;
		     h=0;
		     break;
	     }
	   currentState = ADCMGR_CONFIG;
	   break;
     }
    currentState = ADCMGR_MEASURE;
    break;

  }

}


