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

void destroyTuple(tpl* tuple){
  free((*tuple)->key);
  free((*tuple)->val);
  free(*tuple);
}

void* getKey(tpl tuple){
  return tuple->key;
}

void* getValue(tpl tuple){
  return tuple->val;
}

int isKeyOf(tpl tuple, void* key, int(*equals)(void *val1, void *val2)){
  return (*equals)(tuple->key, key);
}
