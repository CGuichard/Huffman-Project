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
 * The structure huffman is also declared here
 * Overview about the huffman structure functions:
 *    - createHuffman
 *    - createDefinedHuffman
 *    - getHuffmanStr
 *    - getHuffmanTree
 *    - setHuffmanStr
 *    - setHuffmanTree
 *    - destroyHuffman
 *
 * Overview about public functions of the file huffman:
 *    - huffmanEncrypt
 *    - huffmanEncryptFile
 *    - huffmanDecrypt
 *    - huffmanDecryptStr
 *    - huffmanDecryptFile
 *    - getEncryptionOf
 *    - makeCharactersFromBits
 *    - writeEncryptionInFile
 *    - saveKeyInFile
 *    - getDecryptionOf
 *    - writeDecryptionInFile
 *    - getTreeFromKeyFile
 *    - charOccurrencesOfStr
 *    - charOccurrencesOfFile
 *    - contructBinaryTree
 *    - mergeTwoSmallerNodes
 *    - mergeNodes
 *    - prefixesList
 *    - calculatePrefixes
 *    - getTupleInListByKey
 *    - weightNode
 *    - writeBitsInOpenedFile
 */

/* ========================================================= */
/* ================= HUFFMAN_H FILE HEADER ================= */
/* ========================================================================== */

#ifndef HUFFMAN_H
#define HUFFMAN_H

/* ============ Includes =========== */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h" /**< Contains useful tool functions  */
#include "tuple.h" /**< Contains struct tuple and its functions  */
#include "list.h" /**< Contains struct list and its functions  */
#include "node.h" /**< Contains struct node and its functions  */

/* ============= Struct ============ */

/**
 * @typedef hfm
 * @brief Definition of hfm, a pointer of the structure huffman
 *
 * The struct huffman is said existing, but truly implemented in the file
 * "huffman.c". The idea is to make a structure with unknown members so that
 * the structure is manipulated only by the functions detailed here
 */
typedef struct huffman* hfm;

/* ======== Struct functions ======= */

/**
 * @function createHuffman
 * @brief Create a new struct huffman and give its pointer
 *
 * This function create a new struct huffman, set its members to NULL and return
 * a pointer on that struct
 *
 * @return{hfm}: pointer of the new huffman structure
 */
hfm createHuffman();

/**
 * @function createHuffman
 * @brief Create a new struct huffman and give its pointer
 *
 * This function create a new struct huffman, set its members to the given
 * values and return a pointer on that struct
 *
 * @param{char*} str: the encrypted string
 * @param{nd} tree: the tree
 *
 * @return{hfm}: pointer of the new huffman structure
 */
hfm createDefinedHuffman(char *str, nd tree);

/**
 * @function getHuffmanStr
 * @brief Getter of the huffman struct encrypted string of characters
 *
 * @param{hfm} huffman: pointer of the huffman structure
 *
 * @return{char*}: encrypted string of characters
 */
char* getHuffmanStr(hfm huffman);

/**
 * @function getHuffmanTree
 * @brief Getter of the huffman struct tree
 *
 * @param{hfm} huffman: pointer of the huffman structure
 *
 * @return{nd}: tree of the huffman struct
 */
nd getHuffmanTree(hfm huffman);

/**
 * @function setHuffmanStr
 * @brief Setter of the huffman struct encrypted string of characters
 *
 * @param{hfm} huffman: pointer of the huffman structure
 * @param{char*} str: encrypted string of characters passed to the huffman
 *                    struct
 *
 * @return{void}
 */
void setHuffmanStr(hfm huffman, char *str);

/**
 * @function setHuffmanTree
 * @brief Setter of the huffman struct tree
 *
 * @param{hfm} huffman: pointer of the huffman structure
 * @param{nd} tree: tree passed to the huffman struct
 *
 * @return{void}
 */
void setHuffmanTree(hfm huffman, nd tree);

