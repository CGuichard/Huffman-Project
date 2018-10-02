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

char* huffmanEncryptStr(char *str){
  if(str != NULL){
    lst charOccurences = charOccurencesOfStr(str);
    int maxPrefixLength = 0;
    lst prefixes = prefixesList(charOccurences, "tests/test_str.hfm.key", &maxPrefixLength);
    char *bytesEncryption = getEncryptionOf(str, prefixes, maxPrefixLength);
    tpl tupleEndChar = (tpl)getTupleInListByKey(prefixes, '\0');
    char* encr = makeCharactersFromBytes(bytesEncryption, (char*)getTupleValue(tupleEndChar));
    destroyList(&prefixes);
    return encr;
  }
  return NULL;
}

void huffmanEncryptFile(char *fileIn, char *fileOut, char *fileKey){
  if(fileIn != NULL && fileOut != NULL && fileKey != NULL){
    lst charOccurences = charOccurencesOfFile(fileIn);
    int maxPrefixLength = 0;
    lst prefixes = prefixesList(charOccurences, fileKey, &maxPrefixLength);
    writeEncryptionInFile(fileIn, fileOut, prefixes, maxPrefixLength);
    destroyList(&prefixes);
  }
}

/* ========================================================================== */

char* huffmanDecryptStr(char *str){
  nd tree = getTreeFromKeyFile("tests/test_str.hfm.key");
  char* result = getDecryptionOf(str, tree);
  destroyNode(&tree);
  // if(strlen(result) < resultSize){
  //   char *tmp = (char*)realloc(result, strlen(result) + 1);
  //   if(tmp != NULL) result = tmp;
  // }
  return result;
}

void huffmanDecryptFile(char *fileIn, char *fileOut, char *fileKey){
  if(fileIn != NULL && fileOut != NULL && fileKey != NULL){
    nd tree = getTreeFromKeyFile(fileKey);
    FILE *fileToRead = fopen(fileIn, "r");
    FILE *fileToWrite = fopen(fileOut, "w");
    if(fileToRead != NULL && fileToWrite != NULL){
      char line[255];
      char* lineToWrite;
      while(fgets(line, sizeof(line), fileToRead) != NULL){
        lineToWrite = getDecryptionOf(line, tree);
        fputs(lineToWrite, fileToWrite);
        free(lineToWrite);
      }
      destroyNode(&tree);
      fclose(fileToRead);
      fclose(fileToWrite);
    } else {
      if(fileToRead == NULL) perror(fileIn);
      if(fileToWrite == NULL) perror(fileOut);
      exit(0);
    }
  }
}

char* getDecryptionOf(char *str, nd tree){
  const size_t numberOfBits = 8;
  const size_t resultSize = sizeof(char)*strlen(str)*3;
  int* resultIndex = malloc(sizeof(int));
  *resultIndex = 0;
  char* result = malloc(resultSize+1);
  result[resultSize] = '\0';
  char* path;
  nd currentNode = tree;
  for(size_t i = 0; i < strlen(str); i++){
    path = decimalToBinary((size_t)str[i], numberOfBits);
    setResultByReadingTree(tree, &currentNode, path, &result, &resultIndex);
    free(path);
  }

  free(resultIndex);
  return result;
}

void setResultByReadingTree(nd tree, nd *currentNode, char *path, char **result, int **resultIndex){
  for(size_t j = 0; j < sizeof(path)/sizeof(char); j++){
    if(isLeaf((*currentNode))){
      (*result)[(*(*resultIndex))] = (*(char*)getTupleKey(getTag(*currentNode)));
      *currentNode = tree;
      (*(*resultIndex))++;
    }

    if(path[j] == '0'){
      *currentNode = getLeft(*currentNode);
    }

    else if(path[j] == '1'){
      *currentNode = getRight(*currentNode);
    }
  }
}
/* ========================================================================== */

char* getEncryptionOf(char *str, lst prefixes, int maxPrefixLength){
  char *encr = (char*)calloc(sizeof(char), maxPrefixLength * strlen(str) + 1);
  if(str != NULL && prefixes != NULL){
    tpl prefixTuple = NULL;
    char *prefix = NULL;
    for(size_t i = 0; i < strlen(str); i++){
      prefixTuple = getTupleInListByKey(prefixes, str[i]);
      prefix = (char*)getTupleValue(prefixTuple);
      strcat(encr, prefix);
    }
  }
  // if(strlen(encr) < (unsigned int)maxPrefixLength){
  //   char *tmp = (char*)realloc(encr, strlen(encr) + 1);
  //   if(tmp != NULL) encr = tmp;
  // }
  return encr;
}

