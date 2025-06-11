#include "historico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adicionarHistorico(Historico **lista, const char *nome, int movimentos,
                        int numDiscos, const char *dataHora) {
  Historico *novo = malloc(sizeof(Historico));
  if (!novo) {
    printf("Erro de memória.\n");
    return;
  }