/**
 * @function destroyHuffman
 * @brief Destroy a huffman struct
 *
 * Destroyer that destroy a given huffman struct pointer, so it need the
 * pointer of the pointer to not delete a "copy" pointer created for the
 * function call.
 * The tree is detroyed, and the string of characters is freed
 *
 * @param{hfm*} huffman: pointer of the pointer of the huffman structure which
 *                       we want to be destroyed
 *
 * @return{void}
 */
void destroyHuffman(hfm *huffman);

/* =========== Functions =========== */

/**
 * @function huffmanEncrypt
 * @brief Encrypt a string of characters
 *
 * This function encrypt a string of characters using the huffman coding and
 * return the pointer of the corresponding huffman struct
 *
 * @param{char*} str: string of characters to encrypt
 *
 * @return{hfm}: encrypted string
 */
hfm huffmanEncrypt(char *str);

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
 * @function huffmanDecrypt
 * @brief Decrypt an huffman struct
 *
 * This function decrypt a huffman coding contains in a huffman struct (which
 * contains the string of characters to decrypt and the tree needed to do so)
 *
 * @param{hfm} huffmanEncr: A pointer on the huffman struct
 *
 * @return{char*}: decrypted string
 */
char* huffmanDecrypt(hfm huffmanEncr);

/**
 * @function huffmanDecrypt
 * @brief Decrypt a string of characters
 *
 * This function decrypt a string of characters encrypt with the huffman coding
 * by using a tree
 *
 * @param{char*} str: string of characters to decrypt
 * @param{nd} tree: the tree needed to decrypt
 *
 * @return{char*}: decrypted string
 */
char* huffmanDecryptStr(char *str, nd tree);

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
 * @param{char*} str: string of characters to encrypt (bits form)
 * @param{lst} prefixes: list of prefixes that give the bit sequence associated
 *                       for each character in fileIn
 * @param{int} maxPrefixLength: maximal size of a prefix
 *
 * @return{char*}: Encryption in its bits form
 */
char* getEncryptionOf(char *str, lst prefixes, int maxPrefixLength);

/**
 * @function makeCharactersFromBits
 * @brief Return a string of characters encrypted (compressed)
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
 * Returns the decryption of the string of characters given in parameters by
 * using the tree used to the encryption
 *
 * @param{char*} str: string of characters to decrypt
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
 * @function charOccurrencesOfStr
 * @brief Create a list of occurrences from a given string of characters
 *
 * Create a list of occurrences from the string of characters 'str' given in
 * parameter. The character \0 is add to dedicate a prefix for it
 *
 * @param{char*} str: the string of characters
 *
 * @return{lst}: the occurrences
 */
lst charOccurrencesOfStr(char *str);

/**
 * @function charOccurrencesOfFile
 * @brief Create a list of occurrences from a file
 *
 * Create a list of occurrences from a file given in parameter. The
 * character \0 is add to dedicate a prefix for it
 *
 * @param{char*} srcFile: name of the file
 *
 * @return{lst}: the occurrences
 */
lst charOccurrencesOfFile(char *srcFile);

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
 * @param{int()} weight(void *elem): function to get the weight of a node
 *
 * @return{void}
 */
void mergeTwoSmallerNodes(lst list, int(*weight)(void *elem));

/**
 * @function mergeNodes
 * @brief Merge two nodes
 *
 * This function merge two nodes, by making a node with a weight equal to the
 * two nodes weight. The two child of the node are the given nodes.
 *
 * @param{nd} node1: first node
 * @param{nd} node2: second node
 * @param{int()} weight(void *elem): function to get the weight of a node
 *
 * @return{nd}: the new node
 */
nd mergeNodes(nd node1, nd node2, int(*weight)(void *elem));

/**
 * @function prefixesList
 * @brief Returns the prefixes for each character
 *
 * Returns the prefixes for each character from a given tree
 *
 * @param{nd} tree: the tree
 * @param{int} maxPrefixLength: maximal size of a prefix
 *
 * @return{lst}: the prefixes
 */
lst prefixesList(nd tree, int *maxPrefixLength);

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
 * @function weightNode
 * @brief Return the node weight (value of the tuple which is the node tag)
 *
 * @param{void*} elem: the node
 *
 * @return{int}: the node weight
 */
int weightNode(void *elem);

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
