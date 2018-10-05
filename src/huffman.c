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
 *    - huffmanEncryptStr
 *    - huffmanEncryptFile
 *    - huffmanDecryptStr
 *    - huffmanDecryptFile
 *    - getEncryptionOf
 *    - makeCharactersFromBits
 *    - writeEncryptionInFile
 *    - saveKeyInFile
 *    - getDecryptionOf
 *    - writeDecryptionInFile
 *    - getTreeFromKeyFile
 *    - charOccurencesOfStr
 *    - charOccurencesOfFile
 *    - contructBinaryTree
 *    - mergeTwoSmallerNodes
 *    - prefixesList
 *    - calculatePrefixes
 *    - getTupleInListByKey
 *    - writeBitsInOpenedFile
 */

#include "huffman.h"


/* ================================================== */
/* ===================== PUBLIC ===================== */
/* ========================================================================== */

/**
 * @see @file huffman.h / @function
 */
char* huffmanEncryptStr(char *str) {
  if(str != NULL) {
    lst charOccurences = charOccurencesOfStr(str);
    int maxPrefixLength = 0;
    lst prefixes = prefixesList(charOccurences, "tests/test_str.hfm.key", &maxPrefixLength);
    char *bitsEncryption = getEncryptionOf(str, prefixes, maxPrefixLength);
    tpl tupleEndChar = (tpl)getTupleInListByKey(prefixes, '\0');
    char *encr = makeCharactersFromBits(bitsEncryption, (char*)getTupleValue(tupleEndChar));
    destroyList(&prefixes);
    return encr;
  }
  return NULL;
}

/**
 * @see @file huffman.h / @function
 */
void huffmanEncryptFile(char *fileIn, char *fileOut, char *fileKey) {
  if(fileIn != NULL && fileOut != NULL && fileKey != NULL) {
    lst charOccurences = charOccurencesOfFile(fileIn);
    int maxPrefixLength = 0;
    lst prefixes = prefixesList(charOccurences, fileKey, &maxPrefixLength);
    writeEncryptionInFile(fileIn, fileOut, prefixes, maxPrefixLength);
    destroyList(&prefixes);
  }
}


/**
 * @see @file huffman.h / @function
 */
char* huffmanDecryptStr(char *str) {
  nd tree = getTreeFromKeyFile("tests/test_str.hfm.key");
  char *result = getDecryptionOf(str, tree);
  destroyNode(&tree);
  return result;
}

/**
 * @see @file huffman.h / @function
 */
void huffmanDecryptFile(char *fileIn, char *fileOut, char *fileKey) {
  if(fileIn != NULL && fileOut != NULL && fileKey != NULL) {
    nd tree = getTreeFromKeyFile(fileKey);
    writeDecryptionInFile(fileIn, fileOut, tree);
    destroyNode(&tree);
  }
}


/**
 * @see @file huffman.h / @function
 */
char* getEncryptionOf(char *str, lst prefixes, int maxPrefixLength) {
  char *encr = (char*)calloc(sizeof(char), maxPrefixLength * strlen(str) + 1);
  if(str != NULL && prefixes != NULL) {
    tpl prefixTuple = NULL;
    char *prefix = NULL;
    for(size_t i = 0; i < strlen(str); i++) {
      prefixTuple = getTupleInListByKey(prefixes, str[i]);
      prefix = (char*)getTupleValue(prefixTuple);
      strcat(encr, prefix);
    }
  }
  // if(strlen(encr) < (unsigned int)maxPrefixLength) {
  //   char *tmp = (char*)realloc(encr, strlen(encr) + 1);
  //   if(tmp != NULL) encr = tmp;
  // }
  return encr;
}

/**
 * @see @file huffman.h / @function
 */
