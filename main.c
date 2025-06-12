#include "historico.h"
#include "torre.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Aproveitei a função lerInt que já tem na torre.c pra manter tudo consistente (declarei como extern)
extern int lerInt(const char *prompt, int min, int max, int cancelarPartida);

int main() {
  Historico *lista = NULL;

  carregarDoArquivo(&lista, "historico.txt");

  int opcao;

  while (1) {
    printf("\n=== Menu Principal ===\n");
    printf("1. Jogar\n");
    printf("2. Ver histórico\n");
    printf("3. Buscar por nome ou data\n");
    printf("4. Sair\n");
    printf("Escolha uma opção: ");

    opcao = lerInt("", 1, 4, 0);
