#include "cronicas.h" 
#include "grimorio.h" 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

void adicionarCronica(Cronica **lista, const char *nome, int movimentos,
                      int numDiscos, const char *dataHora) {
  Cronica *novo =
      malloc(sizeof(Cronica)); 
  if (!novo) {
    printf("Erro de memória: Não conseguimos registrar essa crônica agora. "
           "Faltou espaço!\\n");
    return;
  }

  strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
  novo->nome[sizeof(novo->nome) - 1] = '\0'; 

  novo->movimentos = movimentos;
  novo->numDiscos = numDiscos;

  strncpy(novo->dataHora, dataHora, sizeof(novo->dataHora) - 1);
  novo->dataHora[sizeof(novo->dataHora) - 1] = '\0';
  novo->proximo = NULL; 
  novo->proximo = *lista;
  *lista = novo;
}

void exibirCronicas(Cronica *lista) {
  if (lista == NULL) {
    printf("\nO Pergaminho de Crônicas ainda está em branco. Nenhuma lenda "
           "registrada!\\n");
    return;
  }

  printf("\n=== Crônicas Antigas ===\n");
  Cronica *atual = lista; 
  while (atual != NULL) { 
    printf("Aventureiro: %s | Feitos: %d movimentos | Discos: %d | Fim da "
           "Jornada: %s\n",
           atual->nome, atual->movimentos, atual->numDiscos, atual->dataHora);
    atual = atual->proximo; 
  }
  printf("========================\n");
}

void salvarCronicasEmArquivo(Cronica *lista, const char *nomeArquivo) {
  FILE *arquivo =
      fopen(nomeArquivo,
            "w");
  if (!arquivo) {
    printf(
        "Guardião: Não foi possível selar as Crônicas no Pergaminho! Erro ao "
        "abrir o arquivo.\n");
    return;
  }

  Cronica *atual = lista;
  while (atual != NULL) {
    fprintf(arquivo, "%s,%d,%d,%s\\n", atual->nome, atual->movimentos,
            atual->numDiscos, atual->dataHora);
    atual = atual->proximo;
  }

  fclose(arquivo); 
}

void carregarCronicasDoArquivo(Cronica **lista, const char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "r"); 
  if (!arquivo) {
    printf("Guardião: O Pergaminho Antigo está lacrado ou vazio. Começando "
           "um novo legado...\n");
    *lista = NULL; 
    return;
  }

  char linha[256]; 
  while (fgets(linha, sizeof(linha), arquivo) != NULL) {

    char *nomeStr = strtok(linha, ",");
    char *movimentosStr = strtok(NULL, ",");
    char *numDiscosStr = strtok(NULL, ",");
    char *dataHoraStr = strtok(NULL, "\\n"); 

    if (nomeStr && movimentosStr && numDiscosStr && dataHoraStr) {
      int movimentos = atoi(movimentosStr);
      int numDiscos = atoi(numDiscosStr);

      adicionarCronica(lista, nomeStr, movimentos, numDiscos, dataHoraStr);
    }
  }

  fclose(arquivo); 
  printf("Guardião: As lendas antigas foram carregadas do Pergaminho.\n");
}

void liberarCronicas(Cronica *lista) {
  Cronica *atual = lista;
  Cronica *proximo;
  while (atual != NULL) {
    proximo = atual->proximo;
    free(atual);         
    atual = proximo;        
  }
  printf("Guardião: A memória das Crônicas foi purificada.\n");
}

void buscarCronicasPorNomeOuData(Cronica *lista, const char *termo) {
  if (lista == NULL) {
    printf("O Pergaminho de Crônicas está em branco. Nenhuma lenda para "
           "buscar!\\n");
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
