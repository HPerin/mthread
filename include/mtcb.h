/*
 * mtcb.h
 *
 *  Created on: Apr 2, 2015
 *      Author: lucas
 */

#ifndef INCLUDE_MTCB_H_
#define INCLUDE_MTCB_H_

#include <ucontext.h>

typedef struct TCB {
	int tid;
	int state;
	int prio;
	int waiting;
	ucontext_t context;
	struct TCB *prev;
	struct TCB *next;
} TCB_t;

TCB_t *mtcb_create(void (*start)(void*), void *arg);
void mtcb_destroy(TCB_t *thread);

void mtcb_initialize();

int mtcb_context_save(TCB_t *thread);
int mtcb_context_restore(TCB_t *thread);
int mtcb_context_create(TCB_t *thread, void (*start)(void*), void *arg);

#endif /* INCLUDE_MTCB_H_ */
