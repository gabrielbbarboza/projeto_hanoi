#include "desafio_enigmatico.h" 
#include <stdio.h>           
#include <stdlib.h>            
#include <string.h> 

// Define o número máximo de discos.

#define MAX_DISC_ENIGMA 10   

// Definição da estrutura Pinaculo (equivalente a uma pilha) para representar as colunas.

typedef struct {
  int artefatos[MAX_DISC_ENIGMA]; 
  int topo; 
} Pinaculo;

// Função para preparar os pináculos no início do jogo, colocando todos os discos no primeiro.

void prepararPinaculos(Pinaculo pinaculos[3], int numArtefatos) {
  for (int i = 0; i < 3; i++)
    pinaculos[i].topo = -1;

  for (int i = numArtefatos; i >= 1; i--)
    pinaculos[0].artefatos[++pinaculos[0].topo] = i;
}

// Função para exibir o estado atual do reino (os três pináculos) com arte ASCII.
// Recebe o array de pináculos e o número total de artefatos para dimensionamento correto.

void exibirReino(Pinaculo pinaculos[3], int numArtefatos) {
  printf("\n--- O Salão das Três Colunas ---\n");

// Calcula a largura máxima em caracteres que o maior disco ocuparia.

  int max_disk_char_width = (numArtefatos * 2) - 1;

// Calcula a largura total de exibição para cada pináculo, incluindo espaços de preenchimento.

  int peg_display_width = max_disk_char_width + 2;

// Itera de cima para baixo, que vai do disco mais alto para o mais baixo ou pino vazio.

  for (int i = numArtefatos - 1; i >= 0; i--) {

        // Itera por cada um dos três pináculos.

    for (int j = 0; j < 3; j++) {

      // Verifica se há um disco na posição 'i' (altura) do pináculo 'j'.
      // "pinaculos[j].topo" é o índice do disco mais alto. Se 'i' for menor ou igual ao topo, há um disco ali.
      
      if (pinaculos[j].topo >= i) {
        int disk_size = pinaculos[j].artefatos[i]; 
        int current_disk_char_width =
            (disk_size * 2) - 1;
        
        // Calcula o preenchimento necessário para centralizar o disco no espaço do pináculo.
     
        int padding_left = (peg_display_width - current_disk_char_width) / 2;
        int padding_right =
            peg_display_width - current_disk_char_width - padding_left;

        for (int k = 0; k < padding_left; k++)
          printf(" ");
        for (int k = 0; k < current_disk_char_width; k++)
          printf("=");
        for (int k = 0; k < padding_right; k++)
          printf(" ");
      } else {

         // Se não há disco na posição 'i' (altura), imprime um pino (representado por '|').
        // Calcula o preenchimento para centralizar o pino.
        
        int padding_left_peg =
            (peg_display_width - 1) / 2; 
        int padding_right_peg = peg_display_width - 1 - padding_left_peg;

        for (int k = 0; k < padding_left_peg; k++)
          printf(" ");
        printf("|"); 
        for (int k = 0; k < padding_right_peg; k++)
          printf(" ");
      }
      printf("  ");
    }
    printf("\n"); 
  }

  for (int j = 0; j < 3; j++) {
    for (int k = 0; k < peg_display_width; k++)
      printf("=");
    printf("  ");
  }
  printf("\n");

  // Imprime os números dos pináculos (1, 2, 3) abaixo da base.
  
  for (int j = 0; j < 3; j++) {
    int padding_left_num =
        (peg_display_width - 1) / 2; 
    for (int k = 0; k < padding_left_num; k++)
      printf(" ");
    printf("%d", j + 1); 
    for (int k = 0; k < (peg_display_width - 1) - padding_left_num; k++)
      printf(" ");
    printf("  "); 
  }
  printf("\n");
  printf(
      "----------------------------------------------------------------\n"); 
}

// Função para mover um artefato (disco) de um pináculo de origem para um de destino.
// Implementa as regras da Torre de Hanói.

