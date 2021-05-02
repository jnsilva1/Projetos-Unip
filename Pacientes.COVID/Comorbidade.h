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
    bool AsmaOuDoencaPulmonar;
    bool RelizouAlgumTransplante;
    bool RealizouAlgumaQuimioterapia;
    bool FazDialise;
    bool PossuiDoencaRenal;
    bool GestanteAltoRisco;
    bool PossuiDoencaNoFigado;
    bool Tuberculoso;
    int IMC;
    Data DataDiagnostico;
} Comorbidade;

Comorbidade newComorbidade();
bool ArmazernarComorbidadeEmArquivo(Comorbidade *  _comorbidade, char * nomeArquivo, char * diretorio);
Comorbidade RetornaComorbidadeEmArquivo(char * nomeArquivo);
#endif // COMORBIDADE_H
