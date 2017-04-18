/*
 * FSM_TEST.c
 *
 *  Created on: 3. apr 2017
 *      Author: Karl
 */
#include "FSM.h"
#include "CUnit/Basic.h"

extern tulis[10];

void
test_FSM_getState ()
{
  FSM_setState(FSM_CONFIG);
  CU_ASSERT(FSM_getState() == FSM_CONFIG);

}

void
test_FSM_setState ()
{
 /* write invalid input tests */

  /*proper input */

}

void
test_FSM_setCmd()
{

  FSM_setCmd(MEASURE_IDLE);
  CU_ASSERT(FSM_getCmd() == MEASURE_IDLE);

}

void
test_FSM_init()
{
  FSM_init();
  cmdQueue_t *test;
  test = FSM_getCmdQueue();
  CU_ASSERT(test->head == 0);
  CU_ASSERT(test->tail == 0);
  CU_ASSERT(FSM_getState() == FSM_IDLE);
  /*write test to see if buffer size is correct*/
}


void
test_FSM_emptyCmdQueue()
{

}

void
test_FSM_getCurrentCmd()
{

}

void
test_FSM_getCurrentQueueSize()
{

}

void
test_FSM_initCmdQueue()
{


  cmdQueue_t *p;
  FSM_initCmdQueue(p, 1);

  CU_ASSERT(p->size == 1);
  CU_ASSERT(p->tail== 0);
  CU_ASSERT(p->head== 0);

  FSM_initCmdQueue(p, 4);
  CU_ASSERT(p->size == 4);

  cmdQueue_t *p2;
  FSM_initCmdQueue(p2, 6); /* add return for invalid input? */


  cmdQueue_t *test = FSM_getCmdQueue();
  /*see if memory for queue was reserved? */
  CU_ASSERT_PTR_NOT_NULL(test);

  FSM_initCmdQueue(test, 5);
  while(COMMAND_QUEUE_FULL!=FSM_addCmdToQueue(test, MEASURE_TEMP));
  //FSM_addCmdToQueue(test, MEASURE_TEMP);
  //FSM_addCmdToQueue(test, MEASURE_HUMIDITY);
 // FSM_addCmdToQueue(test, MEASURE_BATTERY);
  //FSM_addCmdToQueue(test, MEASURE_TEMP);

  CU_ASSERT( *(test->commands) == MEASURE_TEMP);
  CU_ASSERT( *((test->commands)+1) == MEASURE_TEMP);
  CU_ASSERT( *((test->commands)+2) == MEASURE_TEMP);
  CU_ASSERT( *((test->commands)+3) == MEASURE_TEMP);
  /*try to read outside of buffer */
  CU_ASSERT( *((test->commands)+4) == MEASURE_TEMP);

/*

  FSM_initCmdQueue(p, 6);
  CU_ASSERT(p->size == 6);

  FSM_initCmdQueue(p, 5);
  CU_ASSERT(p->size == 5);

  FSM_initCmdQueue(p, 0);
  CU_ASSERT(p->size == 0);

*/
}

void
test_FSM_addCmdToQueue()
{

  cmdQueue_t *p;
  //commandType e = MEASURE_TEMP;
  FSM_initCmdQueue(p, 4);
  CU_ASSERT(COMMAND_ADDED == FSM_addCmdToQueue(p, MEASURE_TEMP) );
  CU_ASSERT(p->head == 1);
  CU_ASSERT(*(p->commands) == MEASURE_TEMP);
  CU_ASSERT(COMMAND_ADDED == FSM_addCmdToQueue(p, MEASURE_TEMP) );
  CU_ASSERT(p->head == 2);
  CU_ASSERT(COMMAND_ADDED == FSM_addCmdToQueue(p, MEASURE_TEMP) );
  CU_ASSERT(p->head == 3);
  CU_ASSERT(COMMAND_QUEUE_FULL == FSM_addCmdToQueue(p, MEASURE_TEMP) );
  CU_ASSERT(COMMAND_QUEUE_FULL == FSM_addCmdToQueue(p, MEASURE_TEMP) );

}

void
test_FSM_getCmd()
{

  cmdQueue_t *test = FSM_getCmdQueue();
  CU_ASSERT_PTR_NOT_NULL(test);
  FSM_initCmdQueue(test, 5);
  while(COMMAND_QUEUE_FULL != FSM_addCmdToQueue(test, MEASURE_TEMP));

  /* finish tests */
  FSM_setCmd(MEASURE_IDLE);
  CU_ASSERT(FSM_getCmd() == MEASURE_IDLE);
  FSM_setCmd(MEASURE_TEMP);
  CU_ASSERT(FSM_getCmd() == MEASURE_TEMP);


}

