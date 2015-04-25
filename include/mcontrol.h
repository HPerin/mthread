//
// Created by lucas on 21/04/15.
//

#ifndef MTHREAD_MCONTROL_H
#define MTHREAD_MCONTROL_H

#include <stdbool.h>
#include "metcb.h"

void mcontrol_initialize();

void mcontrol_finalize_thread();

void mcontrol_schedule();

void mcontrol_add_ready(METCB *etcb);

void mcontrol_add_waiting(METCB *etcb);

void mcontrol_add_locked(METCB *etcb);

void mcontrol_add_running(METCB *etcb);

METCB *mcontrol_pop_highest_priority();

METCB *mcontrol_pop_running();

bool mcontrol_is_running();

bool mcontrol_exist_tid(int tid);

bool mcontrol_waiting_already_check(int tid);

void mcontrol_waiting_drop(int tid);

void mcontrol_locked_remove(int tid);

#endif //MTHREAD_MCONTROL_H
