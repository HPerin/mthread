//
// Created by lucas on 27/04/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/mlist.h"

void test_mlist_pop_tid() {
    int THREADS = 30000;
    MLIST *mlist = mlist_create();
    METCB *tcb;
    int i;

    for ( i = 0; i < THREADS; i++ ) {
        tcb = malloc(sizeof(METCB));
        assert(tcb != NULL);
        tcb->tcb.tid = i;
        mlist_push_end(mlist, tcb);
    }

    for ( i = THREADS - 1; i >= 0; i-- ) {
        tcb = mlist_pop_tid(mlist, i);
        assert(tcb != NULL);
        assert(tcb->tcb.tid == i);
    }
}

int main() {
    test_mlist_pop_tid();

    printf("SUCCESS!\n");

    return 0;
}