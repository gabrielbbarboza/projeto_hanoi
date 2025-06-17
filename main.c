#include "cronicas.h"       
#include "desafio_enigmatico.h"
#include "grimorio.h" 
#include <stdio.h> 
#include <stdlib.h> 

int main() {

    // Declara um ponteiro para o início da lista encadeada de crônicas, inicialmente vazia.

  Cronica *pergaminhoCronicas =
      NULL; 

    // Tenta carregar as crônicas de uma sessão anterior do arquivo.
  
  carregarCronicasDoArquivo(&pergaminhoCronicas,
                            "cronicas.txt");

  int escolhaAventureiro;

  // Loop principal do menu do jogo: o programa continua rodando até que o usuário escolha sair.
  
  while (1) { 
    printf("\n=== O Salão das Três Colunas ===\n");
    printf("1. Enfrentar o Desafio Enigmático (Jogar)\n");
    printf("2. Consultar as Crônicas Antigas\n");
    printf("3. Buscar uma Lenda Específica (Buscar por nome ou data)\n");
    printf("4. Encerrar a Jornada (Sair)\n");

 
    escolhaAventureiro = decifrarNumero("Escolha uma opção: ", 1, 4, 0);

    switch (escolhaAventureiro) {
    case 1:
           // Inicia o jogo da Torre de Hanói.
      iniciarDesafio(&pergaminhoCronicas);
      break;
    case 2:
          // Exibe todas as crônicas atualmente carregadas na memória.
      exibirCronicas(pergaminhoCronicas);
      break;
    case 3: {   
      char termoBusca[50]; 
         // Pede ao usuário o termo para buscar no histórico.
      if (obterTextoDoAventureiro(termoBusca, sizeof(termoBusca),
                                  "Qual lenda buscas (nome do aventureiro ou "
                                  "data da jornada)?: ")) {
        
          // Realiza a busca e exibe os resultados.

        buscarCronicasPorNomeOuData(pergaminhoCronicas,
                                    termoBusca); 
      } else {
        printf("Não conseguimos ouvir sua busca, aventureiro.\n");
      }
      break;
    }
    case 4:
      printf(
          "O Guardião fecha o Portal. Até a próxima jornada, aventureiro!\n");
      
       // Libera toda a memória alocada para as crônicas antes de encerrar.

      liberarCronicas(pergaminhoCronicas);
      return 0;
    default:
   
      printf(
          "Aventureiro, essa escolha não existe no Portal. Tente novamente.\n");
      break;
    }
  }

  return 0; 
}
