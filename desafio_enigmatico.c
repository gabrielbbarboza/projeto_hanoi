#include "desafio_enigmatico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DISC_ENIGMA 10

typedef struct {
  int artefatos[MAX_DISC_ENIGMA]; 
                                
  int topo; 
} Pinaculo;

void prepararPinaculos(Pinaculo pinaculos[3], int numArtefatos) {
  for (int i = 0; i < 3; i++)
    pinaculos[i].topo = -1;

  for (int i = numArtefatos; i >= 1; i--)
    pinaculos[0].artefatos[++pinaculos[0].topo] = i;
}

void exibirReino(Pinaculo pinaculos[3], int numArtefatos) {
  printf("\n=== Visão do Reino Místico ===\n\n");
  for (int nivel = numArtefatos - 1; nivel >= 0; nivel--) {
    for (int p = 0; p < 3; p++) { 
      printf("    ");             

      if (nivel <= pinaculos[p].topo) {
        int artefato = pinaculos[p].artefatos[nivel];
        int tamanhoVisual = artefato;
        int espacosLaterais = numArtefatos - tamanhoVisual;

        for (int i = 0; i < espacosLaterais; i++)
          printf(" ");
        for (int i = 0; i < tamanhoVisual; i++)
          printf("="); 
        printf("|");  
        for (int i = 0; i < tamanhoVisual; i++)
          printf("=");
        for (int i = 0; i < espacosLaterais; i++)
          printf(" ");
      } else {
        for (int i = 0; i < numArtefatos; i++)
          printf(" ");
        printf("|"); 
        for (int i = 0; i < numArtefatos; i++)
          printf(" ");
      }
      printf("   ");
    }
    printf("\n");
  }
  printf("  Pináculo 1   Pináculo 2   Pináculo 3\n"); 
}

int moverArtefato(Pinaculo pinaculos[3], int origem, int destino) {
  origem--; 
  destino--; 

  if (origem < 0 || origem > 2 || destino < 0 || destino > 2) {
    printf("Erro: Pináculo de origem ou destino não existe em nosso reino (use "
           "1, 2 ou 3).\n");
    return 0;
  }
  if (pinaculos[origem].topo == -1) {
    printf("Movimento Proibido: Pináculo de origem vazio! Não há artefatos "
           "para mover.\n");
    return 0;
  }

  int artefatoAMover = pinaculos[origem].artefatos[pinaculos[origem].topo];

  if (pinaculos[destino].topo != -1 &&
      artefatoAMover > pinaculos[destino].artefatos[pinaculos[destino].topo]) {
    printf("Movimento Proibido: Não se pode colocar um artefato maior sobre um "
           "menor! A Antiga Lei.\n");
    return 0;
  }

  pinaculos[destino].artefatos[++pinaculos[destino].topo] = artefatoAMover;
  pinaculos[origem].topo--;
  return 1; 
}

int desafioCompleto(Pinaculo pinaculos[3], int numArtefatos) {
  return (pinaculos[2].topo == numArtefatos - 1);
}

void limparCanalComunicacao() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

int decifrarNumero(const char *prompt, int min, int max, int podeDesistir) {
  int valor;
  char buffer[100];

  while (1) {
    printf("%s", prompt);

    printf(" (%d a %d)%s: ", min, max,
           (podeDesistir ? " ou 0 para retornar à Base" : ""));

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
      printf("Falha na decifração. Tente novamente.\n");
      continue;
    }

    if (sscanf(buffer, "%d", &valor) != 1) {
      printf("Entrada inválida. Por favor, decifre um número inteiro.\n");
    } else {
      if (podeDesistir && valor == 0) {
        return 0;
      }
      if (valor >= min && valor <= max) {
        return valor; 
      } else {
        printf("Número fora dos limites do reino. Digite um valor entre %d e "
               "%d%s.\n",
               min, max, (podeDesistir ? " (ou 0 para retornar à Base)" : ""));
      }
    }
  }
}

void iniciarDesafio(Cronica **listaCronicas) {
  Pinaculo pinaculos[3];
  char nomeAventureiro[50];
  int numArtefatos;
  int feitos = 0;
  char dataHoraFim[30];

  printf("\nComandante, diga-nos seu nome para as Crônicas: ");
  limparCanalComunicacao(); 
  if (!fgets(nomeAventureiro, sizeof(nomeAventureiro), stdin)) {
    printf("Erro na escuta do nome. A aventura não pode começar.\n");
    return;
  }
  nomeAventureiro[strcspn(nomeAventureiro, "\n")] =
      '\0'; 
  numArtefatos = decifrarNumero("Quantos artefatos (discos) enfrentaremos", 1,
                                MAX_DISC_ENIGMA, 0);

  prepararPinaculos(pinaculos, numArtefatos); 

  printf("\n=== O Desafio Enigmático Começa! ===\n");
  exibirReino(pinaculos, numArtefatos);
  printf("\nAntigas Leis do Pináculo:\n");
  printf("- Mova apenas um artefato por vez.\n");
  printf("- Artefato maior não pode ser empilhado sobre um menor.\n");
  printf("- Digite 0 para origem ou destino para retornar à Base (Menu "
         "Principal).\n\n");

  while (1) {
    int origem = decifrarNumero("De qual Pináculo (1-3) mover", 1, 3, 1);
    if (origem == 0) {
      printf("Retornando à Base. A aventura aguarda outro dia...\n");
      break;
    }

    int destino = decifrarNumero("Para qual Pináculo (1-3) mover", 1, 3, 1);
    if (destino == 0) {
      printf("Retornando à Base. A aventura aguarda outro dia...\n");
      break;
    }

    if (moverArtefato(pinaculos, origem, destino)) {
      feitos++;                             
      exibirReino(pinaculos, numArtefatos); 

      if (desafioCompleto(pinaculos, numArtefatos)) {
        printf("\n============================================================="
               "===========\n");
        printf("Vitória! O bravo aventureiro %s dominou o Desafio Enigmático "
               "com %d artefatos em %d feitos!\n",
               nomeAventureiro, numArtefatos, feitos);
        printf("==============================================================="
               "=========\n");

        obterDataHoraAtual(dataHoraFim);
        adicionarCronica(listaCronicas, nomeAventureiro, feitos, numArtefatos,
                         dataHoraFim);
        salvarCronicasEmArquivo(*listaCronicas,
                                "cronicas.txt"); 
        printf("Sua gloriosa crônica foi registrada no Pergaminho Antigo.\n");
        break;
      }
    } else {
    }
  }
}
