//
// Created by lucas on 21/04/15.
//

#include <mlist.h>
#include "mmutex.h"

void mmutex_initialize(mmutex_t *mtx) {
    mtx->flag = FLAG_UNLOCKED;
    mtx->mlist = mlist_create();
}

void mmutex_lock(mmutex_t *mtx) {
    mtx->flag = FLAG_LOCKED;
}

void mmutex_unlock(mmutex_t *mtx) {
    mtx->flag = FLAG_UNLOCKED;
}

bool mmutex_is_locked(mmutex_t *mtx) {
    if (mtx->flag == FLAG_LOCKED) return true;

    return false;
}

bool mmutex_is_empty(mmutex_t *mtx) {
    return mlist_is_empty(mtx->mlist);
}

void mmutex_add(mmutex_t *mtx, METCB *metcb) {
    mlist_push_end(mtx->mlist, metcb);
}

METCB *mmutex_pop(mmutex_t *mtx) {
    return mlist_pop_first(mtx->mlist);
}
