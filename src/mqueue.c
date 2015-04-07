/*
 * queue.c
 *
 *  Created on: Mar 31, 2015
 *      Author: lucas
 */

#include <stdlib.h>

#include "mqueue.h"

TCBQUEUE *mqueue_create() {
	TCBQUEUE *queue = malloc(sizeof(TCBQUEUE));
	queue->root = NULL;

	return queue;
}

void mqueue_destroy(TCBQUEUE *queue) {
	free(queue);
}

TCB_t *mqueue_get_first(TCBQUEUE *queue) {
	return queue->root;
}

TCB_t *mqueue_pop_first(TCBQUEUE *queue) {
	TCB_t *first;

	first = queue->root;
	if (first == NULL) {
		return NULL;
	} else if (first->next == NULL) {
		queue->root = NULL;
	} else {
		queue->root = first->next;
		queue->root->prev = NULL;
	}

	first->next = NULL;
	first->prev = NULL;
	return first;
}

TCB_t *mqueue_pop_tid(TCBQUEUE *queue, int tid) {
	TCB_t *aux0;

	aux0 = queue->root;
	while( aux0 != NULL ) {
		if (aux0->tid == tid) {
			if (aux0 == queue->root) {
				queue->root = NULL;
				return aux0;
			} else if (aux0->next == NULL) {
				aux0->prev->next = NULL;
			} else {
				aux0->prev->next = aux0->next;
				aux0->next->prev = aux0->prev;
			}

			aux0->prev = NULL;
			aux0->next = NULL;
			return aux0;
		}

		aux0 = aux0->next;
	}

	return NULL;
}

void mqueue_add_last(TCBQUEUE *queue, TCB_t *thread) {
	TCB_t *aux0;

	if (queue->root == NULL) {
		queue->root = thread;
		queue->root->next = NULL;
		queue->root->prev = NULL;
	} else {
		aux0 = queue->root;
		while (aux0->next != NULL) {
			aux0 = aux0->next;
		}

		aux0->next = thread;
		aux0->next->prev = aux0;
		aux0->next->next = NULL;
	}
}

int mqueue_exist_tid(TCBQUEUE *queue, int tid) {
	TCB_t *aux0;

	aux0 = queue->root;
	while (aux0 != NULL) {
		if (aux0->tid == tid) {
			return 1;
		}
	}

	return 0;
}
