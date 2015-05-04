//
// Created by lucas on 27/04/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "../include/mlist.h"

void test_mlist_pop_tid_random() {
    int THREADS = 5;
    MLIST *mlist = mlist_create();
    METCB *tcb;
    int i, j, r;
    int wrong;
    int already_checked[THREADS];

    srand((unsigned int) time(NULL));

    for ( i = 0; i < THREADS; i++ ) {
        tcb = malloc(sizeof(METCB));
        assert(tcb != NULL);
        tcb->tcb.tid = i;
        mlist_push_end(mlist, tcb);
    }

    for ( i = 0; i < THREADS; i++ ) {
        r = rand() % THREADS;

        wrong = 0;
        for ( j = 0; j < i; j++ ) {
            if (already_checked[j] == r) {
                wrong = 1;
            }
        }

        if (wrong) {
            i--;

            tcb = mlist_pop_tid(mlist, r);
            assert(tcb == NULL);
        } else {
            already_checked[i] = r;

            tcb = mlist_pop_tid(mlist, r);
            assert(tcb != NULL);
            assert(tcb->tcb.tid == r);
        }
    }
}

int main() {
    int i;
    int RUN_TIMES = 30000;

    for (i = 0; i < RUN_TIMES; i++)
        test_mlist_pop_tid_random();

    printf("SUCCESS!\n");

    return 0;
}