int moverArtefato(Pinaculo pinaculos[3], int origem, int destino) {
  origem--;
  destino--;

    // Validações básicas: pináculos válidos e pináculo de origem não vazio.
  
  if (origem < 0 || origem > 2 || destino < 0 || destino > 2) {
    printf(
        "Guardião: Pináculo inválido. Escolha entre 1, 2 e 3.\n");
                                                            
    return 0; 
  }

  if (pinaculos[origem].topo == -1) {
    printf("Guardião: O pináculo de origem está vazio! Não há artefato para "
           "mover!\n");
    return 0;           
  }

  int artefatoMovido = pinaculos[origem].artefatos[pinaculos[origem].topo];
  
  if (pinaculos[destino].topo != -1 &&
      artefatoMovido > pinaculos[destino].artefatos[pinaculos[destino].topo]) {
    printf("Guardião: Pela Antiga Lei, um artefato maior não pode repousar "
           "sobre um menor!\n"); 
    return 0;                    
  }

  // Realiza o movimento: remove do topo da origem e adiciona ao topo do destino.
  
  pinaculos[origem].topo--;
  pinaculos[destino].artefatos[++pinaculos[destino].topo] = artefatoMovido;

  printf(
      "Guardião: Artefato %d movido do Pináculo %d para o Pináculo %d.\n", 
      artefatoMovido, origem + 1, destino + 1);
  return 1; 
}

// Função para verificar se o desafio da Torre de Hanói foi completado.

int desafioCompleto(Pinaculo pinaculos[3], int numArtefatos) {

  return (pinaculos[2].topo == numArtefatos - 1);
}

// Função principal para iniciar o desafio da Torre de Hanói.
// Esta é a função chamada pelo 'main' para iniciar o jogo.

void iniciarDesafio(Cronica **listaCronicas) {
  char nomeAventureiro[50]; 
  int numArtefatos;         
  Pinaculo pinaculos[3];  
  int feitos = 0;         
  char dataHoraFim[30];   

  printf("\n============================================\n");
  printf("=== BEM-VINDO AO DESAFIO ENIGMÁTICO! ===\n");
  printf("============================================\n");
  printf("Sua missão é mover todos os artefatos do Pináculo 1 para o Pináculo "
         "3.\n");
  printf("Lembre-se da Antiga Lei: Um artefato maior nunca pode repousar sobre "
         "um menor!\n");

  if (!obterTextoDoAventureiro(
          nomeAventureiro, sizeof(nomeAventureiro),
          "\nComandante, diga-nos seu nome para as Crônicas: ")) {
    printf("Erro na escuta do nome. A aventura não pode começar.\n");
    return; 
  }

 
  numArtefatos =
      decifrarNumero("Quantos artefatos (discos) o Guardião deve invocar para "
                     "este desafio (2 a 10)? (0 para desistir): ",
                     2, MAX_DISC_ENIGMA, 1);

  if (numArtefatos == 0) {
    printf("Aventura adiada. Retornando ao Portal...\n");
    return;
  }

  prepararPinaculos(pinaculos, numArtefatos); 

    // exibirReino(pinaculos, numArtefatos); // Função para exibir o estado visual do jogo.

  exibirReino(pinaculos, numArtefatos);

  int origem, destino; 

  while (1) {
    origem = decifrarNumero("\nArtefato de qual Pináculo Místico moverá (1-3)? "
                            "(0 para retornar à Base): ",
                            0, 3, 1);
    if (origem == 0) {
      printf("Retornando à Base. A aventura aguarda outro dia...\n");
      break;
    }

    destino = decifrarNumero(
        "Para qual Pináculo Místico (1-3) ele irá? (0 para retornar à Base): ",
        0, 3, 1);
    if (destino == 0) {
      printf("Retornando à Base. A aventura aguarda outro dia...\n");
      break;
    }

    if (moverArtefato(pinaculos, origem, destino)) {
      feitos++;                    
      exibirReino(pinaculos, numArtefatos); 

      // exibirReino(pinaculos, numArtefatos); // Exibe o estado após movimento válido.

      if (desafioCompleto(pinaculos, numArtefatos)) {
        printf("\n============================================================="
               "====\n");
        printf("Vitória! O bravo aventureiro %s dominou o Desafio Enigmático "
               "com %d artefatos em %d feitos!\n",
               nomeAventureiro, numArtefatos, feitos);
        printf("==============================================================="
               "==\n");

        obterDataHoraAtual(dataHoraFim);

        // Adiciona a crônica da vitória à lista.

        adicionarCronica(listaCronicas, nomeAventureiro, feitos, numArtefatos,
                         dataHoraFim);
        
        // Salva as crônicas atualizadas no arquivo.
        
        salvarCronicasEmArquivo(*listaCronicas,
                                "cronicas.txt"); 
        printf("Sua gloriosa crônica foi registrada no Pergaminho Antigo.\n");
        break;
      }
    } else {
    }
  }
}
