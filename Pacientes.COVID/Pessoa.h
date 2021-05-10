#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef PESSOA_H
#define PESSOA_H
#include "OutrosTipos.h"
#include "Endereco.h"
#include "DataHora.h"

typedef struct telefone {
    int DDD;
    long Numero;
    bool ECelular;
} Telefone;

typedef enum sexo{
    Feminino = 1,
    Masculino = 2
} Sexo;

typedef struct pessoa {
    char Nome[50];
    char CPF[12];
    Telefone Telefone;
    Endereco Endereco;
    Data DataNascimento;
    char Email[60];
    double Peso;
    double Altura;
    Sexo Sexo;
} Pessoa;

Telefone newTelefone(void);
void ImprimeTelefone(Telefone* tel);
Pessoa newPessoa(void);
void ImprimePessoa(Pessoa* p, bool varios);
int CalcularIdade(Data* dtNascto);
bool ArmazernarPessoaEmArquivo(Pessoa* _pessoa, char * nomeArquivo, char * diretorio);
Pessoa RetornaPessoaEmArquivo(char * nomeArquivo);
Sexo GetSexo();
#endif // PESSOA_H
