//
// Created by lucas on 28/04/15.
//

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "../include/mvector.h"

void test_mvector_pop_tid() {
    int THREADS = 30000;
    MVECTOR *mvector = mvector_create();
    METCB *tcb;
    int i;

    for ( i = 0; i < THREADS; i++ ) {
        tcb = malloc(sizeof(METCB));
        assert(tcb != NULL);
        tcb->tcb.tid = i;
        mvector_insert(mvector, tcb, tcb->tcb.tid);
    }

    for ( i = THREADS - 1; i >= 0; i-- ) {
        tcb = mvector_pop(mvector, i);
        assert(tcb != NULL);
        assert(tcb->tcb.tid == i);
    }
}

int main() {
    test_mvector_pop_tid();

    printf("SUCCESS!\n");

    return 0;
}