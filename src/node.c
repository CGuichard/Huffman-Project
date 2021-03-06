/**
 * @file node.c
 * @author Thàng long CAMA <thang-long.cama@etu.univ-orleans.fr>
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

#include "node.h"


/* ================================================== */
/* ==================== STRUCT DEF ================== */
/* ========================================================================== */


/**
 * @struct node
 * @brief A node contains two children and a tag (is used to represent a tree)
 *
 * The structure node represents two children, a generic-typed tag and
 * pointers on functions needed to manage the node. It is used to represent
 * trees.
 */
struct node {
  nd left; /**< Pointer on a child of the node, which is an other node */
  nd right; /**< Pointer on a child of the node, which is an other node */
  void *tag; /**< Generic pointer on the node's tag */
  void (*destroyTag)(void **elem); /**< Function used to destroy the tag */
  void (*printTag)(void *elem); /**< Function used to print the tag */
};


/* ================================================== */
/* ================ STRUCT FUNCTIONS ================ */
/* ========================================================================== */


/**
 * @see @file node.h / @function createNode
 */
nd createNode(void *tag) {
  nd node = (nd)malloc(sizeof(struct node));

  node->left       = NULL;
  node->right      = NULL;
  node->tag        = tag;
  node->destroyTag = NULL;
  node->printTag   = NULL;

  return node;
}

/**
 * @see @file node.h / @function createDefinedNode
 */
nd createDefinedNode(void *tag, void(*destroyTag)(void **elem), void(*printTag)(void *elem)) {
  nd node = (nd)malloc(sizeof(struct node));

  node->left       = NULL;
  node->right      = NULL;
  node->tag        = tag;
  node->destroyTag = destroyTag;
  node->printTag   = printTag;

  return node;
}

/**
 * @see @file node.h / @function setNodeTagDestroyer
 */
void setNodeTagDestroyer(nd node, void(*destroyTag)(void **elem)) {
  node->destroyTag = destroyTag;
}

/**
 * @see @file node.h / @function setNodeTagPrinter
 */
void setNodeTagPrinter(nd node, void(*printTag)(void *elem)) {
  node->printTag = printTag;
}

/**
 * @see @file node.h / @function destroyLastNode
 */
void destroyLastNode(nd n) {
  if(n != NULL) {
    if (n->left != NULL) {
      destroyNode(&(n->left));
      n->left = NULL;
    }
    if (n->right != NULL) {
      destroyNode(&(n->right));
      n->right = NULL;
    }
    if(n->destroyTag != NULL)
      n->destroyTag(&(n->tag));
    else
      free(n->tag);
    free(n);
    n = NULL;
  }
}

/**
 * @see @file node.h / @function destroyNode
 */
void destroyNode(nd *n) {
  if((*n) != NULL) {
    if ((*n)->left != NULL) {
      destroyNode(&((*n)->left));
      (*n)->left = NULL;
    }
    if ((*n)->right != NULL) {
      destroyNode(&((*n)->right));
      (*n)->right = NULL;
    }
    if((*n)->destroyTag != NULL)
      (*n)->destroyTag(&((*n)->tag));
    else
      free((*n)->tag);
    free(*n);
    (*n) = NULL;
  }
}

/**
 * @see @file node.h / @function destroyNodeGen
 */
void destroyNodeGen(void **n) {
  destroyNode((nd*)n);
}

/**
* @see @file node.h / @function printNode
*/
void printNode(nd n) {
  if(n != NULL) {
    if(isLeafNode(n)) {
      printf("<Leaf | Tag : ");
      if(n->printTag != NULL)
        n->printTag(n->tag);
      else
        printf("<Key printer is null>");
      printf(">");
    } else {
      printf("<Node | Tag : ");
      if(n->printTag != NULL)
        n->printTag(n->tag);
      else
        printf("<Key printer is null>");
      printf(">[");
      if(isValidNode(n) && n->left != NULL) printNodeGen(n->left);
      printf(", ");
      if(isValidNode(n) && n->right != NULL) printNodeGen(n->right);
      printf("]");
    }
  }
}

/**
 * @see @file node.h / @function printNodeGen
 */
void printNodeGen(void *n) {
  printNode((nd)n);
}

/**
* @see @file node.h / @function getNodeLeft
*/
nd getNodeLeft(nd n) {
  return n->left;
}

/**
 * @see @file node.h / @function setNodeLeft
 */
void setNodeLeft(nd n, nd child) {
  n->left = child;
}

/**
 * @see @file node.h / @function getNodeRight
 */
nd getNodeRight(nd n) {
  return n->right;
}

/**
* @see @file node.h / @function setNodeRight
*/
void setNodeRight(nd n, nd child) {
  n->right = child;
}

/**
 * @see @file node.h / @function getNodeTag
 */
void* getNodeTag(nd n) {
  return n->tag;
}

/**
 * @see @file node.h / @function isValidNode
 */
int isValidNode(nd n) {
  // if the node have a tag AND haven't children, it's a valid node.
  // if the node haven't a tag AND at least one child, it's a valid node.
  return (isLeafNode(n) && n->tag != NULL) || (!isLeafNode(n) && n->tag !=NULL) ? 1 : 0;
}

/**
 * @see @file node.h / @function isLeafNode
 */
int isLeafNode(nd n) {
  // if the node have no children and its tag is set
  // then it's a leaf.
  return n->left == NULL && n->right == NULL ? 1 : 0;
}

/**
 * @see @file node.h / @function getNodeDepth
 */
int getNodeDepth(nd n) {
  if(n != NULL) {
    int left = 0;
    int right = 0;
    if(n->left != NULL) {
      left = getNodeDepth(n->left) + 1;
    }
    if(n->right != NULL) {
      right = getNodeDepth(n->right) + 1;
    }
    return (left > right) ? left : right;
  }
  return 0;
}


/* ========================================================================== */
/* ========================================================================== */
