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
 * to support any type of element. However the type
 * of variables pointed to by the list must be
 * constrained by a principle of uniqueness. One list can
 * contain only integers, or only characters, or only
 * one type of struct for example.
 *
 * Overview about public functions of tuple:
 *    - createList
 *    - createDefinedList
 *    - getListSize
 *    - setElemDestroyer
 *    - setElemPrinter
 *    - destroyList
 *    - emptyTheList
 *    - printList
 *    - addInList
 *    - popList
 *    - removeInList
 *    - popInList
 *    - get
 */

/* ========================================================= */
/* =================== LIST_H FILE HEADER ================== */
/* ========================================================================== */

#ifndef LIST_H
#define LIST_H

/* ========= Includes ======== */

#include <stdlib.h>
#include <stdio.h>
#include "utils.h" /**< Contains useful tool functions  */

/* ========== Struct ========= */

/**
 * @typedef lst
 * @brief Definition of lst, a pointer of the structure list
 *
 * The struct list is said existing, but truly implemented in the file
 * "list.c". The idea is to make a structure with unknown members so that
 * the structure is manipulated only by the functions detailed here
 */
typedef struct list* lst;

/* ======== Functions ======== */

/** ===========================================================================/
 * @function createList
 * @brief Create a new struct list and give its pointer
 *
 * This function create a new struct list, set the size, the number of allocated
 * blocks in memory to 0. The pointer of the list of elements is set NULL, like
 * the destroyer and the printer for the elements of the list.
 *
 * @return{lst}: pointer of the new list
 */
lst createList();

/** ===========================================================================/
 * @function createDefinedList
 * @brief Create a new struct list, give its pointer, set destroyer and printer
 *
 * This function create a new struct list, set the size, the number of allocated
 * blocks in memory to 0. The pointer of the list of elements is set NULL. The
 * destroyer and the printer for the elements of the list are set from the
 * given ones in the parameters of the function.
 *
 * @param{void()} destroyElem(void **elem): function that destroy the type of
 *                                          element currently used in the list
 * @param{void()} printElem(void *elem): function that print the type of element
 *                                       currently used in the list
 *
 * @return{lst}: pointer of the new list
 */
lst createDefinedList(void(*destroyElem)(void **elem), void(*printElem)(void *elem));

/** ===========================================================================/
 * @function getListSize
 * @brief Getter of the list size
 *
 * Getter that give the size of a given list. The size of the list is the number
 * of element in the list, not the "memory size".
 *
 * @param{lst} l: pointer of the list which we want the size
 *
 * @return{int}: size of the list
 */
int getListSize(lst l);

/** ===========================================================================/
 * @function setElemDestroyer
 * @brief Set the element printer for the list
 *
 * Set the element destroyer for the list, because the list is generic and we
 * need to know how to free the element
 *
 * @param{lst} l: pointer of the list
 * @param{void()} destroyElem(void **elem): function that destroy the type of
 *                                          element currently used in the list
 *
 * @return{void}
 */
void setElemDestroyer(lst l, void(*destroyElem)(void **elem));

/** ===========================================================================/
 * @function setElemPrinter
 * @brief Set the element printer for the list
 *
 * Set the element printer for the list, because the list is generic and we need
 * to know how to print the element
 *
 * @param{lst} l: pointer of the list
 * @param{void()} printElem(void *elem): function that print the type of element
 *                                       currently used in the list
 *
 * @return{void}
 */
void setElemPrinter(lst l, void(*printElem)(void *elem));

/** ===========================================================================/
 * @function destroyList
 * @brief Destroy a list
 *
 * Destroyer that destroy a given list pointer, so it need the pointer of the
 * pointer to not delete a "copy" pointer created for the function call.
 * Every element of the list is destroyed, the list of pointers contains in the
 * structure is destroyed too. Finally, the pointer of the list is destroyed
 * when all allocated objects contained by the structure list has been destroyed
 * and pointers set to NULL
 *
 * @param{lst*} l: pointer of the pointer of the list which we want to
 *                 be destroyed
 *
 * @return{void}
 */
void destroyList(lst *l);

/** ===========================================================================/
 * @function emptyTheList
 * @brief Empty the list of its elements
 *
 * This function return the list to an empty state, by destroying each element
 * pointed by the list, and set the size to 0. After the release of all memory
 * allocation for the elements, the pointer on the list of element itself is
 * destroyed (not the struct pointer, but the member of the struct list that
 * contain the list of pointer)
 *
 * @param{lst} l: pointer of the list
 *
 * @return{void}
 */
void emptyTheList(lst l);

/** ===========================================================================/
 * @function printList
 * @brief Print a list
 *
 * Print a given list. This function use a printer contained in the struct list
 * that's used to print the elements of the list
 *
 * @param{lst} l: pointer of the list
 *
 * @return{void}
 */
void printList(lst l);

/** ===========================================================================/
 * @function addInList
 * @brief Add the pointer of an element in the list
 *
 * Add the pointer of an element in the list. The pointer is a generic one
 * (void*) because the list is generic
 *
 * @param{lst} l: pointer of the list
 * @param{void*} elem: pointer of the element
 *
 * @return{void}
 */
void addInList(lst l, void *elem);

/** ===========================================================================/
 * @function popList
 * @brief Destroy the last element of a list
 *
 * This function pop the list, so it destroy the last element of the list and
 * adjust the size to the new size after the pop
 *
 * @param{lst} l: pointer of the list
 *
 * @return{void}
 */
void popList(lst l);

/** ===========================================================================/
 * @function removeInList
 * @brief Remove an element of a list
 *
 * This function destroy the element of the list with it index, and adjust the
 * size to the new size after the remove of the element.
 *
 * @param{lst} l: pointer of the list
 * @param{size_t} pos: index of the element, its position
 *
 * @return{void}
 */
void removeInList(lst l, size_t pos);

/** ===========================================================================/
 * @function popInList
 * @brief Pop an element of a list
 *
 * This function is like removeInList, but don't destroy the element, the
 * pointer of the element is removed from the list, but the pointer is given by
 * the function so that the element is not destroyed
 *
 * @param{lst} l: pointer of the list
 * @param{size_t} pos: index of the element, its position
 *
 * @return{void*}: pointer of the element
 */
void* popInList(lst l, size_t pos);

/** ===========================================================================/
 * @function get
 * @brief Get the pointer of an element of a list
 *
 * This function return the pointer of an element at a given index in the list
 *
 * @param{lst} l: pointer of the list
 * @param{size_t} pos: index of the element, its position
 *
 * @return{void*}: pointer of the element
 */
void* get(lst l, size_t pos);


#endif

/* ========================================================================== */
/* ========================================================================== */
