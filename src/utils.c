/**
 * @file utils.c
 * @author GUICHARD Clément
 * @standard C99
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
 *  - copyInt
 *  - copyChar
 *  - pointerAllocError
 *  - pointerNullError
 */

#include "utils.h"


/* ================================================== */
/* ===================== PUBLIC ===================== */
/* ========================================================================== */


/** ===========================================================================/
 * @see @file utils.h / @function equalsInt
 */
int equalsInt(void *val1, void *val2){
  return *((int*)val1) == *((int*)val2);
}

/** ===========================================================================/
 * @see @file utils.h / @function printInt
 */
void printInt(void *elem){
  printf("%d", *((int*)elem));
}

/** ===========================================================================/
 * @see @file utils.h / @function printChar
 */
void printChar(void *elem){
  printf("'%c'", *((char*)elem));
}

/** ===========================================================================/
 * @see @file utils.h / @function copyInt
 */
void* copyInt(void *elem){
  int* i = (int*)malloc(sizeof(int));
  *i = *((int*)elem);
  return i;
}

/** ===========================================================================/
 * @see @file utils.h / @function copyChar
 */
void* copyChar(void *elem){
  char* i = (char*)malloc(sizeof(char));
  *i = *((char*)elem);
  return i;
}

/** ===========================================================================/
 * @see @file utils.h / @function pointerAllocError
 */
void pointerAllocError(){
  printf("Memory error: memory allocation can't be done\n");
  exit(0);
}

/** ===========================================================================/
 * @see @file utils.h / @function pointerNullError
 */
void pointerNullError(){
  printf("Null pointer error: a function pointer needed to not be null has been found null\n");
  exit(0);
}


/* ========================================================================== */
/* ========================================================================== */