char* makeCharactersFromBits(char *bits, char *endChar) {
  int size = (strlen(bits) + strlen(endChar))/7 + 2;
  char *encr = (char*)calloc(sizeof(char), size);
  int actualBitIndex = 0;
  char *chars = (char*)calloc(sizeof(char), 9);
  const int E_CHAR = 7;
  chars[7] = '0';
  for(size_t i = 0; i < strlen(bits) + strlen(endChar); i++) {
      if(actualBitIndex >= E_CHAR) {
        actualBitIndex = 0;
        encr[strlen(encr)] = charBitsToChar(chars);
      }
      if(i < strlen(bits)) chars[actualBitIndex] = bits[i];
      else
        chars[actualBitIndex] = endChar[i-strlen(bits)];
      actualBitIndex++;
  }
  if(actualBitIndex != 0) {
    while(actualBitIndex < E_CHAR) {
      chars[actualBitIndex] = '0';
      actualBitIndex++;
    }
    encr[strlen(encr)] = charBitsToChar(chars);
  }
  free(chars);
  free(bits);
  return encr;
}

/**
 * @see @file huffman.h / @function
 */
void writeEncryptionInFile(char *fileIn, char *fileOut, lst prefixes, int maxPrefixLength) {
  if(fileIn != NULL && fileOut != NULL && prefixes != NULL) {
    FILE *file = fopen(fileIn, "r");
    FILE *fileW = fopen(fileOut, "wb");
    if(file != NULL && fileOut != NULL) {
      char ligne[255];
      int actualBitIndex = 0;
      char *bits = (char*)calloc(sizeof(char), 9);
      const int E_CHAR = 7;
      bits[E_CHAR] = '0';
      char *endChar = (char*)getTupleValue((tpl)getTupleInListByKey(prefixes, '\0'));
      while(fgets(ligne, sizeof(ligne), file) != NULL) {
        char *encrOfLigne = getEncryptionOf(ligne, prefixes, maxPrefixLength);
        for(size_t i = 0; i < strlen(encrOfLigne); i++) {
          if(actualBitIndex >= E_CHAR) {
            actualBitIndex = 0;
            writeBitsInOpenedFile(fileW, bits);
          }
          bits[actualBitIndex] = encrOfLigne[i];
          actualBitIndex++;
        }
        free(encrOfLigne);
      }
      for (size_t i = 0; i < strlen(endChar); i++) {
        if(actualBitIndex >= E_CHAR) {
          actualBitIndex = 0;
          writeBitsInOpenedFile(fileW, bits);
        }
        bits[actualBitIndex] = endChar[i];
        actualBitIndex++;
      }
      if(actualBitIndex != 0) {
        while(actualBitIndex != 0) {
          bits[actualBitIndex] = '0';
          actualBitIndex++;
          if(actualBitIndex >= E_CHAR) actualBitIndex = 0;
        }
        writeBitsInOpenedFile(fileW, bits);
      }
      printf("Encryption process completed\n");
      free(bits);
      fclose(fileW);
      fclose(file);
    } else {
      if(file == NULL) perror(fileIn);
      if(fileW == NULL) perror(fileOut);
      exit(0);
    }
  }
}

/**
 * @see @file huffman.h / @function
 */
void saveKeyInFile(lst occurrences, char *fileKey) {
  if(occurrences != NULL && fileKey != NULL) {
    FILE *file = fopen(fileKey, "w");
    tpl occurrence = NULL;
    if(file != NULL) {
      for (size_t i = 0; i < getListSize(occurrences); i++) {
        occurrence = getOfList(occurrences, i);
        if(*((char*)getTupleKey(occurrence)) != '\0') {
          fprintf(file, "%c:%d;", *((char*)getTupleKey(occurrence)), *((int*)getTupleValue(occurrence)));
        }
      }
      fclose(file);
    } else {
      if(file == NULL) perror(fileKey);
      exit(0);
    }
  }
}


/**
 * @see @file huffman.h / @function
 */
