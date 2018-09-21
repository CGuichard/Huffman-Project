#include "list.h"

struct list {
  size_t numberOfElements;
  size_t allocatedBlocks;
  void** objectList;
  void (*destroyElem)(void **elem);
  void (*printElem)(void *elem);
};

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

void setElemDestroyer(lst l, void(*destroyElem)(void **elem)){
    l->destroyElem = destroyElem;
}

void setElemPrinter(lst l, void(*printElem)(void *elem)){
  l->printElem = printElem;
}

void destroyList(lst *l){
  emptyTheList(*l);
  free(*l);
  *l = NULL;
}

void emptyTheList(lst l){
  if(l != NULL){
    if(l->objectList != NULL){
      for(size_t i = 0; i < l->numberOfElements; i++){
        if(l->objectList[i] != NULL){
          if(l->destroyElem != NULL)
            l->destroyElem(&(l->objectList[i]));
          else
            free(l->objectList[i]);
          l->objectList[i] = NULL;
        }
      }
      free(l->objectList);
    }
    l->objectList = NULL;
    l->numberOfElements = 0;
    l->allocatedBlocks   = 0;
  }
}

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

void addInList(lst l, void *elem){
  if(l != NULL){
    resizeAlloc(l, 1);
    l->objectList[l->numberOfElements] = elem;
    l->numberOfElements++;
  }
}

#include "tuple.h"

void popList(lst l){
  if(l != NULL && l->numberOfElements > 0){
    if (l->objectList[l->numberOfElements - 1] != NULL) {
        if (l->destroyElem != NULL)
          l->destroyElem((void**)&(l->objectList[l->numberOfElements - 1]));
        else{
            free(l->objectList[l->numberOfElements - 1]);
            l->objectList[l->numberOfElements - 1] = NULL;
        }
        l->numberOfElements--;
        resizeAlloc(l, 0);
    }
  }
}

void* get(lst l, size_t pos){
  if(pos < l->numberOfElements)
    return l->objectList[pos];
  return NULL;
}

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
    int actual_size = (int)(N*sizeof(void*));
    // printf("%d: %d <-> %d\n", N, actual_size, B);
    if(N == 0){
      emptyTheList(l);
    }else if(actual_size > B){
      // printf("RESIZE +\n");
      size = actual_size + B / 2;
      void** ptr = (void**)realloc(l->objectList, size);
      if(ptr != NULL) l->objectList = ptr;
      else pointerAllocError();
      l->allocatedBlocks = size;
    }
    else if(actual_size < B/2){
      // printf("RESIZE -\n");
      size = actual_size + actual_size / 2;
      void** ptr = (void**)realloc(l->objectList, size);
      if(ptr != NULL) l->objectList = ptr;
      else pointerAllocError();
      l->allocatedBlocks = size;
    }
  }
}
