/*
 * mcontrol.h
 *
 *  Created on: Apr 2, 2015
 *      Author: lucas
 */

#ifndef INCLUDE_MCONTROL_H_
#define INCLUDE_MCONTROL_H_

#include "mdata.h"

void mcontrol_initialize();

void mcontrol_finalize_thread();

void mcontrol_destroy_main();

void mcontrol_schedule();

void mcontrol_add_ready(TCB_t *thread);
void mcontrol_add_blocked(TCB_t *thread);
void mcontrol_add_running(TCB_t *thread);

TCB_t *mcontrol_pop_highest_priority();
TCB_t *mcontrol_pop_running();

int mcontrol_is_running();
TCB_t *mcontrol_get_running();

int mcontrol_mtcb_exist_tid(int tid);

void mcontrol_initialize_check_and_do();

/*
 * Check if the given tid is
 * already been waited for another
 * thread.
 */
int mcontrol_waiting_already_check(int tid);

/*
 * Drop any threads (put them on ready)
 * that are waiting for the given tid
 * to terminate.
 */
void mcontrol_waiting_drop(int tid);

#endif /* INCLUDE_MCONTROL_H_ */
