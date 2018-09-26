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
  printList(charOccurences);
  destroyList(&charOccurences);
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

tpl getTupleInListByKey(lst list, char key){
  tpl tuple = NULL;
  for (int i = 0; i < getListSize(list); i++) {
    tuple = (tpl)get(list, i);
    if (*((char*)getTupleKey(tuple)) == key) return tuple;
  }
  return NULL;
}

/* ========================================================================== */
/* ========================================================================== */
