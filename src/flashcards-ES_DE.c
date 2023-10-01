/* Programa de preguntas Español-Alemán */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
#include "files-names.h"

#define MAXWORDS 200
#define TOTAL_TEMAS 66

struct UsedIndices
{
  int maxWords;  // Número máximo de palabras en la categoría
  int *indices;  // Array de índices utilizados
  int usedCount; // Contador de índices utilizados
};

struct UsedIndices usedIndices[4];

const char FOREIGN[][20] = {
    "Inglés",
    "Alemán"};

struct flshcard
{                   /* Estructura en la que se almacenan los datos de las */
  char Spanish[32]; /* preguntas */
  char FOREIGN[32];
  char spchPart;
  int errorFlg;
} spGe[MAXWORDS];

int retstFlg;

void initlze(int lang, int file, const char files_names[], struct flshcard spGe[], int counts[]);
void testword(char lang1[], char lang2[], char pos, char theme[], char wchWords, int counts[], int lang, struct UsedIndices usedIndices[]);
int generateRandomIndex(int maxIndex, int *usedIndices, int *usedCount);
void clearBuffer();

int main() /* menú principal */
{
  setlocale(LC_ALL, "C.UTF-8");

  srand(time(NULL));

  char ch[2];
  char toAsk[9], toAnswer[9], whchWrds;
  int keepGuessing;
  int counts[4] = {0};

  
  retstFlg = 0;

  keepGuessing = -1;


  while (keepGuessing != 0)
  {
    system("clear");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\tPreguntas sobre Vocabulario =2023= @francoibanezweb\n\n");
    printf("¿Qué idioma desea practicar? > ");
    printf("\n\n\t\t1 - Inglés");
    printf("\n\n\t\t2 - Alemán");
    printf("\n\n\t\t0 - Salir");
    printf("\n\n\t\tSeleccione una opción > ");

    scanf("%d", &keepGuessing);

    if (keepGuessing == 1 || keepGuessing == 2)
    {
      int startIndex = 0;
      int endIndex = 6; // Mostrar los primeros 6 temas

      while (startIndex < TOTAL_TEMAS)
      {
        system("clear");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("\n\t\tPreguntas sobre Vocabulario =2023= @francoibanezweb\n\n");
        printf("\nLos distintos temas a practicar:\n");

        for (int i = startIndex; i < endIndex && i < TOTAL_TEMAS; i++)
        {
          char truncatedFileName[256];
          strncpy(truncatedFileName, files_names[i], strlen(files_names[i]) - 4);
          truncatedFileName[strlen(files_names[i]) - 4] = '\0';

          // Reemplazar '-' por ' ' en la cadena
          for (int j = 0; truncatedFileName[j]; j++)
          {
            if (truncatedFileName[j] == '-')
            {
              truncatedFileName[j] = ' ';
            }
          }

          // Capitalizar la primera letra
          if (truncatedFileName[3])
          {
            truncatedFileName[3] = toupper(truncatedFileName[3]);
          }

          printf("\n\t\t%d - %s\n", i + 1, truncatedFileName + 3);
        }

        printf("\n\nSeleccione un archivo (1-%d) o ingrese 0", TOTAL_TEMAS);
        printf(" para mostrar los siguientes 6 temas: ");

        int selectedFile;
        scanf("%d", &selectedFile);
        clearBuffer();

        if (selectedFile == 0)
        {
          // Mostrar los siguientes 6 temas
          startIndex = endIndex;
          endIndex += 6;
        }
        else if (selectedFile >= 1 && selectedFile <= TOTAL_TEMAS)
        {
          // Aquí puedes realizar acciones con el archivo seleccionado,
          // por ejemplo, abrirlo o realizar alguna operación.
          // printf("Seleccionaste el archivo %d - %s\n", selectedFile,
          //        files_names[selectedFile - 1]);

          initlze(keepGuessing, selectedFile, files_names[selectedFile - 1], spGe, counts);

          printf("\n\n\n\n\n\n\n\n\n\n\n\n");
          printf("\n\t\tPreguntas de Vocabulario =2023= @francoibanezweb\n\n");
          printf("\n\n\t\t1 - Español a %s, sustantivos", FOREIGN[keepGuessing - 1]);
          printf("\n\n\t\t2 - Español a %s, verbos", FOREIGN[keepGuessing - 1]);
          printf("\n\n\t\t3 - Español a %s, adjetivos", FOREIGN[keepGuessing - 1]);
          printf("\n\n\t\t4 - Español a %s, otros", FOREIGN[keepGuessing - 1]);
          printf("\n\n\t\t5 - Español a %s, todo", FOREIGN[keepGuessing - 1]);
          printf("\n\n\t\t6 - %s a Español, sustantivos", FOREIGN[keepGuessing - 1]);
          printf("\n\n\t\t7 - %s a Español, verbos", FOREIGN[keepGuessing - 1]);
          printf("\n\n\t\t8 - %s a Español, adjetivos", FOREIGN[keepGuessing - 1]);
          printf("\n\n\t\t9 - %s a Español, otros", FOREIGN[keepGuessing - 1]);
          printf("\n\n\t\t10 - %s a Español, todo", FOREIGN[keepGuessing - 1]);

          if (retstFlg == 1)
          {
            printf("\n\n\t\t11 - Repetir errores de la última prueba");
          }

          printf("\n\n\t\t0 - Salir del Programa");

          if (retstFlg != 1)
          {
            printf("\n\n");
          }

          printf("\n\n\t\t\t¿Qué opción desea? > ");

          fgets(ch, sizeof(ch), stdin);
          ch[strcspn(ch, "\n")] = '\0';
          clearBuffer();

          int option = atoi(ch); // Convert the input to an integer

          switch (option)
          {
          case 1:
          case 2:
          case 3:
          case 4:
          case 5:
            strcpy(toAsk, "Español");
            strcpy(toAnswer, FOREIGN[keepGuessing - 1]);
            whchWrds = (option == 1 || option == 6) ? 'S' : (option == 2 || option == 7) ? 'V'
                                                        : (option == 3 || option == 8)   ? 'A'
                                                        : (option == 4 || option == 9)   ? 'O'
                                                                                         : 'T';
            break;
          case 6:
          case 7:
          case 8:
          case 9:
          case 10:
            strcpy(toAsk, FOREIGN[keepGuessing - 1]);
            strcpy(toAnswer, "Español");
            whchWrds = (option == 6 || option == 1) ? 'S' : (option == 7 || option == 2) ? 'V'
                                                        : (option == 8 || option == 3)   ? 'A'
                                                        : (option == 9 || option == 4)   ? 'O'
                                                                                         : 'T';
            break;
          case 11:
            if (retstFlg == 1)
            {
              whchWrds = 'R';
            }
            break;
          case 0:
            // Handle the case for '0' (Exit) if needed
            exit(0);
            break;
          default:
            whchWrds = ' '; // Set a default value or handle other cases
            break;
          }

          char theme[256];
          strcpy(theme, files_names[selectedFile - 1]);
          // Reemplazo '-' por ' ' en la cadena
          for (int j = 0; theme[j]; j++)
          {
            if (theme[j] == '-')
            {
              theme[j] = ' ';
            }
          }

          // Capitalizo la primera letra
          if (theme[3])
          {
            theme[3] = toupper(theme[3]);
          }
          // Elimino la extensión .txt
          size_t length = strlen(theme);
          if (length >= 4)
          {
            theme[length - 4] = '\0';
          };

          system("clear");

          testword(toAsk, toAnswer, whchWrds, theme, whchWrds, counts, keepGuessing, usedIndices);
        }
        else
        {
          printf("Opción no válida. Por favor, seleccione un número válido.\n");
        }
      }
    }
  }
}

