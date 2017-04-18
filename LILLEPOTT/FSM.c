/*
 * FSM.c
 *
 *  Created on: 3. apr 2017
 *      Author: Karl
 *      TODO: fix enums (currently there is comparison between commandType and CommandQueueReturns)
 *	* 100% code coverage reached
 */

#include "FSM.h"

FSMcmdInfoType  priv_commands[] =
{

  /*           		 sample_size,  	configuration 		*/
  /* MEASURE_IDLE */ 	{    0,  	ADC_IDLE},
  /* MEASURE_TEMP */	{    3,   	ADC_TEMP},
  /* MEASURE_HUMIDITY */{    1,   	ADC_HUMIDITY},
  /* MEASURE_BATTERY */	{    1,   	ADC_BATTERY},

};

#define FSM_COMMAND_BUFFER_SIZE (sizeof(buf) / sizeof(commandType))
#define COMMANDS_ARRAY_SIZE sizeof(priv_commands) / sizeof(FSMcmdInfoType)

static commandType currentCommand = MEASURE_IDLE; /*index for priv_commands[] */

static FSM_state currentState = FSM_IDLE; /* FSM state variable for getter functionality */

static FSMcmdInfoType cmdData; /*variable for information obtained from priv_commands using the currentCommand index variable */

commandType buf[5]; /*maximum 4 commands in queue */

static cmdQueue_t cmdQueue;



int o = 0;
int tulis[10];

float tulemus;

cmdQueue_t*
FSM_getCmdQueue()
{

  cmdQueue_t *cmdQueueptr = &cmdQueue;
  return cmdQueueptr;

}

FSM_state
FSM_getState()
{

  return currentState;

}

void
FSM_setState(FSM_state state)
{

  currentState = state;

}

commandType
FSM_getCmd()
{

  return currentCommand;

}

void
FSM_setCmd(commandType cmd)
{

  currentCommand = cmd;

}

commandType
FSM_readCmdFromQueue(cmdQueue_t * f)
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
      return p;

      if(f->size == f->tail ) /*wrap around */
          f->tail = 0;


    }
  return COMMAND_QUEUE_EMPTY;
}

uint8
FSM_addCmdToQueue (cmdQueue_t * f, commandType command)
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
      return COMMAND_QUEUE_FULL;

}

void
FSM_init()
/*******************************************************
 * initilizes command queue and other FSM variables
 *
 *
********************************************************/
{

  currentState = FSM_IDLE;
  cmdData = priv_commands[MEASURE_IDLE];
  FSM_initCmdQueue(&cmdQueue, 5);

}

void
FSM_initCmdQueue(cmdQueue_t *f, uint8 size)
/*******************************************************
** TODO: do proper returns
** initializes simple FIFO queue
**
********************************************************/
{

  if ((size > FSM_COMMAND_BUFFER_SIZE) || size == 0) /* do proper return, currently stalls as no memory is allocated?*/
    return ;

  f->head = 0;
  f->tail = 0;
  f->size = size;
  f->commands = buf;

}

void
FSM_cyclic()
/*******************************************************
** TODO:
**
**
********************************************************/
{

  switch (currentState)
  {

   case FSM_IDLE:

    currentCommand = FSM_readCmdFromQueue(&cmdQueue);
     if(currentCommand != COMMAND_QUEUE_EMPTY)
     {
	 currentState = FSM_CONFIG;
	 break;

     }

    currentState = FSM_IDLE;
    break;

   case FSM_CONFIG:
     //ADC_configureADC( CurrentCommandInfo.ADC_configuration);
     cmdData = priv_commands[currentCommand];
     currentState = FSM_MEASURE;
     break;

   case FSM_MEASURE:
     tulis[o] += 1;
     o++;
    //tulemus = ADC_measure();
    cmdData.sample_size -= 1;
    if (cmdData.sample_size == 0)
       {
	  currentCommand = FSM_readCmdFromQueue(&cmdQueue);
	   if (currentCommand == COMMAND_QUEUE_EMPTY)
	     {
		     currentState = FSM_IDLE;
		     break;
	     }
	   currentState = FSM_CONFIG;
	   break;
     }
    currentState = FSM_MEASURE;
    break;

  }

}


