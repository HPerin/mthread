/*
 * mthread.c
 *
 *  Created on: Mar 31, 2015
 *      Author: lucas
 */

#include "mthread.h"
#include "mqueue.h"
#include "mdata.h"
#include "mcontrol.h"
#include "mtcb.h"

int mcreate (int prio, void (*start)(void*), void *arg) {
	TCB_t *thread;

	mcontrol_initialize_check_and_do();

	thread = mtcb_create( start, arg );
	if (!thread) return -1;
	thread->prio = prio;

	mcontrol_add_ready( thread );

	return thread->tid;
}

int myield(void) {
	TCB_t *thread;

	mcontrol_initialize_check_and_do();

	thread = mcontrol_pop_running();
	mcontrol_add_ready( thread );
	mtcb_context_save( thread );

	if (!mcontrol_is_running()) {
		mcontrol_schedule();
	}

	return 0;
}

int mwait(int tid) {
	TCB_t *thread;

	mcontrol_initialize_check_and_do();

	if (mcontrol_waiting_already_check( tid )) {
		return -1;
	}

	if (!mcontrol_mtcb_exist_tid( tid )) {
		return -1;
	}

	thread = mcontrol_pop_running();
	if (!thread) return -1;
	if (thread->tid == tid) return -1;
	thread->waiting = tid;

	mcontrol_add_blocked( thread );
	mtcb_context_save( thread );

	if (!mcontrol_is_running()) {
		mcontrol_schedule();
	}

	return 0;
}

int mmutex_init(mmutex_t *mtx) {
	return 0;
}

int mlock (mmutex_t *mtx) {
	return 0;
}

int munlock (mmutex_t *mtx) {
	return 0;
}