char* getDecryptionOf(char *str, nd tree) {
  const size_t numberOfBits = 8;
  unsigned int resultSize = strlen(str)*3 + 1;
  char *result = (char*)calloc(sizeof(char), resultSize);
  nd currentNode = tree;
  char *path;
  char *charToWrite;
  int resultIndex = 0;
  int endFound = 0;
  for(size_t i = 0; i < strlen(str); i++) {
    path = decimalToBinary((unsigned int)str[i], numberOfBits);
    for(size_t j = 0; j < strlen(path)-1; j++) {
      if(isLeafNode((currentNode))) {
        charToWrite = (char*)getTupleKey((tpl)getNodeTag(currentNode));
        result[resultIndex] = *charToWrite;
        currentNode = tree;
        resultIndex++;
        if(*charToWrite == '\0') endFound = 1;
      }
      if(path[j] == '0') {
        currentNode = getNodeLeft(currentNode);
      } else if(path[j] == '1') {
        currentNode = getNodeRight(currentNode);
      }
      if(endFound == 1) break;
    }
    free(path);
    if(endFound == 1) break;
  }
  // if(strlen(result) < resultSize) {
  //   char *tmp = (char*)realloc(result, strlen(result) + 1);
  //   if(tmp != NULL) result = tmp;
  // }
  return result;
}

/**
 * @see @file huffman.h / @function
 */
void writeDecryptionInFile(char *fileIn, char *fileOut, nd tree) {
  FILE *fileToRead = fopen(fileIn, "r");
  FILE *fileToWrite = fopen(fileOut, "w");
  if(fileToRead != NULL && fileToWrite != NULL) {
    nd currentNode = tree;
    char *currentCharBits;
    char charToWrite;
    char c;
    int again = 1;
    while((c = fgetc(fileToRead)) != EOF && again == 1) {
      currentCharBits = decimalToBinary(c, 8);
      currentCharBits[7] = '\0';
      for (size_t i = 0; i < strlen(currentCharBits); i++) {
        if(isLeafNode(currentNode)) {
          charToWrite = *((char*)getTupleKey((tpl)getNodeTag(currentNode)));
          if (charToWrite == '\0') {
            again = 0;
            break;
          }
          fprintf(fileToWrite, "%c", charToWrite);
          currentNode = tree;
        }
        if(currentCharBits[i] == '0') {
          currentNode = getNodeLeft(currentNode);
        } else if(currentCharBits[i] == '1') {
          currentNode = getNodeRight(currentNode);
        }
      }
      free(currentCharBits);
    }
    printf("Decryption process completed\n");
    fclose(fileToRead);
    fclose(fileToWrite);
  } else {
    if(fileToRead == NULL) perror(fileIn);
    if(fileToWrite == NULL) perror(fileOut);
    destroyNode(&tree);
    exit(0);
  }
}

/**
 * @see @file huffman.h / @function
 */
nd getTreeFromKeyFile(char *fileKey) {
  FILE *file = fopen (fileKey, "r");
  if(file != NULL) {
    char ligne[255];
    tpl occurrence = NULL;
    int etape = 1;
    char l = 0;
    unsigned int tmp = 0;
    char *nb = (char*)calloc(sizeof(char), 11);
    lst occurrences = createDefinedList(&destroyTupleGen, &printTupleGen);
    while(fgets(ligne, sizeof(ligne), file) != NULL) {
      for (unsigned int i = 0; i < strlen(ligne); i++) {
        if (etape == 1) {
          l = ligne[i];
          etape++;
        } else if(etape == 2) {
          if (ligne[i] == ':') etape++;
        } else if(etape == 3) {
          nb[tmp] = ligne[i];
          tmp++;
          if(ligne[i+1] == ';') {
            while(tmp < 11) {
              nb[tmp] = 0;
              tmp++;
            }
            tmp = 0;
            char *letter = (char*)malloc(sizeof(char)); *letter = l;
            int *value = (int*)malloc(sizeof(int)); *value = strToInt(nb);
            occurrence = createTuple(letter, value, NULL, printChar, NULL, printInt);
            addInList(occurrences, occurrence);
            etape++;
          }
        } else if(etape == 4) {
          if (ligne[i] == ';') etape = 1;
        }
      }
    }
    fclose(file);
    free(nb);
    char *letter = (char*)malloc(sizeof(char)); *letter = '\0';
    int *value = (int*)malloc(sizeof(int)); *value = 1;
    occurrence = createTuple(letter, value, NULL, printChar, NULL, printInt);
    addInList(occurrences, occurrence);
    nd tree = contructBinaryTree(occurrences);
    destroyList(&occurrences);
    return tree;
  } else {
    perror(fileKey);
  }
  return NULL;
}


