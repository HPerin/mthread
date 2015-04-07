/*
 * main.c
 *
 *  Created on: Apr 2, 2015
 *      Author: lucas
 */

#include <stdlib.h>
#include <stdio.h>

#define THREADS 10000
#define PRINT 1
#define MUTEX 1
#define YIELD 1

#include "mthread.h"

mmutex_t mtx;

void func0(void *arg) {
	int i = (int) arg;

	if (PRINT) printf("[STARTED] id = %d\n", i);

	if (MUTEX) mlock( &mtx );
	if (YIELD) myield();
	if (PRINT) printf("[FINISHED] id = %d\n", i);
	if (MUTEX) munlock( &mtx );
}

int main(int argc, char *argv[]) {
	int tid[THREADS];
	int i;

	mmutex_init( &mtx );

	for ( i = 0; i < THREADS; i++ ) {
		tid[i] = mcreate( PRIORITY_LOW, func0, (void*) i);
		if (PRINT) printf("[CREATED] tid = %d\n", tid[i]);
	}

	for ( i = 0; i < THREADS; i++ ) {
		mwait(tid[i]);
		if (PRINT) printf("[DONE] tid = %d\n", tid[i]);
	}

	if (PRINT) printf("[EXIT_SUCCESSFUL]\n");
	return 0;
}
