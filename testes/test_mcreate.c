//
// Created by lucas on 03/05/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/mthread.h"

void test_mcreate_0(void *arg) {

}

void test_mcreate() {
    int THREADS = 30000;
    int i;

    for (i = 0; i < THREADS; i++) {
        int tid;

        tid = mcreate(PRIORITY_HIGH, test_mcreate_0, NULL);
        assert(tid != -1);
    }
}

int main() {
    test_mcreate();

    printf("SUCCESS!\n");

    return 0;
}