/**
 * @file huffman_exec.c
 * @author Clément GUICHARD <clement.guichard1@etu.univ-orleans.fr>
 * @author Thàng long CAMA <thang-long.cama@etu.univ-orleans.fr>
 * @standard C99
 * @version 1.0
 * @date 11th October 2018
 *
 * @brief Main file
 *
 * This file is the main file that calls the functions created to do a huffman
 * coding.
 */

#include "huffman.h"

char* TESTS_V[4] = {
  "Hello World!",
  "J'ai perdu ma force et ma vie,\nEt mes amis et ma gaieté,\nJ'ai perdu jusqu'à la fierté\nQui faisait croire à mon génie.\n\nQuand j'ai connu la Vérité,\nJ'ai cru que c'était une amie ;\nQuand je l'ai comprise et sentie,\nJ'en étais déjà dégoûté.\n\nEt pourtant elle est éternelle,\nEt ceux qui se sont passés d'elle\nIci-bas ont tout ignoré.\n\nDieu parle, il faut qu'on lui réponde.\nLe seul bien qui me reste au monde\nEst d'avoir quelquefois pleuré.\nAlfred de Musset.",
  "This is a test to verify if the encryption and the decryption are correct",
  "TTT"
};
int TESTS_C = 4;

/* ================================================== */
/* ============== DEF PRIVATE FUNCTIONS ============= */
/* ========================================================================== */


/**
 * @function displayConsoleInterface
 * @brief Function used to display a terminal interface.
 *
 * @return{void}
 */
void displayConsoleInterface();

/**
 * @function testStr
 * @brief Function used to test a string of characters encryption and decryption.
 *
 * @param{char*} str: string of characters to test.
 *
 * @return{void}
 */
void testStr(char *str);

/**
 * @function emptyBuffer
 * @brief Function used to empty the buffer of stdin
 *
 * @return{void}
 */
void emptyBuffer();

/**
 * @function setFilesNames
 * @brief Function used to set the files names.
 *
 * @param{char**} argv: list of argument pass to the executable.
 * @param{int} argc: size of argv.
 * @param{char**} fileIn: pointer of the string of the input file.
 * @param{char**} fileOut: pointer of the string of the output file.
 * @param{char**} fileKey: pointer of the string of the file containing the
 *                         encryption key.
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
  } else if(argc == 2) {
    if (!strcmp("interface", argv[1]))
      displayConsoleInterface(); // Launch terminal interface
  } else {
    /*=================================================






                  You can place here the
                  tests you want to run
                       by default







    =================================================*/
    testStr(TESTS_V[0]); // example of test
  }
  return EXIT_SUCCESS;
}


/* ================================================== */
/* ===================== PRIVATE ==================== */
/* ========================================================================== */


/**
 * @see @file huffman_exec.c / @function testStr
 */
void displayConsoleInterface() {
  int again = 1;
  int inputreturn;
  char input[200];
  int choice = -1;
  while(again == 1) {
    printf("\n# ==================================== #\n# ============ TEST MENU ============= #\n# ==================================== #\n\n");
    printf("0. Quit\n");
    printf("1. Test a string of characters\n");
    printf("2. Test a file\n");
    printf("3. Start a predefined test\n");
    printf( "\nEnter your choice (ex: 0 for quit): ");
    inputreturn = scanf("%s", input);
    if(inputreturn < 0) {
      printf("\nError while reading the input\n");
    } else {
      choice = strToInt(input);
      if(choice < 0 || choice > 3) {
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
                printf("\nPlease enter the string to test: ");
                emptyBuffer();
                char *test = fgets(input, sizeof(input), stdin);
                if(test[strlen(test)-1] == '\n') test[strlen(test)-1] = '\0';
                testStr(test);
              } else {
                printf("\nProcess stopped");
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
              choice = strToInt(input);
              if(choice == 0) {
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
                  printf("\nTest started\n");
                  huffmanEncryptFile(fileIn, fileOut, fileKey);
                  huffmanDecryptFile(fileOut, fileOutDecr, fileKey);
                }
              } else {
                printf("\nProcess stopped");
              }
            }
            break;
          case 3:
            printf("\nYou choosed to use a predefined test\n");
            printf("Enter 0 to continue: ");
            inputreturn = scanf("%s", input);
            if(inputreturn < 0) {
              printf("\nError while reading the input\n");
            } else {
              choice = strToInt(input);
              if(choice == 0) {
                printf("\n\n");
                int again2 = 1;
                while(again2 == 1) {
                  printf("\nWhich test do you want to do (enter 0 to quit)?\n");
                  for (short int i = 0; i < TESTS_C; i++) printf("Test n°%d\n", i+1);
                  printf("Your choice: Test n°");
                  inputreturn = scanf("%s", input);
                  if(inputreturn < 0) {
                    printf("\nError while reading the input\n");
                  } else {
                    choice = strToInt(input);
                    if(choice <= 0) {
                      again2 = 0;
                      printf("\nRunning of predefined tests stopped");
                    } else {
                      if(choice > TESTS_C) {
                        printf("\nThis test does not exist\n\n");
                      } else {
                        testStr(TESTS_V[choice-1]);
                      }
                    }
                  }
                }
              } else {
                printf("\nProcess stopped");
              }
            }
        }
        printf("\n\n");
      }
    }
    if(again != 1) printf("\n# ==================================== #\n# ==================================== #\n\n");
  }
}

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
 * @see @file huffman_exec.c / @function emptyBuffer
 */
void emptyBuffer() {
  int c = 0;
  while (c != '\n' && c != EOF) c = getchar();
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