void writeEncryptionInFile(char *fileIn, char *fileOut, lst prefixes, int maxPrefixLength){
  if(fileIn != NULL && fileOut != NULL && prefixes != NULL){
    FILE* file = fopen(fileIn, "r");
    FILE *fileW = fopen(fileOut, "wb");
    if(file != NULL && fileOut != NULL){
      char charToWrite;
      char ligne[255];
      int actualByteIndex = 0;
      char *bytes = (char*)calloc(sizeof(char), 9);
      char *endChar = (char*)getTupleValue((tpl)getTupleInListByKey(prefixes, '\0'));
      while(fgets(ligne, sizeof(ligne), file) != NULL){
        char *encrOfLigne = getEncryptionOf(ligne, prefixes, maxPrefixLength);
        for(size_t i = 0; i < strlen(encrOfLigne); i++){
          if(actualByteIndex == 8){
            actualByteIndex = 0;
            charToWrite = charBytesToChar(bytes);
            fwrite(&charToWrite, 1, sizeof(charToWrite), fileW);
          }
          bytes[actualByteIndex] = encrOfLigne[i];
          actualByteIndex++;
        }
        free(encrOfLigne);
      }
      for (size_t i = 0; i < strlen(endChar); i++) {
        if(actualByteIndex == 8){
          actualByteIndex = 0;
          charToWrite = charBytesToChar(bytes);
          fwrite(&charToWrite, 1, sizeof(charToWrite), fileW);
        }
        bytes[actualByteIndex] = endChar[i];
        actualByteIndex++;
      }
      if(actualByteIndex != 0){
        while(actualByteIndex != 0){
          bytes[actualByteIndex] = '0';
          actualByteIndex++;
          if(actualByteIndex == 8) actualByteIndex = 0;
        }
        charToWrite = charBytesToChar(bytes);
        fwrite(&charToWrite, 1, sizeof(charToWrite), fileW);
      }
      printf("Encryption process completed\n");
      free(bytes); fclose(fileW); fclose(file);
    }else{
      if(file == NULL) perror(fileIn);
      if(fileW == NULL) perror(fileOut);
      exit(0);
    }
  }
}

void saveKeyInFile(lst occurences, char *fileKey){
  if(occurences != NULL && fileKey != NULL){
    FILE *file = fopen(fileKey, "w");
    tpl occurence = NULL;
    if(file != NULL){
      for (size_t i = 0; i < getListSize(occurences); i++) {
        occurence = get(occurences, i);
        if(*((char*)getTupleKey(occurence)) != '\0'){
          fprintf(file, "%c:%d;", *((char*)getTupleKey(occurence)), *((int*)getTupleValue(occurence)));
        }
      }
      fclose(file);
    }else{
      if(file == NULL) perror(fileKey);
      exit(0);
    }
  }
}

nd getTreeFromKeyFile(char *fileKey){
  FILE* file = fopen (fileKey, "r");
  if(file != NULL) {
    char ligne[255];
    tpl occurence = NULL;
    int etape = 1;
    char l = 0;
    unsigned int tmp = 0;
    char* nb = (char*)calloc(sizeof(char), 11);
    lst occurences = createDefinedList(&destroyTupleGen, &printTupleGen);
    while(fgets(ligne, sizeof(ligne), file) != NULL){
      for (unsigned int i = 0; i < strlen(ligne); i++){
        if (etape == 1) {
          l = ligne[i];
          etape++;
        }else if(etape == 2){
          if (ligne[i] == ':') etape++;
        }else if(etape == 3){
          nb[tmp] = ligne[i];
          tmp++;
          if(ligne[i+1] == ';'){
            while(tmp < 11){
              nb[tmp] = 0;
              tmp++;
            }
            tmp = 0;
            char *letter = (char*)malloc(sizeof(char)); *letter = l;
            int *value = (int*)malloc(sizeof(int)); *value = strToInt(nb);
            occurence = createTuple(letter, value, NULL, printChar, NULL, printInt);
            addInList(occurences, occurence);
            etape++;
          }
        }else if(etape == 4){
          if (ligne[i] == ';') etape = 1;
        }
      }
    }
    fclose(file);
    free(nb);
    char *letter = (char*)malloc(sizeof(char)); *letter = '\0';
    int *value = (int*)malloc(sizeof(int)); *value = 1;
    occurence = createTuple(letter, value, NULL, printChar, NULL, printInt);
    addInList(occurences, occurence);
    nd tree = contructBinaryTree(occurences);
    destroyList(&occurences);
    return tree;
  } else {
    perror(fileKey);
  }
  return NULL;
}

/* ========================================================================== */

