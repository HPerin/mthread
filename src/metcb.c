//
// Created by lucas on 21/04/15.
//

#include <stddef.h>
#include "metcb.h"
#include <stdlib.h>
#include <mcontrol.h>

ucontext_t *etcb_get_finish_context() {
    static ucontext_t *finish_context = NULL;

    if (finish_context == NULL) {
        finish_context = malloc(sizeof(ucontext_t));

        getcontext(finish_context);

        finish_context->uc_link = NULL;
        finish_context->uc_stack.ss_sp = malloc(SIGSTKSZ);
        finish_context->uc_stack.ss_size = SIGSTKSZ;

        makecontext(finish_context, mcontrol_finalize_thread, 0);
    }

    return finish_context;
}

METCB *metcb_create(int prio, void (*start)(void *), void *arg) {
    static int current_tid = 0;

    METCB *etcb = malloc(sizeof(METCB));
    if (!etcb) return NULL;

    etcb->tcb.tid = current_tid++;
    etcb->waiting_tid = TID_INVALID;
    etcb->tcb.prio = prio;
    etcb->next = NULL;
    etcb->prev = NULL;

    /*
     * Get an context model to
     * create a new one on top
     */
    getcontext(&(etcb->tcb.context));

    /*
     * Create the new context, if
     * start equals NULL, then we
     * are just saving the main thread
     * context.
     */
    if (start != NULL) {
        /*
        * Allocate memory to the
        * stack
        */
        etcb->tcb.context.uc_stack.ss_sp = malloc(SIGSTKSZ);
        etcb->tcb.context.uc_stack.ss_size = SIGSTKSZ;
        etcb->tcb.context.uc_link = etcb_get_finish_context();

        makecontext(&(etcb->tcb.context), (void (*) (void)) start, 1, arg);
    }

    return etcb;
}

METCB *metcb_create_copy(METCB *src) {
    METCB *metcb;

    metcb = malloc(sizeof(METCB));
    if (!metcb) return NULL;

    metcb->tcb = src->tcb;
    metcb->next = src->next;
    metcb->prev = src->prev;
    metcb->waiting_tid = src->waiting_tid;

    return metcb;
}

void metcb_destroy(METCB *etcb) {
    free(etcb);
}

void metcb_context_save(METCB *etcb) {
    getcontext(&(etcb->tcb.context));
}

void metcb_context_restore(METCB *etcb) {
    setcontext(&(etcb->tcb.context));
}
