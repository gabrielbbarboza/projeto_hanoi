#include "torre.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DISC 999

typedef struct {
  int discos[MAX_DISC];
  int topo;
} Torre;

void inicializarTorres(Torre torres[3], int numDiscos) {
  for (int i = 0; i < 3; i++)
    torres[i].topo = -1;

  for (int i = numDiscos; i >= 1; i--)
    torres[0].discos[++torres[0].topo] = i;
}
void exibirTorres(Torre torres[3], int numDiscos) {
  printf("\nEstado atual:\n\n");
  for (int nivel = numDiscos - 1; nivel >= 0; nivel--) {
    for (int t = 0; t < 3; t++) {
      if (nivel <= torres[t].topo) {
        int disco = torres[t].discos[nivel];
        int tamanho = disco;
        int maxTamanho = numDiscos;
        int espacos = maxTamanho - tamanho;
        for (int i = 0; i < espacos; i++)
          printf(" ");
        for (int i = 0; i < tamanho; i++)
          printf("#");
        printf("0");
        for (int i = 0; i < tamanho; i++)
          printf("#");
        for (int i = 0; i < espacos; i++)
          printf(" ");
        printf("  ");
      } else {
        for (int i = 0; i < numDiscos; i++)
          printf(" ");
        printf("0");
        for (int i = 0; i < numDiscos; i++)
          printf(" ");
        printf("  ");
      }
    }
    printf("\n");
  }
  printf("\n");
  printf(" Torre 1         Torre 2         Torre 3\n\n");
}
int moverDisco(Torre torres[3], int origem, int destino) {
  origem--;
  destino--;
  if (origem < 0 || origem > 2 || destino < 0 || destino > 2)
    return 0;

  if (torres[origem].topo == -1) // torre origem vazia
    return 0;

  int disco = torres[origem].discos[torres[origem].topo];
  if (torres[destino].topo != -1 &&
      torres[destino].discos[torres[destino].topo] < disco)
    return 0; 

torres[destino].discos[++torres[destino].topo] = disco;
  torres[origem].topo--;
  return 1;
}
int jogoFinalizado(Torre torres[3], int numDiscos) {
  return torres[2].topo == numDiscos - 1;
}
void limparBufferStdin() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}
int lerInt(const char *prompt, int min, int max, int cancelarPartida) {
  int valor;
  char linha[100];
  while (1) {
    printf("%s", prompt);
    if (!fgets(linha, sizeof(linha), stdin)) {
      printf("Erro na leitura. Tente novamente.\n");
      continue;
    }
    if (linha[0] == '\n')
      continue;

    if (sscanf(linha, "%d", &valor) != 1) {
      printf("Entrada inválida. Digite um número.\n");
      continue;
    }
    if ((valor == 0 && cancelarPartida) || (valor >= min && valor <= max)) {
      return valor;
    }
    printf("Número fora do intervalo (%d a %d)%s.\n", min, max,
      cancelarPartida ? " ou zero para sair" : "");
  }
}
void executarPartida(Historico **lista) {
  Torre torres[3];
  char nome[50];
  int numDiscos, movimentos = 0;
  char dataHora[30];

  printf("Digite seu nome: ");
  if (!fgets(nome, sizeof(nome), stdin)) {
    printf("Erro na leitura do nome.\n");
    return;
  }
  nome[strcspn(nome, "\n")] = 0;
numDiscos = lerInt("Digite o número de discos (1 a 999): ", 1, 999, 0);

  inicializarTorres(torres, numDiscos);

  printf("\n=== Início do Jogo ===\n");
  exibirTorres(torres, numDiscos);
  printf("Regras:\n");
  printf("- Mova apenas um disco por vez.\n");
  printf("- Disco maior não pode ficar sobre disco menor.\n");
  printf("- Digite 0 para origem ou destino para voltar ao menu.\n\n");

  while (1) {
    int origem = lerInt("Digite a origem (1-3) ou 0 para menu: ", 0, 3, 1);
    if (origem == 0) {
      printf("Voltando ao menu principal...\n");
      break;
    }

    int destino = lerInt("Digite o destino (1-3) ou 0 para menu: ", 0, 3, 1);
    if (destino == 0) {
      printf("Voltando ao menu principal...\n");
      break;
    }

    if (moverDisco(torres, origem, destino)) {
      movimentos++;
      exibirTorres(torres, numDiscos);

      if (jogoFinalizado(torres, numDiscos)) {
        printf("Parabéns, %s! Você completou o jogo em %d movimentos.\n", nome,
               movimentos);
        obterDataHoraAtual(dataHora);
        adicionarHistorico(lista, nome, movimentos, numDiscos, dataHora);
        salvarEmArquivo(*lista, "historico.txt");
        break;
      }
    } else {
      printf("Movimento inválido! Tente novamente.\n");
    }
  }
}
