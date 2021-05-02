#include <stdio.h>
#include <stdlib.h>
#ifndef COMORBIDADE_H
#define COMORBIDADE_H
#include "OutrosTipos.h"
#include "DataHora.h"

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
    int IMC;
    Data DataDiagnostico;
} Comorbidade;

Comorbidade newComorbidade(int imc);
bool ArmazernarComorbidadeEmArquivo(Comorbidade *  _comorbidade, char * nomeArquivo, char * diretorio);
Comorbidade RetornaComorbidadeEmArquivo(char * nomeArquivo);
#endif // COMORBIDADE_H
