#include "tuple.h"

struct tuple {
  void* key;
  void* val;
};

tpl createTuple(void *key, void *val){
  tpl t = (tpl)malloc(sizeof(struct tuple));
  t->key = key;
  t->val = val;
  return t;
}

void destroyTuple(tpl *tuple){
  free((*tuple)->key);
  free((*tuple)->val);
  free(*tuple);
}

void destroyTupleGen(void **tuple){
  destroyTuple((tpl*)tuple);
}

void* getTupleKey(tpl tuple){
  return tuple->key;
}

void* getTupleValue(tpl tuple){
  return tuple->val;
}

int isKeyOf(tpl tuple, void *key, int(*equals)(void *val1, void *val2)){
  return (*equals)(tuple->key, key);
}
