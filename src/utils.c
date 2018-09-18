#include "utils.h"

int equalsInt(void *val1, void *val2){
  return *((int*)val1) == *((int*)val2);
}

void printInt(void *elem){
  printf("%d", *((int*)elem));
}

void printChar(void *elem){
  printf("%c", *((char*)elem));
}

void pointerError(){
  printf("Memory error: memory allocation can't be done\n");
  exit(1);
}
