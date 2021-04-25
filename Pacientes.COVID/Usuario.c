#include "Usuario.h"

Usuario AcessarSistema(char * login, char * senha){
    AdicionaUsuarioPadrao();
    Usuario usuario;
    FILE * fptr;
    char diretorioUsuarios[50];

    strcat(diretorioUsuarios, DEFAULT_DIR);
    strcat(diretorioUsuarios, "usuarios.unip");
    //Abrindo arquivo para leitura e gravação em modo binário
    if((fptr = fopen(diretorioUsuarios, "ab+")) == NULL) return usuario;

    while(fread(&usuario, sizeof(Usuario), 1,fptr) == 1){
        if(stricmp(login, usuario.Login) && stricmp(senha, usuario.Senha)){
            break;
        }
    }
    return usuario;
}

void ObtemSenha(char * _dest){
    const int maxPasswordLength = 15;
    char password[maxPasswordLength+1],ch;
    int characterPosition = 0;

    printf("Informe a senha. Tamanho 1-%d\n", maxPasswordLength);
    while(1){
        ch = getch();
        if(ch == ENTER_CHAR){
            break;
        }else if( ch == BLANCKSPACE_CHAR){
            if(characterPosition > 0){
                characterPosition--;
                password[characterPosition] = EMPTYCHAR;
                printf("\b \b");
            }
        }else if(ch == 32 || ch == 9){ //When user enters space / tab
            continue;
        }else{
            if(characterPosition < maxPasswordLength){
                password[characterPosition] = ch;
                characterPosition++;
                printf("*");
            }else{
                printf("\nSua senha excede a quantidade maxima de caractreses. Apenas os %d primeiros caracteres serão considerados!", maxPasswordLength);
                break;
            }
        }
    }
    password[characterPosition] = EMPTYCHAR;
    printf("\n");
    if(strlen(password) == 0){
        printf("Nenhuma senha informada.");
    }
    strcpy(_dest, password);
    free(password);
}

int TotalUsuariosCadastrados(){
    FILE * fptr;
    char diretorioUsuarios[50];
    long numeroRegistros = 0;

    strcat(diretorioUsuarios, DEFAULT_DIR);
    strcat(diretorioUsuarios, "usuarios.unip");

    if((fptr = fopen(diretorioUsuarios, "rb")) == NULL) return (int)numeroRegistros;

    fseek(fptr, 0, 2); //Indo para o final do arquivo
    //Calcula o numero de registros
    numeroRegistros = ftell(fptr)/sizeof(Usuario);
    return (int)numeroRegistros;
}

void AdicionaUsuarioPadrao(){
    if(TotalUsuariosCadastrados() == 0){
        Usuario user;
        user.Id = 1;
        user.Login = "ADMIN";
        user.Senha = "#UNIP.123";
        user.Nome = "ADMINISTRADOR";

        FILE * fptr;
        char diretorioUsuarios[50];

        strcat(diretorioUsuarios, DEFAULT_DIR);
        strcat(diretorioUsuarios, "usuarios.unip");
        //Abrindo arquivo para leitura e gravação em modo binário
        if((fptr = fopen(diretorioUsuarios, "ab+")) == NULL) return;

        //adiciono o usuário padrão
        fwrite(&user, sizeof(Usuario), 1,fptr);

        fclose(fptr);
    }
}
