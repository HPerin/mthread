/*
 * queue.h
 *
 *  Created on: Mar 31, 2015
 *      Author: lucas
 */

#ifndef INCLUDE_MQUEUE_H_
#define INCLUDE_MQUEUE_H_

#include "mtcb.h"

typedef struct tcbqueue_t {
	TCB_t *root;
} TCBQUEUE;

TCBQUEUE *mqueue_create();
void mqueue_destroy(TCBQUEUE *queue);

TCB_t *mqueue_get_first(TCBQUEUE *queue);
TCB_t *mqueue_pop_first(TCBQUEUE *queue);
TCB_t *mqueue_pop_tid(TCBQUEUE *queue, int tid);
void mqueue_add_last(TCBQUEUE *queue, TCB_t *thread);

int mqueue_exist_tid(TCBQUEUE *queue, int tid);

#endif /* INCLUDE_MQUEUE_H_ */
