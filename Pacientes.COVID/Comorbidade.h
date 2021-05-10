#include <stdio.h>
#include <stdlib.h>
#ifndef COMORBIDADE_H
#define COMORBIDADE_H
#include "OutrosTipos.h"
#include "DataHora.h"
#include "Pessoa.h"

typedef struct comorbidade{
    bool Diabetico;
    bool Obeso;
    bool Hipertenso;
    bool Tuberculoso;
    bool AsmaOuDoencaPulmonar;
    bool DoencaRenal;
    bool DoencaNoFigado;
    bool GestanteAltoRisco;
    bool RelizouAlgumTransplante;
    bool RealizouAlgumaQuimioterapia;
    bool FazDialise;
    bool HIV;
    int IMC;
    Data DataDiagnostico;
} Comorbidade;

Comorbidade newComorbidade(int imc, Sexo sexo);
bool ArmazernarComorbidadeEmArquivo(Comorbidade *  _comorbidade, char * nomeArquivo, char * diretorio);
Comorbidade RetornaComorbidadeEmArquivo(char * nomeArquivo);
void ImprimeComorbidade(Comorbidade* comor);
#endif // COMORBIDADE_H
