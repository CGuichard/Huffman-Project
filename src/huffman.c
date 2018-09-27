/**
 * @file huffman.c
 * @author Clément GUICHARD
 * @author Thàng long CAMA
 * @standard C99
 * @version 1.0
 * @date 11th October 2018
 *
 * @brief This file implements the functions used in "huffman.h"
 *
 * This file implements function of the huffman coding using trees in C.
 * The tree is a binary tree, which is composed of nodes.
 *
 * Overview about public functions of this file:
 *    -
 */

#include "huffman.h"


/* ================================================== */
/* ===================== PUBLIC ===================== */
/* ========================================================================== */

char* encryptStr(char *str){
  lst charOccurences = charOccurencesOfStr(str);
  nd tree = contructBinaryTree(charOccurences);

  printf("Tree: ");
  printNode(tree);
  destroyList(&charOccurences);
  destroyNode(&tree);
  return NULL;
}

// void encryptFile(char *fileIn, char *fileOut, char *fileKey){
//
// }
//
// char* decryptStr(char *str){
//   return NULL;
// }
//
// void decryptFile(char *fileIn, char *fileOut, char *fileKey){
//
// }

lst charOccurencesOfStr(char *str) {
  lst occurences = createDefinedList(&destroyTupleGen, &printTupleGen);
  char *key = (char*)malloc(sizeof(char));
  int *val = (int*)malloc(sizeof(int)); *val = 1;
  tpl tupleTmp = NULL;
  for (size_t i = 0; i < strlen(str); i++) {
    tupleTmp = getTupleInListByKey(occurences, str[i]);
    if(tupleTmp == NULL){
      *key = str[i];
      tpl tuple = createTupleByCopy(key, val, &copyChar, NULL, &printChar, &copyInt, NULL, &printInt);
      addInList(occurences, tuple);
    }else{
      (*((int*)getTupleValue(tupleTmp)))++;
      tupleTmp = NULL;
    }
  }
  free(key);
  free(val);
  return occurences;
}

lst charOccurencesOfFile(char *srcFile){
  FILE* file = fopen (srcFile, "r");
  if(file != NULL) {
    char ligne[255];
    lst occurences = createDefinedList(&destroyTupleGen, &printTupleGen);
    char *key = (char*)malloc(sizeof(char));
    int *val = (int*)malloc(sizeof(int)); *val = 1;
    tpl tupleTmp   = NULL;
    while(fgets(ligne, sizeof(ligne), file) != NULL) {
      for(unsigned int i = 0; i < strlen(ligne); i++) {
        tupleTmp = getTupleInListByKey(occurences, ligne[i]);
        if(tupleTmp == NULL){
          *key = ligne[i];
          tpl tuple = createTupleByCopy(key, val, &copyChar, NULL, &printChar, &copyInt, NULL, &printInt);
          addInList(occurences, tuple);
        }else{
          (*((int*)getTupleValue(tupleTmp)))++;
          tupleTmp = NULL;
        }
      }
    }
    free(key);
    free(val);
    fclose(file);
    return occurences;
  }else{
    perror(srcFile);
    exit(0);
  }
  return NULL;
}

nd contructBinaryTree(lst occurences){
  // nd tree = createDefinedNode(NULL, destroyTupleGen, printTupleGen);
  lst treeNodes = createDefinedList(destroyNodeGen, printNodeGen);
  nd tree = NULL;
  tpl tuple = NULL;
  for(size_t i = 0; i < getListSize(occurences); i++){
    tuple = get(occurences, i);
    tpl tmp = makeCopyTuple(tuple, copyChar, copyInt);
    nd node = createDefinedNode(tmp, destroyTupleGen, printTupleGen);
    addInList(treeNodes, node);
  }
  if (getListSize(treeNodes) > 0){
    while(getListSize(treeNodes) > 1){
      mergeTwoSmallerNodes(treeNodes);
    }
    if(getListSize(treeNodes) == 1) tree = (nd)popInList(treeNodes, 0);
  }
  destroyList(&treeNodes);
  return tree;
}

tpl getTupleInListByKey(lst list, char key){
  tpl tuple = NULL;
  for (size_t i = 0; i < getListSize(list); i++) {
    tuple = (tpl)get(list, i);
    if (*((char*)getTupleKey(tuple)) == key) return tuple;
  }
  return NULL;
}

void mergeTwoSmallerNodes(lst list){
  size_t j = 0;
  size_t k = 1;
  int valueJ = *((int*)getTupleValue((tpl)getTag((nd)get(list, j))));
  int valueK = *((int*)getTupleValue((tpl)getTag((nd)get(list, k))));
  int *currentValue = NULL;
  for(size_t i = 2; i < getListSize(list); i++){
    currentValue = (int*)getTupleValue((tpl)getTag((nd)get(list, i)));
    if(k < j){
      if(*currentValue < valueK && i != j && i != k){
        k = i;
        valueK = *currentValue;
      }
    }else{
      if(*currentValue < valueJ && i != j && i != k){
        j = i;
        valueJ = *currentValue;
      }
    }
  }
  if(j < k) k--;
  nd child1 = (nd)popInList(list, j);
  nd child2 = (nd)popInList(list, k);
  int valChild1 = *((int*)getTupleValue((tpl)getTag(child1)));
  int valChild2 = *((int*)getTupleValue((tpl)getTag(child2)));
  int* newValue = (int*)malloc(sizeof(int));
  *newValue = valChild1 + valChild2;
  tpl newTuple = createTuple(NULL, newValue, NULL, printChar, NULL, printInt);
  nd newNode = createDefinedNode(newTuple, destroyTupleGen, printTupleGen);
  if(valChild1 <= valChild2){
    setLeft(newNode, child1);
    setRight(newNode, child2);
  }else{
    setLeft(newNode, child2);
    setRight(newNode, child1);
  }
  printNode(newNode);
  printf("\n");
  destroyNode(&newNode);
  // addInList(list, newNode);
}


/* ========================================================================== */
/* ========================================================================== */
