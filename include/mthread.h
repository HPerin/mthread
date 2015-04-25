//
// Created by lucas on 21/04/15.
//

#ifndef MTHREAD_MTHREAD_H
#define MTHREAD_MTHREAD_H

#include "mdata.h"

int mcreate (int prio, void (*start)(void*), void *arg);
int myield(void);
int mwait(int tid);
int mmutex_init(mmutex_t *mtx);
int mlock (mmutex_t *mtx);
int munlock (mmutex_t *mtx);

#endif //MTHREAD_MTHREAD_H
