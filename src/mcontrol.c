//
// Created by lucas on 21/04/15.
//

#include <mlist.h>
#include <assert.h>
#include <mvector.h>
#include <malloc.h>
#include "mcontrol.h"

MLIST **ready = NULL;
MVECTOR **v_ready = NULL;
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
    ready = malloc(3 * sizeof(MLIST*));
    ready[PRIORITY_HIGH] = mlist_create();
    ready[PRIORITY_MEDIUM] = mlist_create();
    ready[PRIORITY_LOW] = mlist_create();

    v_ready = malloc(3 * sizeof(MVECTOR*));
    v_ready[PRIORITY_HIGH] = mvector_create();
    v_ready[PRIORITY_MEDIUM] = mvector_create();
    v_ready[PRIORITY_LOW] = mvector_create();

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
    mvector_insert(v_ready[etcb->tcb.prio], etcb, etcb->tcb.tid);
    mlist_push_end(ready[etcb->tcb.prio], etcb);
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
    METCB *metcb = NULL;

    if (mlist_is_empty(ready[PRIORITY_HIGH]) == false) {
        metcb = mlist_pop_first(ready[PRIORITY_HIGH]);
        mvector_pop(v_ready[PRIORITY_HIGH], metcb->tcb.tid);
    } else if (mlist_is_empty(ready[PRIORITY_MEDIUM]) == false) {
        metcb = mlist_pop_first(ready[PRIORITY_MEDIUM]);
        mvector_pop(v_ready[PRIORITY_MEDIUM], metcb->tcb.tid);
    } else if (mlist_is_empty(ready[PRIORITY_LOW]) == false) {
        metcb = mlist_pop_first(ready[PRIORITY_LOW]);
        mvector_pop(v_ready[PRIORITY_LOW], metcb->tcb.tid);
    }

    assert(metcb != NULL);
    return metcb;
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
    if (    mvector_exist(v_ready[PRIORITY_HIGH], tid) ||
            mvector_exist(v_ready[PRIORITY_MEDIUM], tid) ||
            mvector_exist(v_ready[PRIORITY_LOW], tid) ||
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
