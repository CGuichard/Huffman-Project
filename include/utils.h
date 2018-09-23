/**
 * @file utils.h
 * @author GUICHARD Clément
 * @standard C99
 *
 * @brief Header file for "utils.c"
 *
 * This file contains tool functions, used by
 * other files but not really belonging to a file,
 * and being useful in many places of the project
 *
 * Overview about public functions of utils:
 *  - equalsInt
 *  - printInt
 *  - printChar
 *  - copyInt
 *  - copyChar
 *  - pointerAllocError
 *  - pointerNullError
 */

/* ========================================================= */
/* ================== UTILS_H FILE HEADER ================== */
/* ========================================================================== */

#ifndef UTILS_H
#define UTILS_H

/* ========= Includes ======== */

#include <stdlib.h>
#include <stdio.h>

/* ======== Functions ======== */

/** ===========================================================================/
* @function equalsInt
* @brief Tell if two integer are equals
*
* This function tell if two given integer values are equals. The function used
* generic pointers to make the function generic, so this is the pointers of the
* integers that's needed to be pass
*
* @param{void*} val1: pointer on the first integer (the pointer is generic)
* @param{void*} val2: pointer on the second integer (the pointer is generic)
*
* @return{int}: 0 for false and other values equals to true
*/
int equalsInt(void *val1, void *val2);

/** ===========================================================================/
* @function printInt
* @brief Print an integer
*
* This function print an integer. The generic pointer of the integer is given
* to the function
*
* @param{void*} elem: pointer on the integer (the pointer is generic)
*
* @return{void}
*/
void printInt(void *elem);

/** ===========================================================================/
* @function printChar
* @brief Print a character
*
* This function print a character. The generic pointer of the character is given
* to the function
*
* @param{void*} elem: pointer on the character (the pointer is generic)
*
* @return{void}
*/
void printChar(void *elem);

/** ===========================================================================/
* @function copyInt
* @brief Return the pointer of the copy of the given integer
*
* This function allocates a new integer in the memory, copies the value of
* the given integer into the new, and returns the pointer of the copy
*
* @param{void*} elem: pointer on the integer to copy (the pointer is generic)
*
* @return{void*}: The generic pointer of the new integer
*/
void* copyInt(void *elem);

/** ===========================================================================/
* @function copyChar
* @brief Return the pointer of the copy of the given character
*
* This function allocates a new character in the memory, copies the value of
* the given character into the new, and returns the pointer of the copy
*
* @param{void*} elem: pointer on the character to copy (the pointer is generic)
*
* @return{void*}: The generic pointer of the new character
*/
void* copyChar(void *elem);

/** ===========================================================================/
* @function pointerAllocError
* @brief Print a memory allocation error, and stop the program
*
* This function is called when an allocation has failed, it prints an error and
* stops the program
*
* @return{void}
*/
void pointerAllocError();

/** ===========================================================================/
* @function pointerNullError
* @brief Print a null pointer error, and stop the program
*
* This function is called when a function pointer that you need not null is
* null, it prints an error and stops the program
*
* @return{void}
*/
void pointerNullError();


#endif

/* ========================================================================== */
/* ========================================================================== */
