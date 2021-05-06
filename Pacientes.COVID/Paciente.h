#include <stdio.h>
#include <stdlib.h>
#include "Pessoa.h"
#include "Comorbidade.h"
#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct paciente{
    Pessoa Pessoa;
    double Peso;
    double Altura;
    Comorbidade Comorbidade;
} Paciente;
#endif // PACIENTE_H

#ifndef NO_PACIENTE
#define NO_PACIENTE
typedef struct noPaciente{
    Paciente* Paciente;
    struct noPaciente * proximo;
} NoPaciente;
#endif // NO_PACIENTE

#ifndef LISTA_PACIENTE
#define LISTA_PACIENTE
typedef struct listaPaciente{
    int tamanho;
    NoPaciente* inicio;
} ListaPaciente;

void AdicionarPaciente(ListaPaciente * lista, Paciente* _paciente);
void ImprimirListaPaciente(ListaPaciente * lista);
void GetPacienteEmArquivo(Paciente * _paciente, const char * CPFPaciente);
void RemoverNoListaPaciente(ListaPaciente * lista);
void OrdenarListaPorNomeAscendente(ListaPaciente* lista);
void MudarPacientesNaLista(ListaPaciente * lista, Paciente* pacienteA, Paciente* pacienteB);
void OrdenarListaPorNomeDescrescente(ListaPaciente* lista);
int PosicaoNaLista(ListaPaciente * lista, Paciente * _paciente);
bool ArmazenarPacienteEmArquivo(Paciente * _paciente);
bool ListaPacienteEstaVazia(ListaPaciente * lista);
Paciente* newPaciente();
ListaPaciente* criarListaPaciente();
NoPaciente* NaPosicao(ListaPaciente * lista, int posicao);
NoPaciente* RetornaNoPacientePrimeiroAscendentePorNome(ListaPaciente * lista, int posicaoInicial);
NoPaciente* RetornaNoPacienteUltimoAscendentePorNome(ListaPaciente * lista, int posicaoInicial);
#endif // LISTA_PACIENTE
