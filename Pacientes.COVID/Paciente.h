#include <stdio.h>
#include <stdlib.h>
#ifndef PACIENTE_H
#define PACIENTE_H
#include "Pessoa.h"
#include "Comorbidade.h"

typedef struct paciente{
    Pessoa Pessoa;
    Comorbidade Comorbidade;
} Paciente;

Paciente newPaciente();
bool ArmazenarPacienteEmArquivo(Paciente * _paciente);
void GetPacienteEmArquivo(Paciente * _paciente, const char * CPFPaciente);
#endif // PACIENTE_H
