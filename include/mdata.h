/*
 * mdata.h
 *
 *  Created on: Apr 2, 2015
 *      Author: lucas
 */

#ifndef INCLUDE_MDATA_H_
#define INCLUDE_MDATA_H_

#include <ucontext.h>

#define PRIORITY_HIGH 0
#define PRIORITY_MEDIUM 1
#define PRIORITY_LOW 2

typedef struct TCB {
	int tid;
	int state;
	int prio;
	int waiting;
	ucontext_t context;
	struct TCB *prev;
	struct TCB *next;
} TCB_t;

typedef struct mutex {
	int	flag;
	TCB_t *first;
	TCB_t *last;
} mmutex_t;

#endif /* INCLUDE_MDATA_H_ */
