#ifndef TUPLE_H
#define TUPLE_H

/* ========================================================= */
/* ================== TUPLE_H FILE HEADER ================== */
/* ========================================================= */

/* ========= Includes ======== */

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

/* ========== Struct ========= */

typedef struct tuple* tpl;

/* ======== Functions ======== */

tpl createTuple(void *key, void *val, void(*destroyKey)(void **elem), void(*printKey)(void *key), void(*destroyValue)(void **elem), void(*printValue)(void *val));
tpl createTupleByCopy(void *key, void *val, void*(*copyKey)(void *key), void(*destroyKey)(void **elem), void(*printKey)(void *key), void*(*copyValue)(void *val), void(*destroyValue)(void **elem), void(*printValue)(void *val));
tpl makeCopyTuple(tpl tuple, void*(*copyKey)(void *key), void*(*copyValue)(void *val));

void destroyTuple(tpl *tuple);
void destroyTupleGen(void **tuple);
void printTuple(tpl tuple);
void printTupleGen(void *tuple);

void* getTupleValue(tpl tuple);
void* getTupleKey(tpl tuple);

int isKeyOf(tpl tuple, void *key, int(*equals)(void *val1, void *val2));

/* ========================================================= */

#endif
