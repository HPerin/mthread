/*
 * mcontrol.c
 *
 *  Created on: Apr 2, 2015
 *      Author: lucas
 */

#include <stdlib.h>
#include <stdio.h>

#include "mqueue.h"
#include "mtcb.h"
#include "mcontrol.h"

TCBQUEUE *ready_low;
TCBQUEUE *ready_medium;
TCBQUEUE *ready_high;
TCBQUEUE *blocked;
TCB_t *running;

int initialized = 0;

void mcontrol_initialize_check_and_do() {
	if (!initialized) {
		initialized = 1;
		mcontrol_initialize();
	}
}

void mcontrol_initialize() {
	/*
	 * initialize queues
	 */
	ready_low = mqueue_create();
	ready_medium = mqueue_create();
	ready_high = mqueue_create();
	blocked = mqueue_create();
	running = NULL;

	/*
	 * initialize mtcb creator
	 */
	mtcb_initialize();

	/*
	 * initialize main thread
	 */
	TCB_t *thread;
	thread = mtcb_create( NULL, NULL );
	thread->prio = PRIORITY_LOW;
	mcontrol_add_running( thread );
	mtcb_context_save( thread );
}

void mcontrol_destroy_main() {
	mqueue_destroy( ready_low );
	mqueue_destroy( ready_medium );
	mqueue_destroy( ready_high );
	mqueue_destroy( blocked );

	mtcb_finalize();
}

void mcontrol_finalize_thread() {
	TCB_t *thread;

	thread = mcontrol_pop_running();

	mcontrol_waiting_drop( thread->tid );
	mtcb_destroy( thread );

	mcontrol_schedule();
}

void mcontrol_schedule() {
	TCB_t *thread;

	if (running != NULL) {
		printf("[WARNING] running != NULL on schedule!\n");
	}

	thread = mcontrol_pop_highest_priority();
	if (!thread) printf("[ERROR] no more threads left!\n");
	mcontrol_add_running( thread );
	mtcb_context_restore( thread );
}

void mcontrol_add_ready(TCB_t *thread) {
	switch (thread->prio) {
	case PRIORITY_HIGH:
		mqueue_add_last( ready_high, thread );
		break;
	case PRIORITY_MEDIUM:
		mqueue_add_last( ready_medium, thread );
		break;
	case PRIORITY_LOW:
		mqueue_add_last( ready_low, thread );
		break;
	}
}

void mcontrol_add_blocked(TCB_t *thread) {
	mqueue_add_last( blocked, thread );
}

void mcontrol_add_running(TCB_t *thread) {
	running = thread;
}

TCB_t *mcontrol_pop_highest_priority() {
	if (mqueue_get_first( ready_high )) {
		return mqueue_pop_first( ready_high );
	} else if (mqueue_get_first( ready_medium )) {
		return mqueue_pop_first( ready_medium );
	} else if (mqueue_get_first( ready_low )) {
		return mqueue_pop_first( ready_low );
	}

	return NULL;
}

TCB_t *mcontrol_pop_running() {
	TCB_t *thread;

	thread = running;
	running = NULL;

	return thread;
}

int mcontrol_is_running() {
	if (running == NULL) {
		return 0;
	}

	return 1;
}

int mcontrol_mtcb_exist_tid(int tid) {
	return ( mqueue_exist_tid( ready_high, tid ) ||
			 mqueue_exist_tid( ready_medium, tid ) ||
			 mqueue_exist_tid( ready_low, tid) ||
			 mqueue_exist_tid( blocked, tid ) ||
			 running->tid == tid );
}

int mcontrol_waiting_already_check(int tid) {
	TCB_t *aux0;

	aux0 = mqueue_get_first( blocked );
	while (aux0 != NULL) {
		if (aux0->waiting == tid) {
			return 1;
		}
	}

	return 0;
}

void mcontrol_waiting_drop(int tid) {
	TCB_t *aux0;

	aux0 = mqueue_get_first( blocked );
	while (aux0 != NULL) {
		if (aux0->waiting == tid) {
			mqueue_pop_tid( blocked, aux0->tid );
			mcontrol_add_ready( aux0 );
			return;
		}

		aux0 = aux0->next;
	}
}
