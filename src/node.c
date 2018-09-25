#include "node.h"

struct node{
  nd left;
  nd right;
  void *tag;
};

int isLeaf(nd n){
  // if the node have no children and its tag is set
  // then it's a leaf.
  return n->left == NULL && n->right == NULL ? 1 : 0;
}

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

nd createNode(void* tag){
  nd node = (nd)malloc(sizeof(struct node));

  node->left = NULL;
  node->right = NULL;
  node->tag = tag;

  return node;
}

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

void setLeft(nd n, void *tag){
  n->left = createNode(tag);
}

nd* getLeft(nd n){
  return &n->left;
}

void setRight(nd n, void *tag){
  n->right = createNode(tag);
}

nd* getRight(nd n){
  return &n->right;
}

void* getTag(nd n){
  return &n->tag;
}

int isValidNode(nd n){
  // if the node have a tag AND haven't children, it's a valid node.
  // if the node haven't a tag AND at least one child, it's a valid node.
  return (isLeaf(n) && n->tag != NULL) || (!isLeaf(n) && n->tag !=NULL) ? 1 : 0;
}
