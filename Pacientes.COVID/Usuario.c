#include "Usuario.h"

/**
 * Responsável por montar o caminho/nome completo do arquivo que armazena os usuário que possuem acesso ao sistema
 * @param _destino ponteiro para a cadeia de caracteres que receberá o nome completo do arquivo
 **/
void ObtemNomeCompletoArquivoDeUsuarios(char * _destino){
    _destino[0] = EMPTYCHAR;
    strcat(_destino, DEFAULT_DIR);
    strcat(_destino, "usuarios.unip");
}

/**
 * Responsável por validade os dados de acesso ao sistema
 * @param login Login do usuário
 * @param senha Senha do usuário
 * @return ponteiro para o usuário de acordo com os dados informados
 **/
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

/**
 * Responsável por obter a senha da entrada do usuário no console
 * @param _dest ponteiro para a cadeia de caracteres que irá receber a senha
 * @param login determina se o momento a ser exigida a senha será para realizar login
 * @param descricao Descrição auxiliar
 **/
void ObtemSenha(char * _dest, bool login, String descricao){
    const int maxPasswordLength = 15;
    char password[maxPasswordLength+1],ch;
    int characterPosition = 0;
    fflush(stdin);
    if(descricao != NULL){
        printf(descricao, maxPasswordLength);
    }else{
        printf(" Informe a senha (%d caracteres): ", maxPasswordLength);
    }
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
        GetString("   Nenhuma senha informada.\n", password, 1, false);
    }
}

/**
 * Responsável por verificar a quantidade total de usuários cadastrados.
 **/
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

/**
 * Responsável por adicionar o usuário administrador
 **/
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

/**
 * Responsável por buscar o usuário em arquvo por seu id
 * @param usuarioDestino ponteiro para armazenar o usuário encontrado
 * @param Id id do usuário que se deseja encontrar
 * @return ponteiro para resultado de busca em arquivo
 ***/
ResultadoBuscaEmArquivo* BuscaUsuarioPeloId(Usuario * usuarioDestino, int Id){

    FILE * fptr;
    ResultadoBuscaEmArquivo* res = (ResultadoBuscaEmArquivo*)malloc(sizeof(ResultadoBuscaEmArquivo));
    res->EncontrouRegistro = false;
    res->Posicao = -1;
    char diretorioUsuarios[50];
    ObtemNomeCompletoArquivoDeUsuarios(diretorioUsuarios);

    //Abrindo arquivo para leitura e gravação em modo binário
    if((fptr = fopen(diretorioUsuarios, "rb")) == NULL) return &res;

    while(fread(usuarioDestino, sizeof(Usuario), 1,fptr) == 1){
        //Se usuário atual possui os mesmos dados de acesso, saio do laço e retorno o usuário
        if(usuarioDestino->Id == Id){
            res->EncontrouRegistro = true;
            res->Posicao = ftell(fptr);
            break;
        }
    }
    fclose(fptr);
    return res;
}

/**
 * Retorna a próxima sequência para o usuário
 **/
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

/**
 * Preenche a lista com os usuários cadastrados
 * @param lista ponteiro da lista que irá armazenar em memória os usuários cadastrados
 ***/
void RetornaTodosUsuariosCadastrados(ListaUsuario* lista){
    int indiceAtual = 0;
    FILE * fptr;
    char diretorioUsuarios[50];
    ObtemNomeCompletoArquivoDeUsuarios(diretorioUsuarios);

    if((fptr = fopen(diretorioUsuarios, "rb")) == NULL) return;

    NoUsuario* no = criarNoUsuario();
    Usuario* usr = criarUsuario();
    while(fread(usr, sizeof(Usuario), 1, fptr) == 1){
        no->atual = usr;
        no->proximo = lista->inicio;
        lista->inicio = no;
        lista->tamanho++;
        no = criarNoUsuario();
        usr = criarUsuario();
        indiceAtual++;
    }
    free(no);
    free(usr);
}

/**
 * Responsável por determinar se já foi cadastrado um usuário com o login informado
 * @param login ponteiro para cadeia de caracteres que contém o login a ser verificado
 **/
bool ExisteUsuarioComLogin(char * login){
    bool resposta = false;
    ListaUsuario* lista = criarListaUsuario();
    RetornaTodosUsuariosCadastrados(lista);
    String loginComparer = criarString(strlen(login));
    strcpy(loginComparer, login);
    StringUpperCase(loginComparer);

    NoUsuario* aux = lista->inicio;
    while(aux != NULL){
        StringUpperCase(aux->atual->Login);
        resposta = resposta || strcmp(loginComparer, aux->atual->Login) == 0;
        aux = aux->proximo;
    }
    free(aux);
    free(lista);
    return resposta;
}

/**
 * Responsável por executar o armazenamento do usuário em arquivo e as devidas validações
 * @param usr ponteiro para o usuário a ser armazenado
 * @param atualizacao determina se devo ignora a validação de duplicidade de login
 * @return true quando armazenou sem problemas o usuário
 **/
bool GravarUsuario(Usuario* usr, bool atualizacao){
    if(ExisteUsuarioComLogin(usr->Login) && !atualizacao){
        printf("\n\n  J%c existe usu%crio cadastrado com o login informado.\n",160,160);
        getche();
        return false;
    }

    AdicionarUsuario(usr);
    return true;
}

/**
 * Processo a ser acionado pelo usuário na tela principal
 **/
void CadastrarUsuario(){
    bool gravou = false;
    do{
        Usuario* usr = ObterNovoUsuario();
        gravou = GravarUsuario(usr, false);
    }while(gravou == false);

    String texto = criarString(255);
    sprintf(texto,"  Deseja adicionar mais um usu%crio? (S/N) ", a_AGUDO);
    if(GetBool(texto, 'S')){
        CadastrarUsuario();
    }
}

