//
// Created by lucas on 28/04/15.
//

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "../include/mvector.h"

void test_mvector_exist_tid() {
    int THREADS = 30000;
    MVECTOR *mvector = mvector_create();
    METCB *tcb;
    int i;

    for ( i = 0; i < THREADS; i++ ) {
        tcb = malloc(sizeof(METCB));
        assert(tcb != NULL);
        mvector_insert(mvector, tcb, i);
    }

    for ( i = 0; i < THREADS; i++ ) {
        assert(mvector_exist(mvector, i) == true);
        assert(mvector_exist(mvector, i - THREADS == false));
        assert(mvector_exist(mvector, i + THREADS == false));
    }
}

int main() {
    test_mvector_exist_tid();

    printf("SUCCESS!\n");

    return 0;
}