#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dirent.h>
#include "Modulos.h"
#include "Paciente.h"
#include "OutrosTipos.h"
#include "Usuario.h"
Usuario* usuarioLogado;

void ImprimirHeaderPadrao(){
    LimparTela();
    printf(" |==================================================================================|\n");
    printf(" |                                LUNICARE - COVID-19                               |\n");
    printf(" |==================================================================================|\n\n");
}

Usuario* RealizarLogin(){
    char senha[30], login[50], texto[255];
    senha[0] = EMPTYCHAR;
    login[0] = EMPTYCHAR;
    Usuario* user;
    COORD* posInicial = GetCursorPosition();
    do{
        do{

            AddCursorPosition(0, -1);
            GetString("\n   Informe o login: ", login, 49);
            if(strlen(login) == 0) {
                AddCursorPosition(0, -1);
                GetString("   Nenhum login informado.", senha, 29);
                AddCursorPosition(0, -1);
            }
        }while(strlen(login) == 0);

        AddCursorPosition(0, 2);
        do{

            AddCursorPosition(0, -2);
            printf("  ");
            ObtemSenha(senha, true, " Informe a senha: ");
        }while(strlen(senha) ==0);

        user = AcessarSistema(login, senha);
        if(user == NULL){
            sprintf(texto, "   Usu%crio e/ou senha incorretos. (Pressione qualquer tecla para continuar. . .)", a_AGUDO);
            GetString(texto, login, 2);
            AddCursorPosition(0,-1);
            AddCursorPosition(0,-1);
            AddCursorPosition(0,-1);
        }
    }while(user == NULL);
    return user;
}

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


void ListarPacientes(){

    ListaPaciente* pacientes =  CarregarPacientesCadastrados();
    OrdenarListaPorNomeAscendente(pacientes);
    ImprimirListaPaciente(pacientes);

    GetComandoPadrao();
}

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

        ObtemSenha(novaSenha1, false, "   Informe a nova senha: ");
            if(strlen(novaSenha1) <= 0){
                novaSenha1[0] = '1';
                continue;
            }
        ObtemSenha(novaSenha2, false, "   Confirme a nova senha: ");
            if(strlen(novaSenha2) <= 0){
                novaSenha2[0] = '2';
                continue;
            }

    }while(strcmp(novaSenha1, novaSenha2) != 0);

    strcpy(usuarioLogado->Senha, novaSenha1);
    if(GravarUsuario(usuarioLogado, true)){
        printf("\n   Senha alterada com sucesso!\n\n");
    }
    GetComandoPadrao();
}

void InformaMenuInvalido(){
    ImprimirHeaderPadrao();
    printf("   Op%c%co inv%clida!", c_DILHA, a_TILDE, a_AGUDO);
    getch();
    ImprimirMenu();
}

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
            if(usuarioLogado->Admin)
                CadastrarUsuario();
            else
                InformaMenuInvalido();
            break;
        default:
            InformaMenuInvalido();
    }
}

void Inicializar(){

    InicializarDiretorioPadrao();
    ImprimirHeaderPadrao();
    if(usuarioLogado == NULL)
        usuarioLogado = RealizarLogin();
    ImprimirMenu();
}
