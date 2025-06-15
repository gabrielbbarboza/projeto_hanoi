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

void carregarDoArquivo(Historico **lista, const char *nomeArquivo) {
  FILE *arq = fopen(nomeArquivo, "r");
  if (!arq)
    return;

  char linha[150];
  while (fgets(linha, sizeof(linha), arq)) {
    char nome[50], dataHora[30];
    int movimentos, numDiscos;

    char *token = strtok(linha, ";");
    if (!token)
      continue;
    strncpy(nome, token, sizeof(nome));

    token = strtok(NULL, ";");
    if (!token)
      continue;
    movimentos = atoi(token);

    token = strtok(NULL, ";");
    if (!token)
      continue;
    numDiscos = atoi(token);

    token = strtok(NULL, ";\n");
    if (!token)
      continue;
    strncpy(dataHora, token, sizeof(dataHora));

    adicionarHistorico(lista, nome, movimentos, numDiscos, dataHora);
  }

  fclose(arq);
}
