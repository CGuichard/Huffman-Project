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

char *TEST1 = "J'ai perdu ma force et ma vie,\nEt mes amis et ma gaieté,\nJ'ai perdu jusqu'à la fierté\nQui faisait croire à mon génie.\n\nQuand j'ai connu la Vérité,\nJ'ai cru que c'était une amie ;\nQuand je l'ai comprise et sentie,\nJ'en étais déjà dégoûté.\n\nEt pourtant elle est éternelle,\nEt ceux qui se sont passés d'elle\nIci-bas ont tout ignoré.\n\nDieu parle, il faut qu'on lui réponde.\nLe seul bien qui me reste au monde\nEst d'avoir quelquefois pleuré.\nAlfred de Musset.";
char *TEST2 = "This is a test to verify if the encryption and the decryption are correct";
char *TEST3 = "TTT";

/* ================================================== */
/* ============== DEF PRIVATE FUNCTIONS ============= */
/* ========================================================================== */

/**
 * @function testStr
 * @brief Function used to test a string of characters encryption and decryption
 *
 * @param{char*} str: string of characters to test
 *
 * @return{void}
 */
void testStr(char *str);

/**
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

int main(int argc, char *argv[]) {
  printf("%c\n", 50089);
  if (argc >= 3) {
    char *fileOut = NULL;
    char *fileKey = NULL;
    char *fileIn = NULL;
    setFilesNames(argv, argc, &fileIn, &fileOut, &fileKey);
    if(!strcmp("encrypt", argv[1])) {
      printf("Encrypt file: '%s'. Output file: '%s' (Key file generated: '%s').\n", fileIn, fileOut, fileKey);
      huffmanEncryptFile(fileIn, fileOut, fileKey);
    } else if (!strcmp("decrypt", argv[1])) {
      printf("Decrypt file: '%s'. Output file: '%s' (Key file given: '%s').\n", fileIn, fileOut, fileKey);
      huffmanDecryptFile(fileIn, fileOut, fileKey);
    } else {
      printf("Wrong command\n");
    }
    free(fileOut);
    free(fileKey);
  } else {
    int again = 1;
    int inputreturn;
    char input[10];
    int choice = -1;
    while(again == 1) {
      printf("# ==================================== #\n# ============ TEST MENU ============= #\n# ==================================== #\n\n");
      printf("0. Quit\n");
      printf("1. Test a string of characters\n");
      printf("2. Test a file\n");
      printf( "\nEnter your choice (ex: 0 for quit): ");
      inputreturn = scanf("%s", input);
      if(inputreturn < 0) {
        printf("\nError while reading the input\n");
      } else {
        choice = strToInt(input);
        if(choice < 0 || choice > 2) {
          printf("\nUnknown choice\n");
        } else {
          switch (choice) {
            case 0:
              again = 0;
              printf("\nGood bye!\n");
              break;
            case 1:
              printf("\nYou choosed to test the encryption and the decryption of a string of characters\n");
              printf("Enter 0 to continue: ");
              inputreturn = scanf("%s", input);
              if(inputreturn < 0) {
                printf("\nError while reading the input\n");
              } else {
                choice = strToInt(input);
                if(choice == 0) {
                  char *test = (char*)calloc(sizeof(char), 201);
                  printf("\nPlease enter the string to test: ");
                  test = fgets(test, 200, stdin);
                  printf("\n\n");
                  testStr(test);
                  free(test);
                } else {
                  printf("\nProcess stopped\n");
                }
              }
              break;
            case 2:
              printf("\nYou choosed to test the encryption and the decryption of a file\n");
              printf("Enter 0 to continue: ");
              inputreturn = scanf("%s", input);
              if(inputreturn < 0) {
                printf("\nError while reading the input\n");
              } else {
                char fileIn[100];
                char fileOut[104];
                char fileKey[108];
                char fileOutDecr[108];
                printf("\nEnter your file path: ");
                inputreturn = scanf("%s", fileIn);
                if(inputreturn < 0) {
                  printf("\nError while reading the input\n");
                } else {
                  strcpy(fileOut, fileIn);
                  strcat(fileOut, ".hfm");
                  strcpy(fileKey, fileOut);
                  strcat(fileKey, ".key");
                  strcpy(fileOutDecr, fileOut);
                  strcat(fileOutDecr, ".txt");
                  huffmanEncryptFile(fileIn, fileOut, fileKey);
                  huffmanDecryptFile(fileOut, fileOutDecr, fileKey);
                }
              }
          }
          printf("\n\n");
        }
      }
      if(again != 1) printf("\n# ==================================== #\n# ==================================== #\n\n");
    }
  }
  return EXIT_SUCCESS;
}


/* ================================================== */
/* ===================== PRIVATE ==================== */
/* ========================================================================== */


/**
 * @see @file huffman_exec.c / @function testStr
 */
void testStr(char *str) {
  hfm huffmanEncr = huffmanEncrypt(str);
  printf("# =============== TEST =============== #\n");
  printf("====== Text ======\n\n\"%s\"\n\n", str);
  if(huffmanEncr != NULL) {
    printf("=== Encryption ===\n\n\"%s\"\n\n", getHuffmanStr(huffmanEncr));
    char *decr = huffmanDecrypt(huffmanEncr);
    if(decr != NULL) {
      printf("=== Decryption ===\n\n\"%s\"\n\n", decr);
    } else {
      printf("==== Decryption failed ====\n");
    }
    free(decr);
  } else {
    printf("==== Encryption failed ====\n");
  }
  destroyHuffman(&huffmanEncr);
  printf("# =========== END OF TEST ============ #\n");
}

/**
 * @see @file huffman_exec.c / @function setFilesNames
 */
void setFilesNames(char *argv[], int argc, char **fileIn, char **fileOut, char **fileKey) {
  *(fileOut) = (char*)malloc(sizeof(char) * 101);
  *(fileKey) = (char*)malloc(sizeof(char) * 105);
  *(fileIn) = argv[2];
  if(!strcmp("encrypt", argv[1])) {
    if(argc >= 4) {
      strcpy(*(fileOut), argv[3]);
    } else {
      strcpy(*(fileOut), *(fileIn));
      strcat(*(fileOut), ".hfm");
    }
    if(argc >= 5) {
      strcpy(*(fileKey), argv[4]);
    } else {
      strcpy(*(fileKey), *(fileOut));
      strcat(*(fileKey), ".key");
    }
  } else if(!strcmp("decrypt", argv[1])) {
    if(argc >= 4) {
      strcpy(*(fileKey), argv[3]);
    } else {
      strcpy(*(fileKey), *(fileIn));
      strcat(*(fileKey), ".key");
    }
    if(argc >= 5) {
      strcpy(*(fileOut), argv[4]);
    } else {
      strcpy(*(fileOut), *(fileIn));
      strcat(*(fileOut), ".txt");
    }
  }
}


/* ========================================================================== */
/* ========================================================================== */
