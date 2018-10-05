/**
 * @file utils.c
 * @author Clément GUICHARD
 * @standard C99
 * @version 1.0
 * @date 11th October 2018
 *
 * @brief Implementation file for "utils.h"
 *
 * This file contains tool functions, used by
 * other files but not really belonging to a file,
 * and being useful in many places of the project
 *
 * Overview about public functions of utils
 *  - equalsInt
 *  - printInt
 *  - printChar
 *  - printString
 *  - copyInt
 *  - copyChar
 *  - copyString
 *  - charBitsToChar
 *  - strToInt
 *  - pointerAllocError
 *  - pointerNullError
 */

#include "utils.h"


/* ================================================== */
/* ===================== PUBLIC ===================== */
/* ========================================================================== */


/**
 * @see @file utils.h / @function equalsInt
 */
int equalsInt(void *val1, void *val2){
  return *((int*)val1) == *((int*)val2);
}

/**
 * @see @file utils.h / @function printInt
 */
void printInt(void *elem){
  if(elem != NULL)
    printf("%d", *((int*)elem));
  else
    printf("NULL");
}

/**
 * @see @file utils.h / @function printChar
 */
void printChar(void *elem){
  if(elem != NULL)
    printf("'%c'", *((char*)elem));
  else
    printf("NULL");
}

/**
 * @see @file utils.h / @function printString
 */
void printString(void *elem){
  if(elem != NULL)
    printf("\"%s\"", (char*)elem);
  else
    printf("NULL");
}

/**
 * @see @file utils.h / @function copyInt
 */
void* copyInt(void *elem){
  int* i = (int*)malloc(sizeof(int));
  *i = *((int*)elem);
  return i;
}

/**
 * @see @file utils.h / @function copyChar
 */
void* copyChar(void *elem){
  char* c = (char*)malloc(sizeof(char));
  *c = *((char*)elem);
  return c;
}

/**
 * @see @file utils.h / @function copyString
 */
void* copyString(void *elem){
  char* s = (char*)malloc(sizeof(char) * (strlen((char*)elem)+1));
  strcpy(s, (char*)elem);
  return s;
}

/**
 * @see @file utils.h / @function charBitsToChar
 */
char charBitsToChar(char *bits){
  if (strlen(bits) == 8) {
    unsigned int val = 0;
    for (unsigned int i = 0; i < strlen(bits); i++)
      val += (bits[i] - 48) * pow(2, strlen(bits)-i-1);
    return val;
  }
  return 0;
}

/**
 * @see @file utils.h / @function strToInt
 */
int strToInt(char* str){
  int val = 0;
  for (unsigned int i = 0; i < strlen(str); i++)
    val += (str[i] - 48) * pow(10, strlen(str)-i-1);
  return val;
}

/**
 * @see @file utils.h / @function decimalToBinary
 */
char* decimalToBinary(unsigned int decimal, int numberOfBits){
  char* binaryCode = malloc(sizeof(char) * numberOfBits + 1);
  size_t index = numberOfBits-1;
  for(int c = numberOfBits; c > 0; c--)
  {
    if(decimal%2 & 1)
      binaryCode[index] = '1';
    else
      binaryCode[index] = '0';

    decimal /= 2;
    index--;
  }
  binaryCode[numberOfBits] = '\0';
  return binaryCode;
}


/**
 * @see @file utils.h / @function pointerAllocError
 */
void pointerAllocError(){
  printf("Memory error: memory allocation can't be done\n");
  exit(0);
}

/**
 * @see @file utils.h / @function pointerNullError
 */
void pointerNullError(){
  printf("Null pointer error: a function pointer needed to not be null has been found null\n");
  exit(0);
}


/* ========================================================================== */
/* ========================================================================== */