/**
 * Processo responsável por imprimir todos os usuários cadastrados
 **/
void ImprimirTodosUsuarios(){
    ListaUsuario* lista = criarListaUsuario();
    RetornaTodosUsuariosCadastrados(lista);
    ImprimeUsuarios(lista);
    free(lista);
}

/**
 * Responsável por determinar a posição na lista, do usuário informado.
 * @param lista ponteiro para a lista de usuários
 * @param usr usuário que se deseja saber a posição na lista
 * @return a posição, será -1 quando não encontrado
 **/
int RetornaPosicaoUsuario(ListaUsuario* lista, Usuario* usr){
    int pos = 0;
    NoUsuario* no = lista->inicio;
    while(no!= NULL){
        if(no->atual->Id == usr->Id || strcmp(no->atual->Login, usr->Login) == 0)
            return pos;
        no = no->proximo;
        pos++;
    }
    return -1;
}

/**
 * Retorna o Nó de usuário da lista na posição informada.
 * @param lista ponteiro para a lista de usuários
 * @param posição em que está o nó desejado.
 **/
NoUsuario* RetornaNoUsuarioNaPosicao(ListaUsuario* lista, int posicao){
    if(posicao < 0 || posicao > lista->tamanho) return NULL;
    NoUsuario* no = lista->inicio;
    int pos=0;
    while(no != NULL){
        if(pos == posicao)
            return no;

        no = no->proximo;
        pos++;
    }
    return NULL;
}

/**
 * Responsável por gravar o usuário no arquivo
 * @param usr usuário que se deseja armazenar
 **/
void AdicionarUsuario(Usuario* usr){
    int totalUsuarios = TotalUsuariosCadastrados(), pos = 0;
    ListaUsuario* lista = criarListaUsuario();
    RetornaTodosUsuariosCadastrados(lista);
    NoUsuario* no = RetornaNoUsuarioNaPosicao(lista, RetornaPosicaoUsuario(lista, usr));
    if(no != NULL){
        Usuario* aux = no->atual;
        no->atual = usr;
        free(aux);
    }else{
        no = criarNoUsuario();
        no->atual = usr;
        no->proximo = lista->inicio;
        lista->inicio = no;
    }

    FILE * fptr;
    char diretorioUsuarios[50];
    ObtemNomeCompletoArquivoDeUsuarios(diretorioUsuarios);

    if((fptr = fopen(diretorioUsuarios, "wb")) == NULL) return;

    no =  lista->inicio;
    while(no != NULL){
        fwrite(no->atual, sizeof(Usuario), 1, fptr);
        no = no->proximo;
    }

    fclose(fptr);
    free(no);
    free(lista);
}

/**
 * Responsável por obter da entrada do console, os dados do novo usuário
 * @return ponteiro para o novo usuário obtido
 **/
Usuario* ObterNovoUsuario(){
    fflush(stdin);
    system("cls");
    Usuario* usuario = (Usuario*)malloc(sizeof(Usuario));

    printf(" |==================================================================================|\n");
    printf(" |                               CADASTRO DE USUARIO                                |\n");
    printf(" |==================================================================================|\n");

    GetString(" Informe o nome do usuario: ", usuario->Nome, 49, true);
    GetString(" Informe o login: ", usuario->Login, 29, true);
    ObtemSenha(usuario->Senha, false, NULL);
    usuario->Id = ProximaSequenciaUsuario();

    return usuario;
}

/**
 * Imprime os dados do usuário informado em tela
 * @param usr ponteiro para o usuário que se quer imprimir
 **/
void ImprimeUsuario(Usuario* usr){
    printf("\n      Id: %d", usr->Id);
    printf("\n    Nome: %s", usr->Nome);
    printf("\n   Login: %s", usr->Login);
    printf("%c", NEWLINE);
}

/**
 * Executa as impressão em tela dos dados dos usuários contidos na lista informada
 * @param lista lista de usuários a serem impresso os dados
 **/
void ImprimeUsuarios(ListaUsuario* lista){
    system("cls");
    printf(" |==================================================================================|\n");
    printf(" |                                     USUARIOS                                     |\n");
    printf(" |==================================================================================|\n");

    NoUsuario* no = lista->inicio;
    while(no != NULL){
        ImprimeUsuario(no->atual);
        no = no->proximo;
    }
    printf("\n\n");
}

/**
 * Responsável por criar o ponteiro para a lista de usuário
 * @return ponteiro criado
 **/
ListaUsuario* criarListaUsuario(){
    ListaUsuario* lista = (ListaUsuario*)malloc(sizeof(ListaUsuario));
    lista->inicio = NULL;
    lista->tamanho = 0;
    return lista;
}

/**
 * Responsável por criar o ponteiro para nó de usuário
 * @return ponteiro criado
 **/
NoUsuario* criarNoUsuario(){
    NoUsuario* no = (NoUsuario*)malloc(sizeof(NoUsuario));
    no->atual = NULL;
    no->proximo = NULL;
    return no;
}

/**
 * Responsável por criar o ponteiro para usuário
 * @return ponteiro criado
 **/
Usuario* criarUsuario(){
    Usuario* usuario = (Usuario*)malloc(sizeof(Usuario));
    usuario->Id = 0;
    usuario->Nome[0] = EMPTYCHAR;
    usuario->Login[0] = EMPTYCHAR;
    usuario->Senha[0] = EMPTYCHAR;
    usuario->Admin = false;
}
