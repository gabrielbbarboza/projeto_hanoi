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
void exibirHistorico(Historico *lista) {
  if (lista == NULL) {
    printf("Nenhum histórico para exibir.\n");
    return;
  }

  printf("\n=== Histórico de Jogos ===\n");
  while (lista != NULL) {
    printf("Nome: %s | Movimentos: %d | Discos: %d | Data/Hora: %s\n",
           lista->nome, lista->movimentos, lista->numDiscos, lista->dataHora);
    lista = lista->proximo;
  }
  printf("\n");
}

void salvarEmArquivo(Historico *lista, const char *nomeArquivo) {
  FILE *arq = fopen(nomeArquivo, "w");
  if (!arq) {
    printf("Erro ao salvar histórico.\n");
    return;
  }
  while (lista != NULL) {
    fprintf(arq, "%s;%d;%d;%s\n", lista->nome, lista->movimentos,
            lista->numDiscos, lista->dataHora);
    lista = lista->proximo;
  }
  fclose(arq);
}
