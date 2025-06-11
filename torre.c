#include "torre.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DISC 999

typedef struct {
  int discos[MAX_DISC];
  int topo;
} Torre;

void inicializarTorres(Torre torres[3], int numDiscos) {
  for (int i = 0; i < 3; i++)
    torres[i].topo = -1;

  for (int i = numDiscos; i >= 1; i--)
    torres[0].discos[++torres[0].topo] = i;
}
void exibirTorres(Torre torres[3], int numDiscos) {
  printf("\nEstado atual:\n\n");
  for (int nivel = numDiscos - 1; nivel >= 0; nivel--) {
    for (int t = 0; t < 3; t++) {
      if (nivel <= torres[t].topo) {
        int disco = torres[t].discos[nivel];
        int tamanho = disco;
        int maxTamanho = numDiscos;
        int espacos = maxTamanho - tamanho;
        for (int i = 0; i < espacos; i++)
          printf(" ");
        for (int i = 0; i < tamanho; i++)
          printf("#");
        printf("0");
        for (int i = 0; i < tamanho; i++)
          printf("#");
        for (int i = 0; i < espacos; i++)
          printf(" ");
        printf("  ");
      } else {
        for (int i = 0; i < numDiscos; i++)
          printf(" ");
        printf("0");
        for (int i = 0; i < numDiscos; i++)
          printf(" ");
        printf("  ");
      }
    }
    printf("\n");
  }
  printf("\n");
  printf(" Torre 1         Torre 2         Torre 3\n\n");
}
