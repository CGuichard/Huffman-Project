/**
 * @file tuple.c
 * @author Clément GUICHARD
 * @standard C99
 * @version 1.0
 * @date 11th October 2018
 *
 * @brief Implementation file for the struct "tuple".
 *
 * This file implements the struct "tuple" described in the file "tuple.h",
 * a generic structure for multiple uses.
 *
 * Overview about public functions of tuple:
 *  - createTuple
 *  - createTupleByCopy
 *  - makeCopyTuple
 *  - destroyTuple
 *  - destroyTupleGen
 *  - printTuple
 *  - printTupleGen
 *  - getTupleKey
 *  - getTupleValue
 *  - isKeyOfTuple
 *  - isValueOfTuple
 */

#include "tuple.h"


/* ================================================== */
/* ==================== STRUCT DEF ================== */
/* ========================================================================== */


/**
 * @struct tuple
 * @brief A tuple contains a key and a value.
 *
 * The structure tuple represents a key and a value, both with generic types,
 * and pointers on functions needed to manage a tuple.
 */
struct tuple {
  void *key; /**< Generic pointer on the key of the tuple */
  void *val; /**< Generic pointer on the value of the tuple */
  void (*destroyKey)(void **elem); /**< Function used to destroy the key */
  void (*destroyValue)(void **elem); /**< Function used to destroy the value */
  void (*printKey)(void *key); /**< Function used to print the key */
  void (*printValue)(void *val); /**< Function used to print the value */
};


/* ================================================== */
/* ================ STRUCT FUNCTIONS ================ */
/* ========================================================================== */


/**
 * @see @file tuple.h / @function createTuple
 */
tpl createTuple(void *key, void *val, void(*destroyKey)(void **elem), void(*printKey)(void *key), void(*destroyValue)(void **elem), void(*printValue)(void *val)) {
  tpl t = (tpl)malloc(sizeof(struct tuple));
  t->key = key;
  t->val = val;
  t->destroyKey   = destroyKey;
  t->printKey     = printKey;
  t->destroyValue = destroyValue;
  t->printValue   = printValue;
  return t;
}

/**
 * @see @file tuple.h / @function createTupleByCopy
 */
tpl createTupleByCopy(void *key, void *val, void*(*copyKey)(void *key), void(*destroyKey)(void **elem), void(*printKey)(void *key), void*(*copyValue)(void *val), void(*destroyValue)(void **elem), void(*printValue)(void *val)) {
  tpl t = (tpl)malloc(sizeof(struct tuple));
  t->key = (*copyKey)(key);
  t->val = (*copyValue)(val);
  t->destroyKey   = destroyKey;
  t->printKey     = printKey;
  t->destroyValue = destroyValue;
  t->printValue   = printValue;
  return t;
}

/**
 * @see @file tuple.h / @function makeCopyTuple
 */
tpl makeCopyTuple(tpl tuple, void*(*copyKey)(void *key), void*(*copyValue)(void *val)) {
  tpl t = (tpl)malloc(sizeof(struct tuple));
  t->key = (*copyKey)(tuple->key);
  t->val = (*copyValue)(tuple->val);
  t->destroyKey   = tuple->destroyKey;
  t->printKey     = tuple->printKey;
  t->destroyValue = tuple->destroyValue;
  t->printValue   = tuple->printValue;
  return t;
}

/**
 * @see @file tuple.h / @function destroyTuple
 */
void destroyTuple(tpl *tuple) {
  if(*tuple != NULL) {
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

/**
 * @see @file tuple.h / @function destroyTupleGen
 */
void destroyTupleGen(void **tuple) {
  destroyTuple((tpl*)tuple);
}

/**
 * @see @file tuple.h / @function printTuple
 */
void printTuple(tpl tuple) {
  if(tuple != NULL) {
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

/**
 * @see @file tuple.h / @function printTupleGen
 */
void printTupleGen(void *tuple) {
  printTuple((tpl)tuple);
}

/**
 * @see @file tuple.h / @function getTupleKey
 */
void* getTupleKey(tpl tuple) {
  return tuple->key;
}

/**
 * @see @file tuple.h / @function getTupleValue
 */
void* getTupleValue(tpl tuple) {
  return tuple->val;
}

/**
 * @see @file tuple.h / @function isKeyOfTuple
 */
int isKeyOfTuple(tpl tuple, void *key, int(*equals)(void *val1, void *val2)) {
  return (*equals)(tuple->key, key);
}

/**
 * @see @file tuple.h / @function isValueOfTuple
 */
int isValueOfTuple(tpl tuple, void *val, int(*equals)(void *val1, void *val2)) {
  return (*equals)(tuple->val, val);
}


/* ========================================================================== */
/* ========================================================================== */
