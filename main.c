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
