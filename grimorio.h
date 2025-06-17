#ifndef GRIMORIO_H 
#define GRIMORIO_H

#include <stdio.h>

// Protótipo da função para limpar o buffer de entrada do teclado.

void limparCanalComunicacao();

// Protótipo da função para decifrar (validar) um número inteiro a partir da entrada do usuário.
// Garante que o usuário digite um número dentro de um intervalo esperado.

int decifrarNumero(const char *prompt, int min, int max, int podeDesistir);

// Protótipo da função para obter uma string (texto) do aventureiro (usuário).
// Lê texto de forma segura, evitando estouro de buffer.

int obterTextoDoAventureiro(char *buffer, int tamanhoBuffer, const char *prompt);

// Protótipo da função para obter a data e hora atuais.

void obterDataHoraAtual(char *buffer);

#endif 
