#!/bin/bash

echo
echo
echo :test_mlist_exist_tid
time ./test_mlist_exist_tid.out

echo
echo
echo :test_mlist_pop_first
time ./test_mlist_pop_first.out

echo
echo
echo :test_mlist_pop_tid
time ./test_mlist_pop_tid.out

echo
echo
echo :test_mlist_exist_tid_random
time ./test_mlist_pop_tid_random.out

echo
echo
echo :test_mthread
time ./test_mthread.out

echo
echo
echo :test_mutex
time ./test_mutex.out

echo
echo
