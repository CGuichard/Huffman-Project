/**
 * @file huffman_exec.c
 * @author Clément GUICHARD
 * @author Thàng long CAMA
 * @standard C99
 * @version 1.0
 * @date 11th October 2018
 *
 * @brief Main file
 *
 * This file is the main file that call the functions created to do a huffman
 * coding.
 */

#include "huffman.h"


/* ================================================== */
/* ====================== MAIN ====================== */
/* ========================================================================== */


int main(int argc, char *argv[]){

  if (argc >= 3) {
    char* fileIn = argv[2];
    char* fileOut = (char*)malloc(sizeof(char) * 100);
    char* fileKey = (char*)malloc(sizeof(char) * 104);

    if(argc >= 4){
      strcpy(fileOut, argv[3]);
      strcpy(fileKey, fileOut);
      strcat(fileKey, ".key");
    }else{
      strcpy(fileOut, fileIn);
      strcat(fileOut, ".hfm");
    }

    if(argc >= 5){
      strcpy(fileKey, argv[4]);
    }else{
      strcpy(fileKey, fileOut);
      strcat(fileKey, ".key");
    }

    if(!strcmp("encrypt", argv[1])){
      printf("Encrypt file: '%s'. Output file: '%s' (Key file generated: '%s').\n", fileIn, fileOut, fileKey);
      // encryptFile(fileIn, fileOut, fileKey);
    }else if (!strcmp("decrypt", argv[1])){
      printf("Decrypt file: '%s'. Output file: '%s' (Key file given: '%s').\n", fileIn, fileOut, fileKey);
      // decryptFile(fileIn, fileOut, fileKey);
    }else{
      printf("Wrong command\n");
    }
    free(fileOut);
    free(fileKey);
  }else{
    printf("#============== TEST ==============#\n\n");
    char* encr = encryptStr("TEST TABERNACLE");
    // printf("Encrypt: %s\n", encr);
    printf("\n\n#==================================#\n");
  }

  return EXIT_SUCCESS;
}


/* ========================================================================== */
/* ========================================================================== */
