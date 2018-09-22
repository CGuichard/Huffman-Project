#include "tuple.h"

/* ================================================== */
/* ==================== STRUCT DEF ================== */
/* ============================================================================ */

struct tuple {
  void* key;
  void* val;
  void (*destroyKey)(void **elem);
  void (*destroyValue)(void **elem);
  void (*printKey)(void *key);
  void (*printValue)(void *val);
};

/* ================================================== */
/* ===================== PUBLIC ===================== */
/* ============================================================================ */

tpl createTuple(void *key, void *val, void(*destroyKey)(void **elem), void(*printKey)(void *key), void(*destroyValue)(void **elem), void(*printValue)(void *val)){
  tpl t = (tpl)malloc(sizeof(struct tuple));
  t->key = key;
  t->val = val;
  t->destroyKey   = destroyKey;
  t->printKey     = printKey;
  t->destroyValue = destroyValue;
  t->printValue   = printValue;
  return t;
}

tpl createTupleByCopy(void *key, void *val, void*(*copyKey)(void *key), void(*destroyKey)(void **elem), void(*printKey)(void *key), void*(*copyValue)(void *val), void(*destroyValue)(void **elem), void(*printValue)(void *val)){
  tpl t = (tpl)malloc(sizeof(struct tuple));
  t->key = (*copyKey)(key);
  t->val = (*copyValue)(val);
  t->destroyKey   = destroyKey;
  t->printKey     = printKey;
  t->destroyValue = destroyValue;
  t->printValue   = printValue;
  return t;
}

tpl makeCopyTuple(tpl tuple, void*(*copyKey)(void *key), void*(*copyValue)(void *val)){
  tpl t = (tpl)malloc(sizeof(struct tuple));
  t->key = (*copyKey)(tuple->key);
  t->val = (*copyValue)(tuple->val);
  t->destroyKey   = tuple->destroyKey;
  t->printKey     = tuple->printKey;
  t->destroyValue = tuple->destroyValue;
  t->printValue   = tuple->printValue;
  return t;
}

void destroyTuple(tpl *tuple){
  if(*tuple != NULL){
    if ((*tuple)->key != NULL) {
      if((*tuple)->destroyKey != NULL) (*tuple)->destroyKey(&((*tuple)->key));
      else free((*tuple)->key);
    }
    if ((*tuple)->val != NULL) {
      if((*tuple)->destroyValue != NULL) (*tuple)->destroyValue(&((*tuple)->val));
      else free((*tuple)->val);
    }
    free(*tuple);
  }
}

void destroyTupleGen(void **tuple){
  destroyTuple((tpl*)tuple);
}

void printTuple(tpl tuple){
  if(tuple != NULL){
    printf("(");
    if(tuple->printKey != NULL)
      tuple->printKey(tuple->key);
    else
      printf("<Key printer is null>");
    printf(" : ");
    if(tuple->printValue != NULL)
      tuple->printValue(tuple->val);
    else
      printf("<Value printer is null>");
    printf(")");
  }
}

void printTupleGen(void *tuple){
  printTuple((tpl)tuple);
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
