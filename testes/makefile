CC	=	gcc
LIBDIR	=	../lib

all:	test_mlist_exist_tid test_mlist_pop_first test_mlist_pop_tid test_mlist_pop_tid_random test_mthread test_mutex

test_mlist_exist_tid:	test_mlist_exist_tid.c
	$(CC) -o test_mlist_exist_tid.out test_mlist_exist_tid.c -L$(LIBDIR) -lmthread -Wall

test_mlist_pop_first:	test_mlist_pop_first.c
	$(CC) -o test_mlist_pop_first.out test_mlist_pop_first.c -L$(LIBDIR) -lmthread -Wall

test_mlist_pop_tid:	test_mlist_pop_tid.c
	$(CC) -o test_mlist_pop_tid.out test_mlist_pop_tid.c -L$(LIBDIR) -lmthread -Wall

test_mlist_pop_tid_random:	test_mlist_pop_tid_random.c
	$(CC) -o test_mlist_pop_tid_random.out test_mlist_pop_tid_random.c -L$(LIBDIR) -lmthread -Wall

test_mthread:	test_mthread.c
	$(CC) -o test_mthread.out test_mthread.c -L$(LIBDIR) -lmthread -Wall

test_mutex:	test_mutex.c
	$(CC) -o test_mutex.out test_mutex.c -L$(LIBDIR) -lmthread -Wall

clean:
	rm test_mutex.out
	rm test_mthread.out
	rm test_mlist_pop_tid_random.out
	rm test_mlist_pop_tid.out
	rm test_mlist_pop_first.out
	rm test_mlist_exist_tid.out
