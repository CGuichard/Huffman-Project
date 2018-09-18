#ifndef TUPLE_H
#define TUPLE_H

  #ifndef STD_LIBS_H
  #define STD_LIBS_H

  #include <stdlib.h>
  #include <stdio.h>

  #endif

#include "utils.h"

typedef struct tuple* tpl;

tpl createTuple(void *key, void *val);
void destroyTuple(tpl *tuple);
void destroyTupleGen(void **tuple);
void* getTupleValue(tpl tuple);
void* getTupleKey(tpl tuple);
int isKeyOf(tpl tuple, void *key, int(*equals)(void *val1, void *val2));

#endif
