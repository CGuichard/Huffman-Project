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
 *  - createDefinedNode
 *  - setNodeTagDestroyer
 *  - setNodeTagPrinter
 *  - destroyLastNode
 *  - destroyNode
 *  - destroyNodeGen
 *  - printNode
 *  - printNodeGen
 *  - getNodeLeft
 *  - setNodeLeft
 *  - getNodeRight
 *  - setNodeRight
 *  - getNodeTag
 *  - isValidNode
 *  - isLeafNode
 *  - getNodeDepth
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

/**
 * @function createNode
 * @brief This function creates a new node
 *
 * @param{void*} tag: pointer on the tag of the node
 *
 * @return{nd}: The pointer of the new node
 */
nd createNode(void *tag);

/**
 * @function createDefinedNode
 * @brief This function creates a new node
 *
 * @param{void*} tag: pointer on the tag of the node
 * @param{void*()} destroyTag(void **elem): function used to destroy the value
 *                                         when the type cannot be destroyed
 *                                         with a simple "free"
 * @param{void* ()} printTag(void *elem): function used to print the key (because
 *                                       we don't know the real type of the key)
 *
 * @return{nd}: The pointer of the new node
 */
nd createDefinedNode(void *tag,
                     void(*destroyTag)(void **elem),
                     void(*printTag)(void *elem)
                    );

/**
 * @function setNodeTagDestroyer
 * @brief This function sets a function to destroy a node's tag
 *
 * @param{nd} node: pointer on a node
 * @param{void*()} destroyTag(void **elem): function used to destroy the value
 *                                         when the type cannot be destroyed
 *                                         with a simple "free"
 *
 * @return{void}
 */
void setNodeTagDestroyer(nd node, void(*destroyTag)(void **elem));

/**
 * @function setNodeTagPrinter
 * @brief This function sets a function to print a node's tag
 *
 * @param{nd} node: pointer on a node
 * @param{void*()} printTag(void *elem): function used to destroy the value
 *                                         when the type cannot be destroyed
 *                                         with a simple "free"
 *
 * @return{void}
 */
void setNodeTagPrinter(nd node, void(*printTag)(void *elem));

/**
 * @function destroyLastNode
 * @brief Destroys recursively all the children of a node
 *
 * @param{nd} n: pointer on a node
 *
 * @return{void}
 */
void destroyLastNode(nd n);

/**
 * @function destroyNode
 * @brief Destroys safely a node
 *
 * @param{nd*} n: pointer on a node's pointer
 *
 * @return{void}
 */
void destroyNode(nd *n);

/**
 * @function destroyNodeGen
 * @brief Destroys safely a generic node
 *
 * @param{void**} n: pointer on a node's pointer
 *
 * @return{void}
 */
void destroyNodeGen(void **n);

/**
* @function printNode
* @brief Prints a node
*
* This function prints a node, by printing its children and its tag like:
* <Node | Tag : 50>[<Leaf | Tag : 25>[,],<Leaf | Tag : 25>[,]]
*
*
* @param{nd} node: pointer on a node
*
* @return{void}
*/
void printNode(nd n);

/**
* @function printNodeGen
* @brief Prints a generic node
*
* This function prints a node, by printing its children and its tag like:
* <Node | Tag : 50>[<Leaf | Tag : 25>[,],<Leaf | Tag : 25>[,]]
*
*
* @param{void*} n: pointer on a generic node
*
* @return{void}
*/
void printNodeGen(void *n);

/**
 * @function getNodeLeft
 * @brief Gets the left child of a node
 *
 * @param{nd} n: pointer on a node
 *
 * @return{nd}: the pointer of the left child's pointer
 */
nd getNodeLeft(nd n);

/**
 * @function setNodeLeft
 * @brief Sets the left child of the node
 *
 * @param{nd} n: pointer on a node
 * @param{nd} child: pointer on a child node
 *
 * @return{void}
 */
void setNodeLeft(nd n, nd child);

/**
 * @function getNodeRight
 * @brief Gets the right child of the node
 *
 * @param{nd} n: pointer on a node
 *
 * @return{nd}: the pointer of the right child's pointer
 */
nd getNodeRight(nd n);

/**
 * @function setNodeRight
 * @brief Sets the right child of the node
 *
 * @param{nd} n: pointer on a node
 * @param{nd} child: pointer on a child node
 *
 * @return{void}
 */
void setNodeRight(nd n, nd child);

/**
 * @function getNodeTag
 * @brief Gets the node's tag
 *
 * @param{nd} n: pointer on a node
 *
 * @return{void*}: pointer on the tag of the node
 */
void* getNodeTag(nd n);

/**
 * @function isValidNode
 * @brief Checks a node's validity
 *
 * @param{nd} n: pointer on a node
 *
 * @return{int}: a boolean, 0 if it's false else 1
 */
int isValidNode(nd n);

/**
 * @function isLeafNode
 * @brief Checks if a node is a leaf
 *
 * @param{nd} n: pointer on a node
 *
 * @return{int}: a boolean, 0 if it's false else 1
 */
int isLeafNode(nd n);

/**
 * @function getNodeDepth
 * @brief Return the depth/height of a node
 *
 * @param{nd} n: pointer of node
 *
 * @return{int}: the depth/height of a node
 */
int getNodeDepth(nd n);


#endif

/* ========================================================================== */
/* ========================================================================== */
