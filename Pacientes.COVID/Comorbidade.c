#include <Comorbidade.h>
#include <dirent.h>

Comorbidade newComorbidade(){
    Comorbidade _comorbidade;
    _comorbidade.Diabetico = GetBool("\n  Paciente possui Diabete? (S/N): ", 'S');
    _comorbidade.Hipertenso = GetBool("\n  Paciente possui Hipertensao? (S/N): ", 'S');
    _comorbidade.Obeso = GetBool("\n  Paciente possui Obesidade? (S/N): ", 'S');
    _comorbidade.Tuberculoso = GetBool("\n  Paciente possui Tuberculose? (S/N): ", 'S');
    if(GetBool("\n  Paciente possui alguma outra comorbidade? (S/N): ", 'S')){
       GetString("\n  Informe a comorbidade: ",_comorbidade.Outros);
    }else{
        _comorbidade.Outros[0] = EMPTYCHAR;
    }
    _comorbidade.DataDiagnostico = Agora().Data;
    return _comorbidade;
}

/**
* Usage: Armazena a comorbidade me um arquivo no diretório informado com o nome especificado.
*/
bool ArmazernarComorbidadeEmArquivo(Comorbidade * _comorbidade, char * nomeArquivo, char * diretorio){
    FILE *arquivo;
    char fileName[50] = "";
    bool retorno = true;
    strcat(fileName, diretorio);
    strcat(fileName, nomeArquivo);

    if(mkdir(diretorio) == -1){
        puts("Diretório já existe!");
    }else{
        puts("Diretório criado!");
    }
    if((arquivo = fopen(fileName, "wb")) == NULL){
        retorno = false;
    }

    if(fwrite(_comorbidade, sizeof(Comorbidade), 1,arquivo)!=1){
        retorno = true;
    }

    fclose(arquivo);
    return retorno;
}

Comorbidade RetornaComorbidadeEmArquivo(char * nomeArquivo){

    FILE * fptr;
    Comorbidade comor;
    if((fptr = fopen(nomeArquivo, "rb")) == NULL) return comor;

    while(fread(&comor, sizeof(Comorbidade), 1,fptr) == 1)
        1+1;
    fclose(fptr);

    return comor;
}
