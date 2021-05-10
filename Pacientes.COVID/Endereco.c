#include "Endereco.h"

Endereco newEndereco(){
    Endereco novoEndereco;
    sprintf(novoEndereco.Complemento, "%s", "   \0");

    novoEndereco.CEP = GetLong("   Informe o CEP (numeros apenas): ");

    AddCursorPosition(0,-1);
    GetStringLetrasApenas("   Informe o Logradouro (sem acentos): ", novoEndereco.Logradouro, 59);
    AddCursorPosition(0,-1);
    novoEndereco.Numero = GetInteiro("   Informe o Numero (numeros apenas): ");
    AddCursorPosition(0,-1);
    GetString("   Informe o Complemento: ", novoEndereco.Complemento, 59);
    AddCursorPosition(0,-1);
    GetStringLetrasApenas("   Informe o Bairro (sem acentos): ", novoEndereco.Bairro, 29);
    AddCursorPosition(0,-1);
    GetStringLetrasApenas("   Informe o Cidade (sem acentos): ", novoEndereco.Cidade, 39);
    AddCursorPosition(0,-1);
    GetString("   Informe o Estado (UF): ", novoEndereco.Estado, 2);

    return novoEndereco;
}
