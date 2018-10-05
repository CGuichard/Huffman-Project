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
 *    - makeCharactersFromBits
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

/**
 * @function huffmanEncryptStr
 * @brief Encrypt a string of characters
 *
 * This function encrypt a string of characters using the huffman coding and
 * return the pointer of the new encrypted string
 *
 * @param{char*} str: string of characters to encrypt
 *
 * @return{char*}: encrypted string
 */
char* huffmanEncryptStr(char *str);

/**
 * @function huffmanEncryptFile
 * @brief Encrypt a file
 *
 * This function encrypt a file by using the huffman coding
 *
 * @param{char*} fileIn: name of the file we want to encrypt
 * @param{char*} fileOut: name of the file to write
 * @param{char*} fileKey: name of the file to write the key in
 *
 * @return{void}
 */
void huffmanEncryptFile(char *fileIn, char *fileOut, char *fileKey);


/**
 * @function huffmanDecryptStr
 * @brief Decrypt a string of characters
 *
 * This function decrypt a string of characters using the huffman coding and
 * return the pointer of the decrypted string
 *
 * @param{char*} str: string of characters to decrypt
 *
 * @return{char*}: decrypted string
 */
char* huffmanDecryptStr(char *str);

/**
 * @function huffmanDecryptFile
 * @brief Decrypt a file
 *
 * This function decrypt a file by using the huffman coding
 *
 * @param{char*} fileIn: name of the file we want to decrypt
 * @param{char*} fileOut: name of the file to write
 * @param{char*} fileKey: name of the file to write the key in
 *
 * @return{void}
 */
void huffmanDecryptFile(char *fileIn, char *fileOut, char *fileKey);

/**
 * @function getEncryptionOf
 * @brief Returns the encryption in its bit form
 *
 * Returns the encryption in its bit form, that is the sequence of prefixes
 * corresponding for each character of the string passed as parameter
 *
 * @param{char*} str: string of character to encrypt (bits form)
 * @param{lst} prefixes: list of prefixes that give the bit sequence associated
 *                       for each character in fileIn
 * @param{int} maxPrefixLength: maximal size of a prefix
 *
 * @return{char*}: Encryption in its bits form
 */
char* getEncryptionOf(char *str, lst prefixes, int maxPrefixLength);

/**
 * @function makeCharactersFromBits
 * @brief Return a string of character encrypted (compressed)
 * @see @function getEncryptionOf
 *
 * Return an encrypted string. The string is the compressed form of the
 * encryption returned by getEncryptionOf, with some modification to handle
 * the problems with the potential generation of the EOF and \0
 *
 * @param{char*} bits: the sequence of bits to compress
 * @param{char*} endChar: the prefix of the end character
 *
 * @return{char*}: Encrypted characters (compressed form)
 */
char* makeCharactersFromBits(char *bits, char *endChar);

/**
 * @function writeEncryptionInFile
 * @brief Write the encryption in a file
 *
 * Encrypt a file with a list of prefixes for each character obtained by using
 * an huffman tree, and write it in another file. Handle problems with the
 * potential generation of the EOF and \0
 *
 * @param{char*} fileIn: name of the file we want to encrypt
 * @param{char*} fileOut: name of the file to write
 * @param{lst} prefixes: list of prefixes that give the bit sequence associated
 *                       for each character in fileIn
 * @param{int} maxPrefixLength: maximal size of a prefix
 *
 * @return{void}
 */
void writeEncryptionInFile(char *fileIn,
                           char *fileOut,
                           lst prefixes,
                           int maxPrefixLength
                          );

/**
 * @function saveKeyInFile
 * @brief Save the occurrences in a file (used as key to decrypt)
 *
 * Save the occurrences in a file, because it is needed to generate the huffman
 * tree to decrypt a file
 *
 * @param{lst} occurrences: occurrences to save in the file
 * @param{char*} fileKey: file to write in
 *
 * @return{void}
 */
void saveKeyInFile(lst occurrences, char *fileKey);

/**
 * @function getDecryptionOf
 * @brief Returns the decryption of the string given
 *
 * Returns the decryption of the string of character given in parameters by
 * using the tree used to the encryption
 *
 * @param{char*} str: string of character to decrypt
 * @param{lst}
 *
 * @return{char*}: Encryption in its bits form
 */
