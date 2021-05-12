#include "Pessoa.h"
#include <dirent.h>

/**
 * Realiza a criação de um novo telefone através das entradas do usuário no console
 * @return estrutura da dados do tipo Telefone com os dados obtidos
 **/
Telefone newTelefone(void){

    Telefone tel;
    char resposta/*, teclado = '\0'*/;
    char tempFone[30] = "";
    //int i = 0;

    bool primeiroLoop = true;
    bool Valido = false;
    do{
        fflush(stdin);
        if(!primeiroLoop){
            AddCursorPosition(0, -1);
            printf(" Telefone inv%clido.\n",160);
            getch();
            AddCursorPosition(0,-1);
        }
        printf("  Informe o telefone com DDD \'(00) 000000000\': ");
        tempFone[0] = EMPTYCHAR;
        gets(tempFone);
        ReplaceChar(tempFone, '(', (char)0);
        ReplaceChar(tempFone, ')', (char)0);
        ReplaceChar(tempFone, '.', (char)0);
        ReplaceChar(tempFone, '-', (char)0);
        ReplaceChar(tempFone, BLANKCHAR, (char)0);

        primeiroLoop = false;

        //scanf("(%i) %ld", &tel.DDD , &tel.Numero);

        fflush(stdin);
        AddCursorPosition(0,-1);
        printf("  Eh celular? (S/N): ");
        scanf("%c", &resposta);

        if(resposta == 's' || resposta == 'S'){
            tel.ECelular = true;
        }else{
            tel.ECelular = false;
        }

        if(tel.ECelular){
            Valido = (Length(tempFone) >= Length("11911111111") && Length(tempFone) <= Length("011911111111"));
        }else{
            Valido = (Length(tempFone) >= Length("1111111111") && Length(tempFone) <= Length("01111111111"));
        }

    }while(!ContemApenasNumero(tempFone) || !Valido);

    char tempDDD[4] = "", tempNum[11] = "";
    int indice = (tempFone[0] == '0' ? 3 : 2);
    Substring(tempDDD, tempFone, 0, indice);
    Substring(tempNum, tempFone, indice, Length(tempFone) - indice);
    tel.DDD = ConverteParaInteiro(tempDDD);
    tel.Numero = ConverteParaLongo(tempNum);

    return tel;
}

/**
 * Imprime o telefone em tela com formatação específica
 * @param tel ponteiro para o telefone a ser impresso
 **/
void ImprimeTelefone(Telefone* tel){
    char num[15];
    sprintf(num, "%ld",tel->Numero);

    if(tel->ECelular){
        printf("Telefone: (%i) %c.%c%c%c%c-%c%c%c%c \n", tel->DDD, num[0], num[1], num[2], num[3], num[4], num[5], num[6], num[7], num[8]);
    }else{
        printf("Telefone: (%i) %c%c%c%c-%c%c%c%c \n", tel->DDD, num[0], num[1], num[2], num[3], num[4], num[5], num[6], num[7]);
    }
}

/**
 * Realiza a impressão dos dados da pessoa em tela
 * @param p ponteiro para a pessoa a ser impressa
 * @param varios indica se devo ou não limpar a tela antes de imprimir os dados (Deve ser true quando for impresso em laço)
 ***/
void ImprimePessoa(Pessoa* p, bool varios){
    if(!varios)
        LimparTela();
    char nomePessoa[84];
    char EspacoEmBranco[85] = " ";
    CentralizarString(nomePessoa, p->Nome, 82);
    StringUpperCase(nomePessoa);
    CentralizarString(EspacoEmBranco, " ", 82);

    printf(" |==================================================================================|\n");//84
   // printf(" |%s%s%s|\n", padding, p.Nome, paddingRight);
    printf(" |%s|\n", nomePessoa);
    printf(" |==================================================================================|\n");
    printf(" |%s|\n", EspacoEmBranco);

    //Imprime o CPF
    char _cpf[16],CPF[85];
    FormataCPF(_cpf, p->CPF);
    PadRight(' ', CPF, _cpf, 62);
    printf(" |               CPF: %s|\n", CPF);

   //Imprime a data de nascimento
    char dataNascto[20], txtDtNascto[85];
    DataToString(dataNascto, &p->DataNascimento);
    PadRight(' ', txtDtNascto, dataNascto, 62);
    printf(" |Data de Nascimento: %s|\n", txtDtNascto);

    char Idade[3], __idade[85];
    sprintf(Idade, "%d", CalcularIdade(&p->DataNascimento));
    PadRight(' ', __idade, Idade, 62);
    printf(" |             Idade: %s|\n", __idade);


    String tempTexto = criarString(60), printTexto = criarString(255);
    sprintf(tempTexto, "%.2f", p->Peso);
    PadRight(' ', printTexto, tempTexto, 62);
    printf(" |              Peso: %s|\n", printTexto);

    sprintf(tempTexto, "%.2f", p->Altura);
    PadRight(' ', printTexto, tempTexto, 62);
    printf(" |            Altura: %s|\n", printTexto);
    free(tempTexto);
    free(printTexto);

    //IMPRIME EMAIL
    char eMail[85];
    PadRight(' ', eMail, p->Email, 62);
    printf(" |            E-Mail: %s|\n", eMail);

    //Imprime Telefone
    char telefone[85];
    FormataTelefone(telefone, p->Telefone.DDD, p->Telefone.Numero, p->Telefone.ECelular);
    PadRight(' ', telefone, telefone, 72);
    printf(" |          %s|\n", telefone);
    printf(" |----------------------------------------------------------------------------------|\n");

    char Logradouro[85];
    PadRight(' ', Logradouro, p->Endereco.Logradouro, 62);
    printf(" |        Logradouro: %s|\n", Logradouro);

    char NumeroEndereco[85], num[10];
    sprintf(num, "%d", p->Endereco.Numero);
    PadRight(' ', NumeroEndereco, num, 62);
    printf(" |            Numero: %s|\n", NumeroEndereco);

    char ComplementoEndereco[85];
    PadRight(' ', ComplementoEndereco, p->Endereco.Complemento, 62);
    printf(" |       Complemento: %s|\n", ComplementoEndereco);

    char BairroEndereco[85];
    PadRight(' ', BairroEndereco, p->Endereco.Bairro, 62);
    printf(" |            Bairro: %s|\n", BairroEndereco);

    char CidadeEndereco[85];
    PadRight(' ', CidadeEndereco, p->Endereco.Cidade, 62);
    printf(" |            Cidade: %s|\n", CidadeEndereco);

    char UFEndereco[85];
    PadRight(' ', UFEndereco, p->Endereco.Estado, 62);
    printf(" |                UF: %s|\n", UFEndereco);

    char CEPEndereco[85], _cep[15];
    sprintf(_cep, "%ld", p->Endereco.CEP);
    FormataCEP(_cep, _cep);
    PadRight(' ', CEPEndereco, _cep, 62);
    printf(" |               CEP: %s|\n", CEPEndereco);

    printf(" |==================================================================================|\n");
}

