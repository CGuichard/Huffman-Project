/**
 * @file node.h
 * @author Thàng long CAMA
 * @standard C99
 * @version 1.0
 * @date 11th October 2018
 *
 * @brief Header file for the struct "node".
 *
 * The structure node declared here represent a binary tree. This structure have
 * two "childrens", of the type node too so that a tree can be made. All nodes
 * have a tag, which have a generic tag. Our tree of node can be a tree of
 * integers, characters or even structures.
 *
 * Overview about public functions of node:
 *  - createNode
 *  - destroyLastNode
 *  - destroyNodeGen
 *  - printNodeGen
 *  - getLeft
 *  - setLeft
 *  - getRight
 *  - setRight
 *  - getTag
 *  - isValidNode
 *  - isLeaf
 */

/* ========================================================= */
/* =================== NODE_H FILE HEADER ================== */
/* ========================================================================== */

#ifndef NODE_H
#define NODE_H

/* ========= Includes ======== */

#include <stdlib.h>
#include <stdio.h>

/* ========== Struct ========= */

/**
 * @typedef nd
 * @brief Definition of nd, a pointer of the structure node
 *
 * The struct node is said existing, but truly implemented in the file
 * "node.c". The idea is to make a structure with unknown members so that
 * the structure is manipulated only by the functions detailed here
 */
typedef struct node* nd;

/* ======== Functions ======== */

/** ===========================================================================/
 * @function createNode
 * @brief This function creates a new node
 *
 * @param{void*} tag: pointer on the tag of the node
 *
 * @return{nd}: The pointer of the new node
 */
nd createNode(void* tag);

/** ===========================================================================/
 * @function destroyLastNode
 * @brief Destroys recursively all the children of a node
 *
 * @param{nd} n: the node where the children have to be freed
 * @param{void*()} destroyer(void **elem): function used to destroy the value
 *                                         when the type cannot be destroyed
 *                                         with a simple "free"
 *
 * @return{void}
 */
void destroyLastNode(nd n, void(*destroyer)(void **elem));

/** ===========================================================================/
 * @function destroyLastNode
 * @brief Destroys recursively all the children of a node AND the node itself
 *
 * @param{nd} n: the node where the children have to be freed
 * @param{void*()} destroyer(void **elem): function used to destroy the value
 *                                         when the type cannot be destroyed
 *                                         with a simple "free"
 *
 * @return{void}
 */
void destroyNodeGen(nd* n, void(*destroyer)(void **elem));

/** ===========================================================================/
* @function printNodeGen
* @brief Prints a node
*
* This function prints a node, by printing its children and its tag like:
* <Node | Tag : 50>[<Leaf | Tag : 25>[,],<Leaf | Tag : 25>[,]]
*
*
* @param{nd} node: the node to print
* @param{void*()} printTag(void *tag): function used to print the tag with the
*                                       correct format
*
* @return{void}
*/
void printNodeGen(nd n, void(*printTag)(void *tag));

/** ===========================================================================/
 * @function getLeft
 * @brief Gets the left child of the node
 *
 * @param{nd} n: the node where the child is
 *
 * @return{nd*}: the address of the left child's pointer
 */
nd* getLeft(nd n);

/** ===========================================================================/
 * @function setLeft
 * @brief Sets the left child of the node
 *
 * @param{nd} n: the node where the child has to be set
 * @param{void*} tag: pointer on the tag of the node
 *
 * @return{void}
 */
void setLeft(nd n, void* tag);

/** ===========================================================================/
 * @function getRight
 * @brief Gets the right child of the node
 *
 * @param{nd} n: the node where the child is
 *
 * @return{nd*}: the address of the right child's pointer
 */
nd* getRight(nd n);

/** ===========================================================================/
 * @function setRight
 * @brief Sets the right child of the node
 *
 * @param{nd} n: the node where the child has to be set
 * @param{void*} tag: pointer on the tag of the node
 *
 * @return{void}
 */
void setRight(nd n, void* tag);

/** ===========================================================================/
 * @function getTag
 * @brief Gets the node's tag
 *
 * @param{nd} n: the node where the tag can be read
 *
 * @return{void*}: pointer on the tag of the node
 */
void* getTag(nd n);

/** ===========================================================================/
 * @function isValidNode
 * @brief Checks a node's validity
 *
 * @param{nd} n: the node to check
 *
 * @return{int}: a boolean, 0 if it's false else 1
 */
int isValidNode(nd n);

/** ===========================================================================/
 * @function isLeaf
 * @brief Checks if a node is a leaf
 *
 * @param{nd} n: the node to check
 *
 * @return{int}: a boolean, 0 if it's false else 1
 */
int isLeaf(nd n);


#endif

/* ========================================================================== */
/* ========================================================================== */
