#include <stdio.h>
#include <stdlib.h>
#ifndef ENDERECO_H
#define ENDERECO_H

typedef struct endereco {
    char Logradouro[60];
    int Numero;
    char Complemento[60];
    char Bairro[30];
    char Cidade[40];
    char Estado[3];
    long CEP;
} Endereco;

Endereco newEndereco();
#endif // ENDERECO_H
