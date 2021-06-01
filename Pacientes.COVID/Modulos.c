#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dirent.h>
#include "Usuario.h"
#include "Modulos.h"
#include "Paciente.h"
#include "OutrosTipos.h"

/**
 Ponteiro para armazenar o usu�rio atualmente logado.
*/
Usuario* usuarioLogado;

/***
 Imprime o header padr�o para a tela prinicipal
**/
void ImprimirHeaderPadrao(){
    LimparTela();
    printf(" |==================================================================================|\n");
    printf(" |                                UNIPCARE - COVID-19                               |\n");
    if(usuarioLogado != NULL){
        printf(" |----------------------------------------------------------------------------------|\n");
        String label = criarString(255), dataHoraString = criarString(16), labelPrint = criarString(255);
        DataHoraToString(dataHoraString, Agora(), S_DATAHORA_FORMATO_DATAHORA);
        sprintf(label,"Usu%crio: %s, Data/Hora: %s", a_AGUDO, usuarioLogado->Nome, dataHoraString);
        PadLeft(' ', labelPrint, label, 82);
        printf(" |%s|\n", labelPrint);
        free(label);
        free(dataHoraString);
        free(labelPrint);
    }
    printf(" |==================================================================================|\n\n");
}

/**
 * Reliza o processo de acesso ao sistema por meio de usu�rio (Login/Senha).
 */
Usuario* RealizarLogin(){
    char senha[30], login[50], texto[255];
    senha[0] = EMPTYCHAR;
    login[0] = EMPTYCHAR;
    Usuario* user;
    COORD* posInicial = GetCursorPosition();
    do{
        do{ //Enquanto o login for vazio, solicito a informa��o ao usu�rio

            AddCursorPosition(0, -1);
            GetString("\n   Informe o login: ", login, 49, false);
            if(strlen(login) == 0) {
                AddCursorPosition(0, -1);
                GetString("   Nenhum login informado.", senha, 29, false);
                AddCursorPosition(0, -1);
            }
        }while(strlen(login) == 0);

        AddCursorPosition(0, 2);
        do{//Enquanto a senha for vazia, continuo solicitando ao usu�rio

            AddCursorPosition(0, -2);
            printf("  ");
            ObtemSenha(senha, true, " Informe a senha: ");
        }while(strlen(senha) ==0);

        //Aciona a fun��o respons�vel por validar os dados de acesso
        user = AcessarSistema(login, senha);
        if(user == NULL){ //Se usu�rio n�o foi encontrado, apresento mensagem
            sprintf(texto, "   Usu%crio e/ou senha incorretos. (Pressione qualquer tecla para continuar. . .)", a_AGUDO);
            GetString(texto, login, 2, false);
            AddCursorPosition(0,-1);
            AddCursorPosition(0,-1);
            AddCursorPosition(0,-1);
        }
    }while(user == NULL);
    return user; //Retorno ponteiro para usu�rio logado
}

/**
 * Realiza o processo de cadastro de paciente
 */
void CadastrarPaciente(){
    Paciente* p = newPaciente();
    ArmazenarPacienteEmArquivo(p);
    AddCursorPosition(0,-1);
    printf("   Paciente %s cadastrado com sucesso!\n", p->Pessoa.Nome);
    getch();
    AddCursorPosition(0,-1);
    if(GetBool("   Deseja cadastrar mais um paciente? (S/N): ",'S'))
        CadastrarPaciente();
    GetComandoPadrao();
}

/**
 * Lista todos os pacientes cadastrados.
 **/
void ListarPacientes(){

    ListaPaciente* pacientes =  CarregarPacientesCadastrados();
    OrdenarListaPorNomeAscendente(pacientes);
    ImprimirListaPaciente(pacientes);

    GetComandoPadrao();
}

/**
 * Executa o processo respons�vel pela altera��o de senha do usu�rio logado.
 **/
