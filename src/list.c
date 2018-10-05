/**
 * @file list.c
 * @author Clément GUICHARD
 * @standard C99
 * @version 1.0
 * @date 11th October 2018
 *
 * @brief Implementation file for the struct list and the functions in "list.h"
 *
 * This file implements the struct "list" described in the file "list.h" (and
 * here in the comments of the struct implementation), a generic structure
 * for multiple uses
 *
 * Overview about private functions of list:
 *    - destroyElemInList
 *    - resizeAlloc
 *
 * The private functions are not in the header file because they are not
 * supposed to be used in other files. To prevent that, they are declared here,
 * in the .c file and not in the header file. They are used only by functions in
 * this file
 *
 * Overview about public functions of list:
 *    - createList
 *    - createDefinedList
 *    - getListSize
 *    - setElemDestroyer
 *    - setElemPrinter
 *    - destroyList
 *    - emptyTheList
 *    - printList
 *    - addInList
 *    - popList
 *    - removeInList
 *    - popInList
 *    - get
 */

#include "list.h"


/* ================================================== */
/* ==================== STRUCT DEF ================== */
/* ========================================================================== */


/**
 * @struct list
 * @brief A dynamic generic list
 *
 * The structure list is a dynamic list, it size is modified when needed. This
 * list is also generic to support any type of element. However the type of
 * variables pointed to by the list must be constrained by a principle of
 * uniqueness. For example, one list can contain only integers, or only
 * characters, or only one type of struct.
 */
struct list {
  size_t numberOfElements; /**< Number of elements in the list */
  size_t allocatedBlocks; /**< Number of blocks allocated in the memory */
  void** objectList; /**< List of pointers */
  void (*destroyElem)(void **elem); /**< Function used to destroy an element */
  void (*printElem)(void *elem); /**< Function used to print an element */
};


/* ================================================== */
/* ============== DEF PRIVATE FUNCTIONS ============= */
/* ========================================================================== */


/**
 * @function destroyElemInList
 * @brief Destroy an element of the list
 *
 * This function destroy an element of the list. If the destroyElem of the
 * list is set, it is used, if not the function free() is used
 *
 * @param{lst} l: pointer of the list
 * @param{size_t} pos: position of the element in the list, its index
 *
 * @return{void}
 */
void destroyElemInList(lst l, size_t pos);

/**
 * @function resizeAlloc
 * @brief Resizes the current size of memory took by the list
 *
 * This function resizes the current size of the list in memory according to the
 * number of items that will be added soon if necessary
 *
 * @param{lst} l: pointer of the list
 * @param{int} nbNewElements: number of new elements add in the list (can be
 * inferior to 0 if elements are removed)
 *
 * @return{void}
 */
void resizeAlloc(lst l, int nbNewElements);


/* ================================================== */
/* ===================== PUBLIC ===================== */
/* ========================================================================== */


/**
 * @see @file list.h / @function createList
 */
lst createList(){
  lst l = (lst)malloc(sizeof(struct list));
  if(l == NULL) exit(1);
  l->numberOfElements = 0;
  l->allocatedBlocks  = 0;
  l->objectList       = NULL;
  l->destroyElem      = NULL;
  l->printElem        = NULL;
  return l;
}

/**
 * @see @file list.h / @function createDefinedList
 */
lst createDefinedList(void(*destroyElem)(void **elem), void(*printElem)(void *elem)){
  lst l = (lst)malloc(sizeof(struct list));
  if(l == NULL) pointerAllocError();
  l->numberOfElements = 0;
  l->allocatedBlocks  = 0;
  l->objectList       = NULL;
  l->destroyElem      = destroyElem;
  l->printElem        = printElem;
  return l;
}

/**
 * @see @file list.h / @function getListSize
 */
size_t getListSize(lst l){
  return (l != NULL)?l->numberOfElements:0;
}

/**
 * @see @file list.h / @function setElemDestroyer
 */
void setElemDestroyer(lst l, void(*destroyElem)(void **elem)){
    l->destroyElem = destroyElem;
}

/**
 * @see @file list.h / @function setElemPrinter
 */
void setElemPrinter(lst l, void(*printElem)(void *elem)){
  l->printElem = printElem;
}

/**
 * @see @file list.h / @function destroyList
 */
void destroyList(lst *l){
  emptyTheList(*l);
  free(*l);
  *l = NULL;
}

/**
 * @see @file list.h / @function emptyTheList
 */
