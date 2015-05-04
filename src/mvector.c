//
// Created by lucas on 28/04/15.
//

#include <stddef.h>
#include <mvector.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

/*
 * Vector Block Size:
 * More equals faster, but
 * also equals more memory
 * wasted when you don't use
 * the whole block.
 */
#define VECTOR_BLOCK_SIZE 1024
#define VECTOR_GROW_RATE 2

void mvector_zero_fill(MVECTOR *mvector, size_t init, size_t end) {
    size_t i;

    for (i = init; i < end; i++) {
        mvector->vector[i] = NULL;
    }
}

MVECTOR *mvector_create() {
    MVECTOR *mvector;

    mvector = malloc(sizeof(MVECTOR));

    mvector->size = VECTOR_BLOCK_SIZE;
    mvector->vector = malloc(VECTOR_BLOCK_SIZE * sizeof(METCB*));
    assert(mvector->vector != NULL);
    mvector_zero_fill(mvector, 0, VECTOR_BLOCK_SIZE-1);

    return mvector;
}

void mvector_insert(MVECTOR *mvector, METCB *metcb, int id) {
    assert(id >= 0);

    while (id >= mvector->size) {
        mvector->size *= VECTOR_GROW_RATE;
        mvector->vector = realloc(mvector->vector, (mvector->size * sizeof(METCB*)));
        assert(mvector->vector != NULL);
        mvector_zero_fill(mvector, mvector->size / VECTOR_GROW_RATE, mvector->size);
        assert(mvector != NULL);
    }

    mvector->vector[id] = metcb;
}

METCB *mvector_pop(MVECTOR *mvector, int id) {
    METCB *metcb;

    assert(mvector != NULL);
    if (id < 0) return NULL;
    if (id >= mvector->size) return NULL;

    metcb = mvector->vector[id];
    mvector->vector[id] = NULL;
    return metcb;
}

bool mvector_exist(MVECTOR *mvector, int id) {
    if (id < 0) return false;
    if (id >= mvector->size) return false;
    if (mvector->vector[id] != NULL) return true;

    return false;
}
