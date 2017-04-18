/*
 * FSM_TEST.h
 *
 *  Created on: 3. apr 2017
 *      Author: Karl
 */

#ifndef FSM_TEST_H_
#define FSM_TEST_H_

/*undone tests */

void
test_FSM_cyclic();

void
test_FSM_getState();

void
test_FSM_setState ();

void
test_FSM_init();

void
test_FSM_getCmdQueue();

void
test_FSM_getCmd();

void
test_FSM_setCmd();

void
test_FSM_readCmdFromQueue();

void
test_FSM_emptyCmdQueue();

/* done tests */
void
test_FSM_initCmdQueue();

void
test_FSM_addCmdToQueue();

/*
void
test_FSM_getCurrentCmd();

void
test_FSM_setCurrentCmd();
*/

int
init_FSMsuite (void);

int
clean_FSMsuite (void);

#endif /* FSM_TEST_H_ */
