#include "cronicas.h" 
#include "grimorio.h" 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

// Função para adicionar uma nova crônica à lista encadeada de crônicas.
// Esta é a função central para registrar uma nova partida.

void adicionarCronica(Cronica **lista, const char *nome, int movimentos,
                      int numDiscos, const char *dataHora) {
  
// Aloca dinamicamente memória para uma nova estrutura Cronica.

  Cronica *novo =
      malloc(sizeof(Cronica)); 
  if (!novo) {
    printf("Erro de memória: Não conseguimos registrar essa crônica agora. "
           "Faltou espaço!\\n");
    return;
  }
  
  // Copia os dados fornecidos para a nova crônica, com segurança.

  strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
  novo->nome[sizeof(novo->nome) - 1] = '\0'; 
  novo->movimentos = movimentos;
  novo->numDiscos = numDiscos;
  strncpy(novo->dataHora, dataHora, sizeof(novo->dataHora) - 1);
  novo->dataHora[sizeof(novo->dataHora) - 1] = '\0';
  novo->proximo = NULL; 

    // Adiciona o novo nó no INÍCIO da lista encadeada.

  novo->proximo = *lista;
  *lista = novo;
}

  // Função para exibir todas as crônicas registradas na lista.
  // Recebe o ponteiro inicial da lista de crônicas.

void exibirCronicas(Cronica *lista) {
  if (lista == NULL) {
    printf("\nO Pergaminho de Crônicas ainda está em branco. Nenhuma lenda "
           "registrada!\\n");
    return;
  }

  // Imprime um cabeçalho para a seção de crônicas, para melhor formatação.
  
  printf("\n=== Crônicas Antigas ===\n");
  Cronica *atual = lista; 
  while (atual != NULL) { 

  // Imprime os detalhes de cada crônica formatados.
  // %s para strings, %d para inteiros.
    
    printf("Aventureiro: %s | Feitos: %d movimentos | Discos: %d | Fim da "
           "Jornada: %s\n",
           atual->nome, atual->movimentos, atual->numDiscos, atual->dataHora);
    
  // Move para a próxima crônica na lista, avançando o ponteiro.
    
    atual = atual->proximo; 
  }
  printf("========================\n");
}

 // Função para salvar todas as crônicas da lista em um arquivo de texto.
 // Permite que o histórico seja mantido entre as execuções do programa.

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

  // Percorre a lista e escreve cada crônica no arquivo.
  
  Cronica *atual = lista;
  while (atual != NULL) {
    fprintf(arquivo, "%s,%d,%d,%s\\n", atual->nome, atual->movimentos,
            atual->numDiscos, atual->dataHora);
    atual = atual->proximo;
  }

  fclose(arquivo); 
}

// Função para carregar crônicas de um arquivo de texto para a lista encadeada.
// Recupera o histórico de partidas anteriores.

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

  // Usa strtok para dividir a linha em partes (tokens) usando a vírgula como delimitador.

    char *nomeStr = strtok(linha, ",");
    char *movimentosStr = strtok(NULL, ",");
    char *numDiscosStr = strtok(NULL, ",");
    char *dataHoraStr = strtok(NULL, "\\n"); 

    if (nomeStr && movimentosStr && numDiscosStr && dataHoraStr) {

    // Converte os strings de números para inteiros.

      int movimentos = atoi(movimentosStr);
      int numDiscos = atoi(numDiscosStr);

    // Adiciona a crônica lida do arquivo à lista.

      adicionarCronica(lista, nomeStr, movimentos, numDiscos, dataHoraStr);
    }
  }

  fclose(arquivo); 
  printf("Guardião: As lendas antigas foram carregadas do Pergaminho.\n");
}

// Função para liberar a memória alocada para todos os nós da lista de crônicas.
// ESSENCIAL para evitar vazamentos de memória em programas C.

void liberarCronicas(Cronica *lista) {
  Cronica *atual = lista;
  Cronica *proximo;
  while (atual != NULL) {
    proximo = atual->proximo;   // Salva o próximo antes de liberar o atual.
    free(atual);                // Libera a memória do nó atual.
    atual = proximo;            // Move para o próximo nó.
  }
  printf("Guardião: A memória das Crônicas foi purificada.\n");
}

// Função para buscar crônicas na lista por nome do aventureiro ou data/hora.
// Recebe o ponteiro inicial da lista de crônicas e o termo de busca (string).

void buscarCronicasPorNomeOuData(Cronica *lista, const char *termo) {
  if (lista == NULL) {
    printf("O Pergaminho de Crônicas está em branco. Nenhuma lenda para "
           "buscar!\\n");
    return;
  }

  printf("\n=== Buscando Crônicas por '%s' ===\n", termo);

    // Inicializa um contador para registrar quantas crônicas foram encontradas.

  int encontrados = 0;
  Cronica *atual = lista;

  while (atual != NULL) {

    if (strstr(atual->nome, termo) != NULL ||
        strstr(atual->dataHora, termo) != NULL) {

       // Se o termo de busca for encontrado em qualquer um dos campos (nome ou dataHora):
      // Imprime os detalhes completos da crônica encontrada.
      
      printf("Aventureiro: %s | Feitos: %d movimentos | Discos: %d | Fim da "
             "Jornada: %s\n",
             atual->nome, atual->movimentos, atual->numDiscos, atual->dataHora);
      encontrados++;
    }

        // Move para a próxima crônica na lista.

    atual = atual->proximo;
  }

  if (encontrados == 0) {
    printf("Nenhuma crônica encontrada com o termo '%s'.\n", termo);
  }
  printf("===================================\n");
}