void AlterarSenha(){
    ImprimirHeaderPadrao();
    String senhaAtual = criarString(18), novaSenha1 = criarString(18), novaSenha2 = criarString(18);
    ObtemSenha(senhaAtual, false, "   Informe a senha atual: ");
    if(strcmp(senhaAtual, usuarioLogado->Senha) != 0){
        AddCursorPosition(0,-2);
        printf("   Senha inv%clida!", a_AGUDO);
        getch();
        AlterarSenha();
    }

    //Ajudar� a verificar se devo ou n�o exibir mensagem de erro referente as senhas informadas pelo usu�rio.
    bool primeiraIteracao = true;
    do{
        if(!primeiraIteracao){
            printf("   Senha inv%clida!\n", a_AGUDO);
            getch();
            AddCursorPosition(0,-1);
            AddCursorPosition(0,-1);
            AddCursorPosition(0,-1);
        }
        primeiraIteracao = false;

        //Nova senha, que ser� comparada com a segunda
        ObtemSenha(novaSenha1, false, "   Informe a nova senha: ");
            if(strlen(novaSenha1) <= 0){
                novaSenha1[0] = '1';
                continue;
            }
        //Pede ao usu�rio que confirme a senha, para que ele tenha certeza que diitou a senha desejada de forma correta.
        ObtemSenha(novaSenha2, false, "   Confirme a nova senha: ");
            if(strlen(novaSenha2) <= 0){
                novaSenha2[0] = '2';
                continue;
            }

     //Continuo executando o processo enquanto as senhas n�o estiverem de acordo.
    }while(strcmp(novaSenha1, novaSenha2) != 0);

    //Defino a nova senha ao usu�rio logado e envio para grava��o em arquivo.
    strcpy(usuarioLogado->Senha, novaSenha1);
    if(GravarUsuario(usuarioLogado, true)){
        printf("\n   Senha alterada com sucesso!\n\n");
    }
    GetComandoPadrao();
}

/**
 * Respons�vel por informar ao usu�rio que a op��o informada no menu � inv�lida
 **/
void InformaMenuInvalido(){
    ImprimirHeaderPadrao();
    printf("   Op%c%co inv%clida!", c_DILHA, a_TILDE, a_AGUDO);
    getch();
    ImprimirMenu();
}

/**
 * Apresenta mensagem para usu�rio sobre os comandos poss�veis a serem executados no momento.
 **/
void GetComandoPadrao(){
    puts("   Pressione:\n   [ENTER] para voltar ao menu.\n   [ESC] para encerrar o sistema.\n   [F2] para logout.\n   ");
    int comando = getch();
    if(comando == ENTER_CHAR){
        ImprimirMenu();
    }else if(comando == ESC){
        exit(0);
    }else if(comando == 0){
        comando = getch();
        if(comando == 60){//F2
            free(usuarioLogado);
            usuarioLogado = NULL;
            Inicializar();
        }
    }else{
        printf("   Comando inv%clido!\n", a_AGUDO);
        getch();
        AddCursorPosition(0,-1);//Limpa linha a linha
        AddCursorPosition(0,-1);
        AddCursorPosition(0,-1);
        AddCursorPosition(0,-1);
        AddCursorPosition(0,-1);
        AddCursorPosition(0,-1);

        GetComandoPadrao();
    }
}

/**
 * Imprime o menu para que o usu�rio possa decidir o que deseja fazer no momento
 */
void ImprimirMenu(){
    LimparTela();
    ImprimirHeaderPadrao();
    int option;
    printf("   1 - Cadastrar Paciente.\n\n");
    printf("   2 - Listar Pacientes.\n\n");
    printf("   3 - Alterar Senha.\n\n");
    if(usuarioLogado->Admin){
        printf("   4 - Adicionar Usu%crio.\n\n", a_AGUDO);
    }
    AddCursorPosition(3,0);
    scanf("%d", &option);

    switch(option)
    {
        case 1:
            CadastrarPaciente();
            break;
        case 2:
            ListarPacientes();
            break;
        case 3:
            AlterarSenha();
            break;
        case 4:
            if(usuarioLogado->Admin){
                CadastrarUsuario();
                GetComandoPadrao();
            }
            else
                InformaMenuInvalido();
            break;
        default:
            InformaMenuInvalido();
    }
}

/**
 * Respons�vel por inicializar o sistema
 */
void Inicializar(){

    InicializarDiretorioPadrao();
    ImprimirHeaderPadrao();
    if(usuarioLogado == NULL)
        usuarioLogado = RealizarLogin();
    ImprimirMenu();
}