/**
 * @see @file huffman.h / @function
 */
lst charOccurencesOfStr(char *str) {
  lst occurrences = createDefinedList(&destroyTupleGen, &printTupleGen);
  char *key = (char*)malloc(sizeof(char));
  int *val = (int*)malloc(sizeof(int));
  *val = 1;
  tpl tupleTmp = NULL;
  for(size_t i = 0; i < strlen(str); i++) {
    tupleTmp = getTupleInListByKey(occurrences, str[i]);
    if(tupleTmp == NULL) {
      *key = str[i];
      tpl tuple = createTupleByCopy(key, val, &copyChar, NULL, &printChar, &copyInt, NULL, &printInt);
      addInList(occurrences, tuple);
    } else {
      (*((int*)getTupleValue(tupleTmp)))++;
      tupleTmp = NULL;
    }
  }
  *key = '\0';
  tpl tuple = createTupleByCopy(key, val, &copyChar, NULL, &printChar, &copyInt, NULL, &printInt);
  addInList(occurrences, tuple);
  free(key);
  free(val);
  return occurrences;
}

/**
 * @see @file huffman.h / @function
 */
lst charOccurencesOfFile(char *srcFile) {
  FILE *file = fopen (srcFile, "r");
  if(file != NULL) {
    char ligne[512];
    lst occurrences = createDefinedList(&destroyTupleGen, &printTupleGen);
    char *key = (char*)malloc(sizeof(char));
    int *val = (int*)malloc(sizeof(int));
    *val = 1;
    tpl tupleTmp = NULL;
    while(fgets(ligne, sizeof(ligne), file) != NULL) {
      for(unsigned int i = 0; i < strlen(ligne); i++) {
        tupleTmp = getTupleInListByKey(occurrences, ligne[i]);
        if(tupleTmp == NULL) {
          *key = ligne[i];
          tpl tuple = createTupleByCopy(key, val, &copyChar, NULL, &printChar, &copyInt, NULL, &printInt);
          addInList(occurrences, tuple);
        } else {
          (*((int*)getTupleValue(tupleTmp)))++;
          tupleTmp = NULL;
        }
      }
    }
    *key = '\0';
    tpl tuple = createTupleByCopy(key, val, &copyChar, NULL, &printChar, &copyInt, NULL, &printInt);
    addInList(occurrences, tuple);
    free(key);
    free(val);
    fclose(file);
    return occurrences;
  } else {
    perror(srcFile);
    exit(0);
  }
  return NULL;
}

/**
 * @see @file huffman.h / @function
 */
nd contructBinaryTree(lst occurrences) {
  lst treeNodes = createDefinedList(destroyNodeGen, printNodeGen);
  nd tree = NULL;
  tpl tuple = NULL;
  for(size_t i = 0; i < getListSize(occurrences); i++) {
    tuple = getOfList(occurrences, i);
    tpl tmp = makeCopyTuple(tuple, copyChar, copyInt);
    nd node = createDefinedNode(tmp, destroyTupleGen, printTupleGen);
    addInList(treeNodes, node);
  }
  if(getListSize(treeNodes) > 0) {
    while(getListSize(treeNodes) > 1) {
      mergeTwoSmallerNodes(treeNodes);
    }
    if(getListSize(treeNodes) == 1) tree = (nd)removeFromList(treeNodes, 0);
  }
  destroyList(&treeNodes);
  return tree;
}

/**
 * @see @file huffman.h / @function
 */
