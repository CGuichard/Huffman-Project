#ifndef UTILS_H
#define UTILS_H

  #ifndef STD_LIBS_H
  #define STD_LIBS_H

  #include <stdlib.h>
  #include <stdio.h>

  #endif

int equalsInt(void *val1, void *val2);
void printInt(void *elem);
void printChar(void *elem);
void* copyInt(void *elem);
void* copyChar(void *elem);
void pointerAllocError();
void pointerNullError();

#endif
