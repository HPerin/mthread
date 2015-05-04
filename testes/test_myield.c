//
// Created by lucas on 03/05/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/mthread.h"

void test_myield_0(void *arg) {
    int *counter = arg;

    *counter += 1;
}

void test_myield() {
    int THREADS = 30000;
    int i;

    int counter = 0;

    for (i = 0; i < THREADS; i++) {
        int tid;

        tid = mcreate(PRIORITY_HIGH, test_myield_0, (void*) &counter);
        assert(tid != -1);
    }

    myield();
    assert(counter > 0);
}

int main() {
    test_myield();

    printf("SUCCESS!\n");

    return 0;
}