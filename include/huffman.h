/**
 * @file huffman.h
 * @author Clément GUICHARD
 * @author Thàng long CAMA
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
 *    - huffmanEncryptStr
 *    - huffmanEncryptFile
 *    - huffmanDecryptStr
 *    - huffmanDecryptFile
 *    - getEncryptionOf
 *    - writeEncryptionInFile
 *    - saveKeyInFile
 *    - getDecryptionOf
 *    - writeDecryptionInFile
 *    - getTreeFromKeyFile
 *    - charOccurencesOfStr
 *    - charOccurencesOfFile
 *    - contructBinaryTree
 *    - mergeTwoSmallerNodes
 *    - prefixesList
 *    - calculatePrefixes
 *    - makeCharactersFromBits
 *    - getTupleInListByKey
 *    - writeBitsInOpenedFile
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

char* huffmanEncryptStr(char *str);
void huffmanEncryptFile(char *fileIn, char *fileOut, char *fileKey);


char* huffmanDecryptStr(char *str);
void huffmanDecryptFile(char *fileIn, char *fileOut, char *fileKey);


char* getEncryptionOf(char *str, lst prefixes, int maxPrefixLength);
void writeEncryptionInFile(char *fileIn, char *fileOut, lst prefixes, int maxPrefixLength);
void saveKeyInFile(lst occurences, char *fileKey);


char* getDecryptionOf(char *str, nd tree);
void setResultByReadingTree(nd tree, nd *currentNode, char *path, char **result, int **resultIndex);
void writeDecryptionInFile(char *fileIn, char *fileOut, nd tree);
nd getTreeFromKeyFile(char *fileKey);


lst charOccurencesOfStr(char *str);
lst charOccurencesOfFile(char *srcFile);
nd contructBinaryTree(lst occurences);
void mergeTwoSmallerNodes(lst list);
lst prefixesList(lst occurences, char *fileKey, int *maxPrefixLength);
void calculatePrefixes(nd node, lst prefixes, char *prefix);
char* makeCharactersFromBits(char *bits, char *endChar);


tpl getTupleInListByKey(lst list, char key);
void writeBitsInOpenedFile(FILE *fileW, char *bits);


#endif

/* ========================================================================== */
/* ========================================================================== */
