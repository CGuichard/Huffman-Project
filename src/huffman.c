#include "huffman.h"

int main(void){

  encrypt("test/halo_rebirth.txt");

  return EXIT_SUCCESS;
}

void encrypt(char *srcFile){
  lst occurences = charOccurences(srcFile);
  printList(occurences);
  destroyList(&occurences);
}

lst charOccurences(char *srcFile){
  FILE* file = fopen (srcFile, "r");
  if(file != NULL) {
    char ligne[255];
    lst occurences = createDefinedList(&destroyTupleGen, &printTupleGen);
    char *key = (char*)malloc(sizeof(char));
    int *val = (int*)malloc(sizeof(int)); *val = 1;
    tpl tupleTmp   = NULL;
    while(fgets(ligne, sizeof(ligne), file) != NULL) {
      for(unsigned int i = 0; i < strlen(ligne); i++) {
        tupleTmp = getTupleInListByKey(occurences, ligne[i]);
        if(tupleTmp == NULL){
          *key = ligne[i];
          tpl tuple = createTupleByCopy(key, val, &copyChar, NULL, &printChar, &copyInt, NULL, &printInt);
          addInList(occurences, tuple);
        }else{
          (*((int*)getTupleValue(tupleTmp)))++;
          tupleTmp = NULL;
        }
      }
    }
    free(key);
    free(val);
    fclose(file);
    return occurences;
  }else{
    perror(srcFile);
    exit(0);
  }
  return NULL;
}

tpl getTupleInListByKey(lst list, char key){
  tpl tuple = NULL;
  for (int i = 0; i < getListSize(list); i++) {
    tuple = (tpl)get(list, i);
    if (*((char*)getTupleKey(tuple)) == key) return tuple;
  }
  return NULL;
}
