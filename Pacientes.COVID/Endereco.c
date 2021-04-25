#include "Endereco.h"

Endereco newEndereco(){
    Endereco novoEndereco;
    sprintf(novoEndereco.Complemento, "%s", "   \0");

    printf("\n");
    novoEndereco.CEP = GetLong("  Informe o CEP (numeros apenas): ");

    GetStringLetrasApenas("  Informe o Logradouro: ", novoEndereco.Logradouro);
    novoEndereco.Numero = GetInteiro("  Informe o Numero: ");
    GetString("  Informe o Complemento: ", novoEndereco.Complemento);
    GetStringLetrasApenas("  Informe o Bairro: ", novoEndereco.Bairro);
    GetStringLetrasApenas("  Informe o Cidade: ", novoEndereco.Cidade);
    GetString("  Informe o Estado (UF): ", novoEndereco.Estado);

    return novoEndereco;
}
