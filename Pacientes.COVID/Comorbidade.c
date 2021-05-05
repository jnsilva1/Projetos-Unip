#include "Comorbidade.h"
#include <dirent.h>

Comorbidade newComorbidade(int imc){
    Comorbidade _comorbidade;
    char texto[255];
    printf("\n  Paciente possui:");
    _comorbidade.Diabetico = GetBool("\n  Diabete? (S/N): ", 'S');

    _comorbidade.Obeso = GetBool("\n  Obesidade? (S/N): ", 'S');

    sprintf(texto, "\n  Hipertens%co? (S/N): ", a_TILDE);
    _comorbidade.Hipertenso = GetBool(texto, 'S');

    _comorbidade.Tuberculoso = GetBool("\n  Tuberculose? (S/N): ", 'S');

    sprintf(texto, "\n  Asma ou Doen%ca Pulmonar? (S/N): ", c_DILHA);
    _comorbidade.AsmaOuDoencaPulmonar = GetBool(texto, 'S');

    sprintf(texto, "\n  Alguma Doen%ca Renal? (S/N): ", c_DILHA);
    _comorbidade.DoencaRenal = GetBool(texto, 'S');

    sprintf(texto, "\n  Doen%ca no F%cgado? (S/N): ", c_DILHA, i_AGUDO);
    _comorbidade.DoencaNoFigado = GetBool(texto, 'S');

    sprintf(texto, "\n  Gesta%c%co de Alto Risco? (S/N): ", c_DILHA,a_TILDE);
    _comorbidade.GestanteAltoRisco = GetBool(texto, 'S');

    _comorbidade.RelizouAlgumTransplante = GetBool("\n  Transplante? (S/N): ", 'S');

    _comorbidade.RealizouAlgumaQuimioterapia = GetBool("\n\n  Paciente Fez Quimioterapia? (S/N): ", 'S');

    sprintf(texto, "\n  Paciente Faz Di%clise? (S/N): ", a_AGUDO);
    _comorbidade.FazDialise = GetBool(texto, 'S');

    _comorbidade.IMC = imc;

    _comorbidade.DataDiagnostico = Agora()->Data;
    return _comorbidade;
}

/**
* Usage: Armazena a comorbidade me um arquivo no diretório informado com o nome especificado.
*/
bool ArmazernarComorbidadeEmArquivo(Comorbidade * _comorbidade, char * nomeArquivo, char * diretorio){
    FILE *arquivo;
    char fileName[50] = "";
    bool retorno = true;
    strcat(fileName, diretorio);
    strcat(fileName, nomeArquivo);

    if(mkdir(diretorio) == -1){
        puts("Diretório já existe!");
    }else{
        puts("Diretório criado!");
    }
    if((arquivo = fopen(fileName, "wb")) == NULL){
        retorno = false;
    }

    if(fwrite(_comorbidade, sizeof(Comorbidade), 1,arquivo)!=1){
        retorno = true;
    }

    fclose(arquivo);
    return retorno;
}

Comorbidade RetornaComorbidadeEmArquivo(char * nomeArquivo){

    FILE * fptr;
    Comorbidade comor;
    if((fptr = fopen(nomeArquivo, "rb")) == NULL) return comor;

    while(fread(&comor, sizeof(Comorbidade), 1,fptr) == 1)
        1+1;
    fclose(fptr);

    return comor;
}