void mergeTwoSmallerNodes(lst list) {
  size_t j = 0;
  size_t k = 1;
  int valueJ = *((int*)getTupleValue((tpl)getNodeTag((nd)getOfList(list, j))));
  int valueK = *((int*)getTupleValue((tpl)getNodeTag((nd)getOfList(list, k))));
  int *currentValue = NULL;
  for(size_t i = 2; i < getListSize(list); i++) {
    currentValue = (int*)getTupleValue((tpl)getNodeTag((nd)getOfList(list, i)));
    if(k < j) {
      if(*currentValue < valueK && i != j && i != k) {
        k = i;
        valueK = *currentValue;
      }
    } else {
      if(*currentValue < valueJ && i != j && i != k) {
        j = i;
        valueJ = *currentValue;
      }
    }
  }
  if(j < k) k--;
  nd child1 = (nd)removeFromList(list, j);
  nd child2 = (nd)removeFromList(list, k);
  int valChild1 = *((int*)getTupleValue((tpl)getNodeTag(child1)));
  int valChild2 = *((int*)getTupleValue((tpl)getNodeTag(child2)));
  int *newValue = (int*)malloc(sizeof(int));
  *newValue = valChild1 + valChild2;
  tpl newTuple = createTuple(NULL, newValue, NULL, printChar, NULL, printInt);
  nd newNode = createDefinedNode(newTuple, destroyTupleGen, printTupleGen);
  if(valChild1 <= valChild2) {
    setNodeLeft(newNode, child1);
    setNodeRight(newNode, child2);
  } else {
    setNodeLeft(newNode, child2);
    setNodeRight(newNode, child1);
  }
  addInList(list, newNode);
}

/**
 * @see @file huffman.h / @function
 */
lst prefixesList(lst occurrences, char *fileKey, int *maxPrefixLength) {
  nd tree = contructBinaryTree(occurrences);
  *maxPrefixLength = getNodeDepth(tree);
  saveKeyInFile(occurrences, fileKey);
  destroyList(&occurrences);
  lst prefixes = createDefinedList(&destroyTupleGen, &printTupleGen);
  char *prefix = (char*)calloc(sizeof(char), *maxPrefixLength + 1);
  calculatePrefixes(tree, prefixes, prefix);
  free(prefix);
  destroyNode(&tree);
  return prefixes;
}

/**
 * @see @file huffman.h / @function
 */
void calculatePrefixes(nd node, lst prefixes, char *prefix) {
  if(node == NULL || prefix == NULL || prefixes == NULL) pointerNullError();
  int next = (int)strlen(prefix);
  if(isLeafNode(node)) {
    char *ch = (char*)copyChar(getTupleKey((tpl)getNodeTag(node)));
    char *pr = copyString(prefix);
    tpl prefixTuple = createTuple(ch, pr, NULL, printChar, NULL, printString);
    addInList(prefixes, prefixTuple);
  } else {
    nd left = getNodeLeft(node);
    nd right = getNodeRight(node);
    if(left != NULL) {
      prefix[next] = '0';
      calculatePrefixes(left, prefixes, prefix);
      prefix[next] = 0;
    }
    if(right != NULL) {
      prefix[next] = '1';
      calculatePrefixes(right, prefixes, prefix);
      prefix[next] = 0;
    }
  }
}


/**
 * @see @file huffman.h / @function
 */
tpl getTupleInListByKey(lst list, char key) {
  tpl tuple = NULL;
  for(size_t i = 0; i < getListSize(list); i++) {
    tuple = (tpl)getOfList(list, i);
    if(*((char*)getTupleKey(tuple)) == key) return tuple;
  }
  return NULL;
}

/**
 * @see @file huffman.h / @function
 */
void writeBitsInOpenedFile(FILE *fileW, char *bits) {
  if(fileW != NULL) {
    char charToWrite = charBitsToChar(bits);
    if(charToWrite == '\0') charToWrite = 1; // Bits values: 00000001
    fprintf(fileW, "%c", charToWrite);
    // fprintf(fileW, "%s ", bits); // To print the string of bits in the file
  }
}


/* ========================================================================== */
/* ========================================================================== */