void emptyTheList(lst l){
  if(l != NULL){
    if(l->objectList != NULL){
      for(size_t i = 0; i < l->numberOfElements; i++){
        if(l->objectList[i] != NULL){
          destroyElemInList(l, i);
        }
      }
      free(l->objectList);
    }
    l->objectList = NULL;
    l->numberOfElements = 0;
    l->allocatedBlocks   = 0;
  }
}

/**
 * @see @file list.h / @function printList
 */
void printList(lst l){
  if(l == NULL){
    printf("<List destroyed>\n");
  }else{
    printf("<List | size: %zd ; blocks: %zd>[", l->numberOfElements, l->allocatedBlocks);
    if(l->objectList != NULL){
      for(size_t i = 0; i < l->numberOfElements; i++){
        if(l->printElem != NULL){
          l->printElem(l->objectList[i]);
        }else{
          printf("<Undefined element printer>");
        }
        printf("%s", ((i < l->numberOfElements - 1)?", ":""));
      }
    }
    printf("]\n");
  }
}

/**
 * @see @file list.h / @function addInList
 */
void addInList(lst l, void *elem){
  if(l != NULL){
    resizeAlloc(l, 1);
    l->objectList[l->numberOfElements] = elem;
    l->numberOfElements++;
  }
}

/**
 * @see @file list.h / @function popList
 */
void popList(lst l){
  if(l != NULL && l->numberOfElements > 0 && l->objectList[l->numberOfElements-1] != NULL){
    destroyElemInList(l, l->numberOfElements-1);
    l->numberOfElements--;
    resizeAlloc(l, 0);
  }
}

/**
 * @see @file list.h / @function removeInList
 */
void removeInList(lst l, size_t pos){
  if(l != NULL && l->numberOfElements > 0 && l->objectList[l->numberOfElements-1] != NULL && pos < l->numberOfElements){
    destroyElemInList(l, pos);
    for (size_t i = pos; i < l->numberOfElements-1; i++)
      l->objectList[i] = l->objectList[i+1];
    l->objectList[l->numberOfElements-1] = NULL;
    l->numberOfElements--;
    resizeAlloc(l, 0);
  }
}

/**
 * @see @file list.h / @function popInList
 */
void* popInList(lst l, size_t pos){
  if(l != NULL && l->numberOfElements > 0 && l->objectList[l->numberOfElements-1] != NULL && pos < l->numberOfElements){
    void* elem = l->objectList[pos];
    for (size_t i = pos; i < l->numberOfElements-1; i++)
      l->objectList[i] = l->objectList[i+1];
    l->objectList[l->numberOfElements-1] = NULL;
    l->numberOfElements--;
    resizeAlloc(l, 0);
    return elem;
  }
  return NULL;
}

/**
 * @see @file list.h / @function get
 */
void* get(lst l, size_t pos){
  if(pos < l->numberOfElements)
    return l->objectList[pos];
  return NULL;
}

/* ================================================== */
/* ===================== PRIVATE ==================== */
/* ========================================================================== */

/**
 * @see @file list.c / @function destroyElemInList
 */
void destroyElemInList(lst l, size_t pos){
  if(l->destroyElem != NULL)
    l->destroyElem((void**)&(l->objectList[pos]));
  else{
      free(l->objectList[pos]);
      l->objectList[pos] = NULL;
  }
}

/**
 * @see @file list.c / @function resizeAlloc
 */
void resizeAlloc(lst l, int nbNewElements){
  if(l != NULL){
    unsigned int size = 0;
    int N = l->numberOfElements + nbNewElements;
    int B = l->allocatedBlocks;
    if(l->objectList == NULL){
      size = 2 * sizeof(void*);
      l->objectList = (void**)malloc(size);
      if(l->objectList == NULL) pointerAllocError();
      l->allocatedBlocks = size;
      B = size;
    }
    int actualSize = (int)(N*sizeof(void*));
    // printf("%d: %d <-> %d\n", N, actualSize, B);
    if(N == 0){
      emptyTheList(l);
    }else if(actualSize > B){
      // printf("RESIZE +\n");
      size = actualSize + B / 2;
      void** ptr = (void**)realloc(l->objectList, size);
      if(ptr != NULL) l->objectList = ptr;
      else pointerAllocError();
      l->allocatedBlocks = size;
    }else if(actualSize < B/2){
      // printf("RESIZE -\n");
      // size = actualSize + actualSize / 2;
      // void** ptr = (void**)realloc(l->objectList, size);
      // if(ptr != NULL) l->objectList = ptr;
      // else pointerAllocError();
      // l->allocatedBlocks = size;
    }
  }
}


/* ========================================================================== */
/* ========================================================================== */
