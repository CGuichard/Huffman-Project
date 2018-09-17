#include "node.h"

struct node{
  nd left;
  nd right;
  int val;
  char tag;
};

int isLeaf(nd n){
  // if the node have no children and its tag is set
  // then it's a leaf.
  return n->left == NULL && n->right == NULL && n->tag != '\0' ? 1 : 0;
}

void printNode(nd n){
  // if(n == NULL)
  //   puts("The node is empty!");
  //
  // if(isLeaf(n))
  //   printf("<Leaf | Value : %i; Tag : %c>\n", n->val, n->tag);
  //
  // do {
  //   printf("<Node | Value : %i; Tag : %c> [", n->val, n->tag);
  //   printf("]");
  // } while(isValidNode(n));
}

nd createNode(int val){
  nd node = (nd)malloc(sizeof(struct node));

  node->left = NULL;
  node->right = NULL;
  node->val = val;
  node->tag = '\0';

  return node;
}

void destroyLastNode(nd n){
  if(n == NULL)
    puts("The node is empty!");

  else{
    if(n->left != NULL){
      destroyLastNode(n->left);
      free(n->left);
      n->left = NULL;
    }

    if(n->right != NULL){
      destroyLastNode(n->right);
      free(n->right);
      n->right = NULL;
    }
  }
}

void destroyNode(nd *n){
  if((*n) == NULL)
      puts("The node is empty!");

  else{
    if((*n)->left != NULL)
      destroyLastNode((*n)->left);
    if((*n)->right != NULL)
      destroyLastNode((*n)->right);
    free(*n);
    (*n) = NULL;
  }
}

void setLeft(nd n, int val){
  n->left = createNode(val);
}

void setRight(nd n, int val){
  n->right = createNode(val);
}

int* getVal(nd n){
  return &n->val;
}

void setVal(nd n, int val){
  n->val = val;
}

char* getTag(nd n){
  return &n->tag;
}

void setTag(nd n, char t){
  n->tag = t;
}

int isValidNode(nd n){
  // if the node have a tag AND haven't children, it's a valid node.
  // if the node haven't a tag AND at least one child, it's a valid node.
  return (n->tag != '\0' && (n->left == NULL && n->right == NULL)) || (n->tag == '\0' && (n->left != NULL || n->right != NULL)) ? 1 : 0;
}
