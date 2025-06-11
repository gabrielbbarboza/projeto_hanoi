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
