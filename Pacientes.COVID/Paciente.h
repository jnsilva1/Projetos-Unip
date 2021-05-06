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

struct noPaciente{
    Paciente* Paciente;
    struct noPaciente* proximo;
};
typedef struct noPaciente NoPaciente;

typedef struct listaPaciente{
    int tamanho;
    NoPaciente* inicio;
} ListaPaciente;

Paciente* newPaciente();
bool ArmazenarPacienteEmArquivo(Paciente * _paciente);
void GetPacienteEmArquivo(Paciente * _paciente, const char * CPFPaciente);
ListaPaciente* criarListaPaciente();
void AdicionarPaciente(ListaPaciente * lista, Paciente* _paciente);
void ImprimirListaPaciente(ListaPaciente * lista);
bool ListaPacienteEstaVazia(ListaPaciente * lista);
void RemoverPrimeiroNoListaPaciente(ListaPaciente * lista);
NoPaciente* NaPosicao(ListaPaciente * lista, int posicao);
int PosicaoNaLista(ListaPaciente * lista, Paciente * _paciente);
void RemoverPacienteNaPosicao(ListaPaciente* lista, int posicao);
void AdicionarPacienteNaPosicao(ListaPaciente* lista, Paciente* _paciente, int posicao);
void MudarPacientesNaLista(ListaPaciente * lista, Paciente* pacienteA, Paciente* pacienteB);
NoPaciente* RetornaNoPacientePrimeiroAscendentePorNome(ListaPaciente * lista, int posicaoInicial);
NoPaciente* RetornaNoPacienteUltimoAscendentePorNome(ListaPaciente * lista, int posicaoInicial);
void OrdenarListaPorNomeAscendente(ListaPaciente* lista);
void OrdenarListaPorNomeDescrescente(ListaPaciente* lista);
#endif // PACIENTE_H
