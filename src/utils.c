#include "utils.h"

int equalsInt(void *val1, void *val2){
  return *((int*)val1) == *((int*)val2);
}

void printInt(void *elem){
  printf("%d", *((int*)elem));
}

void printChar(void *elem){
  printf("'%c'", *((char*)elem));
}

void* copyInt(void *elem){
  int* i = (int*)malloc(sizeof(int));
  *i = *((int*)elem);
  return i;
}

void* copyChar(void *elem){
  char* i = (char*)malloc(sizeof(char));
  *i = *((char*)elem);
  return i;
}

void pointerAllocError(){
  printf("Memory error: memory allocation can't be done\n");
  exit(1);
}

void pointerNullError(){
  printf("Null pointer error: a function pointer needed to not be null has been found null\n");
  exit(1);
}
