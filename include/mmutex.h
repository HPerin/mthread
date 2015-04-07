/*
 * mmutex.h
 *
 *  Created on: Apr 5, 2015
 *      Author: lucas
 */

#ifndef INCLUDE_MMUTEX_H_
#define INCLUDE_MMUTEX_H_

#include "mtcb.h"
#include "mqueue.h"

typedef struct mutex {
	int lock;
	TCBQUEUE *queue;
} mmutex_t;

void mmutex_initialize(mmutex_t *mtx);

void mmutex_add(mmutex_t *mtx, TCB_t *thread);
TCB_t *mmutex_drop(mmutex_t *mtx);

#endif /* INCLUDE_MMUTEX_H_ */
