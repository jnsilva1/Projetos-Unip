#include <stdio.h>
#include <stdlib.h>
#include "Paciente.h"
#include "Usuario.h"

int main(void)
{
    //Adiciono automaticamente o usu�rio Administrador.
    AdicionarUsuarioPadrao();
    /*
    Paciente pa = newPaciente();
    ArmazenarPacienteEmArquivo(&pa);

    Paciente pac;
    GetPacienteEmArquivo(&pac, pa.Pessoa.CPF);
    */

/*
    char login[30], senha[30];
    GetString("\nInforme o usu�rio: ", login);
    ObtemSenha(senha, true);

    AcessarSistema(login, senha);*/

    Usuario USRS[TotalUsuariosCadastrados()];
    RetornaTodosUsuariosCadastrados(USRS);
    ImprimeUsuarios(USRS, TotalUsuariosCadastrados());

    system("pause");
    return 0;
}
