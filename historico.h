#ifndef HISTORICO_H
#define HISTORICO_H

typedef struct Historico {
  char nome[50];
  int movimentos;
  int numDiscos;
  char dataHora[30];
 struct Historico *proximo;
} Historico;

void adicionarHistorico(Historico **lista, const char *nome, int movimentos,
                        int numDiscos, const char *dataHora);

void exibirHistorico(Historico *lista);

void salvarEmArquivo(Historico *lista, const char *nomeArquivo);

void carregarDoArquivo(Historico **lista, const char *nomeArquivo);

void liberarHistorico(Historico *lista);
void buscarPorNomeOuData(Historico *lista, const char *termo);

#endif
