//
// Created by lucas on 21/04/15.
//

#include <stdbool.h>
#include <mcontrol.h>
#include <stddef.h>
#include "mthread.h"


int mcreate_func(int priority, void (*start)(void *), void *arg) {
    METCB *metcb;

    metcb = metcb_create(priority, start, arg);
    if (!metcb) return -1;
    mcontrol_add_ready(metcb);

    return metcb->tcb.tid;
}

int myield() {
    METCB *metcb;

    metcb = mcontrol_pop_running();
    if (!metcb) return -1;
    mcontrol_add_ready(metcb);
    metcb_context_save(metcb);

    if (mcontrol_is_running() == false) {
        mcontrol_schedule();
    }

    return 0;
}

int mwait(int tid) {
    METCB *metcb;

    if (mcontrol_exist_tid(tid) == false) return -1;
    if (mcontrol_waiting_already_check(tid)) return -1;

    metcb = mcontrol_pop_running();
    mcontrol_add_waiting(metcb);
    metcb->waiting_tid = tid;
    metcb_context_save(metcb);

    if (mcontrol_is_running() == false) {
        mcontrol_schedule();
    }

    return 0;
}


int mmutex_init_func(mmutex_t *mtx) {

    if (!mtx) return -1;

    mmutex_initialize(mtx);

    return 0;
}

int mlock(mmutex_t *mtx) {
    METCB *metcb;

    if (!mtx) return -1;

    if (mmutex_is_locked(mtx) == true) {
        metcb = mcontrol_pop_running();
        mmutex_add(mtx, metcb);
        mcontrol_add_locked(metcb_create_copy(metcb));
        metcb_context_save(metcb);

        if (mcontrol_is_running() == false) {
            mcontrol_schedule();
        }
    } else {
        mmutex_lock(mtx);
    }

    return 0;
}

int munlock(mmutex_t *mtx) {
    METCB *metcb;

    if (!mtx) return -1;

    if (mmutex_is_empty(mtx) == false) {
        metcb = mmutex_pop(mtx);
        mcontrol_locked_remove(metcb->tcb.tid);
        mcontrol_add_ready(metcb);
    } else {
        mmutex_unlock(mtx);
    }

    return 0;
}

void initialize() {
    METCB *metcb;

    mcontrol_initialize();

    metcb = metcb_create(PRIORITY_HIGH, NULL, NULL);
    mcontrol_add_running(metcb);

    mcreate = &mcreate_func;
    mmutex_init = &mmutex_init_func;
}

/*
 * Initialization functions
 */

int initialize_by_mcreate(int priority, void (*start)(void *), void *arg) {
    initialize();

    return mcreate_func(priority, start, arg);
}

int initialize_by_mmutex_init(mmutex_t *mtx) {
    initialize();

    return mmutex_init_func(mtx);
}

int (*mcreate)(int, void(*)(void*), void*) = &initialize_by_mcreate;
int (*mmutex_init)(mmutex_t *mtx) = &initialize_by_mmutex_init;