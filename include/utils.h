 /**
 * @file utils.h
 * @author Clément GUICHARD
 * @standard C99
 * @version 1.0
 * @date 11th October 2018
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
 *  - printString
 *  - copyInt
 *  - copyChar
 *  - copyString
 *  - charBitsToChar
 *  - strToInt
 *  - decimalToBinary
 *  - pointerAllocError
 *  - pointerNullError
 */

/* ========================================================= */
/* ================== UTILS_H FILE HEADER ================== */
/* ========================================================================== */

#ifndef UTILS_H
#define UTILS_H

/* ============ Includes =========== */

#include <stdlib.h>
#include <stdio.h>
#include <string.h> /**< used for strlen, strcpy and strcat function */
#include <math.h> /**< used for pow function */

/* =========== Functions =========== */

/**
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

/**
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

/**
 * @function printChar
 * @brief Print a character
 *
 * This function print a character. The generic pointer of the character is
 * given to the function
 *
 * @param{void*} elem: pointer on the character (the pointer is generic)
 *
 * @return{void}
 */
void printChar(void *elem);

/**
 * @function printChar
 * @brief Print a string of character
 *
 * This function print a string. The generic pointer of the string is
 * given to the function
 *
 * @param{void*} elem: pointer on the string (the pointer is generic)
 *
 * @return{void}
 */
void printString(void *elem);

/**
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

/**
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

/**
 * @function copyString
 * @brief Return the pointer of the copy of the given string
 *
 * This function allocates a new string in the memory, copies the value of
 * the given string into the new, and returns the pointer of the copy
 *
 * @param{void*} elem: pointer on the string to copy (the pointer is generic)
 *
 * @return{void*}: The generic pointer of the new string
 */
void* copyString(void *elem);

/**
 * @function charBitsToChar
 * @brief Returns the character corresponding to a sequence of bits
 *
 * This function return a character corresponding to a sequence of bits given
 * in a string (which therefore contains only 0s and 1s)
 *
 * @param{char*} bits: sequence of bits. Must have a size of 8
 *
 * @return{char}: The character
 */
char charBitsToChar(char *bits);

/**
 * @function strToInt
 * @brief Returns the integer corresponding to an integer which is in a string
 *
 * This function return an integer, which is extracted from a string
 *
 * @param{char*} str: string corresponding to an integer
 *
 * @return{int}: The integer
 */
int strToInt(char *str);

/**
 * @function decimalToBinary
 * @brief Converts a decimal to its binary form
 *
 * This function converts an encrypted character to its unsigned binary form.
 *
 * @param{unsigned int} decimal: code of the encrypted character
 * @param(int) numberOfBits: the size of the binary form (8bits, 16bits, ...)
 *
 * @return{char*}: the binary form of the decimal
 */
char* decimalToBinary(unsigned int decimal, int numberOfBits);

/**
 * @function pointerAllocError
 * @brief Print a memory allocation error, and stop the program
 *
 * This function is called when an allocation has failed, it prints an error and
 * stops the program
 *
 * @return{void}
 */
void pointerAllocError();

/**
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
