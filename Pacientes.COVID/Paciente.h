#include <stdio.h>
#include <stdlib.h>
#ifndef PACIENTE_H
#define PACIENTE_H
#include "Pessoa.h"
#include "Comorbidade.h"

typedef struct paciente{
    Pessoa Pessoa;
    double Peso;
    double Altura;
    Comorbidade Comorbidade;
} Paciente;

typedef struct noPaciente{
    Paciente Paciente;
    struct noPaciente * proximo;
} NoPaciente;

typedef struct listaPaciente{
    int tamanho;
    NoPaciente* inicio;
} ListaPaciente;

ListaPaciente* criarListaPaciente();
void AdicionarPaciente(ListaPaciente * lista, Paciente _paciente);
void ImprimirListaPaciente(ListaPaciente * lista);
Paciente newPaciente();
bool ArmazenarPacienteEmArquivo(Paciente * _paciente);
void GetPacienteEmArquivo(Paciente * _paciente, const char * CPFPaciente);
#endif // PACIENTE_H
