
/***************
| Ap.06, Ej.12 |
***************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void clearBuffer();

int main()
{ /* enter vocabulary words into a disk file to be read by flashcard program */
  /* FINAL VERSION */

  FILE *filePtr;
  char Espanol[32];
  char Aleman[32];
  char spPrt[2];

  char again[2], confirm[2];
  int counter;

  filePtr = fopen("wordlist.txt", "a");
  if (filePtr == NULL)
  {
    printf("Error de disco: No se puede abrir el archivo ");
    printf("con la lista de palabras.");
    exit(1);
  }

  while (1 == 1)
  {
    strcpy(Espanol, "               "); /* blank out */
    strcpy(Aleman, "               ");  /* garbage */
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\tINGRESE LAS PALABRAS DEL VOCABULARIO");
    printf("\n\t\t\t-----------------------------------");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("Ingrese la palabra en español > ");
    fgets(Espanol, sizeof(Espanol), stdin);
    Espanol[strcspn(Espanol, "\n")] = '\0';
    clearBuffer();

    printf("\nIngrese la palabra en alemán > ");
    fgets(Aleman, sizeof(Aleman), stdin);
    Aleman[strcspn(Aleman, "\n")] = '\0';
    clearBuffer();

    while (1 == 1)
    {
      printf("\nIngrese el tipo de elemento gramatical");
      printf("\n\tN-nombre, V-verbo, O-otro > ");
      fgets(spPrt, sizeof(spPrt), stdin);
      spPrt[strcspn(spPrt, "\n")] = '\0';
      clearBuffer();

      spPrt[0] = toupper(spPrt[0]);
      if (spPrt[0] == 'N' || spPrt[0] == 'V' || spPrt[0] == 'O')
      {
        break;
      }
      else
      {
        putchar(7);
      }
    }
    printf("\n¿Desea guardar esta entrada? (S/N) > ");
    fgets(confirm, sizeof(confirm), stdin);
    confirm[strcspn(confirm, "\n")] = '\0';
    clearBuffer();

    if (toupper(confirm[0]) == 'S')
    {
      fprintf(filePtr, "%s %s %s\n", Espanol, Aleman, spPrt);
    }

    printf("\n¿Desea ingresar otra palabra? (S/N) > ");
    fgets(again, sizeof(again), stdin);
    again[strcspn(again, "\n")] = '\0';
    clearBuffer();

    if (toupper(again[0]) != 'S')
    {
      break;
    }
  }
  fclose(filePtr);

  return 0;
}

void clearBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
  {
  }
}