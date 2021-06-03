#include "Paciente.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

/**
 * Respons�vel por inst�ncia o ponteiro de estrutura do tipo Paciente e preench�-lo com dados obtidos da entrada do usu�rio atrav�s do console.
 * @return ponteiro criado
 **/
Paciente* newPaciente(){
    Paciente* _paciente = (Paciente*)malloc(sizeof(Paciente));
    _paciente->Pessoa = newPessoa();
    AddCursorPosition(0,-1);
    _paciente->Comorbidade = newComorbidade((int)(_paciente->Pessoa.Peso / (_paciente->Pessoa.Altura * _paciente->Pessoa.Altura)), _paciente->Pessoa.Sexo);

    return _paciente;
}

/**
 * Processo respons�vel por armazenar os dados do paciente em arquivo
 * @param _paciente ponteiro para o paciente que ter� os dados arquivados
 * @return True quando processo � executado sem falha
 **/
bool ArmazenarPacienteEmArquivo(Paciente * _paciente){
    char dirName[50] = "";
    bool retorno = true;

    strcat(dirName, DEFAULT_DIR);
    strcat(dirName, "PACIENTES/");
    mkdir(dirName);
    strcat(dirName,  _paciente->Pessoa.CPF);
    strcat(dirName,  "/");

    retorno = retorno && ArmazernarPessoaEmArquivo(&_paciente->Pessoa, "pessoa.txt", dirName);
    retorno = retorno && ArmazernarComorbidadeEmArquivo(&_paciente->Comorbidade, "comorbidade.txt", dirName);

    if(PacienteFazParteGrupoRisco(_paciente)){
        AdicionarPacienteAGrupoRisco(_paciente);
    }

   return retorno;
}

/**
 * Respons�vel por obter os dados de um determinado paciente em arquivo e preencher em uma estrutura de dados.
 * @param _paciente ponteiro para estrutura que ir� receber os dados
 * @param CPFPaciente CPF do paciente que se quer os dados
 **/
