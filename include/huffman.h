/**
 * @file huffman.h
 * @author Clément GUICHARD
 * @standard C99
 * @version 1.0
 * @date 11th October 2018
 *
 * @brief Header file for the huffman project.
 *
 * This file describe the functions used in the file "huffman.c" to encrypt and
 * decrypt ASCII text using the Huffman coding.
 *
 * Overview about public functions of tuple:
 *    - encrypt
 *    - charOccurences
 *    - getTupleInListByKey
 */

/* ========================================================= */
/* ================= HUFFMAN_H FILE HEADER ================= */
/* ========================================================================== */

#ifndef HUFFMAN_H
#define HUFFMAN_H

/* ========= Includes ======== */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h" /**< Contains useful tool functions  */
#include "tuple.h" /**< Contains struct tuple and its functions  */
#include "list.h" /**< Contains struct list and its functions  */
#include "node.h" /**< Contains struct node and its functions  */

/* ======== Functions ======== */

char* encryptStr(char *str);
// void encryptFile(char *fileIn, char *fileOut, char *fileKey);
// char* decryptStr(char *str);
// void decryptFile(char *fileIn, char *fileOut, char *fileKey);

lst charOccurencesOfStr(char *str);
lst charOccurencesOfFile(char *srcFile);
tpl getTupleInListByKey(lst list, char key);


#endif

/* ========================================================================== */
/* ========================================================================== */
