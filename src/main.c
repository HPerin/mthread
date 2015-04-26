#include <stdio.h>
#include <mlist.h>
#include <stdlib.h>
#include <time.h>
#include <mthread.h>
#include <assert.h>

void test_mlist_pop_tid() {
    int THREADS = 10000;
    MLIST *mlist = mlist_create();
    METCB *tcb;
    int i;

    for ( i = 0; i < THREADS; i++ ) {
        tcb = malloc(sizeof(METCB));
        assert(tcb != NULL);
        tcb->tcb.tid = i;
        mlist_push_end(mlist, tcb);
    }

    for ( i = THREADS - 1; i >= 0; i-- ) {
        tcb = mlist_pop_tid(mlist, i);
        assert(tcb != NULL);
        assert(tcb->tcb.tid == i);
    }
}

void test_mlist_pop_first() {
    int THREADS = 10000;
    MLIST *mlist = mlist_create();
    METCB *tcb;
    int i;

    for ( i = 0; i < THREADS; i++ ) {
        tcb = malloc(sizeof(METCB));
        assert(tcb != NULL);
        tcb->tcb.tid = i;
        mlist_push_end(mlist, tcb);
    }

    for ( i = 0; i < THREADS; i++ ) {
        tcb = mlist_pop_first(mlist);
        assert(tcb != NULL);
        assert(tcb->tcb.tid == i);
    }
}

void test_mlist_exist_tid() {
    int THREADS = 1000;
    MLIST *mlist = mlist_create();
    METCB *tcb;
    int i;

    for ( i = 0; i < THREADS; i++ ) {
        tcb = malloc(sizeof(METCB));
        assert(tcb != NULL);
        tcb->tcb.tid = i;
        mlist_push_end(mlist, tcb);
    }

    for ( i = 0; i < THREADS; i++ ) {
        assert(mlist_exist_tid(mlist, i) == true);
        assert(mlist_exist_tid(mlist, i - THREADS == false));
        assert(mlist_exist_tid(mlist, i + THREADS == false));
    }
}

void test_mlist_pop_tid_random() {
    int THREADS = 10;
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

void test_mthread_1(void *arg) {
    int i = (int) arg;

    printf("ID = %d, before\n", i);
    if (i % 2 == 0) myield();
    printf("ID = %d, after\n", i);
}

void test_mthread() {
    int THREADS = 10;
    int tid[THREADS];
    int i;

    for ( i = 0; i < THREADS; i++ ) {
        tid[i] = mcreate(PRIORITY_HIGH, test_mthread_1, (void*) i);
    }

    myield();

    printf("MAIN!\n");

    for ( i = 0; i < THREADS; i++ ) {
        mwait( tid[i] );
    }
}

void test_mutex_0(void *arg) {
    mmutex_t *mtx = (mmutex_t*) arg;
    mlock(mtx);
    printf("Locked\n");
    myield();
    munlock(mtx);
    printf("Unlocked\n");
}

void test_mutex() {
    mmutex_t mtx;
    int THREADS = 3;
    int tid[THREADS];
    int i;

    mmutex_init(&mtx);

    for ( i = 0; i < THREADS; i++ ) {
        tid[i] = mcreate(PRIORITY_HIGH, test_mutex_0, (void*) &mtx);
    }

    myield();

    printf("MAIN!\n");

    for ( i = 0; i < THREADS; i++ ) {
        mwait( tid[i] );
    }
}

#define MAX_THR 10
#define MAX_SIZE 250
int vector[MAX_SIZE];
int inc;

void test_prio_0(void *arg) {
    while ( inc < MAX_SIZE ) {
        vector[inc] = (int)arg;
        inc++;
        if ( (inc % 20) == 0 )
            myield();
        else
            continue;
    }
}

void test_prio() {
    int i, pid[MAX_THR];


    for (i = 0; i < MAX_THR; i++) {
        pid[i] = mcreate((i%3), test_prio_0, (void *)('A'+i));
        if ( pid[i] == -1) {
            printf("ERRO: criação de thread!\n");
            exit(-1);
        }
    }

    for (i = 0; i < MAX_THR; i++)
        mwait(pid[i]);

    for (i = 0; i < MAX_SIZE; i++) {
        if ( (i % 20) == 0 )
            printf("\n");
        printf("%c", (char) vector[i]);
    }

    printf("\nConcluido vector de letras com priuoridades...\n");
}

int main() {
    int i;
    int RUN_TIMES = 100000;

    //test_mlist_pop_tid();
    //test_mlist_pop_first();
    //test_mlist_exist_tid();
    //for ( i = 0; i < RUN_TIMES; i++ )
    //    test_mlist_pop_tid_random();
    //test_mthread();
    //test_mutex();
    test_prio();

    return 0;
}