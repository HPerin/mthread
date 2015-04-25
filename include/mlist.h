//
// Created by lucas on 21/04/15.
//

#ifndef MTHREAD_MLIST_H
#define MTHREAD_MLIST_H

#include <stdbool.h>
#include "metcb.h"

typedef struct s_mlist {
    METCB *root;
    METCB *last;
} MLIST;

MLIST *mlist_create();

bool mlist_is_empty(MLIST *mlist);

METCB *mlist_pop_first(MLIST *mlist);

void mlist_push_end(MLIST *mlist, METCB *tcb);

METCB *mlist_pop_tid(MLIST *mlist, int tid);

METCB *mlist_pop_waiting_tid(MLIST *mlist, int tid);

bool mlist_exist_tid(MLIST *mlist, int tid);

bool mlist_exist_waiting_tid(MLIST *mlist, int waiting_tid);

#endif //MTHREAD_MLIST_H
