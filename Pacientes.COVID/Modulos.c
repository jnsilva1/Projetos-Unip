#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dirent.h>
#include "Modulos.h"
Usuario* usuarioLogado;

void ImprimirHeaderPadrao(){
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
            GetString("\n   Informe o login: ", login);
            if(strlen(login) == 0) {
                AddCursorPosition(0, -1);
                GetString("   Nenhum login informado.", senha);
                AddCursorPosition(0, -1);
            }
        }while(strlen(login) == 0);

        AddCursorPosition(0, 2);
        do{

            AddCursorPosition(0, -2);
            printf("  ");
            ObtemSenha(senha, true);
        }while(strlen(senha) ==0);

        user = AcessarSistema(login, senha);
        if(user == NULL){
            sprintf(texto, "   Usu%crio e/ou senha incorretos. (Pressione qualquer tecla para continuar. . .)", a_AGUDO);
            GetString(texto, login);
            LimparTelaAtePontoDeterminado(posInicial);
        }
    }while(user->Id == 0);
    return user;
}

void CadastrarPaciente(){
    Paciente* p = newPaciente();
    ArmazenarPacienteEmArquivo(p);
    printf("Paciente %s armazenado em arquivo com sucesso!\n", p->Pessoa.Nome);
}


void ListarPacientes(){

    DIR *dir;
    struct dirent *lsdir;

    dir = opendir(DEFAULT_DIR);

    /* print all the files and directories within directory */
    while ( ( lsdir = readdir(dir) ) != NULL )
    {
        printf ("%s\n", lsdir->d_name);
    }

    closedir(dir);


    /**
        [
        "AMOR",
        "DINHEIRO",
        "PROSPERIDADE",
        "ESPERANCA"
        ]


    **/

}

void AlterarSenha(){
}

void InformaMenuInvalido(){
    printf("   Op%c%co inv%clida!", c_DILHA, a_TILDE, a_AGUDO);
    getch();
    ImprimirMenu();
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
    ImprimirHeaderPadrao();
    usuarioLogado = RealizarLogin();
    ImprimirMenu();
}
