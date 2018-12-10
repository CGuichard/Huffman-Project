 /**
 * @file utils.h
 * @author Clément GUICHARD <clement.guichard1@etu.univ-orleans.fr>
 * @standard C99
 * @version 1.0
 * @date 11th October 2018
 *
 * @brief Header file for "utils.c"
 *
 * This file contains tool functions, used by
 * other files but not really belonging to a file,
 * and being useful in many places of the project.
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
* @brief Tells if two integer are equals.
*
* This function tells if two given integer values are equals. The function used
* generic pointers to make the function generic, so this is the pointers of the
* integers that's need to be passed.
*
* @param{void*} val1: pointer on the first integer (the pointer is generic).
* @param{void*} val2: pointer on the second integer (the pointer is generic).
*
* @return{int}: 0 for false and other values equals to true.
*/
int equalsInt(void *val1, void *val2);

/**
 * @function printInt
 * @brief Prints an integer.
 *
 * This function prints an integer. The generic pointer of the integer is given
 * to the function.
 *
 * @param{void*} elem: pointer on the integer (the pointer is generic).
 *
 * @return{void}
 */
void printInt(void *elem);

/**
 * @function printChar
 * @brief Prints a character.
 *
 * This function prints a character. The generic pointer of the character is
 * given to the function.
 *
 * @param{void*} elem: pointer on the character (the pointer is generic).
 *
 * @return{void}
 */
void printChar(void *elem);

/**
 * @function printChar
 * @brief Prints a string of character.
 *
 * This function prints a string. The generic pointer of the string is
 * given to the function.
 *
 * @param{void*} elem: pointer on the string (the pointer is generic).
 *
 * @return{void}
 */
void printString(void *elem);

/**
 * @function copyInt
 * @brief Returns the pointer of the copy of the given integer.
 *
 * This function allocates a new integer in the memory, copies the value of
 * the given integer into the new, and returns the pointer of the copy.
 *
 * @param{void*} elem: pointer on the integer to copy (the pointer is generic).
 *
 * @return{void*}: The generic pointer of the new integer.
 */
void* copyInt(void *elem);

/**
 * @function copyChar
 * @brief Returns the pointer of the copy of the given character.
 *
 * This function allocates a new character in the memory, copies the value of
 * the given character into the new, and returns the pointer of the copy.
 *
 * @param{void*} elem: pointer on the character to copy (the pointer is generic).
 *
 * @return{void*}: The generic pointer of the new character.
 */
void* copyChar(void *elem);

/**
 * @function copyString
 * @brief Returns the pointer of the copy of the given string.
 *
 * This function allocates a new string in the memory, copies the value of
 * the given string into the new, and returns the pointer of the copy.
 *
 * @param{void*} elem: pointer on the string to copy (the pointer is generic).
 *
 * @return{void*}: The generic pointer of the new string.
 */
void* copyString(void *elem);

/**
 * @function charBitsToChar
 * @brief Returns the character corresponding to a sequence of bits.
 *
 * This function returns a character corresponding to a sequence of bits given
 * in a string (which therefore contains only 0s and 1s).
 *
 * @param{char*} bits: sequence of bits. Must have a size of 8.
 *
 * @return{char}: The character.
 */
char charBitsToChar(char *bits);

/**
 * @function strToInt
 * @brief Returns the integer corresponding to an integer which is in a string.
 *
 * This function returns an integer, which is extracted from a string.
 *
 * @param{char*} str: string corresponding to an integer.
 *
 * @return{int}: The integer.
 */
int strToInt(char *str);

/**
 * @function decimalToBinary
 * @brief Converts a decimal to its binary form.
 *
 * This function converts an encrypted character to its unsigned binary form and
 * puts it in a buffer.
 *
 * @param{unsigned int} decimal: code of the encrypted character.
 * @param{unsigned int} nbBits: number of bits.
 * @param{char*} buffer: the buffer.
 *
 * @return{void}
 */
void decimalToBinary(unsigned int decimal, unsigned int nbBits, char *buffer);

/**
 * @function pointerAllocError
 * @brief Prints a memory allocation error, and stops the program.
 *
 * This function is called when an allocation has failed, it prints an error and
 * stops the program.
 *
 * @return{void}
 */
void pointerAllocError();

/**
 * @function pointerNullError
 * @brief Prints a null pointer error, and stops the program.
 *
 * This function is called when a function pointer that you need is
 * null, it prints an error and stops the program.
 *
 * @return{void}
 */
void pointerNullError();


#endif

/* ========================================================================== */
/* ========================================================================== */