void GetPacienteEmArquivo(Paciente * _paciente, const char * CPFPaciente){

        char DirName[50] = "", arquivoPessoa[50] = "", arquivoComorbidade[50] = "";
        strcat(DirName, DEFAULT_DIR);
        strcat(DirName, "PACIENTES/");
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
* Inicializa a lista com os N�s de Pacientes
* @return ponteiro para a lista criada
*/
ListaPaciente* criarListaPaciente(){
    ListaPaciente * lista = (ListaPaciente *) malloc(sizeof(ListaPaciente));
    lista->tamanho = 0;
    lista->inicio = NULL;

    return lista;
}

/**
 * Adiciona o paciente a lista informada
 * @param lista ponteiro para a lista em que se quer adicionar o paciente
 * @param _paciente ponteiro para o paciente que quer adicionar
 **/
void AdicionarPaciente(ListaPaciente * lista, Paciente* _paciente){
    //Aloco mem�ria para o n� de paciente
    NoPaciente* No = (NoPaciente *)malloc(sizeof(NoPaciente));

    //Determino o N� do paciente
    No->Paciente = _paciente;
    //Indico que o pr�ximo n� � o inicio da lista;
    No->proximo = lista->inicio;
    //Digo para a lista come�ar a partir deste novo n�.
    lista->inicio = No;
    //Incremento o tamanho da lista
    lista->tamanho++;
}

/**
 * Imprime a lista de pacientes
 * @param lista ponteiro para a lista de pacientes a ser impressa
 ***/
void ImprimirListaPaciente(ListaPaciente * lista){
    LimparTela();
    if(ListaPacienteEstaVazia(lista)){
        printf("   Nenhum Paciente Cadastrado!\n");
        return;
    }

    NoPaciente* ponteiro = lista->inicio;
    while(ponteiro != NULL){
        ImprimePessoa(&ponteiro->Paciente->Pessoa, true);
        ImprimeComorbidade(&ponteiro->Paciente->Comorbidade);
        ponteiro = ponteiro->proximo;
    }
}

/**
 * Informa se h� n�s na Lista de Paciente
 * @param lista ponteiro para a lista a ser verificada
 * @return true quando h� pelo menos 1 elemento na lista
 **/
bool ListaPacienteEstaVazia(ListaPaciente * lista){
    return (lista->tamanho == 0);
}

/**
 * Remove o Primeiro N� da Lista de Paciente
 * @param lista ponteiro para a lista do paciente a que ter� seu primeiro n� removido
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
 * @param lista ponteiro para a lista de paciente a ser localizado o n� de acordo com a posi��o informada
 * @param posicao posi��o/indice em que deva estar o n� esperado.
 * @return Retorna o paciente contido na posicao informada da Lista.
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
 * @param lista ponteiro para a lista de paciente a ser examinada
 * @param _paciente ponteiro do paciente que se quer encontrar a posi��o na lista
 * @return Retorna a posi��o em que o paciente est� na Lista. Ser� -1 quando n�o encontrar
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
 * Remove o paciente da Lista na posi��o informada
 * @param lista ponteiro da lista que ter� o n� de paciente removido na posi��o determinada
 * @param posicao posi��o/indice em que quer remover o n�
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
 * Adiciona o paciente a Lista na posi��o informada
 * @param lista ponteiro para a lista que ser� adicionad o paciente
 * @param _paciente ponteiro para o paciente que quer adicionar a lista
 * @param posicao posi��o/indice em que se quer adicionar o paciente
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
 * Muda os pacientes de posi��o.
 * @param lista ponteiro da lista em que os pacientes ser�o trocados de posi��o
 * @param pacienteA ponteiro para o primeiro paciente da troca
 * @param pacienteB ponteiro apra o segundo paciente da troca
 **/
void MudarPacientesNaLista(ListaPaciente * lista, Paciente* pacienteA, Paciente* pacienteB){
    //Se os pacientes forem iguais, n�o fa�o nada;
    if(pacienteA == pacienteB) return;
    //Obtenho a posi��o de A e B
    int posicaoA = PosicaoNaLista(lista, pacienteA),
        posicaoB = PosicaoNaLista(lista, pacienteB);

        if(posicaoA == -1 || posicaoB == -1) return;

        NoPaciente* NoA = NaPosicao(lista, posicaoA), *NoB = NaPosicao(lista, posicaoB), *NoAnteA = NULL, *NoAnteB = NULL;

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

/**
 * @param lista ponteiro para a lista a ser examinada
 * @param posicaoInicial posi��o inicial da ordena��o.
 * @return Retorna ponteiro para o primeiro paciente da lista ordenada por nome em forma crescente a partir de determinada posi��o
 **/
NoPaciente* RetornaNoPacientePrimeiroAscendentePorNome(ListaPaciente * lista, int posicaoInicial){
    NoPaciente * ponteiro = NaPosicao(lista, posicaoInicial);
    if(ponteiro != NULL){
        NoPaciente* min = ponteiro;
        while(ponteiro != NULL){
            if(strcmp(min->Paciente->Pessoa.Nome, ponteiro->Paciente->Pessoa.Nome) > 0)
                min = ponteiro;
            ponteiro = ponteiro->proximo;
        }
        return min;
    }
    return NULL;
}

/**
 * @param lista ponteiro para a lista a ser examinada
 * @param posicaoInicial posi��o inicial da ordena��o.
 * @return Retorna ponteiro para o �ltimo paciente da lista ordenada por nome em forma crescente a partir de determinada posi��o
 **/
NoPaciente* RetornaNoPacienteUltimoAscendentePorNome(ListaPaciente * lista, int posicaoInicial){
    NoPaciente * ponteiro = NaPosicao(lista, posicaoInicial);
    if(ponteiro != NULL){
        NoPaciente* max = ponteiro;
        while(ponteiro != NULL){
            if(strcmp(max->Paciente->Pessoa.Nome, ponteiro->Paciente->Pessoa.Nome) < 0)
                max = ponteiro;
            ponteiro = ponteiro->proximo;
        }
        return max;
    }
    return NULL;
}

/**
 * Ordena a lista informada por nome do paciente em ascend�ncia
 * @param lista ponteiro para a lista a ser ordenada
 ***/
void OrdenarListaPorNomeAscendente(ListaPaciente* lista){
    int i;
    for(i = 0; i < lista->tamanho - 1; i++){
        MudarPacientesNaLista(lista, NaPosicao(lista, i)->Paciente, RetornaNoPacientePrimeiroAscendentePorNome(lista, i)->Paciente);
    }
}

/**
 * Ordena a lista informada por nome do paciente em decresc�ncia
 * @param lista ponteiro para a lista a ser ordenada
 ***/
void OrdenarListaPorNomeDescrescente(ListaPaciente* lista){
    int i;
    for(i = 0; i < lista->tamanho - 1; i++){
        MudarPacientesNaLista(lista, NaPosicao(lista, i)->Paciente, RetornaNoPacienteUltimoAscendentePorNome(lista, i)->Paciente);
    }
}

/**
 * Respons�vel por carregar todos os pacientes armazenados em arquivo
 * @return ponteiro para lista de pacientes cadastrados
 ***/
ListaPaciente* CarregarPacientesCadastrados(){
    ListaPaciente* lista = criarListaPaciente();

    DIR *dir;
    struct dirent *lsdir;
    String diretorio = criarString(255);
    strcat(diretorio, DEFAULT_DIR);
    strcat(diretorio, "PACIENTES/");

    dir = opendir(diretorio);
    /* print all the files and directories within directory */
    while ( ( lsdir = readdir(dir) ) != NULL )
    {
        if(ContemApenasNumero(lsdir->d_name)){
            Paciente* paciente = (Paciente*)malloc(sizeof(Paciente));
            GetPacienteEmArquivo(paciente, lsdir->d_name);
            AdicionarPaciente(lista, paciente);
        }
    }
    closedir(dir);
    return lista;
}

/**
 * Determina se o paciente faz parte do grupo de risco
 * Fonte: http://www.oncoguia.org.br/conteudo/grupos-de-risco/13468/1204/
 * @param paciente ponteiro para o paciente a ser examinado
 * @return true quando o paciente examinado possuir pelo menos 1 dos par�metros de risco
 */
bool PacienteFazParteGrupoRisco(Paciente* paciente){
    return paciente->Comorbidade.IMC >= 40 ||
           CalcularIdade(&paciente->Pessoa.DataNascimento) >= 65 ||
           paciente->Comorbidade.AsmaOuDoencaPulmonar ||
           paciente->Comorbidade.Diabetico ||
           paciente->Comorbidade.DoencaNoFigado ||
           paciente->Comorbidade.DoencaRenal ||
           paciente->Comorbidade.FazDialise ||
           paciente->Comorbidade.GestanteAltoRisco ||
           paciente->Comorbidade.Hipertenso ||
           paciente->Comorbidade.HIV ||
           paciente->Comorbidade.Obeso ||
           paciente->Comorbidade.RealizouAlgumaQuimioterapia ||
           paciente->Comorbidade.RelizouAlgumTransplante ||
           paciente->Comorbidade.Tuberculoso;
}

/**
 * Realiza o armazenamento de dados em arquivo para ser enviar � Secretaria da Sa�de Municipal
 * @param paciente ponteiro para o paciente que ser� incluso ao grupo de risco
 ***/
void AdicionarPacienteAGrupoRisco(Paciente* paciente){
    String diretorio = criarString(90);
    strcat(diretorio, DEFAULT_DIR);
    strcat(diretorio, "GRUPO.RISCO/");

    mkdir(diretorio);

    strcat(diretorio, paciente->Pessoa.Nome);
    ReplaceChar(diretorio, ' ', 0);
    strcat(diretorio, ".txt");

    FILE *arquivo;
    if((arquivo = fopen(diretorio, "wb")) == NULL){
        return;
    }else{
        String linha = criarString(255);
        sprintf(linha, "CEP: %ld\n", paciente->Pessoa.Endereco.CEP);
        fputs(linha, arquivo);

        linha[0] = '\0';
        sprintf(linha, "IDADE: %d\n", CalcularIdade(&paciente->Pessoa.DataNascimento));
        fputs(linha, arquivo);
    }

    fclose(arquivo);

    printf("   Paciente pertence ao grupo de risco!\n");
    printf("   Arquivo com os dados a serem encaminhados para a Secretaria Municipal da Saude foi salvo no caminho abaixo.\n");
    printf("   %s\n\n",diretorio);
    getch();
}
