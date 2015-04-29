//
// Created by lucas on 21/04/15.
//

#include <mlist.h>
#include <assert.h>
#include <stddef.h>
#include <mvector.h>
#include <stdio.h>
#include "mcontrol.h"

MLIST *ready_low = NULL;
MLIST *ready_medium = NULL;
MLIST *ready_high = NULL;
MVECTOR *waiting = NULL;
MVECTOR *waiting_tid = NULL;
MVECTOR *locked = NULL;
METCB *running = NULL;

void mcontrol_finalize_thread() {
    METCB *etcb;

    etcb = mcontrol_pop_running();
    mcontrol_waiting_drop(etcb->tcb.tid);
    metcb_destroy(etcb);

    mcontrol_schedule();
}

void mcontrol_initialize() {
    ready_high = mlist_create();
    ready_medium = mlist_create();
    ready_low = mlist_create();
    waiting = mvector_create();
    waiting_tid = mvector_create();
    locked = mvector_create();
    
    running = NULL;
}

void mcontrol_schedule() {
    METCB *etcb;

    assert(running == NULL);
    etcb = mcontrol_pop_highest_priority();
    assert(etcb != NULL);
    mcontrol_add_running(etcb);
    metcb_context_restore(etcb);
}

void mcontrol_add_ready(METCB *etcb) {
    switch (etcb->tcb.prio) {
        case PRIORITY_HIGH:
            mlist_push_end(ready_high, etcb);
            break;
        case PRIORITY_LOW:
            mlist_push_end(ready_low, etcb);
            break;
        case PRIORITY_MEDIUM:
            mlist_push_end(ready_medium, etcb);
            break;
        default:
            break;
    }
}

void mcontrol_add_waiting(METCB *etcb) {
    mvector_insert(waiting, etcb, etcb->tcb.tid);
    mvector_insert(waiting_tid, etcb, etcb->waiting_tid);
}

void mcontrol_add_locked(METCB *etcb) {
    mvector_insert(locked, etcb, etcb->tcb.tid);
}

void mcontrol_add_running(METCB *etcb) {
    running = etcb;
}

METCB *mcontrol_pop_highest_priority() {
    if (mlist_is_empty(ready_high) == false) {
        return mlist_pop_first(ready_high);
    } else if (mlist_is_empty(ready_medium) == false) {
        return mlist_pop_first(ready_medium);
    } else if (mlist_is_empty(ready_low) == false) {
        return mlist_pop_first(ready_low);
    }

    return NULL;
}

METCB *mcontrol_pop_running() {
    METCB *etcb;
    etcb = running;
    running = NULL;
    return etcb;
}

bool mcontrol_is_running() {
    if (running != NULL) {
        return true;
    }

    return false;
}

bool mcontrol_exist_tid(int tid) {
    if (    mlist_exist_tid(ready_low, tid) ||
            mlist_exist_tid(ready_medium, tid) ||
            mlist_exist_tid(ready_high, tid) ||
            mvector_exist(waiting, tid) ||
            mvector_exist(locked, tid)) {

        return true;
    }

    return false;
}

bool mcontrol_waiting_already_check(int tid) {
    return mvector_exist(waiting_tid, tid);
}

void mcontrol_waiting_drop(int tid) {
    METCB *etcb;

    etcb = mvector_pop(waiting_tid, tid);
    if (!etcb) return;
    assert(mvector_pop(waiting, etcb->tcb.tid) != NULL);

    etcb->waiting_tid = TID_INVALID;
    mcontrol_add_ready(etcb);
}

void mcontrol_locked_remove(int tid) {
    METCB *metcb;

    metcb = mvector_pop(locked, tid);
    assert(metcb != NULL);
}
