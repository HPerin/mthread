//
// Created by lucas on 27/04/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/mlist.h"

void test_mlist_exist_tid() {
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

    for ( i = 0; i < THREADS; i++ ) {
        assert(mlist_exist_tid(mlist, i) == true);
        assert(mlist_exist_tid(mlist, i - THREADS == false));
        assert(mlist_exist_tid(mlist, i + THREADS == false));
    }
}

int main() {
    test_mlist_exist_tid();

    printf("SUCCESS!\n");

    return 0;
}