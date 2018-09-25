#ifndef NODE_H
#define NODE_H

  #ifndef STD_LIBS_H
  #define STD_LIBS_H

  #include <stdlib.h>
  #include <stdio.h>

  #endif

  typedef struct node* nd;

  int isLeaf(nd n);
  void printNodeGen(nd n, void(*printTag)(void *tag));
  nd createNode(void* tag);
  void destroyLastNode(nd n, void(*destroyer)(void **elem));
  void destroyNodeGen(nd* n, void(*destroyer)(void **elem));
  void setLeft(nd n, void* tag);
  nd* getLeft(nd n);
  void setRight(nd n, void* tag);
  nd* getRight(nd n);
  void* getTag(nd n);
  int isValidNode(nd n);

#endif
