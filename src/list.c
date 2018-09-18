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
  if(l == NULL) pointerError();
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
  if(l != NULL && l->destroyElem != NULL){
    if(l->objectList != NULL){
      for(size_t i = 0; i < l->numberOfElements; i++){
        if(l->objectList[i] != NULL){
          l->destroyElem(&(l->objectList[i]));
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
    printf("<list destroyed>\n");
  }else if(l->printElem != NULL){
    printf("<list | size: %zd ; blocs: %zd>[", l->numberOfElements, l->allocatedBlocks);
    if(l->objectList != NULL){
      for(size_t i = 0; i < l->numberOfElements; i++){
        l->printElem(l->objectList[i]);
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

void popList(lst l){
  resizeAlloc(l, -1);
  if(l != NULL && l->objectList != NULL && l->numberOfElements > 0){
    if(l->objectList[l->numberOfElements - 1] != NULL){
      l->destroyElem(l->objectList[l->numberOfElements - 1]);
      l->objectList[l->numberOfElements - 1] = NULL;
      l->numberOfElements--;
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
      size = 4 * sizeof(void*);
      l->objectList = (void**)malloc(size);
      if(l->objectList == NULL) pointerError();
      l->allocatedBlocks = size;
      B = size;
    }

    int size_actu = (int)(N*sizeof(void*));
    // printf("%d <-> %d\n", size_actu, B);
    if(size_actu == 0){
      emptyTheList(l);
    }else if(size_actu > B){
      // printf("RESIZE +\n");
      size = size_actu + (B/2);
      void** ptr = (void**)realloc(l->objectList, size);
      if(ptr != NULL) l->objectList = ptr;
      else pointerError();
      l->allocatedBlocks = size;
    }else if(size_actu < B/2 && N >= 0){
      // printf("RESIZE -\n");
      size = size_actu + B / 4;
      void** ptr = (void**)realloc(l->objectList, size);
      if(ptr != NULL) l->objectList = ptr;
      else pointerError();
      l->allocatedBlocks = size;
    }
  }
}
