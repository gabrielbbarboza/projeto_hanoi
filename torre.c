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
