#ifndef NODE_H
#define NODE_H

  #ifndef STD_LIBS_H
  #define STD_LIBS_H

  #include <stdlib.h>
  #include <stdio.h>

  #endif

  typedef struct node* nd;

  int isLeaf(nd n);
  void printNode(nd n);
  nd createNode(int val);
  void destroyLastNode(nd n);
  void destroyNode(nd* n);
  void setLeft(nd n, int val);
  nd* getLeft(nd n);
  void setRight(nd n, int val);
  nd* getRight(nd n);
  int* getVal(nd n);
  void setVal(nd n, int val);
  char* getTag(nd n);
  void setTag(nd n, char t);
  int isValidNode(nd n);

#endif
