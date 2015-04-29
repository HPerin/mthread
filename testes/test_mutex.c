//
// Created by lucas on 27/04/15.
//

#include <stdio.h>
#include <stdlib.h>
#include "../include/mthread.h"

void test_mutex_0(void *arg) {
    mmutex_t *mtx = (mmutex_t*) arg;
    mlock(mtx);
    //printf("Locked\n");
    myield();
    munlock(mtx);
    //printf("Unlocked\n");
}

void test_mutex() {
    mmutex_t mtx;
    int THREADS = 30000;
    int tid[THREADS];
    int i;

    mmutex_init(&mtx);

    for ( i = 0; i < THREADS; i++ ) {
        tid[i] = mcreate(PRIORITY_HIGH, test_mutex_0, (void*) &mtx);
    }

    myield();

    //printf("MAIN!");

    for ( i = 0; i < THREADS; i++ ) {
        mwait( tid[i] );
    }
}

int main() {
    test_mutex();

    printf("SUCCESS!\n");

    return 0;
}