void initlze(int lang, int file, const char files_names[], struct flshcard spGe[], int counts[])
/* lectura de una lista de palabras de disco */
{
  FILE *filePtr;
  char filePath[256]; // Define a buffer for the file path

  if (counts)
  {
    for (int i = 0; i < 4; i++)
    {
      counts[i] = 0;
    }
  }

  if (lang == 1)
  {
    snprintf(filePath, sizeof(filePath), "../assets/english/%s", files_names);
  }
  else if (lang == 2)
  {
    snprintf(filePath, sizeof(filePath), "../assets/german/%s", files_names);
  }

  if ((filePtr = fopen(filePath, "r")) == NULL)
  {
    // Handle file open error here
    printf("Error de Disco: no puede abrirse el fichero de palabras\n");
    exit(1);
  }

  int entrCntr = 0;
  char line[64];

  while (fgets(line, sizeof(line), filePtr) != NULL)
  {
    char Spanish[32];
    char German[32];
    char spchPart;

    if (sscanf(line, "%s %s %c", Spanish, German, &spchPart) == 3)
    {
      strcpy(spGe[entrCntr].Spanish, Spanish);
      strcpy(spGe[entrCntr].FOREIGN, German);
      spGe[entrCntr].spchPart = spchPart;

      // printf("Debug: Spanish: %s, German: %s, Part of Speech: %c\n",
      //        Spanish, German, spchPart);

      if (spchPart == 'S')
      {
        counts[0]++; // Incrementa el contador de sustantivos
      }
      else if (spchPart == 'V')
      {
        counts[1]++; // Incrementa el contador de adjetivos
      }
      else if (spchPart == 'A')
      {
        counts[2]++; // Incrementa el contador de otros elementos gramaticales
      }
      else if (spchPart == 'O')
      {
        counts[3]++; // Incrementa el contador de todo tipo de elementos gramaticales
      }

      entrCntr++;

      if (entrCntr >= MAXWORDS)
      {
        printf("ERROR: lista de palabras, demasiado larga.\n");
        printf("El programa solo utilizará, %d palabras.", MAXWORDS);
        printf("\n\tSi desea utilizar, todas las palabras");
        printf("\n\talmacenadas en el fichero, deberá modificar ");
        printf("\n\tpreviamente el programa.");
        break;
      }
    }
    else
    {
      printf("ADVERTENCIA: Formato de línea no válido en ");
      printf("el archivo de la lista de palabras: %s\n", line);
    }
  }

  fclose(filePtr);
};

