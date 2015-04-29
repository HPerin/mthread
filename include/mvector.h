//
// Created by lucas on 28/04/15.
//

#ifndef MTHREAD_MVECTOR_H
#define MTHREAD_MVECTOR_H

#include <stdbool.h>
#include "metcb.h"

typedef struct s_mvector {
    size_t size;
    METCB **vector;
} MVECTOR;

MVECTOR *mvector_create();

void mvector_insert(MVECTOR *mvector, METCB *metcb, int id);

METCB *mvector_pop(MVECTOR *mvector, int id);

bool mvector_exist(MVECTOR *mvector, int id);

#endif //MTHREAD_MVECTOR_H
