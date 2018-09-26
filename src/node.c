/**
 * @file node.c
 * @author Thàng long CAMA
 * @standard C99
 * @version 1.0
 * @date 11th October 2018
 *
 * @brief Implementation file for the struct "node".
 *
 * This file implements the struct "node" described in the file "node.h",
 * a generic structure for multiple uses
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

#include "node.h"


/* ================================================== */
/* ==================== STRUCT DEF ================== */
/* ========================================================================== */


/**
 * @struct node
 * @brief A node contains two children and a tag (is used to represent a tree)
 *
 * The structure node represents two children and a tag, the latter with generic
 * type. It is used to represent trees.
 */
struct node{
  nd left; /**< Pointer on a child of the node, which is an other node */
  nd right; /**< Pointer on a child of the node, which is an other node */
  void *tag; /**< Generic pointer on the node's tag */
};


/* ================================================== */
/* ===================== PUBLIC ===================== */
/* ========================================================================== */


/** ===========================================================================/
 * @see @file node.h / @function createNode
 */
nd createNode(void* tag){
  nd node = (nd)malloc(sizeof(struct node));

  node->left = NULL;
  node->right = NULL;
  node->tag = tag;

  return node;
}

/** ===========================================================================/
 * @see @file node.h / @function destroyLastNode
 */
void destroyLastNode(nd n, void(*destroyer)(void **elem)){
  if(n == NULL)
    puts("The node is empty!");

  else{
    if(destroyer == NULL)
      free(n->tag);
    else
      (*destroyer)(&(n->tag));

    if(n->left != NULL){
      destroyLastNode(n->left, destroyer);
      free(n->left);
      n->left = NULL;
    }

    if(n->right != NULL){
      destroyLastNode(n->right, destroyer);
      if(destroyer == NULL)
        free(n->tag);
      else
        (*destroyer)(&(n->tag));
      free(n->right);
      n->right = NULL;
    }
  }
}

/** ===========================================================================/
 * @see @file node.h / @function destroyNodeGen
 */
void destroyNodeGen(nd *n, void(*destroyer)(void **elem)){
  if((*n) == NULL)
      puts("The node is empty!");

  else{
    if((*n)->left != NULL){
      destroyLastNode((*n)->left, destroyer);
      free((*n)->left);
    }

    if((*n)->right != NULL){
      destroyLastNode((*n)->right, destroyer);
      free((*n)->right);
    }
    if(destroyer == NULL)
      free((*n)->tag);
    else
      (*destroyer)(&(*n)->tag);
    free(*n);
    (*n) = NULL;
  }
}

/** ===========================================================================/
* @see @file node.h / @function printNodeGen
*/
void printNodeGen(nd n, void(*printTag)(void *tag)){
  if(n == NULL)
  return;

  else if(printTag == NULL){
    printf("<Key printer is null>");
  }

  else{
    if(isLeaf(n)){
      printf("<Leaf | Tag : ");
      (*printTag)(n->tag);
      printf(">");
    }

    else{
      printf("<Node | Tag : ");
      (*printTag)(n->tag);
      printf(">[");
      if(isValidNode(n) && n->left != NULL)
      printNodeGen(n->left, printTag);
      printf(", ");
      if(isValidNode(n) && n->right != NULL)
      printNodeGen(n->right, printTag);
      printf("]");
    }
  }
}

/** ===========================================================================/
* @see @file node.h / @function getLeft
*/
nd* getLeft(nd n){
  return &n->left;
}

/** ===========================================================================/
 * @see @file node.h / @function setLeft
 */
void setLeft(nd n, void *tag){
  n->left = createNode(tag);
}

/** ===========================================================================/
 * @see @file node.h / @function getRight
 */
nd* getRight(nd n){
  return &n->right;
}

/** ===========================================================================/
* @see @file node.h / @function setRight
*/
void setRight(nd n, void *tag){
  n->right = createNode(tag);
}

/** ===========================================================================/
 * @see @file node.h / @function getTag
 */
void* getTag(nd n){
  return &n->tag;
}

/** ===========================================================================/
 * @see @file node.h / @function isValidNode
 */
int isValidNode(nd n){
  // if the node have a tag AND haven't children, it's a valid node.
  // if the node haven't a tag AND at least one child, it's a valid node.
  return (isLeaf(n) && n->tag != NULL) || (!isLeaf(n) && n->tag !=NULL) ? 1 : 0;
}

/** ===========================================================================/
 * @see @file node.h / @function isLeaf
 */
int isLeaf(nd n){
  // if the node have no children and its tag is set
  // then it's a leaf.
  return n->left == NULL && n->right == NULL ? 1 : 0;
}


/* ========================================================================== */
/* ========================================================================== */
