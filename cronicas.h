#ifndef CRONICAS_H
#define CRONICAS_H

typedef struct Cronica {
  char nome[50];   
  int movimentos;     
  int numDiscos;           
  char dataHora[30];       
  struct Cronica *proximo;
                         
} Cronica;

void adicionarCronica(Cronica **lista, const char *nome, int movimentos,
                      int numDiscos, const char *dataHora);
void exibirCronicas(Cronica *lista);

void salvarCronicasEmArquivo(Cronica *lista, const char *nomeArquivo);

void carregarCronicasDoArquivo(Cronica **lista, const char *nomeArquivo);

void liberarCronicas(Cronica *lista);

void buscarCronicasPorNomeOuData(Cronica *lista, const char *termo);

#endif
