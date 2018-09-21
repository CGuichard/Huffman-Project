#ifndef HUFFMAN_H
#define HUFFMAN_H

  #ifndef STD_LIBS_H
  #define STD_LIBS_H

  #include <stdlib.h>
  #include <stdio.h>

  #endif

#include <string.h>
#include "utils.h"
#include "tuple.h"
#include "list.h"
#include "node.h"

void encrypt(char *srcFile);
// void decrypt(char *srcFile, tr tree);

lst charOccurences(char *srcFile);
// tr construct_binary_tree(lst occurences);
// lst contruct_encryption_tab(tr);

tpl getTupleInListByKey(lst list, char key);


#endif
