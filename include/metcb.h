//
// Created by lucas on 21/04/15.
//

#ifndef MTHREAD_MTCB_H
#define MTHREAD_MTCB_H

#include <ucontext.h>

#define TID_INVALID -1

#define PRIORITY_HIGH 0
#define PRIORITY_MEDIUM 1
#define PRIORITY_LOW 2

typedef struct TCB {
    int  tid;
    int  state;     // 0: Criação; 1: Apto; 2: Execução; 3: Bloqueado e 4: Término
    int  prio;		// prioridade da thread (0:alta; 1: média, 2:baixa)
    ucontext_t   context;
    struct TCB   *prev;
    struct TCB   *next;
} TCB_t;

typedef struct s_metcb {
    TCB_t tcb;
    int waiting_tid;

    struct s_metcb *next;
    struct s_metcb *prev;
} METCB;

void metcb_initialize();

METCB *metcb_create(int prio, void (*start)(void *), void *arg);

METCB *metcb_create_copy(METCB *src);

void metcb_destroy(METCB *etcb);

void metcb_context_save(METCB *etcb);

void metcb_context_restore(METCB *etcb);

#endif //MTHREAD_MTCB_H
