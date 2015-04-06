/*
 * mtcb.c
 *
 *  Created on: Apr 2, 2015
 *      Author: lucas
 */

#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>

#include "mtcb.h"
#include "mcontrol.h"

int current_tid = 1000;

ucontext_t *finish_context = NULL;
ucontext_t *terminate_context = NULL;

void mtcb_initialize_finish_context() {
	finish_context = malloc(sizeof(ucontext_t));

	getcontext(finish_context);

	finish_context->uc_link = NULL;
	finish_context->uc_stack.ss_sp = malloc(SIGSTKSZ);
	finish_context->uc_stack.ss_size = SIGSTKSZ;

	makecontext(finish_context, mcontrol_finalize_thread, 0);
}

void mtcb_initialize_terminate_context() {
	terminate_context = malloc(sizeof(ucontext_t));

	getcontext(terminate_context);

	terminate_context->uc_link = NULL;
	terminate_context->uc_stack.ss_sp = malloc(SIGSTKSZ);
	terminate_context->uc_stack.ss_size = SIGSTKSZ;

	makecontext(terminate_context, mcontrol_destroy_main, 0);
}

void mtcb_initialize() {
	mtcb_initialize_finish_context();
	mtcb_initialize_terminate_context();
}

void mtcb_finalize() {
	free(finish_context->uc_stack.ss_sp);
	free(finish_context);

	free(terminate_context->uc_stack.ss_sp);
	free(terminate_context);
}

TCB_t *mtcb_create(void (*start)(void*), void *arg) {
	TCB_t *thread;

	thread = malloc(sizeof(TCB_t));
	if (!thread) return NULL;

	thread->tid = current_tid++;
	thread->prio = PRIORITY_LOW;
	thread->state = 0;
	thread->waiting = 0;

	thread->prev = NULL;
	thread->next = NULL;

	mtcb_context_save( thread );

	if (start == NULL) {
		thread->context.uc_link = terminate_context;
	} else {
		thread->context.uc_link = finish_context;
		thread->context.uc_stack.ss_sp = malloc(SIGSTKSZ);
		thread->context.uc_stack.ss_size = SIGSTKSZ;

		mtcb_context_create(thread, start, arg);
	}

	return thread;
}

void mtcb_destroy(TCB_t *thread) {
	free(thread->context.uc_stack.ss_sp);
	free(thread);
}

int mtcb_context_save(TCB_t *thread) {
	if (getcontext(&(thread->context)) == -1) {
		printf("[ERROR] saving context!\n");
		return -1;
	}

	return 0;
}

int mtcb_context_restore(TCB_t *thread) {
	if (setcontext(&(thread->context)) == -1) {
		printf("[ERROR] setting context!\n");
		return -1;
	}

	return 0;
}

int mtcb_context_create(TCB_t *thread, void (*start)(void*), void *arg) {
	makecontext(&(thread->context), (void (*) (void)) start, 1, arg);

	return 0;
}
