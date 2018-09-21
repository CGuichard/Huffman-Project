#ifndef LIST_H
#define LIST_H

  #ifndef STD_LIBS_H
  #define STD_LIBS_H

  #include <stdlib.h>
  #include <stdio.h>

  #endif

#include "utils.h"

typedef struct list* lst;

lst createList();
lst createDefinedList(void(*destroyElem)(void **elem), void(*printElem)(void *elem));
int getListSize(lst l);
void setElemDestroyer(lst l, void(*destroyElem)(void **elem));
void setElemPrinter(lst l, void(*printElem)(void *elem));
void destroyList(lst *l);
void emptyTheList(lst l);
void printList(lst l);
void addInList(lst l, void *elem);
void popList(lst l);
void* get(lst l, size_t pos);
void resizeAlloc(lst l, int nbNewElements);

#endif
