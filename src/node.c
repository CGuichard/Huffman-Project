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
  void (*destroyTag)(void **elem); /**< Function used to destroy the tag */
  void (*printTag)(void *elem); /**< Function used to print the tag */
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
  node->destroyTag = NULL;
  node->printTag = NULL;

  return node;
}

nd createDefinedNode(void* tag, void(*destroyTag)(void **elem), void(*printTag)(void *elem)){
  nd node = (nd)malloc(sizeof(struct node));

  node->left = NULL;
  node->right = NULL;
  node->tag = tag;
  node->destroyTag = destroyTag;
  node->printTag = printTag;

  return node;
}

void setTagDestroyer(nd node, void(*destroyTag)(void **elem)){
  node->destroyTag = destroyTag;
}

void setTagPrinter(nd node, void(*printTag)(void *elem)){
  node->printTag = printTag;
}

/** ===========================================================================/
 * @see @file node.h / @function destroyLastNode
 */
void destroyLastNode(nd n){
  if(n != NULL){
    if(n->destroyTag == NULL)
      free(n->tag);
    else
      n->destroyTag(&(n->tag));

    if(n->left != NULL){
      destroyLastNode(n->left);
      free(n->left);
      n->left = NULL;
    }

    if(n->right != NULL){
      destroyLastNode(n->right);
      if(n->destroyTag == NULL)
        free(n->tag);
      else
        n->destroyTag(&(n->tag));
      free(n->right);
      n->right = NULL;
    }
  }
}

void destroyNode(nd *n){
  if((*n) != NULL){
    if((*n)->left != NULL){
      destroyLastNode((*n)->left);
      free((*n)->left);
    }

    if((*n)->right != NULL){
      destroyLastNode((*n)->right);
      free((*n)->right);
    }
    if((*n)->destroyTag == NULL)
      free((*n)->tag);
    else
      (*n)->destroyTag(&(*n)->tag);
    free(*n);
    (*n) = NULL;
  }
}

/** ===========================================================================/
 * @see @file node.h / @function destroyNodeGen
 */
void destroyNodeGen(void **n){
  destroyNode((nd*)n);
}

/** ===========================================================================/
* @see @file node.h / @function printNodeGen
*/
void printNode(nd n){
  if(n != NULL){
    if(isLeaf(n)){
      printf("<Leaf | Tag : ");
      if(n->printTag != NULL)
        n->printTag(n->tag);
      else
        printf("<Key printer is null>");
      printf(">");
    }else{
      printf("<Node | Tag : ");
      if(n->printTag != NULL)
        n->printTag(n->tag);
      else
        printf("<Key printer is null>");
      printf(">[");
      if(isValidNode(n) && n->left != NULL)
      printNodeGen(n->left);
      printf(", ");
      if(isValidNode(n) && n->right != NULL)
      printNodeGen(n->right);
      printf("]");
    }
  }
}

void printNodeGen(void *n){
  printNode((nd)n);
}


/** ===========================================================================/
* @see @file node.h / @function getLeft
*/
nd getLeft(nd n){
  return n->left;
}

/** ===========================================================================/
 * @see @file node.h / @function setLeft
 */
void setLeft(nd n, nd child){
  n->left = child;
}

/** ===========================================================================/
 * @see @file node.h / @function getRight
 */
nd getRight(nd n){
  return n->right;
}

/** ===========================================================================/
* @see @file node.h / @function setRight
*/
void setRight(nd n, nd child){
  n->right = child;
}

/** ===========================================================================/
 * @see @file node.h / @function getTag
 */
void* getTag(nd n){
  return n->tag;
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
