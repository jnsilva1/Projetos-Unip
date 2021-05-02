#include "Paciente.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

Paciente newPaciente(){
    Paciente _paciente;
    _paciente.Pessoa = newPessoa();
    _paciente.Peso = GetDouble("\n  Informe o peso:");
    _paciente.Altura = GetDouble("\n  Informe a altura:");
    _paciente.Comorbidade = newComorbidade((int)(_paciente.Peso / (_paciente.Altura * _paciente.Altura)));

    return _paciente;
}

bool ArmazenarPacienteEmArquivo(Paciente * _paciente){
    char fileNamePessoa[50] = "";
    char dirName[50] = "";
    bool retorno = true;

    strcat(dirName, DEFAULT_DIR);
    strcat(dirName,  _paciente->Pessoa.CPF);
    strcat(dirName,  "/");

    if(mkdir(dirName) == -1){
        puts("Diretório já existe!");
    }else{
        puts("Diretório criado!");
    }

    retorno = retorno && ArmazernarPessoaEmArquivo(_paciente->Pessoa, "pessoa.txt", dirName);
    retorno = retorno && ArmazernarComorbidadeEmArquivo(&_paciente->Comorbidade, "comorbidade.txt", dirName);

   return retorno;
}

void GetPacienteEmArquivo(Paciente * _paciente, const char * CPFPaciente){

        char DirName[50] = "", arquivoPessoa[50] = "", arquivoComorbidade[50] = "";
        strcat(DirName, DEFAULT_DIR);
        strcat(DirName, CPFPaciente);
        strcat(DirName,"/");

        strcat(arquivoPessoa, DirName);
        strcat(arquivoPessoa, "pessoa.txt");
        strcat(arquivoComorbidade, DirName);
        strcat(arquivoComorbidade, "comorbidade.txt");

        _paciente->Pessoa = RetornaPessoaEmArquivo(arquivoPessoa);
        _paciente->Comorbidade = RetornaComorbidadeEmArquivo(arquivoComorbidade);
}
