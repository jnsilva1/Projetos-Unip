#include "Endereco.h"
#include "OutrosTipos.h"

/**
 * Responsável por criar uma nova estrutura de dados do tipo Endereço com as informações obtidas da entrada do usuário no console.
 * @return a estrutura Endereço preenchida e validada
 ***/
Endereco newEndereco(){
    Endereco novoEndereco;
    sprintf(novoEndereco.Complemento, "%s", "   \0");

    novoEndereco.CEP = GetLong("   Informe o CEP (numeros apenas): ");

    AddCursorPosition(0,-1);
    GetStringLetrasApenas("   Informe o Logradouro (sem acentos): ", novoEndereco.Logradouro, 59, false);
    AddCursorPosition(0,-1);
    novoEndereco.Numero = GetInteiro("   Informe o Numero (numeros apenas): ");
    AddCursorPosition(0,-1);
    GetString("   Informe o Complemento: ", novoEndereco.Complemento, 59, false);
    AddCursorPosition(0,-1);
    GetStringLetrasApenas("   Informe o Bairro (sem acentos): ", novoEndereco.Bairro, 29, false);
    AddCursorPosition(0,-1);
    GetStringLetrasApenas("   Informe o Cidade (sem acentos): ", novoEndereco.Cidade, 39, false);
    AddCursorPosition(0,-1);
    GetString("   Informe o Estado (UF): ", novoEndereco.Estado, 2, false);

    return novoEndereco;
}
