/***************
| Ap.06, Ej.13 |
***************/
                        /* Programa de preguntas Español-Alemán */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXWORDS 100

const char FOREIGN[] = "Alemán";

struct flshcard
{                     /* Estructura en la que se almacenan los datos de las */
  char Spanish[16];   /* preguntas */
  char FOREIGN[16]; 
  char spchPart;
  int errorFlg;
} spGe[MAXWORDS];

int retstFlg;

void initlze();
void testword(char lang1[], char lang2[], char pos);
void clearBuffer();

int main()            /* menú principal */
{
  char ch[2];
  char toAsk[9], toAnswer[9], whchWrds;

  initlze();
  retstFlg = 0;

  while (1 == 1)      /* presentación en pantalla de menú */
  {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n\t\tPreguntas de Vocabulario =2023= @francoibanezweb\n\n");
    printf("\n\n\t\t1 - Español a %s, nombres",FOREIGN);
    printf("\n\n\t\t2 - Español a %s, verbos",FOREIGN);
    printf("\n\n\t\t3 - Español a %s, otros",FOREIGN);
    printf("\n\n\t\t4 - Español a %s, todo",FOREIGN);
    printf("\n\n\t\t5 - %s a Español, nombres",FOREIGN);
    printf("\n\n\t\t6 - %s a Español, verbos",FOREIGN);
    printf("\n\n\t\t7 - %s a Español, otros",FOREIGN);
    printf("\n\n\t\t8 - %s a Español, todo",FOREIGN);

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
    clearBuffer(); /* get user's choice and set parameters accordingly */

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

void initlze()        /* lectura de una lista de palabras de disco */
{
  FILE *filePtr;

  if ((filePtr = fopen("/home/franco/programacion/aprendoC/build/wordlist.txt",
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
    char Spanish[16];
    char German[16];
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
        printf("El programa solo utilizará, %d palabras.",MAXWORDS);
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
{                                                  /* utilizando parámetros */
  int wrdCntr, ltrCntr;                            /* a los que se les han */
  char answer[16];                              /* asignado valores en main() */
  char yorn[2];
  int retestFlg;

  wrdCntr = 0;
  if (pos != 'R') /* si no se van a repetir las preguntas erróneas, poner a 0 */
  {              /* las banderas de error para poder anotar los nuevos errores*/
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
    printf("\t\t   Traducción de %s a %s", lang1, lang2);
    printf("\n\n\t\t\t    preguntas de ");
    if (pos == 'N')
    { /* presentación en pantalla */
      printf("nombres");
    }
    else if (pos == 'V')
    {
      printf("verbos");
    }
    else if (pos == 'O')
    {
      printf("otros elementos gramaticales");
    }
    else if (pos == 'A')
    {
      printf("todo tipo de elementos gramaticales");
    }
    if (lang1[0] == 'A')
    {
      printf("\n\n\n\n\n\n\n\n\n");
      printf("\t\t\t\t%s", spGe[wrdCntr].FOREIGN);
      printf("\n\n\n\n\n\n\n\n");
      printf("¿Cuál es la traducción al Español? (doble Enter) > ");

      fgets(answer, sizeof(answer), stdin); /* Obtención de la respuesta del  */
      answer[strcspn(answer, "\n")] = '\0'; /* usuario, paso a mayúsculas */
      clearBuffer(); 

      ltrCntr = 0;
      while (answer[ltrCntr] != '\0')
      {
        answer[ltrCntr] = toupper(answer[ltrCntr]);
        ltrCntr = ltrCntr + 1;
      }

      if (strcmp(answer, spGe[wrdCntr].Spanish) == 0)
      {                                            
        printf("\n\nFelicitaciones. Respuesta correcta.");
        printf("\n¿Desea intentarlo de nuevo? (S/N) > ");

        fgets(yorn, sizeof(yorn), stdin);
        yorn[strcspn(yorn, "\n")] = '\0';
        clearBuffer();

        if (toupper(yorn[0]) == 'N')
        {
          return;
        }
      }
      else   /* mensaje para respuesta correcta o errónea */
      {
        spGe[wrdCntr].errorFlg = 1;
        retstFlg = 1;
        printf("\n\tLa respuesta correcta es %s.", spGe[wrdCntr].Spanish);
        printf("\n¿Desea intentarlo de nuevo? (S/N) > ");

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
      printf("\t\t\t\t%s", spGe[wrdCntr].Spanish);
      printf("\n\n\n\n\n\n\n\n");
      printf("¿Cuál es la traducción al %s? (doble Enter) > ",FOREIGN);

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
        printf("\n\nFelicitaciones. Respuesta correcta.");
        printf("\n¿Desea intentarlo de nuevo? (S/N) > ");

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
        printf("\n\nLa respuesta correcta es %s.", spGe[wrdCntr].FOREIGN);
        printf("\n¿Desea intentarlo de nuevo? (S/N) > ");

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
