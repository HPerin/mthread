//
// Created by lucas on 03/05/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/mthread.h"

void test_mwait_0(void *arg) {
    int *counter = arg;

    *counter += 1;
}

void test_mwait() {
    int THREADS = 30000;
    int i;
    int tid[THREADS];

    int counter = 0;

    for (i = 0; i < THREADS; i++) {
        tid[i] = mcreate(PRIORITY_HIGH, test_mwait_0, (void*) &counter);
        assert(tid[i] != -1);
    }

    for (i = 0; i < THREADS; i++) {
        mwait(tid[i]);
    }
    assert(counter == THREADS);
}

int main() {
    test_mwait();

    printf("SUCCESS!\n");

    return 0;
}