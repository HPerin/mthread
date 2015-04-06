/*
 * mthread.h: arquivo de inclus�o com os prot�tipos das fun��es a serem
 *            implementadas na realiza��o do trabalho.
 *
 * N�O MODIFIQUE ESTE ARQUIVO.
 *
 * VERS�O 1 - 24/03/2015
 */
#ifndef __mthread__
#define __mthread__

#include "mdata.h"

int mcreate (int prio, void (*start)(void*), void *arg);
int myield(void);
int mwait(int tid);
int mmutex_init(mmutex_t *mtx);
int mlock (mmutex_t *mtx);
int munlock (mmutex_t *mtx);

#endif
