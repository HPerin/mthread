/*
 * main.c
 *
 *  Created on: Apr 2, 2015
 *      Author: lucas
 */

#include <stdlib.h>
#include <stdio.h>

#include "mthread.h"

#define THREADS 5

void func0(void *arg) {
	int i = (int) arg;

	printf("[STARTED] id = %d\n", i);
	myield();
	printf("[FINISHED] id = %d\n", i);
}

int main() {
	int tid[THREADS];
	int i;

	for ( i = 0; i < THREADS; i++ ) {
		tid[i] = mcreate( PRIORITY_HIGH, func0, (void*) i);
		printf("[CREATED] tid = %d\n", tid[i]);
	}

	for ( i = 0; i < THREADS; i++ ) {
		mwait(tid[i]);
		printf("[DONE] tid = %d\n", tid[i]);
	}

	printf("[EXIT_SUCCESSFUL]\n");
	return 0;
}
