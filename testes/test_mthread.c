//
// Created by lucas on 27/04/15.
//

#include <stdio.h>
#include <stdlib.h>
#include "../include/mthread.h"

void test_mthread_1(void *arg) {
    int i = (int) arg;

    //printf("ID = %d, before\n", i);
    if (i % 2 == 0) myield();
    //printf("ID = %d, after\n", i);
}

void test_mthread() {
    int THREADS = 30000;
    int tid[THREADS];
    int i;

    for ( i = 0; i < THREADS; i++ ) {
        tid[i] = mcreate(PRIORITY_HIGH, test_mthread_1, (void*) i);
    }

    myield();

    //printf("MAIN!\n");

    for ( i = 0; i < THREADS; i++ ) {
        mwait( tid[i] );
    }

    printf("SUCCESS!\n");
}

int main() {
    test_mthread();

    return 0;
}