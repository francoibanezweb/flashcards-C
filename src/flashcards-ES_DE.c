/***************
| Ap.06, Ej.13 |
***************/
/* Programa de preguntas Español-Alemán */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

#define MAXWORDS 100

const char FOREIGN[] = "Alemán";

struct flshcard
{                   /* Estructura en la que se almacenan los datos de las */
  char Spanish[32]; /* preguntas */
  char FOREIGN[32];
  char spchPart;
  int errorFlg;
} spGe[MAXWORDS];

int retstFlg;

void initlze();
void testword(char lang1[], char lang2[], char pos);
void clearBuffer();

int main() /* menú principal */
{
  setlocale(LC_ALL, "C.UTF-8");

  char ch[2];
  char toAsk[9], toAnswer[9], whchWrds;

  initlze();
  retstFlg = 0;

  while (1 == 1) /* presentación en pantalla de menú */
  {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\tPreguntas de Vocabulario =2023= @francoibanezweb\n\n");
    printf("\n\n\t\t1 - Español a %s, nombres", FOREIGN);
    printf("\n\n\t\t2 - Español a %s, verbos", FOREIGN);
    printf("\n\n\t\t3 - Español a %s, otros", FOREIGN);
    printf("\n\n\t\t4 - Español a %s, todo", FOREIGN);
    printf("\n\n\t\t5 - %s a Español, nombres", FOREIGN);
    printf("\n\n\t\t6 - %s a Español, verbos", FOREIGN);
    printf("\n\n\t\t7 - %s a Español, otros", FOREIGN);
    printf("\n\n\t\t8 - %s a Español, todo", FOREIGN);

    if (retstFlg == 1)
    {
      printf("\n\n\t\t9 - Repetir errores de la última prueba");
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
    // captura la decisión del usuario y actualiza los parámetros apropiadamente
    if (ch[0] == '1' || ch[0] == '2' || ch[0] == '3' || ch[0] == '4')
    {
      strcpy(toAsk, "Español");
      strcpy(toAnswer, FOREIGN);
    }
    if (ch[0] == '5' || ch[0] == '6' || ch[0] == '7' || ch[0] == '8')
    {
      strcpy(toAsk, FOREIGN);
      strcpy(toAnswer, "Español");
    }
    if (ch[0] == '1' || ch[0] == '5')
    {
      whchWrds = 'N';
    }
    else if (ch[0] == '2' || ch[0] == '6')
    {
      whchWrds = 'V';
    }
    else if (ch[0] == '3' || ch[0] == '7')
    {
      whchWrds = 'O';
    }
    else if (ch[0] == '4' || ch[0] == '8')
    {
      whchWrds = 'A';
    }
    else if (ch[0] == '9' && retstFlg == 1)
    {
      whchWrds = 'R';
    }
    else if (ch[0] == '0')
    {
      break;
    }
    else
    {
      putchar(7);
      continue;
    }
    testword(toAsk, toAnswer, whchWrds);
  }
  return 0;
}

void initlze() /* lectura de una lista de palabras de disco */
{
  FILE *filePtr;

  if ((filePtr = fopen("../assets/german/descripcion-de-personas.txt",
                       "r")) == NULL)
  {
    printf("Error de Disco: no puede abrirse\n");
    printf("fichero de palabras");
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
}

void testword(char lang1[], char lang2[], char pos) /* preguntas al usuario */
{                                                   /* utilizando parámetros */
  int wrdCntr, ltrCntr;                             /* a los que se les han */
  char answer[16];                                  // asignado valores en main()
  char yorn[2];
  int retestFlg;

  wrdCntr = 0;
  if (pos != 'R') /* si no se van a repetir las preguntas erróneas, poner a 0 */
  {               /* las banderas de error para poder anotar los nuevos errores*/
    while (wrdCntr < MAXWORDS)
    {
      spGe[wrdCntr].errorFlg = 0;
      wrdCntr = wrdCntr + 1;
    }
  }
  wrdCntr = 0;
  while (wrdCntr < MAXWORDS)
  {
    if (pos != 'A' && pos != 'R' && pos != spGe[wrdCntr].spchPart)
    {
      wrdCntr = wrdCntr + 1;
      continue;
    }
    if (pos == 'R' && spGe[wrdCntr].errorFlg != 1)
    {
      wrdCntr = wrdCntr + 1;
      continue;
    }
    printf("\n\n\n\n\n\n\n");
    printf("\t\t   \033[4mTraducción del %s al %s\033[0m", lang1, lang2);
    printf("\n\n\t\t\t    \033[4mpreguntas sobre \033[0m");
    if (pos == 'N')
    { /* presentación en pantalla */
      printf("\033[4mnombres\033[0m");
    }
    else if (pos == 'V')
    {
      printf("\033[4mverbos\033[0m");
    }
    else if (pos == 'O')
    {
      printf("\033[4motros elementos gramaticales\033[0m");
    }
    else if (pos == 'A')
    {
      printf("\033[4mtodo tipo de elementos gramaticales\033[0m");
    }
    if (lang1[0] == 'A')
    {
      printf("\n\n\n\n\n\n\n\n\n");
      if (strncmp(spGe[wrdCntr].FOREIGN, "der", 3) == 0)
      {
        printf("\t\t\t\t\033[1;38;5;39m%s\033[0m\n", spGe[wrdCntr].FOREIGN);
      }
      else if (strncmp(spGe[wrdCntr].FOREIGN, "die", 3) == 0)
      {
        printf("\t\t\t\t\033[1;38;5;204m%s\033[0m\n", spGe[wrdCntr].FOREIGN);
      }
      else if (strncmp(spGe[wrdCntr].FOREIGN, "das", 3) == 0)
      {
        printf("\t\t\t\t\033[1;38;5;46m%s\033[0m\n", spGe[wrdCntr].FOREIGN);
      }
      else
      {
        printf("\033[1m\t\t\t\t%s\033[0m", spGe[wrdCntr].FOREIGN);
      }
      printf("\n\n\n\n\n\n\n\n");
      printf("¿Cuál es la traducción al Español? \033[1;93m(Doble Enter)\033[0m > ");

      fgets(answer, sizeof(answer), stdin); /* Obtención de la respuesta del  */
      answer[strcspn(answer, "\n")] = '\0'; /* usuario, paso a mayúsculas */
      clearBuffer();

      ltrCntr = 0;
      while (answer[ltrCntr] != '\0')
      {
        answer[ltrCntr] = toupper(answer[ltrCntr]);
        ltrCntr = ltrCntr + 1;
      }

      if (strcasecmp(answer, spGe[wrdCntr].Spanish) == 0)
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
        spGe[wrdCntr].errorFlg = 1;
        retstFlg = 1;
        printf("\033[1;91m\n\tLa respuesta correcta es \033[1;96m%s\033[1;91m.\033[0m",
               spGe[wrdCntr].Spanish);
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
      printf("\n\n\n\n\n\n\n\n\n");
      printf("\t\t\t\t\033[48;5;208;38;5;15m%s\033[0m", spGe[wrdCntr].Spanish);
      printf("\n\n\n\n\n\n\n\n");
      printf("¿Cuál es la traducción al %s? \033[1;93m(Doble Enter)\033[0m > ",
             FOREIGN);

      fgets(answer, sizeof(answer), stdin);
      answer[strcspn(answer, "\n")] = '\0';
      clearBuffer(); /* obtención de la respuesta del usuario, paso a mayús */

      ltrCntr = 0;
      while (answer[ltrCntr] != '\0')
      {
        answer[ltrCntr] = toupper(answer[ltrCntr]);
        ltrCntr = ltrCntr + 1;
      }

      if (strcmp(answer, spGe[wrdCntr].FOREIGN) == 0)
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
        spGe[wrdCntr].errorFlg = 1;
        retstFlg = 1;
        printf("\033[1;91m\n\tLa respuesta correcta es \033[1;96m%s\033[1;91m.\033[0m",
               spGe[wrdCntr].FOREIGN);
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

void clearBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
  {
  }
}