void
test_FSM_readCmdFromQueue()
{

  /*empty queue*/
  cmdQueue_t *p;
  FSM_initCmdQueue(p, 4);
  CU_ASSERT(COMMAND_QUEUE_EMPTY == FSM_readCmdFromQueue(p));

  while(COMMAND_QUEUE_FULL != FSM_addCmdToQueue(p, MEASURE_TEMP));

  CU_ASSERT(MEASURE_TEMP == FSM_readCmdFromQueue(p));
  CU_ASSERT(MEASURE_TEMP == FSM_readCmdFromQueue(p));
  CU_ASSERT(MEASURE_TEMP == FSM_readCmdFromQueue(p));

  /*should be empty now */
  CU_ASSERT(COMMAND_QUEUE_EMPTY  == FSM_readCmdFromQueue(p));
  CU_ASSERT(COMMAND_QUEUE_EMPTY == FSM_readCmdFromQueue(p));

  /* normal */
  FSM_addCmdToQueue(p, MEASURE_TEMP);
  CU_ASSERT(MEASURE_TEMP == FSM_readCmdFromQueue(p));

}

void
test_FSM_cyclic()
{
    cmdQueue_t *test = FSM_getCmdQueue();
    /*see if memory for queue was reserved? */
    CU_ASSERT_PTR_NOT_NULL(test);
    FSM_init();
    //FSM_initCmdQueue(test, 5);
    /*add no commands to queue  FSM_IDLE->FSM_IDLE transition*/
    CU_ASSERT(FSM_getState()==FSM_IDLE);
    CU_ASSERT(FSM_getCmd()== MEASURE_IDLE);
    FSM_cyclic();
    CU_ASSERT(FSM_getState()==FSM_IDLE);

    /*add a command to queue FSM_IDLE->FSM_CONFIG->FSM_MEASURE->FSM_IDLE
    FSM_addCmdToQueue(test, MEASURE_TEMP);
    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_CONFIG);
    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_MEASURE);
    FSM_cyclic();
    CU_ASSERT(FSM_getCmd() == COMMAND_QUEUE_EMPTY);
    CU_ASSERT(FSM_getState() == FSM_IDLE);
    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_IDLE);
    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_IDLE);
    */

    /*add two commands to queue FSM_IDLE->FSM_CONFIG->FSM_MEASURE->FSM_CONF->FSM_MEASURE->FSM_IDLE*/
    /*
    FSM_addCmdToQueue(test, MEASURE_TEMP);
    FSM_addCmdToQueue(test, MEASURE_TEMP);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_CONFIG);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_MEASURE);

    FSM_cyclic();
    CU_ASSERT(FSM_getCmd() != COMMAND_QUEUE_EMPTY);
    CU_ASSERT(FSM_getCmd() == MEASURE_TEMP);
    CU_ASSERT(FSM_getState() == FSM_CONFIG);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_MEASURE);
    CU_ASSERT(FSM_getCmd() == MEASURE_TEMP);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_IDLE);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_IDLE);
    */

    /*add three commands to queue FSM_IDLE->FSM_CONFIG->FSM_MEASURE->FSM_CONF->
     * ->FSM_MEASUR->FSM_CONF->FSM_MEASURE->FSM_IDLE  */
   //while(COMMAND_QUEUE_FULL != FSM_addCmdToQueue(test, MEASURE_TEMP))
    /*
    FSM_addCmdToQueue(test, MEASURE_TEMP);
    FSM_addCmdToQueue(test, MEASURE_HUMIDITY);
    FSM_addCmdToQueue(test, MEASURE_TEMP);
    FSM_addCmdToQueue(test, MEASURE_TEMP);


    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_CONFIG);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_MEASURE);
    CU_ASSERT(FSM_getCmd() != COMMAND_QUEUE_EMPTY);

    FSM_cyclic();

    CU_ASSERT(FSM_getState() == FSM_CONFIG);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_MEASURE);
    CU_ASSERT(FSM_getCmd() != COMMAND_QUEUE_EMPTY);

    FSM_cyclic();

    CU_ASSERT(FSM_getState() == FSM_CONFIG);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_MEASURE);
    CU_ASSERT(FSM_getCmd() != COMMAND_QUEUE_EMPTY);
    CU_ASSERT(FSM_getCmd() == MEASURE_TEMP);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_CONFIG);
    CU_ASSERT(FSM_getCmd() == MEASURE_TEMP);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_MEASURE);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_IDLE);
    CU_ASSERT(FSM_getCmd() == COMMAND_QUEUE_EMPTY);

    */

    /* add command with 3 as sample size */
    /*
    FSM_addCmdToQueue(test, MEASURE_TEMP);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_CONFIG);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_MEASURE);
    CU_ASSERT(FSM_getCmd() != COMMAND_QUEUE_EMPTY);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_MEASURE);
    CU_ASSERT(FSM_getCmd() == COMMAND_QUEUE_EMPTY);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_MEASURE);
    CU_ASSERT(FSM_getCmd() == MEASURE_TEMP);

    FSM_cyclic();

    CU_ASSERT(FSM_getState() == FSM_IDLE);
    CU_ASSERT(FSM_getCmd() == COMMAND_QUEUE_EMPTY);

    FSM_cyclic();

    CU_ASSERT(FSM_getState() == FSM_IDLE);
    CU_ASSERT(FSM_getCmd() == COMMAND_QUEUE_EMPTY);

    FSM_cyclic();

    CU_ASSERT(FSM_getState() == FSM_IDLE);
    CU_ASSERT(FSM_getCmd() == COMMAND_QUEUE_EMPTY);

    CU_ASSERT(tulis[0] == 1);
    CU_ASSERT(tulis[1] == 1);
    CU_ASSERT(tulis[2] == 1);
    CU_ASSERT(tulis[3] == 1);
    CU_ASSERT(tulis[4] == 1); */



    /* add 2 commands with 3 as sample size */

    FSM_addCmdToQueue(test, MEASURE_TEMP);
    FSM_addCmdToQueue(test, MEASURE_TEMP);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_CONFIG);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_MEASURE);
    CU_ASSERT(FSM_getCmd() != COMMAND_QUEUE_EMPTY);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_MEASURE);
    CU_ASSERT(FSM_getCmd() != COMMAND_QUEUE_EMPTY);

    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_MEASURE);
    CU_ASSERT(FSM_getCmd() == MEASURE_TEMP);

    FSM_cyclic();

    CU_ASSERT(FSM_getState() == FSM_CONFIG);
    CU_ASSERT(FSM_getCmd() != COMMAND_QUEUE_EMPTY);

    FSM_cyclic();

    CU_ASSERT(FSM_getState() == FSM_MEASURE);
    CU_ASSERT(FSM_getCmd() != COMMAND_QUEUE_EMPTY);

    FSM_cyclic();

    CU_ASSERT(FSM_getState() == FSM_MEASURE);
    CU_ASSERT(FSM_getCmd() != COMMAND_QUEUE_EMPTY);

    FSM_cyclic();

    CU_ASSERT(FSM_getState() == FSM_MEASURE);
    CU_ASSERT(FSM_getCmd() != COMMAND_QUEUE_EMPTY);

    FSM_cyclic();

    CU_ASSERT(FSM_getState() == FSM_IDLE);
    CU_ASSERT(FSM_getCmd() == COMMAND_QUEUE_EMPTY);

    CU_ASSERT(FSM_getState() == FSM_IDLE);
    CU_ASSERT(FSM_getCmd() == COMMAND_QUEUE_EMPTY);

    CU_ASSERT(FSM_getState() == FSM_IDLE);
    CU_ASSERT(FSM_getCmd() == COMMAND_QUEUE_EMPTY);

    CU_ASSERT(tulis[0] == 1);
    CU_ASSERT(tulis[1] == 1);
    CU_ASSERT(tulis[2] == 1);
    CU_ASSERT(tulis[3] == 1);
    CU_ASSERT(tulis[4] == 1);
    CU_ASSERT(tulis[5] == 1);


    /*check for proper init, let it run */
    /*
    CU_ASSERT(FSM_getState() == FSM_IDLE);
    CU_ASSERT(FSM_getCmd() == COMMAND_QUEUE_EMPTY);
    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_IDLE);
    CU_ASSERT(FSM_getCmd() == COMMAND_QUEUE_EMPTY);
    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_IDLE);
    CU_ASSERT(FSM_getCmd() == COMMAND_QUEUE_EMPTY);
    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_IDLE);
    CU_ASSERT(FSM_getCmd() == COMMAND_QUEUE_EMPTY);
    FSM_cyclic();
    */
    /*
    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_IDLE);
    CU_ASSERT(FSM_getCmd() == COMMAND_QUEUE_EMPTY);
    CU_ASSERT(tulis[3] == 1);


    FSM_cyclic();
    CU_ASSERT(FSM_getState() == FSM_IDLE);
    CU_ASSERT(FSM_getCmd() == COMMAND_QUEUE_EMPTY);

    FSM_cyclic();

*/
}

int
init_FSMsuite (void)
{

  return 0;
}

int
clean_FSMsuite (void)
{


  return 0;
}
