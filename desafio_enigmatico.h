#ifndef DESAFIO_ENIGMATICO_H
#define DESAFIO_ENIGMATICO_H

#include "cronicas.h"
void iniciarDesafio(Cronica **listaCronicas);

void limparCanalComunicacao();

int decifrarNumero(const char *prompt, int min, int max, int podeDesistir);

#endif
