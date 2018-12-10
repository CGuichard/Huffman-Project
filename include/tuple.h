/**
 * @file tuple.h
 * @author Clément GUICHARD <clement.guichard1@etu.univ-orleans.fr>
 * @standard C99
 * @version 1.0
 * @date 11th October 2018
 *
 * @brief Header file for the struct "tuple".
 *
 * The tuple structure represents two variables, a key
 * and a value. The types of the key and the value are generic
 * to allow a free use of the structure.
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

/* ========================================================= */
/* ================== TUPLE_H FILE HEADER ================== */
/* ========================================================================== */

#ifndef TUPLE_H
#define TUPLE_H

/* ============ Includes =========== */

#include <stdlib.h>
#include <stdio.h>
#include "utils.h" /**< Contains useful tool functions  */

/* ============= Struct ============ */

/**
 * @typedef tpl
 * @brief Definition of tpl, a pointer of the structure tuple.
 *
 * The struct tuple is said existing, but truly implemented in the file
 * "tuple.c". The idea is to make a structure with unknown members so that
 * the structure is manipulated only by the functions detailed here.
 */
typedef struct tuple* tpl;

/* ======== Struct functions ======= */

/**
 * @function createTuple
 * @brief This function creates a new tuple.
 *
 * @param{void*} key: pointer on the key of the tuple.
 * @param{void*} val: pointer on the value of the tuple.
 * @param{void()} destroyKey(void **elem): function used to destroy the key when
 *                                         the type cannot be destroyed with a
 *                                         simple "free".
 * @param{void()} printKey(void *key): function used to print the key (because
 *                                     we don't know the real type of the key).
 * @param{void()} destroyValue(void **elem): function used to destroy the value
 *                                           when the type cannot be destroyed
 *                                           with a simple "free".
 * @param{void()} printValue(void *val): function used to print the key (because
 *                                       we don't know the real type of the key).
 *
 * @return{tpl}: The pointer of the new tuple.
 */
tpl createTuple(void *key,
                void *val,
                void(*destroyKey)(void **elem),
                void(*printKey)(void *key),
                void(*destroyValue)(void **elem),
                void(*printValue)(void *val)
               );

/**
 * @function createTupleByCopy
 * @brief Creates a tuple by copy of a key and a value.
 *
 * Like createTuple this function creates a new tuple, but doesn't take directly
 * the pointer of the key and the value, it allocates new pointers and copies their
 * values in the new pointers with the help of copy functions.
 *
 * @param{void*} key: pointer on the key of the tuple.
 * @param{void*} val: pointer on the value of the tuple.
 * @param{void*()} copyKey(void *key): function used to create a new pointer
 *                                     with the copy of the key value.
 * @param{void()} destroyKey(void **elem): function used to destroy the key when
 *                                         the type cannot be destroyed with a
 *                                         simple "free".
 * @param{void()} printKey(void *key): function used to print the key (because
 *                                     we don't know the real type of the key).
 * @param{void*()} copyValue(void *val): function used to create a new pointer
 *                                       with the copy of the key value.
 * @param{void()} destroyValue(void **elem): function used to destroy the value
 *                                           when the type cannot be destroyed
 *                                           with a simple "free".
 * @param{void()} printValue(void *val): function used to print the key (because
 *                                       we don't know the real type of the key).
 *
 * @return{tpl}: The pointer of the new tuple.
 */
tpl createTupleByCopy(void *key,
                      void *val,
                      void*(*copyKey)(void *key),
                      void(*destroyKey)(void **elem),
                      void(*printKey)(void *key),
                      void*(*copyValue)(void *val),
                      void(*destroyValue)(void **elem),
                      void(*printValue)(void *val)
                     );

/**
 * @function makeCopyTuple
 * @brief This function makes a copy of a given tuple.
 *
 * @param{tpl} tuple: pointer on the tuple to copy.
 * @param{void*()} copyKey(void *key): function used to create a new pointer
 *                                     with the copy of the key value.
 * @param{void*()} copyValue(void *val): function used to create a new pointer
 *                                       with the copy of the key value.
 *
 * @return{tpl}: The pointer of the new tuple.
 */
