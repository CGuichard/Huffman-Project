#ifndef UTILS_H
#define UTILS_H

/* ========================================================= */
/* ================== TUPLE_H FILE HEADER ================== */
/* ========================================================= */

/* ========= Includes ======== */

#include <stdlib.h>
#include <stdio.h>

/* ======== Functions ======== */

int equalsInt(void *val1, void *val2);
void printInt(void *elem);
void printChar(void *elem);
void* copyInt(void *elem);
void* copyChar(void *elem);
void pointerAllocError();
void pointerNullError();

/* ========================================================= */

#endif
