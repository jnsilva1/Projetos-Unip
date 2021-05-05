#include "Usuario.h"

void ObtemNomeCompletoArquivoDeUsuarios(char * _destino){
    _destino[0] = EMPTYCHAR;
    strcat(_destino, DEFAULT_DIR);
    strcat(_destino, "usuarios.unip");
}

Usuario* AcessarSistema(char * login, char * senha){
    AdicionarUsuarioPadrao();
    Usuario* usuario = (Usuario *)malloc(sizeof(Usuario));
    FILE * fptr;
    bool ENCONTROU = false;
    char diretorioUsuarios[50];
    ObtemNomeCompletoArquivoDeUsuarios(diretorioUsuarios);

    //Abrindo arquivo para leitura e gravação em modo binário
    if((fptr = fopen(diretorioUsuarios, "rb")) == NULL) return usuario;

    while(fread(usuario, sizeof(Usuario), 1,fptr) == 1){
        //Se usuário atual possui os mesmos dados de acesso, saio do laço e retorno o usuário
        if(strcmp(login, usuario->Login) == 0 && strcmp(senha, usuario->Senha) == 0){
                ENCONTROU = true;
            break;
        }
    }
    if(!ENCONTROU){
        usuario=NULL;
    }
    fclose(fptr);
    return usuario;
}


void ObtemSenha(char * _dest, bool login){
    const int maxPasswordLength = 15;
    char password[maxPasswordLength+1],ch;
    int characterPosition = 0;
    fflush(stdin);
    printf(" Informe a senha: ", maxPasswordLength);
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
                if(!login){
                    printf("\n\n Sua senha excede a quantidade maxima de caractreses. Apenas os %d primeiros caracteres serão considerados!", maxPasswordLength);
                }
                break;
            }
        }
    }
    password[characterPosition] = EMPTYCHAR;
    printf("\n");
    strcpy(_dest, password);
    if(strlen(password) == 0){
        AddCursorPosition(0,-1);
        GetString("   Nenhuma senha informada.\n", password);
    }
}

int TotalUsuariosCadastrados(){
    FILE * fptr;
    char diretorioUsuarios[50];
    long numeroRegistros = 0;

    ObtemNomeCompletoArquivoDeUsuarios(diretorioUsuarios);

    if((fptr = fopen(diretorioUsuarios, "rb")) == NULL) return (int)numeroRegistros;

    fseek(fptr, 0, 2); //Indo para o final do arquivo
    //Calcula o numero de registros
    numeroRegistros = ftell(fptr)/sizeof(Usuario);
    fclose(fptr);
    return (int)numeroRegistros;
}

void AdicionarUsuarioPadrao(){
    if(TotalUsuariosCadastrados() == 0){
        Usuario user;
        user.Id = 1;
        user.Login[0] = EMPTYCHAR;
        user.Nome[0] = EMPTYCHAR;
        user.Nome[0] = EMPTYCHAR;
        strcat(user.Login,"ADMIN");
        strcat(user.Senha,"#UNIP.123");
        strcat(user.Nome,"ADMINISTRADOR");
        user.Admin = true;

        FILE * fptr;
        char diretorioUsuarios[50];
        ObtemNomeCompletoArquivoDeUsuarios(diretorioUsuarios);

        //Abrindo arquivo para leitura e gravação em modo binário
        if((fptr = fopen(diretorioUsuarios, "ab+")) == NULL) return;

        //adiciono o usuário padrão
        fwrite(&user, sizeof(Usuario), 1,fptr);

        fclose(fptr);
    }
}

ResultadoBuscaEmArquivo* BuscaUsuarioPeloId(Usuario * usuarioDestino, int Id){

    FILE * fptr;
    ResultadoBuscaEmArquivo res = {0, false};
    char diretorioUsuarios[50];
    ObtemNomeCompletoArquivoDeUsuarios(diretorioUsuarios);

    //Abrindo arquivo para leitura e gravação em modo binário
    if((fptr = fopen(diretorioUsuarios, "rb")) == NULL) return &res;

    while(fread(usuarioDestino, sizeof(Usuario), 1,fptr) == 1){
        //Se usuário atual possui os mesmos dados de acesso, saio do laço e retorno o usuário
        if(usuarioDestino->Id == Id){
            res.EncontrouRegistro = true;
            res.Posicao = ftell(fptr);
            break;
        }
    }
    fclose(fptr);
    return &res;
}

