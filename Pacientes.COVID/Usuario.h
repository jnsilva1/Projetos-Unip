#include <stdio.h>
#include <stdlib.h>
#include "OutrosTipos.h"

#ifndef USUARIO_HH
#define USUARIO_HH
typedef struct usuario {
    int Id;
    char Login[30];
    char Nome[50];
    char Senha[17];
    bool Admin;
} Usuario;

typedef struct noUsuario{
    Usuario* atual;
    struct noUsuario* proximo;
}NoUsuario;

typedef struct listaUsuario{
    NoUsuario* inicio;
    int tamanho;
}ListaUsuario;

void ObtemNomeCompletoArquivoDeUsuarios(char * _destino);
Usuario* AcessarSistema(char * login, char * senha);
void ObtemSenha(char * _dest, bool login, String descricao);
int TotalUsuariosCadastrados();
void AdicionarUsuarioPadrao();
ResultadoBuscaEmArquivo* BuscaUsuarioPeloId(Usuario * usuarioDestino, int Id);
int ProximaSequenciaUsuario();
void RetornaTodosUsuariosCadastrados(ListaUsuario* lista);
void AdicionarUsuario(Usuario* usr);
Usuario* ObterNovoUsuario();
void ImprimeUsuario(Usuario* usr);
void ImprimeUsuarios(ListaUsuario* lista);
bool ExisteUsuarioComLogin(char * login);
bool GravarUsuario(Usuario* usr, bool atualizacao);
void CadastrarUsuario();
void ImprimirTodosUsuarios();
int RetornaPosicaoUsuario(ListaUsuario* lista, Usuario* usr);
ListaUsuario* criarListaUsuario();
NoUsuario* criarNoUsuario();
Usuario* criarUsuario();
#endif // USUARIO_HH
