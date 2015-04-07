/*
 * mmutex.c
 *
 *  Created on: Apr 5, 2015
 *      Author: lucas
 */

#include "mmutex.h"
#include "mdata.h"

void mmutex_initialize(mmutex_t *mtx) {
	mtx->lock = MUTEX_UNLOCKED;
	mtx->queue = mqueue_create();
}

void mmutex_add(mmutex_t *mtx, TCB_t *thread) {
	mqueue_add_last(mtx->queue, thread);
}

TCB_t *mmutex_drop(mmutex_t *mtx) {
	return mqueue_pop_first(mtx->queue);
}
