#ifndef CRONICAS_H
#define CRONICAS_H

typedef struct Cronica {
  char nome[50];                   // Nome do aventureiro (jogador).
  int movimentos;                // Número de movimentos realizados para resolver o desafio.
  int numDiscos;               // Número de discos usados no desafio.
  char dataHora[30];             // Data e hora de conclusão do desafio.
  struct Cronica *proximo;         // Ponteiro para o próximo nó na lista encadeada.

// Protótipos das funções para manipulação das crônicas (histórico de partidas).
// Estas funções são as "ações" que podem ser realizadas com as crônicas.
                         
} Cronica;

void adicionarCronica(Cronica **lista, const char *nome, int movimentos,
                      int numDiscos, const char *dataHora);

void exibirCronicas(Cronica *lista);

void salvarCronicasEmArquivo(Cronica *lista, const char *nomeArquivo);

void carregarCronicasDoArquivo(Cronica **lista, const char *nomeArquivo);

void liberarCronicas(Cronica *lista);

void buscarCronicasPorNomeOuData(Cronica *lista, const char *termo);

#endif