void testword(char lang1[], char lang2[], char pos, char theme[], char whchWords, int counts[], int lang, struct UsedIndices usedIndices[])
/* preguntas al usuario */
{                       /* utilizando parámetros */
  int wrdCntr, ltrCntr; /* a los que se les han */
  char answer[64];      // asignado valores en main()
  char yorn[2];
  int retestFlg;
  int minIndex, maxIndex;
  int maxWords = 0;

  /* printf("whchWords: %c\n", whchWords);
  printf("counts[0]: %d\n", counts[0]);
  printf("counts[1]: %d\n", counts[1]);
  printf("counts[2]: %d\n", counts[2]);
  printf("counts[3]: %d\n", counts[3]); */

  // if (usedIndices == NULL)
  // {
  //   printf("Error: Unable to allocate memory for usedIndices\n");
  //   exit(1);
  // }

  int usedCount = 0;

  wrdCntr = 0;
  if (pos != 'R') /* si no se van a repetir las preguntas erróneas, poner a 0 */
  {               /* las banderas de error para poder anotar los nuevos errores*/
    while (wrdCntr < maxWords)
    {
      spGe[wrdCntr].errorFlg = 0;
      wrdCntr = wrdCntr + 1;
    }
  }
  wrdCntr = 0;

   for (int i = 0; i < 4; i++)
  {
    usedIndices[i].maxWords = counts[i];
    usedIndices[i].indices = (int *)malloc(usedIndices[i].maxWords * sizeof(int));
    usedIndices[i].usedCount = 0;
  }

  // Determine the minimum and maximum indices based on whchWords
  minIndex = 0;
  // int *usedIndices = NULL;

  if (whchWords == 'S')
  {
    maxWords = counts[0]; // Sustantivos
  }
  else if (whchWords == 'V')
  {
    maxWords = counts[1]; // Verbos
  }
  else if (whchWords == 'A')
  {
    maxWords = counts[2]; // Adjetivos
  }
  else if (whchWords == 'O')
  {
    maxWords = counts[3]; // Otros
  }
  else if (whchWords == 'T')
  {
    maxWords = sizeof(spGe) / sizeof(spGe[0]);
    usedIndices->maxWords = maxWords; // Todo
  }

  printf("maxWords: %d\n", maxWords);

  int intWhchWord;
  switch (whchWords)
  {
  case 'S':
    intWhchWord = 0; // Sustantivos
    break;
  case 'V':
    intWhchWord = 1; // Verbos
    break;
  case 'A':
    intWhchWord = 2; // Adjetivos
    break;
  case 'O':
    intWhchWord = 3; // Otros
    break;
  default:
    // Manejar caso de carácter no válido
    intWhchWord = -1; // O algún valor que indique un error
    break;
  }

  while (wrdCntr < maxWords && usedCount < maxWords)
  {

    printf("Before generateRandomIndex - usedIndices: ");
    for (int i = 0; i < usedIndices[intWhchWord].maxWords; i++)
    {
      printf("%d ", usedIndices[intWhchWord].indices[i]);
    }
    printf("\n");

    int randomIndex = generateRandomIndex(usedIndices[intWhchWord].maxWords, usedIndices[intWhchWord].indices, &usedIndices[intWhchWord].usedCount);

    {
      if (pos != 'T' && pos != 'R' && pos != spGe[randomIndex].spchPart)
      {
        wrdCntr = wrdCntr + 1;
        continue;
      }
      if (pos == 'R' && spGe[randomIndex].errorFlg != 1)
      {
        wrdCntr = wrdCntr + 1;
        continue;
      }
      printf("\n\n\n\n\n\n\n");
      printf("\t\t   \033[4mTraducción del %s al %s\033[0m\n", lang1, lang2);
      printf("\t\t   \033[4m%s\033[0m\n", theme + 3);
      printf("\n\n\t\t\t    \033[4mpreguntas sobre \033[0m");
      if (pos == 'S')
      { /* presentación en pantalla */
        printf("\033[4msustantivos\033[0m");
      }
      else if (pos == 'V')
      {
        printf("\033[4mverbos\033[0m");
      }
      else if (pos == 'A')
      {
        printf("\033[4madjetivos\033[0m");
      }
      else if (pos == 'O')
      {
        printf("\033[4motros elementos gramaticales\033[0m");
      }
      else if (pos == 'T')
      {
        printf("\033[4mtodo tipo de elementos gramaticales\033[0m");
      }
      if (lang1[0] == 'A')
      {

        for (int i = 0; spGe[randomIndex].FOREIGN[i]; i++)
        {
          if (spGe[randomIndex].FOREIGN[i] == '_')
          {
            spGe[randomIndex].FOREIGN[i] = ' ';
          }
        }

        printf("\n\n\n\n\n\n\n\n\n");
        if (strncmp(spGe[randomIndex].FOREIGN, "der", 3) == 0)
        {
          printf("\t\t\t\t\033[1;38;5;39m%s\033[0m\n", spGe[randomIndex].FOREIGN);
        }
        else if (strncmp(spGe[randomIndex].FOREIGN, "die", 3) == 0)
        {
          printf("\t\t\t\t\033[1;38;5;204m%s\033[0m\n", spGe[randomIndex].FOREIGN);
        }
        else if (strncmp(spGe[randomIndex].FOREIGN, "das", 3) == 0)
        {
          printf("\t\t\t\t\033[1;38;5;46m%s\033[0m\n", spGe[randomIndex].FOREIGN);
        }
        else
        {
          printf("\033[1m\t\t\t\t%s\033[0m", spGe[randomIndex].FOREIGN);
        }
        printf("\n\n\n\n\n\n\n\n");
        printf("¿Cuál es la traducción al Español? \033[1;93m(Doble Enter)\033[0m > ");

        fgets(answer, sizeof(answer), stdin); /* Obtención de la respuesta del  */
        answer[strcspn(answer, "\n")] = '\0'; /* usuario*/
        clearBuffer();

        for (int i = 0; answer[i]; i++)
        {
          if (answer[i] == '_')
          {
            answer[i] = ' ';
          }
        }

        for (int i = 0; spGe[randomIndex].Spanish[i]; i++)
        {
          if (spGe[randomIndex].Spanish[i] == '_')
          {
            spGe[randomIndex].Spanish[i] = ' ';
          }
        }

        if (strcasecmp(answer, spGe[randomIndex].Spanish) == 0)
        {
          printf("\033[1;32m%s\033[0m", "\n\nFelicitaciones. Respuesta correcta.");
          printf("\n¿Desea intentarlo de nuevo? (\033[1;32mS\033[0m/\033[1;91mN\033[0m) > ");

          fgets(yorn, sizeof(yorn), stdin);
          yorn[strcspn(yorn, "\n")] = '\0';
          clearBuffer();

          if (toupper(yorn[0]) == 'N')
          {
            return;
          }
        }
        else /* mensaje para respuesta correcta o errónea */
        {
          spGe[randomIndex].errorFlg = 1;
          retstFlg = 1;
          printf("\033[1;91m\n\tLa respuesta correcta es \033[1;96m%s\033[1;91m.\033[0m",
                 spGe[randomIndex].Spanish);
          printf("\n¿Desea intentarlo de nuevo? (\033[1;32mS\033[0m/\033[1;91mN\033[0m) > ");

          fgets(yorn, sizeof(yorn), stdin);
          yorn[strcspn(yorn, "\n")] = '\0';
          clearBuffer();

          if (toupper(yorn[0]) == 'N')
          {
            return;
          }
        }
        wrdCntr = wrdCntr + 1;
      }
      else /* Español-Alemán */
      {

        for (int i = 0; spGe[randomIndex].Spanish[i]; i++)
        {
          if (spGe[randomIndex].Spanish[i] == '_')
          {
            spGe[randomIndex].Spanish[i] = ' ';
          }
        }

        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\033[48;5;208;38;5;15m%s\033[0m", spGe[randomIndex].Spanish);
        printf("\n\n\n\n\n\n\n\n");
        printf("¿Cuál es la traducción al %s? \033[1;93m(Doble Enter)\033[0m > ",
               FOREIGN[lang - 1]);

        fgets(answer, sizeof(answer), stdin);
        answer[strcspn(answer, "\n")] = '\0';
        clearBuffer(); /* obtención de la respuesta del usuario, paso a mayús */

        for (int i = 0; answer[i]; i++)
        {
          if (answer[i] == '_')
          {
            answer[i] = ' ';
          }
        }

        for (int i = 0; spGe[randomIndex].FOREIGN[i]; i++)
        {
          if (spGe[randomIndex].FOREIGN[i] == '_')
          {
            spGe[randomIndex].FOREIGN[i] = ' ';
          }
        }

        if (strcmp(answer, spGe[randomIndex].FOREIGN) == 0)
        {
          printf("\033[1;32m%s\033[0m", "\n\nFelicitaciones. Respuesta correcta.");
          printf("\n¿Desea intentarlo de nuevo? (\033[1;32mS\033[0m/\033[1;91mN\033[0m) > ");

          fgets(yorn, sizeof(yorn), stdin);
          yorn[strcspn(yorn, "\n")] = '\0';
          clearBuffer();

          if (toupper(yorn[0]) == 'N')
          {
            return;
          }
        } /* mensaje para respuesta correcta o errónea */
        else
        {
          spGe[randomIndex].errorFlg = 1;
          retstFlg = 1;
          printf("\033[1;91m\n\tLa respuesta correcta es \033[1;96m%s\033[1;91m.\033[0m",
                 spGe[randomIndex].FOREIGN);
          printf("\n¿Desea intentarlo de nuevo? (\033[1;32mS\033[0m/\033[1;91mN\033[0m) > ");

          fgets(yorn, sizeof(yorn), stdin);
          yorn[strcspn(yorn, "\n")] = '\0';
          clearBuffer();

          if (toupper(yorn[0]) == 'N')
          {
            return;
          }
        }
        wrdCntr = wrdCntr + 1;
      }
    }
  }
}

int generateRandomIndex(int maxIndex, int *usedIndices, int *usedCount)
{
  printf("Debug: maxIndex = %d, usedCount = %d\n", maxIndex, *usedCount);

  int randomIndex;
  do
  {
    randomIndex = rand() % maxIndex;
    printf("Random Index: %d, usedIndices[%d]: %d\n", randomIndex, randomIndex, usedIndices[randomIndex]);
  } while (*usedCount > 0 && usedIndices[randomIndex] == 1);

  usedIndices[randomIndex] = 1;
  (*usedCount)++; // Increment usedCount through the pointer
  return randomIndex;
}

void clearBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
  {
  }
}
