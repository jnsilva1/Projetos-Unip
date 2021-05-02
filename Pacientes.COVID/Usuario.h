#include <stdio.h>
#include <stdlib.h>
#include "OutrosTipos.h"
#ifndef USUARIO_H
#define USUARIO_H
typedef struct usuario {
    int Id;
    char Login[30];
    char Nome[50];
    char Senha[17];
} Usuario;
/*
bool AdicionarUsuario(Usuario * _usuario);
bool RemoverUsuario(Usuario * _usuario);
bool EncontrarUsuario(Usuario * _usuario, char * loginName, char * senha);
*/
void ObtemNomeCompletoArquivoDeUsuarios(char * _destino);
Usuario AcessarSistema(char * login, char * senha);
void ObtemSenha(char * _dest, bool login);
int TotalUsuariosCadastrados();
void AdicionarUsuarioPadrao();
ResultadoBuscaEmArquivo BuscaUsuarioPeloId(Usuario * usuarioDestino, int Id);
int ProximaSequenciaUsuario();
void RetornaTodosUsuariosCadastrados(Usuario usrs[]);
void AdicionarUsuario(Usuario usr);
Usuario ObterNovoUsuario();
void ImprimeUsuario(Usuario usr);
void ImprimeUsuarios(Usuario usrs[], int tamanho);
bool ExisteUsuarioComLogin(char * login);
bool GravarUsuario(Usuario usr, bool atualizacao);
void CadastrarUsuario();
void ImprimirTodosUsuarios();
#endif // USUARIO_H
