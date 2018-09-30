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

char* TEST = "TEST_TABERNACLE";

/* ================================================== */
/* ============== DEF PRIVATE FUNCTIONS ============= */
/* ========================================================================== */


/** ===========================================================================/
 * @function setFilesNames
 * @brief Function used to set the files names
 *
 * @param{char**} argv: list of argument pass to the executable
 * @param{int} argc: size of argv
 * @param{char**} fileIn: pointer of the string of the input file
 * @param{char**} fileOut: pointer of the string of the output file
 * @param{char**} fileKey: pointer of the string of the file containing the
 *                         encryption key
 *
 * @return{void}
 */
void setFilesNames(char *argv[], int argc, char **fileIn, char **fileOut, char **fileKey);


/* ================================================== */
/* ====================== MAIN ====================== */
/* ========================================================================== */

int main(int argc, char *argv[]){
  if (argc >= 3) {
    char* fileOut = NULL;
    char* fileKey = NULL;
    char* fileIn = NULL;
    setFilesNames(argv, argc, &fileIn, &fileOut, &fileKey);
    if(!strcmp("encrypt", argv[1])){
      printf("Encrypt file: '%s'. Output file: '%s' (Key file generated: '%s').\n", fileIn, fileOut, fileKey);
      huffmanEncryptFile(fileIn, fileOut, fileKey);
    }else if (!strcmp("decrypt", argv[1])){
      printf("Decrypt file: '%s'. Output file: '%s' (Key file given: '%s').\n", fileIn, fileOut, fileKey);
      huffmanDecryptFile(fileIn, fileOut, fileKey);
    }else{
      printf("Wrong command\n");
    }
    free(fileOut);
    free(fileKey);
  }else{
    char *encr = huffmanEncryptStr(TEST);
    printf("Text: \"%s\"\n", TEST);
    if(encr != NULL){
      printf("Encryption: \"%s\"\n", encr);
      char *decr = huffmanDecryptStr(encr);
      if(decr != NULL){
        printf("Decryption: \"%s\"\n", decr);
      }else{
        printf("Decryption failed\n");
      }
      free(decr);
    }else{
      printf("Encryption failed\n");
    }
    free(encr);
  }
  return EXIT_SUCCESS;
}


/* ================================================== */
/* ===================== PRIVATE ==================== */
/* ========================================================================== */


/** ===========================================================================/
 * @see @file huffman_exec.c / @function setFilesNames
 */
void setFilesNames(char *argv[], int argc, char **fileIn, char **fileOut, char **fileKey){
  *(fileOut) = (char*)malloc(sizeof(char) * 100);
  *(fileKey) = (char*)malloc(sizeof(char) * 104);
  *(fileIn) = argv[2];
  if(!strcmp("encrypt", argv[1])){
    if(argc >= 4){
      strcpy(*(fileOut), argv[3]);
    }else{
      strcpy(*(fileOut), *(fileIn));
      strcat(*(fileOut), ".hfm");
    }
    if(argc >= 5){
      strcpy(*(fileKey), argv[4]);
    }else{
      strcpy(*(fileKey), *(fileOut));
      strcat(*(fileKey), ".key");
    }
  }else if(!strcmp("decrypt", argv[1])){
    if(argc >= 4){
      strcpy(*(fileKey), argv[3]);
    }else{
      strcpy(*(fileKey), *(fileIn));
      strcat(*(fileKey), ".key");
    }
    if(argc >= 5){
      strcpy(*(fileOut), argv[4]);
    }else{
      strcpy(*(fileOut), *(fileIn));
      strcat(*(fileOut), ".txt");
    }
  }
}


/* ========================================================================== */
/* ========================================================================== */
