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
void GetPassword(char * _dest);
#endif // USUARIO_H