int ProximaSequenciaUsuario(){
    Usuario us;
    FILE * fptr;
    char diretorioUsuarios[50];
    int sequencia = 1, posicao = TotalUsuariosCadastrados();
    if(posicao == 0){
        return sequencia;
    }else{
        posicao =  (posicao - 1) * sizeof(Usuario);
    }
    ObtemNomeCompletoArquivoDeUsuarios(diretorioUsuarios);



    if((fptr = fopen(diretorioUsuarios, "rb")) == NULL) return sequencia;

    fseek(fptr, posicao, 0);
    fread(&us, sizeof(Usuario), 1, fptr);
    fclose(fptr);
    sequencia = us.Id + 1;

    return sequencia;
}

void RetornaTodosUsuariosCadastrados(Usuario usrs[]){
    int indiceAtual = 0;
    FILE * fptr;
    char diretorioUsuarios[50];
    ObtemNomeCompletoArquivoDeUsuarios(diretorioUsuarios);

    if((fptr = fopen(diretorioUsuarios, "rb")) == NULL) return;

    while(fread(&usrs[indiceAtual], sizeof(Usuario), 1, fptr) == 1){
        indiceAtual++;
    }
}

bool ExisteUsuarioComLogin(char * login){
    bool resposta = false;
    int totalUsuarios = TotalUsuariosCadastrados();
    Usuario users[totalUsuarios];
    RetornaTodosUsuariosCadastrados(users);
    StringUpperCase(login);

    for(int i = 0; i < totalUsuarios; i++){
        StringUpperCase(users[i].Login);
        resposta = resposta || strcmp(login, users[i].Login) == 0;
    }

    return resposta;
}

bool GravarUsuario(Usuario* usr, bool atualizacao){
    if(ExisteUsuarioComLogin(usr->Login) && !atualizacao){
        printf("\n\n  J%c existe usu%crio cadastrado com o login informado.\n",160,160);
        getche();
        return false;
    }

    AdicionarUsuario(&usr);
    return true;
}

void CadastrarUsuario(){
    bool gravou = false;
    do{
        Usuario* usr = ObterNovoUsuario();
        gravou = GravarUsuario(usr, false);
    }while(gravou == false);
}

void ImprimirTodosUsuarios(){
    Usuario USRS[TotalUsuariosCadastrados()];
    RetornaTodosUsuariosCadastrados(USRS);
    ImprimeUsuarios(USRS, TotalUsuariosCadastrados());
}


void AdicionarUsuario(Usuario* usr){
    Usuario temp;
    ResultadoBuscaEmArquivo* resultado = BuscaUsuarioPeloId(&temp, usr->Id);
    FILE * fptr;
    char diretorioUsuarios[50];
    ObtemNomeCompletoArquivoDeUsuarios(diretorioUsuarios);

    if((fptr = fopen(diretorioUsuarios, "ab+")) == NULL) return;

    if(resultado->EncontrouRegistro){
        //Atualização
        fseek(fptr, resultado->Posicao, 0);
    }

    fwrite(&usr, sizeof(Usuario), 1, fptr);
    fclose(fptr);
    free(resultado);
}

Usuario* ObterNovoUsuario(){
    fflush(stdin);
    system("cls");
    Usuario usuario;

    printf(" |==================================================================================|\n");
    printf(" |                               CADASTRO DE USUARIO                                |\n");
    printf(" |==================================================================================|\n");

    GetString(" Informe o nome do usuario: ", usuario.Nome);
    GetString(" Informe o login: ", usuario.Login);
    ObtemSenha(usuario.Senha, false);
    usuario.Id = ProximaSequenciaUsuario();

    return &usuario;
}

void ImprimeUsuario(Usuario* usr){
    printf("\n    Id: %d", usr->Id);
    printf("\n  Nome: %s", usr->Nome);
    printf("\n Login: %s", usr->Login);
    printf("%c", NEWLINE);
}

void ImprimeUsuarios(Usuario usrs[], int tamanho){
    system("cls");
    printf(" |==================================================================================|\n");
    printf(" |                                     USUARIOS                                     |\n");
    printf(" |==================================================================================|\n");

    for(int i = 0; i < tamanho; i++){
        ImprimeUsuario(&usrs[i]);
    }
    printf("\n\n");
}
