//
// Created by lucas on 21/04/15.
//

#include "mlist.h"
#include "metcb.h"

#ifndef MTHREAD_MUTEX_H
#define MTHREAD_MUTEX_H

#define FLAG_LOCKED 1
#define FLAG_UNLOCKED 0

typedef struct mmutex {
    int	flag;
    MLIST *mlist;
} mmutex_t;


void mmutex_initialize(mmutex_t *mtx);

void mmutex_lock(mmutex_t *mtx);

void mmutex_unlock(mmutex_t *mtx);

bool mmutex_is_locked(mmutex_t *mtx);

bool mmutex_is_empty(mmutex_t *mtx);

void mmutex_add(mmutex_t *mtx, METCB *metcb);

METCB *mmutex_pop(mmutex_t *mtx);

#endif //MTHREAD_MUTEX_H