lst charOccurencesOfStr(char *str){
  lst occurences = createDefinedList(&destroyTupleGen, &printTupleGen);
  char *key = (char*)malloc(sizeof(char));
  int *val = (int*)malloc(sizeof(int)); *val = 1;
  tpl tupleTmp = NULL;
  for(size_t i = 0; i < strlen(str); i++){
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
  *key = '\0';
  tpl tuple = createTupleByCopy(key, val, &copyChar, NULL, &printChar, &copyInt, NULL, &printInt);
  addInList(occurences, tuple);
  free(key);
  free(val);
  return occurences;
}

lst charOccurencesOfFile(char *srcFile){
  FILE* file = fopen (srcFile, "r");
  if(file != NULL){
    char ligne[512];
    lst occurences = createDefinedList(&destroyTupleGen, &printTupleGen);
    char *key = (char*)malloc(sizeof(char));
    int *val = (int*)malloc(sizeof(int)); *val = 1;
    tpl tupleTmp = NULL;
    while(fgets(ligne, sizeof(ligne), file) != NULL){
      for(unsigned int i = 0; i < strlen(ligne); i++){
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
    *key = '\0';
    tpl tuple = createTupleByCopy(key, val, &copyChar, NULL, &printChar, &copyInt, NULL, &printInt);
    addInList(occurences, tuple);
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
  lst treeNodes = createDefinedList(destroyNodeGen, printNodeGen);
  nd tree = NULL;
  tpl tuple = NULL;
  for(size_t i = 0; i < getListSize(occurences); i++){
    tuple = get(occurences, i);
    tpl tmp = makeCopyTuple(tuple, copyChar, copyInt);
    nd node = createDefinedNode(tmp, destroyTupleGen, printTupleGen);
    addInList(treeNodes, node);
  }
  if(getListSize(treeNodes) > 0){
    while(getListSize(treeNodes) > 1){
      mergeTwoSmallerNodes(treeNodes);
    }
    if(getListSize(treeNodes) == 1) tree = (nd)popInList(treeNodes, 0);
  }
  destroyList(&treeNodes);
  return tree;
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
  addInList(list, newNode);
}

lst prefixesList(lst occurences, char *fileKey, int *maxPrefixLength){
  nd tree = contructBinaryTree(occurences);
  *maxPrefixLength = getNodeDepth(tree);
  saveKeyInFile(occurences, fileKey);
  destroyList(&occurences);
  lst prefixes = createDefinedList(&destroyTupleGen, &printTupleGen);
  char *prefix = (char*)calloc(sizeof(char), *maxPrefixLength + 1);
  calculatePrefixes(tree, prefixes, prefix);
  free(prefix);
  destroyNode(&tree);
  return prefixes;
}

void calculatePrefixes(nd node, lst prefixes, char *prefix){
  if(node == NULL || prefix == NULL || prefixes == NULL) pointerNullError();
  int next = (int)strlen(prefix);
  if(isLeaf(node)){
    char* ch = (char*)copyChar(getTupleKey((tpl)getTag(node)));
    char* pr = copyString(prefix);
    tpl prefixTuple = createTuple(ch, pr, NULL, printChar, NULL, printString);
    addInList(prefixes, prefixTuple);
  } else {
    nd left = getLeft(node);
    nd right = getRight(node);
    if(left != NULL){
      prefix[next] = '0';
      calculatePrefixes(left, prefixes, prefix);
      prefix[next] = 0;
    }
    if(right != NULL){
      prefix[next] = '1';
      calculatePrefixes(right, prefixes, prefix);
      prefix[next] = 0;
    }
  }
}

char* makeCharactersFromBytes(char *bytes, char *endChar){
  int size = (strlen(bytes)+strlen(endChar))/8+2;
  char *encr = (char*)calloc(sizeof(char), size);
  int actualByteIndex = 0;
  char *chars = (char*)calloc(sizeof(char), 9);
  for(size_t i = 0; i < strlen(bytes)+strlen(endChar); i++){
      if(actualByteIndex == 8){
        actualByteIndex = 0;
        encr[strlen(encr)] = charBytesToChar(chars);
      }
      if(i<strlen(bytes))
        chars[actualByteIndex] = bytes[i];
      else
        chars[actualByteIndex] = endChar[i-strlen(bytes)];
      actualByteIndex++;
  }
  if(actualByteIndex != 0){
    while(actualByteIndex != 8){
      chars[actualByteIndex] = '0';
      actualByteIndex++;
    }
    encr[strlen(encr)] = charBytesToChar(chars);
  }
  free(chars); free(bytes);
  return encr;
}

/* ========================================================================== */

tpl getTupleInListByKey(lst list, char key){
  tpl tuple = NULL;
  for(size_t i = 0; i < getListSize(list); i++){
    tuple = (tpl)get(list, i);
    if(*((char*)getTupleKey(tuple)) == key) return tuple;
  }
  return NULL;
}


/* ========================================================================== */
/* ========================================================================== */
