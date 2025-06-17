#include "grimorio.h" 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h> 

// Função para limpar o buffer de entrada do teclado.

void limparCanalComunicacao() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Função para validar um número inteiro a partir da entrada do usuário.
// É uma função robusta para garantir que a entrada seja um número e dentro dos limites.

int decifrarNumero(const char *prompt, int min, int max, int podeDesistir) {
  int numero;
  char entrada[256]; 
  while (1) { 
    printf("%s", prompt); 
    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
      printf("Erro na leitura. Tente novamente.\n");
      continue;
    }
    entrada[strcspn(entrada, "\n")] = '\0';

    if (sscanf(entrada, "%d", &numero) ==
        1) { 
      if (podeDesistir && numero == 0) {
        return 0; 
      }
      if (numero >= min && numero <= max) {
        return numero; 
      } else {
        printf(
            "Aventureiro, o número deve ser entre %d e %d. Tente novamente.\n",
            min, max);
      }
    } else {
      printf(
          "Entrada inválida. Por favor, digite um número. Tente novamente.\n");
    }
  }
}

// Função para obter uma string (texto) do usuário de forma segura.
// Evita estouro de buffer e lida com o caractere de nova linha.

int obterTextoDoAventureiro(char *buffer, int tamanhoBuffer,
                            const char *prompt) {
  printf("%s", prompt);
  if (!fgets(buffer, tamanhoBuffer, stdin)) {
    return 0; 
  }
  buffer[strcspn(buffer, "\n")] = '\0';

  return 1;
}

// Função para obter a data e hora atuais e formatá-las em uma string.

void obterDataHoraAtual(char *buffer) {
  time_t t = time(NULL); 
  struct tm tm = *localtime(&t); 
  snprintf(buffer, 30, "%04d-%02d-%02d %02d:%02d:%02d",
           tm.tm_year + 1900, 
           tm.tm_mon + 1,    
           tm.tm_mday,  
           tm.tm_hour,  
           tm.tm_min,
           tm.tm_sec); 
}