/**
 * Instancia uma nova pessoa com os dados solicitados em tela
 *@return a estrutura de dados do tipo Pessoa com os dados obtidos
 **/
Pessoa newPessoa(void) {
    system("cls");
    Pessoa p;

    printf(" |==================================================================================|\n");
    printf(" |                               CADASTRO DE PESSOA                                 |\n");
    printf(" |==================================================================================|\n");

    AddCursorPosition(0,1);
    GetStringLetrasApenas("   Informe o nome (sem acentos): ", p.Nome, 49);

    AddCursorPosition(0,-1);
    sprintf(p.CPF, "%lld", GetLongLong("   Informe o CPF (numeros apenas): "));

    AddCursorPosition(0, -1);
    p.DataNascimento = GetData("   Informe a data de nascimento \'dd/mm/aaaa\': ");

    AddCursorPosition(0, -1);
    p.Sexo = GetSexo();

    AddCursorPosition(0, -1);
    double min = 0.01, max = 3;
    p.Altura = GetDouble("   Informe a altura (9,99): ", NULL, &max);

    AddCursorPosition(0, -1);
    p.Peso = GetDouble("   Informe o peso (99,99): ", &min,NULL);

    AddCursorPosition(0, -1);
    GetEmail("   Informe o email: ", p.Email);

    AddCursorPosition(0, -1);
    p.Telefone = newTelefone();

    AddCursorPosition(0, -1);
    p.Endereco = newEndereco();

    return p;
}

/**
* Realiza o Cálculo de Idade
* Usage: Calculo de Idade
* @param dtNascto ponteiro para a data de nascimento
* @return idade
*/
int CalcularIdade(Data* dtNascto){
    DataHora* __agora;
    __agora = Agora();
    int idade = __agora->Data.Ano - dtNascto->Ano;

    if(__agora->Data.Mes <= dtNascto->Mes){
        if(__agora->Data.Mes == dtNascto->Mes){ //Mes de Aniversário igual ao atual
            if(__agora->Data.Dia < dtNascto->Dia) //Dia Atual menor que o dia de aniversário, então removo 1 ano, pois ainda não está completo.
                idade--;
        }else{//Mes atual é menor que o mês de aniversário, então diminuo 1 ano, pois ainda não está completo.
            idade--;
        }
    }

    return idade;
}

/**
 * Usage: Armazena os dados da pessoa informada em um Arquivo com o nome especificado no diretório informado
 * @param _pessoa ponteiro para pessoa a ser armazenada
 * @param nomeArquivo nome do arquivo em que será armazenado
 * @param diretorio diretório em que se quer armazenar
 */
bool ArmazernarPessoaEmArquivo(Pessoa* _pessoa, char * nomeArquivo, char * diretorio){
    FILE *arquivo;
    char fileName[50] = "";
    bool retorno = true;
    strcat(fileName, diretorio);
    strcat(fileName, nomeArquivo);

    mkdir(diretorio);

    if((arquivo = fopen(fileName, "wb")) == NULL){
        retorno = false;
    }

    if(fwrite(_pessoa, sizeof(Pessoa), 1,arquivo)!=1){
        retorno = true;
    }

    fclose(arquivo);
    return retorno;
}

/**
 * Responsável por obter os dados da pessoa que estão armazenados em arquivo
 * @param nomeArquivo nome do arquivo que se quer obter os dados
 * @return estrutura de dados do tipo Pessoa com os dados obtidos
 **/
Pessoa RetornaPessoaEmArquivo(char * nomeArquivo){

    FILE * fptr;
    int counter = 0;
    Pessoa pes;
    if((fptr = fopen(nomeArquivo, "rb")) == NULL) return pes;

    while(fread(&pes, sizeof(Pessoa), 1,fptr) == 1)
        counter++;
    fclose(fptr);

    return pes;
}

/**
 * Responsável por obter um sexo de acordo com a entrada do usuário no console.
 * @return o enum sexo obtido
 **/
Sexo GetSexo(){
    int val = GetInteiro("   Inform o sexo: \n   1 - Feminino.\n   2 - Masculino.\n   ");
    AddCursorPosition(0,-1);
    AddCursorPosition(0,-1);
    AddCursorPosition(0,-1);

    if(val < 1 || val > 2){
        AddCursorPosition(0,-1);
        printf("   Sexo inv%clido!\n", a_AGUDO);
        getch();
        AddCursorPosition(0,-1);
        return GetSexo();
    }
    return (Sexo)val;
}
