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
  strncpy(novo->nome, nome, sizeof(novo->nome));
  novo->movimentos = movimentos;
  novo->numDiscos = numDiscos;
  strncpy(novo->dataHora, dataHora, sizeof(novo->dataHora));
  novo->proximo = NULL;

  if (*lista == NULL) {
    *lista = novo;
  } else {
    Historico *atual = *lista;
    while (atual->proximo != NULL)
      atual = atual->proximo;
    atual->proximo = novo;
  }
}