tpl makeCopyTuple(tpl tuple,
                  void*(*copyKey)(void *key),
                  void*(*copyValue)(void *val)
                 );

/**
 * @function destroyTuple
 * @brief Destroys a tuple.
 *
 * This function destroys a tuple, by releasing the allocated memory dedicated to
 * its members, and destroying the pointer.
 *
 * @param{tpl*} tuple: pointer on the pointer of the tuple.
 *
 * @return{void}
 */
void destroyTuple(tpl *tuple);

/**
 * @function destroyTupleGen
 * @brief Destroys a tuple pointed by a generic pointer.
 *
 * Like destroyTuple, but takes a void** in parameter, for generic purposes of the
 * tuple in other files.
 *
 * @param{void**} tuple: pointer on the pointer of the tuple (cast to void).
 *
 * @return{void}
 */
void destroyTupleGen(void **tuple);

/**
 * @function printTuple
 * @brief Prints a tuple.
 *
 * This function prints a tuple, by printing the key and the value like:
 * "(key : value)".
 *
 * @param{tpl} tuple: pointer of the tuple to print.
 *
 * @return{void}
 */
void printTuple(tpl tuple);

/**
 * @function printTupleGen
 * @brief Prints a tuple pointed by a generic pointer.
 *
 * Like printTuple, but takes a void* in parameter, for generic purposes of the
 * tuple in other files.
 *
 * @param{void*} tuple: pointer of the tuple to print.
 *
 * @return{void}
 */
void printTupleGen(void *tuple);

/**
 * @function getTupleKey
 * @brief Gives a pointer of the key of a tuple.
 *
 * This function returns a generic pointer (void*) to the key of the given
 * tuple, which need to be cast to the true type of the key after being get.
 *
 * @param{tpl} tuple: pointer of the tuple.
 *
 * @return{void*}: pointer of the key.
 */
void* getTupleKey(tpl tuple);

/**
 * @function getTupleValue
 * @brief Gives a pointer of the value of a tuple.
 *
 * This function returns a generic pointer (void*) to the value of the given
 * tuple, which need to be cast to the true type of the value after being get.
 *
 * @param{tpl} tuple: pointer of the tuple.
 *
 * @return{void*}: pointer of the value.
 */
void* getTupleValue(tpl tuple);

/**
 * @function isKeyOfTuple
 * @brief Tells if a key is the key of a tuple.
 *
 * This function tells if a given key equals to the key of a given tuple using an
 * equals function.
 *
 * @param{tpl} tuple: pointer of the tuple.
 * @param{void*} key: pointer of the key to test.
 * @param{int()} equals(void *val1, void *val2): equals function to test if the
 *                                               key of the tuple and the key
 *                                               are equals, the function with
 *                                               void* pointers for generic
 *                                               purposes.
 *
 * @return{int}: Integer that represents a boolean value. A '0' equals to false,
 * and another value means true.
 */
int isKeyOfTuple(tpl tuple, void *key, int(*equals)(void *val1, void *val2));

/**
 * @function isValueOfTuple
 * @brief Tells if a value is the value of a tuple.
 *
 * This function tells if a given value equals to the value of a given tuple using
 * an equals function.
 *
 * @param{tpl} tuple: pointer of the tuple.
 * @param{void*} val: pointer of the value to test.
 * @param{int()} equals(void *val1, void *val2): equals function to test if the
 *                                               value of the tuple and the
 *                                               value are equals, the function
 *                                               with void* pointers for generic
 *                                               purposes.
 *
 * @return{int}: Integer that represents a boolean value. A '0' equals to false,
 * and another value means true.
 */
int isValueOfTuple(tpl tuple, void *val, int(*equals)(void *val1, void *val2));


#endif

/* ========================================================================== */
/* ========================================================================== */
