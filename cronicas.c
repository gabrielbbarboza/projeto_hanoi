#include "cronicas.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <time.h> 

void adicionarCronica(Cronica **lista, const char *nome, int movimentos,
                      int numDiscos, const char *dataHora) {
  Cronica *novo =
      malloc(sizeof(Cronica)); 
  if (!novo) {
    printf("Erro de memória: Não conseguimos registrar essa crônica agora. "
           "Faltou espaço!\n");
    return;
  }

  strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
  novo->nome[sizeof(novo->nome) - 1] = '\0'; 

  novo->movimentos = movimentos;
  novo->numDiscos = numDiscos;

  strncpy(novo->dataHora, dataHora, sizeof(novo->dataHora) - 1);
  novo->dataHora[sizeof(novo->dataHora) - 1] = '\0';

  novo->proximo =
      NULL; 

  if (*lista == NULL) {
    *lista = novo;
  } else {
    Cronica *atual = *lista;
    while (atual->proximo != NULL)
      atual = atual->proximo;
    atual->proximo = novo;
  }
}

void exibirCronicas(Cronica *lista) {
  if (lista == NULL) {
    printf("Nosso pergaminho de crônicas está vazio. Nenhuma aventura "
           "registrada ainda!\n");
    return;
  }

  printf("\n=== Livro de Crônicas Antigas ===\n");
  
  while (lista != NULL) {
    printf("Aventureiro: %s | Feitos: %d movimentos | Discos: %d | Fim da "
           "Jornada: %s\n",
           lista->nome, lista->movimentos, lista->numDiscos, lista->dataHora);
    lista = lista->proximo;
  }
  printf("===================================\n");
}

void salvarCronicasEmArquivo(Cronica *lista, const char *nomeArquivo) {
  FILE *arq =
      fopen(nomeArquivo, "w");
  if (!arq) {
    printf("Erro: Não conseguimos abrir o pergaminho '%s' para escrever as "
           "crônicas.\n",
           nomeArquivo);
    return;
  }

  while (lista != NULL) {
    fprintf(arq, "%s;%d;%d;%s\n", lista->nome, lista->movimentos,
            lista->numDiscos, lista->dataHora);
    lista = lista->proximo;
  }

  fclose(arq);
}

void carregarCronicasDoArquivo(Cronica **lista, const char *nomeArquivo) {
  FILE *arq =
      fopen(nomeArquivo, "r"); 
  if (!arq) {

    return;
  }

  char linha[150]; /
  while (fgets(linha, sizeof(linha), arq)) { 
    linha[strcspn(linha, "\n")] = '\0';

    char nome[50];
    char dataHora[30];
    int movimentos, numDiscos;

    char *token = strtok(linha, ";");
    if (!token) {
      nome[0] = '\0';
    } else {
      strncpy(nome, token, sizeof(nome) - 1);
      nome[sizeof(nome) - 1] = '\0';
    }

    token = strtok(NULL, ";");
    if (!token)
      continue;
    movimentos = atoi(token);

    token = strtok(NULL, ";");
    if (!token)
      continue;
    numDiscos = atoi(token);

    token = strtok(NULL, ";");
    if (!token)
      continue;
    strncpy(dataHora, token, sizeof(dataHora) - 1);
    dataHora[sizeof(dataHora) - 1] = '\0';

    adicionarCronica(lista, nome, movimentos, numDiscos, dataHora);
  }

  fclose(arq); 
}

void liberarCronicas(Cronica *lista) {
  while (lista) {
    Cronica *aux = lista;
    lista = lista->proximo;
    free(aux); 
  }
}

void buscarCronicasPorNomeOuData(Cronica *lista, const char *termo) {
  if (lista == NULL) {
    printf("Nosso pergaminho de crônicas está vazio. Não há o que buscar.\n");
    return;
  }

  printf("\n=== Buscando Crônicas por '%s' ===\n", termo);
  int encontrados = 0;
  Cronica *atual = lista;

  while (atual != NULL) {
    if (strstr(atual->nome, termo) != NULL ||
        strstr(atual->dataHora, termo) != NULL) {
      printf("Aventureiro: %s | Feitos: %d movimentos | Discos: %d | Fim da "
             "Jornada: %s\n",
             atual->nome, atual->movimentos, atual->numDiscos, atual->dataHora);
      encontrados++;
    }
    atual = atual->proximo;
  }

  if (encontrados == 0) {
    printf("Nenhuma crônica encontrada com o termo '%s'.\n", termo);
  }
  printf("===================================\n");
}

void obterDataHoraAtual(char *buffer) {
  time_t t = time(NULL);         
  struct tm tm = *localtime(&t); 

  snprintf(buffer, 30, "%02d/%02d/%04d %02d:%02d", tm.tm_mday, tm.tm_mon + 1,
           tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
}
