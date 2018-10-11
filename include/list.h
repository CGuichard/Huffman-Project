/**
 * @file list.h
 * @author Clément GUICHARD
 * @standard C99
 * @version 1.0
 * @date 11th October 2018
 *
 * @brief Header file for the struct "list".
 *
 * The structure list is a dynamic list, it size
 * is modified when needed. This list is also generic
 * to support any type of element. However, the type
 * of variables pointed to by the list must be
 * constrained by a principle of uniqueness. One list can
 * contain only integers, or only characters, or only
 * one type of struct for example.
 *
 * Overview about public functions of list:
 *    - createList
 *    - createDefinedList
 *    - getListSize
 *    - setListElemDestroyer
 *    - setListElemPrinter
 *    - destroyList
 *    - emptyTheList
 *    - printList
 *    - addInList
 *    - popList
 *    - popFromList
 *    - removeFromList
 *    - getOfList
 */

/* ========================================================= */
/* =================== LIST_H FILE HEADER ================== */
/* ========================================================================== */

#ifndef LIST_H
#define LIST_H

/* ============ Includes =========== */

#include <stdlib.h>
#include <stdio.h>
#include "utils.h" /**< Contains useful tool functions  */

/* ============= Struct ============ */

/**
 * @typedef lst
 * @brief Definition of lst, a pointer of the structure list.
 *
 * The struct list is said existing, but truly implemented in the file
 * "list.c". The idea is to make a structure with unknown members so that
 * the structure is manipulated only by the functions detailed here.
 */
typedef struct list* lst;

/* ======== Struct functions ======= */

/**
 * @function createList
 * @brief Creates a new struct list and gives its pointer.
 *
 * This function creates a new struct list, sets the size, the number of allocated
 * blocks in memory to 0. The pointer of the list of elements is set NULL, like
 * the destroyer and the printer for the elements of the list.
 *
 * @return{lst}: pointer of the new list.
 */
lst createList();

/**
 * @function createDefinedList
 * @brief Creates a new struct list, gives its pointer, sets the destroyer
 * and the printer.
 *
 * This function creates a new struct list, sets the size, the number of allocated
 * blocks in memory to 0. The pointer of the list of elements is set NULL. The
 * destroyer and the printer for the elements of the list are set from the
 * given ones in the parameters of the function.
 *
 * @param{void()} destroyElem(void **elem): function that destroy the type of
 *                                          element currently used in the list.
 * @param{void()} printElem(void *elem): function that print the type of element
 *                                       currently used in the list.
 *
 * @return{lst}: pointer of the new list.
 */
lst createDefinedList(void(*destroyElem)(void **elem),
                      void(*printElem)(void *elem)
                     );

/**
 * @function getListSize
 * @brief Getter of the list size.
 *
 * Getter that gives the size of a given list. The size of the list is the number
 * of element in the list, not the "memory size".
 *
 * @param{lst} l: pointer of the list which we want the size.
 *
 * @return{size_t}: size of the list.
 */
size_t getListSize(lst l);

/**
 * @function setListElemDestroyer
 * @brief Sets the element printer for the list.
 *
 * Sets the element destroyer for the list, because the list is generic and we
 * need to know how to free the element.
 *
 * @param{lst} l: pointer of the list
 * @param{void()} destroyElem(void **elem): function that destroys the type of
 *                                          element currently used in the list.
 *
 * @return{void}
 */
void setListElemDestroyer(lst l, void(*destroyElem)(void **elem));

/**
 * @function setListElemPrinter
 * @brief Sets the element printer for the list.
 *
 * Sets the element printer for the list, because the list is generic and we need
 * to know how to print the element.
 *
 * @param{lst} l: pointer of the list.
 * @param{void()} printElem(void *elem): function that print the type of element
 *                                       currently used in the list.
 *
 * @return{void}
 */
void setListElemPrinter(lst l, void(*printElem)(void *elem));

/**
 * @function destroyList
 * @brief Destroys a list.
 *
 * Destroyer that destroys a given list pointer, so it needs the pointer of the
 * pointer not to delete a "copy" pointer created for the function call.
 * Every element of the list is destroyed, the list of pointers contained in the
 * structure is destroyed too. Finally, the pointer of the list is destroyed
 * when all allocated objects contained by the structure list have been destroyed
 * and pointers set to NULL.
 *
 * @param{lst*} l: pointer of the pointer of the list which we want to
 *                 be destroyed.
 *
 * @return{void}
 */
void destroyList(lst *l);

/**
 * @function emptyTheList
 * @brief Empties the list of its elements.
 *
 * This function returns the list to an empty state, by destroying each element
 * pointed by the list, and sets the size to 0. After the release of all memory
 * allocation for the elements, the pointer on the list of elements itself is
 * destroyed (not the struct pointer, but the member of the struct list that
 * contains the list of pointer).
 *
 * @param{lst} l: pointer of the list.
 *
 * @return{void}
 */
void emptyTheList(lst l);

/**
 * @function printList
 * @brief Prints a list.
 *
 * Prints a given list. This function uses a printer contained in the struct list.
 * that's used to print the elements of the list.
 *
 * @param{lst} l: pointer of the list.
 *
 * @return{void}
 */
void printList(lst l);

/**
 * @function addInList
 * @brief Adds the pointer of an element in the list.
 *
 * Adds the pointer of an element in the list. The pointer is a generic one
 * (void*) because the list is generic.
 *
 * @param{lst} l: pointer of the list.
 * @param{void*} elem: pointer of the element.
 *
 * @return{void}
 */
void addInList(lst l, void *elem);

/**
 * @function popList
 * @brief Destroys the last element of a list.
 *
 * This function pops the list, so it destroys the last element of the list and
 * adjusts the size to the new size after the pop.
 *
 * @param{lst} l: pointer of the list.
 *
 * @return{void}
 */
void popList(lst l);

/**
 * @function popFromList
 * @brief Pops a chosen element of a list.
 *
 * This function destroys the element of the list with its index, and adjusts the
 * size to the new size after the remove of the element.
 *
 * @param{lst} l: pointer of the list.
 * @param{size_t} pos: index of the element, its position.
 *
 * @return{void}
 */
void popFromList(lst l, size_t pos);

/**
 * @function removeFromList
 * @brief Removes an element from the list, and gives its pointer.
 *
 * This function is like popFromList, but doesn't destroy the element, the
 * pointer of the element is removed from the list, but the pointer is given by
 * the function so that the element is not destroyed.
 *
 * @param{lst} l: pointer of the list.
 * @param{size_t} pos: index of the element, its position.
 *
 * @return{void*}: pointer of the element.
 */
void* removeFromList(lst l, size_t pos);

/**
 * @function getOfList
 * @brief Gets the pointer of an element of a list.
 *
 * This function returns the pointer of an element at a given index in the list.
 *
 * @param{lst} l: pointer of the list.
 * @param{size_t} pos: index of the element, its position.
 *
 * @return{void*}: pointer of the element.
 */
void* getOfList(lst l, size_t pos);


#endif

/* ========================================================================== */
/* ========================================================================== */
