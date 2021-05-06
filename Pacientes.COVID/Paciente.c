#include "Paciente.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

Paciente* newPaciente(){
    Paciente* _paciente = (Paciente*)malloc(sizeof(Paciente));
    _paciente->Pessoa = newPessoa();
    _paciente->Peso = GetDouble("\n  Informe o peso:");
    _paciente->Altura = GetDouble("\n  Informe a altura:");
    _paciente->Comorbidade = newComorbidade((int)(_paciente->Peso / (_paciente->Altura * _paciente->Altura)));

    return _paciente;
}

bool ArmazenarPacienteEmArquivo(Paciente * _paciente){
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

    retorno = retorno && ArmazernarPessoaEmArquivo(&_paciente->Pessoa, "pessoa.txt", dirName);
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
void AdicionarPaciente(ListaPaciente * lista, Paciente* _paciente){
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

    if(ListaPacienteEstaVazia(lista)){
        printf("   Lista vazia!\n");
        return;
    }

    NoPaciente* ponteiro = lista->inicio;
    while(ponteiro != NULL){
        ImprimePessoa(&ponteiro->Paciente->Pessoa);
        ponteiro = ponteiro->proximo;
    }
}

/**
 *  Informa se há nós na Lista de Paciente
 **/
bool ListaPacienteEstaVazia(ListaPaciente * lista){
    return (lista->tamanho == 0);
}

/**
 * Remove o Primeiro Nó da Lista de Paciente
 **/
void RemoverPrimeiroNoListaPaciente(ListaPaciente * lista){
    if(!ListaPacienteEstaVazia(lista)){
        NoPaciente * no = lista->inicio;
        lista->inicio = no->proximo;
        free(no);
        lista->tamanho--;
    }
}

/**
 * Retorna o paciente contido na posicao informada da Lista.
 **/
NoPaciente* NaPosicao(ListaPaciente * lista, int posicao){

    if(posicao >= 0 && posicao < lista->tamanho){
        NoPaciente * no = lista->inicio;
        int i;
        for(i= 0; i < posicao; i++)
            no = no->proximo;

        return no;
    }
    return NULL;
}

/**
 * Retorna a posição em que o paciente está na Lista. Será -1 quando não encontrar
 **/
int PosicaoNaLista(ListaPaciente * lista, Paciente * _paciente){
    if(_paciente != NULL){
        NoPaciente* no = lista->inicio;

        int posicao = 0;
        while(no != NULL){
            //Comparo pelo CPF
            if(strcmp(no->Paciente->Pessoa.CPF, _paciente->Pessoa.CPF) == 0){
                break;
            }
            no = no->proximo;
            posicao++;
        }

        if(no != NULL)
            return posicao;
    }
    return -1;
}

/**
 * Remove o paciente da Lista na posição informada
 **/
void RemoverPacienteNaPosicao(ListaPaciente* lista, int posicao){
    if(posicao == 0)
        RemoverPrimeiroNoListaPaciente(lista);
    else{
        NoPaciente* NoAtual = NaPosicao(lista, posicao);
        if(NoAtual != NULL){
            NoPaciente* NoAnterior = NaPosicao(lista, posicao - 1);
            NoAnterior->proximo = NoAtual->proximo;

            free(NoAtual);
            lista->tamanho--;
        }
    }
}

/**
 * Adiciona o paciente a Lista na posição informada
 **/
void AdicionarPacienteNaPosicao(ListaPaciente* lista, Paciente* _paciente, int posicao){
    if(posicao == 0)
        AdicionarPaciente(lista, _paciente);
    else{
        NoPaciente* NoAtual = NaPosicao(lista, posicao);
        if(NoAtual != NULL){
            NoPaciente* NoAnterior = NaPosicao(lista, posicao - 1);

            NoPaciente* NovoNo = (NoPaciente *)malloc(sizeof(NoPaciente));
            NovoNo->Paciente = _paciente;

            NoAnterior->proximo = NovoNo;
            NovoNo->proximo = NoAtual;
            lista->tamanho++;
        }
    }
}

/**
 * Muda os pacientes de posição.
 **/
void MudarPacientesNaLista(ListaPaciente * lista, Paciente* pacienteA, Paciente* pacienteB){
    //Se os pacientes forem iguais, não faço nada;
    if(pacienteA == pacienteB) return;
    //Obtenho a posição de A e B
    int posicaoA = PosicaoNaLista(lista, pacienteA),
        posicaoB = PosicaoNaLista(lista, pacienteB);
        if(posicaoA == -1 || posicaoB == -1) return;
        NoPaciente* NoA = NULL, *NoB = NULL, *NoAnteA = NULL, *NoAnteB = NULL;
        if(posicaoA > posicaoB){
            NoA = NaPosicao(lista, posicaoB);
            NoB = NaPosicao(lista, posicaoA);
            int temp = posicaoA;
            posicaoA = posicaoB;
            posicaoB = temp;
        }
        NoAnteB = NaPosicao(lista, posicaoB - 1);
        if(NoA == lista->inicio){
            lista->inicio = NoB;
        }else{
            NoAnteA = NaPosicao(lista, posicaoA - 1);
            NoAnteA->proximo = NoB;
        }
        NoAnteB->proximo = NoA;
        NoPaciente* aux = NoA->proximo;
        NoA->proximo = NoB->proximo;
        NoB->proximo = aux;
}

NoPaciente* RetornaNoPacientePrimeiroAscendentePorNome(ListaPaciente * lista, int posicaoInicial){
    NoPaciente * ponteiro = NaPosicao(lista, posicaoInicial);
    if(ponteiro != NULL){
        NoPaciente* min = ponteiro;
        while(ponteiro != NULL){
            if(strcmp(min->Paciente->Pessoa.Nome, ponteiro->Paciente->Pessoa.Nome) < 0)
                min = ponteiro;
            ponteiro = ponteiro->proximo;
        }
        return min;
    }
    return NULL;
}

NoPaciente* RetornaNoPacienteUltimoAscendentePorNome(ListaPaciente * lista, int posicaoInicial){
    NoPaciente * ponteiro = NaPosicao(lista, posicaoInicial);
    if(ponteiro != NULL){
        NoPaciente* max = ponteiro;
        while(ponteiro != NULL){
            if(strcmp(max->Paciente->Pessoa.Nome, ponteiro->Paciente->Pessoa.Nome) > 0)
                max = ponteiro;
            ponteiro = ponteiro->proximo;
        }
        return max;
    }
    return NULL;
}

void OrdenarListaPorNomeAscendente(ListaPaciente* lista){
    int i;
    for(i = 0; i < lista->tamanho - 1; i++){
        MudarPacientesNaLista(lista, NaPosicao(lista, i)->Paciente, RetornaNoPacientePrimeiroAscendentePorNome(lista, i)->Paciente);
    }
}

void OrdenarListaPorNomeDescrescente(ListaPaciente* lista){
    int i;
    for(i = 0; i < lista->tamanho - 1; i++){
        MudarPacientesNaLista(lista, NaPosicao(lista, i)->Paciente, RetornaNoPacienteUltimoAscendentePorNome(lista, i)->Paciente);
    }
}
