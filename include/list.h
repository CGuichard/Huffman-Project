#ifndef LIST_H
#define LIST_H

/* ========================================================= */
/* ================== LISTE_H FILE HEADER ================== */
/* ========================================================= */

/* ========= Includes ======== */

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

/* ========== Struct ========= */

typedef struct list* lst;

/* ======== Functions ======== */

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
void removeInList(lst l, size_t pos);
void* popInList(lst l, size_t pos);
void* get(lst l, size_t pos);

/* ========================================================= */

#endif
