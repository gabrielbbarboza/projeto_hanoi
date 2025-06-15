#ifndef GRIMORIO_H 
#define GRIMORIO_H

#include <stdio.h>

void limparCanalComunicacao();

int decifrarNumero(const char *prompt, int min, int max, int podeDesistir);

int obterTextoDoAventureiro(char *buffer, int tamanhoBuffer, const char *prompt);

void obterDataHoraAtual(char *buffer);

#endif 
