//
// Created by lucas on 21/04/15.
//

#ifndef MTHREAD_MTHREAD_H
#define MTHREAD_MTHREAD_H

#include "mdata.h"

/*
 * Do not use this function!!!
 */
//int mthread_initialize(int, void (*)(void*), void*);

/*
 * Use this function to create threads,
 * also, this has to be the first
 * function to be called from mthreads
 * library, so everything get initialized
 * correctly.
 *
 * @arg0: priority (PRIORITY_HIGH, PRIORITY_MEDIUM, PRIORITY_LOW)
 * @arg1: function to be executed by the thread [void func(void *arg)]
 * @arg2: argument to be given to the function
 *
 * @ret: created thread tid if successful, -1 if failed.
 */
extern int (*mcreate)(int prio, void (*start)(void*), void *arg);
//int mcreate (int prio, void (*start)(void*), void *arg);

/*
 * This gives away the execution privilege
 * , to get back in the thread queue.
 *
 * @ret: 0 if successful, -1 if failed.
 */
int myield(void);

/*
 * This function makes the current thread
 * wait for the given tid corresponding thread.
 * If the thread doesn't exist or is already been
 * waited for another thread this function
 * returns -1 directly. If everything runs fine
 * it returns 0.
 *
 * @arg0: tid that the current thread is going to wait for.
 *
 * @ret: 0 if successful, -1 if failed.
 */
int mwait(int tid);

/*
 * Initializes the mmutex_t structure, the given
 * structure has to have been already allocated.
 *
 * @arg0: the mmutex_t struct, already allocated
 *
 * @ret: 0 if successful, -1 if failed.
 */
extern int (*mmutex_init)(mmutex_t *mtx);

/*
 * Locks the current thread in the specified
 * code segment, so that only this thread
 * can run it, until it's unlocked.
 *
 * @arg0: the mmutex_t struct to be locked
 *
 * @ret: 0 if successful, -1 if failed.
 */
int mlock (mmutex_t *mtx);

/*
 * Unlocks the previously locked segment
 * of code.
 *
 * @arg0: the mmutex_t struct to be unlocked
 *
 * @ret: 0 if successful, -1 if failed.
 */
int munlock (mmutex_t *mtx);

#endif //MTHREAD_MTHREAD_H
