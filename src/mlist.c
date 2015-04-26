//
// Created by lucas on 21/04/15.
//

#include <stddef.h>
#include <mlist.h>
#include <malloc.h>

MLIST *mlist_create() {
    MLIST *mlist;

    mlist = malloc(sizeof(MLIST));
    if (!mlist) return NULL;

    mlist->root = NULL;
    mlist->last = NULL;

    return mlist;
}

bool mlist_is_empty(MLIST *mlist) {
    if (mlist->root == NULL) {
        return true;
    }
    
    return false;
}

METCB *mlist_pop_first(MLIST *mlist) {
    METCB *aux;

    if (mlist == NULL) return NULL;
    if (mlist->root == NULL) return NULL;

    if (mlist->root == mlist->last) {
        aux = mlist->root;
        mlist->root = NULL;
        mlist->last = NULL;
    } else {
        aux = mlist->root;
        mlist->root->next->prev = NULL;
        mlist->root = mlist->root->next;
        aux->next = NULL;
    }

    return aux;
}

void mlist_push_end(MLIST *mlist, METCB *tcb) {
    if (mlist == NULL) return;

    if (mlist->root == NULL) {
        mlist->root = tcb;
        mlist->last = mlist->root;
        mlist->root->next = NULL;
        mlist->root->prev = NULL;
    } else if (mlist->root == mlist->last) {
        mlist->last = tcb;
        mlist->root->next = mlist->last;
        mlist->last->prev = mlist->root;
        mlist->last->next = NULL;
    } else {
        mlist->last->next = tcb;
        mlist->last->next->prev = mlist->last;
        mlist->last->next->next = NULL;
        mlist->last = mlist->last->next;
    }
}

METCB *mlist_pop_tid(MLIST *mlist, int tid) {
    METCB *aux;

    if (mlist == NULL) return NULL;
    if (mlist->root == NULL) return NULL;

    if (mlist->root->tcb.tid == tid) {
        return mlist_pop_first(mlist);
    } else {
        aux = mlist->root;
        while (aux != NULL) {
            if (aux->tcb.tid == tid) {
                if (aux == mlist->last) {
                    mlist->last = mlist->last->prev;
                    mlist->last->next = NULL;
                } else {
                    aux->prev->next = aux->next;
                    aux->next->prev = aux->prev;
                }

                aux->next = NULL;
                aux->prev = NULL;

                return aux;
            }

            aux = aux->next;
        }
    }

    return NULL;
}

METCB *mlist_pop_waiting_tid(MLIST *mlist, int tid) {
    METCB *aux;

    if (mlist == NULL) return NULL;
    if (mlist->root == NULL) return NULL;

    if (mlist->root->waiting_tid == tid) {
        return mlist_pop_first(mlist);
    } else {
        aux = mlist->root;
        while (aux != NULL) {
            if (aux->waiting_tid == tid) {
                if (aux == mlist->last) {
                    mlist->last = mlist->last->prev;
                    mlist->last->next = NULL;
                } else {
                    aux->prev->next = aux->next;
                    aux->next->prev = aux->prev;
                }

                aux->next = NULL;
                aux->prev = NULL;

                return aux;
            }

            aux = aux->next;
        }
    }

    return NULL;
}


bool mlist_exist_tid(MLIST *mlist, int tid) {
    METCB *aux;

    if (mlist == NULL) return false;

    aux = mlist->root;
    while( aux != NULL ) {
        if (aux->tcb.tid == tid) {
            return true;
        }

        aux = aux->next;
    }

    return false;
}

bool mlist_exist_waiting_tid(MLIST *mlist, int waiting_tid) {
    METCB *aux;

    if (mlist == NULL) return false;
    if (mlist->root == NULL) return false;

    aux = mlist->root;
    while (aux != NULL) {
        if (aux->waiting_tid == waiting_tid) {
            return true;
        }

        aux = aux->next;
    }

    return false;
}
