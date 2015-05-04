CC	=	gcc
LIBDIR	=	../lib
LIBFILE =	$(LIBDIR)/libmthread.a

all:	test_mlist_exist_tid test_mlist_pop_first test_mlist_pop_tid test_mlist_pop_tid_random test_mthread test_mutex test_mvector_exist_tid test_mvector_pop_tid test_mcreate test_myield test_mwait

test_mcreate:	test_mcreate.c $(LIBFILE)
	$(CC) -o test_mcreate.out test_mcreate.c -L$(LIBDIR) -lmthread -Wall

test_mlist_exist_tid:	test_mlist_exist_tid.c $(LIBFILE)
	$(CC) -o test_mlist_exist_tid.out test_mlist_exist_tid.c -L$(LIBDIR) -lmthread -Wall

test_mlist_pop_first:	test_mlist_pop_first.c $(LIBFILE)
	$(CC) -o test_mlist_pop_first.out test_mlist_pop_first.c -L$(LIBDIR) -lmthread -Wall

test_mlist_pop_tid:	test_mlist_pop_tid.c $(LIBFILE)
	$(CC) -o test_mlist_pop_tid.out test_mlist_pop_tid.c -L$(LIBDIR) -lmthread -Wall

test_mlist_pop_tid_random:	test_mlist_pop_tid_random.c $(LIBFILE)
	$(CC) -o test_mlist_pop_tid_random.out test_mlist_pop_tid_random.c -L$(LIBDIR) -lmthread -Wall

test_mthread:	test_mthread.c $(LIBFILE)
	$(CC) -o test_mthread.out test_mthread.c -L$(LIBDIR) -lmthread -Wall

test_mutex:	test_mutex.c $(LIBFILE)
	$(CC) -o test_mutex.out test_mutex.c -L$(LIBDIR) -lmthread -Wall

test_mvector_exist_tid:	test_mvector_exist_tid.c $(LIBFILE)
	$(CC) -o test_mvector_exist_tid.out test_mvector_exist_tid.c -L$(LIBDIR) -lmthread -Wall

test_mvector_pop_tid: test_mvector_pop_tid.c $(LIBFILE)
	$(CC) -o test_mvector_pop_tid.out test_mvector_pop_tid.c -L$(LIBDIR) -lmthread -Wall

test_mwait:	test_mwait.c $(LIBFILE)
	$(CC) -o test_mwait.out test_mwait.c -L$(LIBDIR) -lmthread -Wall

test_myield:	test_myield.c $(LIBFILE)
	$(CC) -o test_myield.out test_myield.c -L$(LIBDIR) -lmthread -Wall

run:	all
	./run.sh

clean:
	rm *.out
