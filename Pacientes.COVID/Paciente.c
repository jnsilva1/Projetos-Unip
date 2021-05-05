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

/**
* Inicializa a lista com os Nós de Pacientes
*/
ListaPaciente* criarListaPaciente(){
    ListaPaciente * lista = (ListaPaciente *) malloc(sizeof(ListaPaciente));
    lista->tamanho = 0;
    lista->inicio = NULL;

    return lista;
}

/**
 * Adiciona o paciente a lista informada
 **/
void AdicionarPaciente(ListaPaciente * lista, Paciente _paciente){
    //Aloco memória para o nó de paciente
    NoPaciente* No = (NoPaciente *)malloc(sizeof(NoPaciente));

    //Determino o Nó do paciente
    No->Paciente = _paciente;
    //Indico que o próximo nó é o inicio da lista;
    No->proximo = lista->inicio;
    //Digo para a lista começar a partir deste novo nó.
    lista->inicio = No;
    //Incremento o tamanho da lista
    lista->tamanho++;
}

void ImprimirListaPaciente(ListaPaciente * lista){
    NoPaciente* ponteiro = lista->inicio;

    while(ponteiro != NULL){
        printf("\n   |-----------------------------------------------------------------------------------------------|\n");
        printf("   %s\n", ponteiro->Paciente.Pessoa.Nome);
        printf("   %s\n", ponteiro->Paciente.Pessoa);
        ponteiro = ponteiro->proximo;
    }
}