char* getDecryptionOf(char *str, nd tree);

/**
 * @function writeDecryptionInFile
 * @brief Write the decryption in a file
 *
 * Decrypt a file with the tree used to generate it, and write the decryption
 * in another file
 *
 * @param{char*} fileIn: name of the file we want to decrypt
 * @param{char*} fileOut: name of the file to write
 * @param{lst} tree: the huffman tree
 *
 * @return{void}
 */
void writeDecryptionInFile(char *fileIn, char *fileOut, nd tree);

/**
 * @function getTreeFromKeyFile
 * @brief Generate a tree from a file
 *
 * Generate a tree from a list of occurrences used to encrypt a file
 *
 * @param{char*} fileKey: name of the file containing the key (list of
 * occurrences of characters)
 *
 * @return{nd}: the tree generated contained in 'fileKey'
 */
nd getTreeFromKeyFile(char *fileKey);

/**
 * @function charOccurencesOfStr
 * @brief Create a list of occurrences from a given string of character
 *
 * Create a list of occurrences from the string of character 'str' given in
 * parameter. The character \0 is add to dedicate a prefix for it
 *
 * @param{char*} str: the string of character
 *
 * @return{lst}: the occurrences
 */
lst charOccurencesOfStr(char *str);

/**
 * @function charOccurencesOfFile
 * @brief Create a list of occurrences from a file
 *
 * Create a list of occurrences from a file given in parameter. The
 * character \0 is add to dedicate a prefix for it
 *
 * @param{char*} srcFile: name of the file
 *
 * @return{lst}: the occurrences
 */
lst charOccurencesOfFile(char *srcFile);

/**
 * @function contructBinaryTree
 * @brief Construct the binary tree used for huffman coding
 *
 * Construct the binary tree used for huffman coding from a list of occurrences
 *
 * @param{lst} occurrences: list of occurrences
 *
 * @return{nd}: the tree generated
 */
nd contructBinaryTree(lst occurrences);

/**
 * @function mergeTwoSmallerNodes
 * @brief Merge the two smaller elements of a list
 *
 * This functions merge the two smaller elements of a list. It removes the two
 * smaller items from the list, merges them into a single item, and places it
 * in the list.
 *
 * @param{lst} list: list of occurrences
 *
 * @return{void}
 */
void mergeTwoSmallerNodes(lst list);


/**
 * @function prefixesList
 * @brief Returns the prefixes for each character
 *
 * Returns the prefixes for each character from a list of occurrences after
 * course of the tree
 *
 * @param{lst} occurrences: list of occurrences
 * @param{char*} fileKey: name of the file to write the key in
 * @param{int} maxPrefixLength: maximal size of a prefix
 *
 * @return{lst}: the prefixes
 */
lst prefixesList(lst occurrences, char *fileKey, int *maxPrefixLength);


/**
 * @function contructBinaryTree
 * @brief Calculate prefixes from a tree
 * @see @function prefixesList
 *
 * Calculate the prefixes from a tree (recursively)
 *
 * @param{nd} node: a node of the tree
 * @param{lst} prefixes: list of prefixes to modifiate
 * @param{char*} prefix: maximal size of a prefix
 *
 * @return{void}
 */
void calculatePrefixes(nd node, lst prefixes, char *prefix);

/**
 * @function getTupleInListByKey
 * @brief Return a pointer on the tuple which correspond to a given key
 *
 * @param{lst} list: the list
 * @param{char} key: the key
 *
 * @return{tpl}: the pointer on the tuple found
 */
tpl getTupleInListByKey(lst list, char key);

/**
 * @function writeBitsInOpenedFile
 * @brief Write a char corresponding to a given sequence of bits in a file
 *
 * Write a char corresponding to a given sequence of bits in a file already
 * opened, and if the char is equal to \0 (00000000) it is replaced by
 * 1 (00000001) to avoid printing \0 in the file
 *
 * @param{FILE*} fileW: the list
 * @param{char*} bits: the key
 *
 * @return{void}
 */
void writeBitsInOpenedFile(FILE *fileW, char *bits);


#endif

/* ========================================================================== */
/* ========================================================================== */
