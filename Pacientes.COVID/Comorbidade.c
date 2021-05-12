#include "Comorbidade.h"
#include <dirent.h>
/**
 * Respons�vel por criar uma nova estrutura de dados do tipo Comorbidade com os dados informados pelo usu�rio em tela.
 * @param imc Indice de Massa Muscular do paciente
 * @param sexo sexo do(a) paciente
 ***/
Comorbidade newComorbidade(int imc, Sexo sexo){
    Comorbidade _comorbidade;
    char texto[255];
    printf("   Paciente possui:\n");
    _comorbidade.Diabetico = GetBool("   Diabete? (S/N): ", 'S');

    AddCursorPosition(0,-1);
    _comorbidade.Obeso = GetBool("   Obesidade? (S/N): ", 'S');

    AddCursorPosition(0,-1);    sprintf(texto, "   Hipertens%co? (S/N): ", a_TILDE);
    _comorbidade.Hipertenso = GetBool(texto, 'S');

    AddCursorPosition(0,-1);
    _comorbidade.Tuberculoso = GetBool("   Tuberculose? (S/N): ", 'S');

    AddCursorPosition(0,-1);
    _comorbidade.HIV = GetBool("   HIV? (S/N): ", 'S');

    AddCursorPosition(0,-1);
    sprintf(texto, "   Asma ou Doen%ca Pulmonar? (S/N): ", c_DILHA);
    _comorbidade.AsmaOuDoencaPulmonar = GetBool(texto, 'S');

    AddCursorPosition(0,-1);    sprintf(texto, "   Alguma Doen%ca Renal? (S/N): ", c_DILHA);
    _comorbidade.DoencaRenal = GetBool(texto, 'S');

    AddCursorPosition(0,-1);
    sprintf(texto, "   Doen%ca no F%cgado? (S/N): ", c_DILHA, i_AGUDO);
    _comorbidade.DoencaNoFigado = GetBool(texto, 'S');

    if(sexo == Feminino){
        AddCursorPosition(0,-1);
        sprintf(texto, "   Gesta%c%co de Alto Risco? (S/N): ", c_DILHA,a_TILDE);
        _comorbidade.GestanteAltoRisco = GetBool(texto, 'S');
    }else{
        _comorbidade.GestanteAltoRisco = false;
    }

    AddCursorPosition(0,-1);
    _comorbidade.RelizouAlgumTransplante = GetBool("   Transplante? (S/N): ", 'S');

    AddCursorPosition(0,-1);
    AddCursorPosition(0,-1);
    _comorbidade.RealizouAlgumaQuimioterapia = GetBool("   Paciente Fez Quimioterapia? (S/N): ", 'S');

    AddCursorPosition(0,-1);
    sprintf(texto, "   Paciente Faz Di%clise? (S/N): ", a_AGUDO);
    _comorbidade.FazDialise = GetBool(texto, 'S');

    _comorbidade.IMC = imc;

    _comorbidade.DataDiagnostico = Agora()->Data;
    return _comorbidade;
}

/**
* Usage: Armazena a comorbidade em um arquivo no diret�rio informado com o nome especificado.
* @param _comorbidade ponteiro para a comorbidade a ser armazenada
* @param nomeArquivo ponteiro para o nome do arquivo que ir� armazenar a comorbidade
* @param diretorio ponteiro para o caminho do diret�rio onde o arquivo ser� gravado.
* @return true quando a grava��o em arquivo ocorre com sucesso.
*/
bool ArmazernarComorbidadeEmArquivo(Comorbidade * _comorbidade, char * nomeArquivo, char * diretorio){
    FILE *arquivo;
    char fileName[50] = "";
    bool retorno = true;
    strcat(fileName, diretorio);
    strcat(fileName, nomeArquivo);

    mkdir(diretorio);
    if((arquivo = fopen(fileName, "wb")) == NULL){
        retorno = false;
    }

    if(fwrite(_comorbidade, sizeof(Comorbidade), 1,arquivo)!=1){
        retorno = true;
    }

    fclose(arquivo);
    return retorno;
}

/**
 * Respons�vel por popular os dados do arquivo em uma estrutura de dados do tipo Comorbidade
 * @param nomeArquivo ponteiro para o nome completo do arquivo
 * @return Estrutura Comorbidade com os dados do arquivo
 **/
Comorbidade RetornaComorbidadeEmArquivo(char * nomeArquivo){

    FILE * fptr;
    Comorbidade comor;
    if((fptr = fopen(nomeArquivo, "rb")) == NULL) return comor;
    int i =0;
    while(fread(&comor, sizeof(Comorbidade), 1,fptr) == 1)
        i++;
    fclose(fptr);

    return comor;
}

/**
 * Respons�vel por imprimir em tela, os dados da comorbidade
 * @param comor ponteiro para a comorbidade a ser impressa
 **/
void ImprimeComorbidade(Comorbidade* comor){
    String textoImpressao = criarString(255), textoAuxiliar = criarString(150);


    sprintf(textoAuxiliar, "%d", comor->IMC);
    PadRight(' ', textoImpressao, textoAuxiliar, 62);
    printf(" |               IMC: %s|\n", textoImpressao);

    textoAuxiliar[0] = EMPTYCHAR;
    textoImpressao[0] = EMPTYCHAR;
    DataToString(textoAuxiliar, &comor->DataDiagnostico);
    PadRight(' ', textoImpressao, textoAuxiliar, 62);
    printf(" |  Data Diagn%cstico: %s|\n", o_AGUDO,textoImpressao);

    printf(" |----------------------------------------------------------------------------------|\n");
    textoAuxiliar[0] = EMPTYCHAR;
    textoImpressao[0] = EMPTYCHAR;
    CentralizarString(textoImpressao, "COMORBIDADES", 82);
    printf(" |%s|\n", textoImpressao);
    /***
    bool Diabetico;
    bool Obeso;
    bool Hipertenso;
    bool Tuberculoso;
    bool AsmaOuDoencaPulmonar;
    bool DoencaRenal;
    bool DoencaNoFigado;
    bool GestanteAltoRisco;
    bool RelizouAlgumTransplante;
    bool RealizouAlgumaQuimioterapia;
    bool FazDialise;
    bool HIV;
    **/

    if(
       !comor->Diabetico &&
       !comor->Obeso &&
       !comor->Hipertenso &&
       !comor->Tuberculoso &&
       !comor->AsmaOuDoencaPulmonar &&
       !comor->DoencaRenal &&
       !comor->DoencaNoFigado &&
       !comor->GestanteAltoRisco &&
       !comor->RealizouAlgumaQuimioterapia &&
       !comor->RelizouAlgumTransplante &&
       !comor->FazDialise &&
       !comor->HIV
       ){ //J� que n�o possui nenhuma comorbidade, informo
        textoAuxiliar[0] = EMPTYCHAR;
        textoImpressao[0] = EMPTYCHAR;
        sprintf(textoAuxiliar, "  N%co possui comorbidades.", a_TILDE);
        PadRight(' ', textoImpressao, textoAuxiliar, 82);
        printf(" |%s|\n", textoImpressao);
    }else{
        //Imprimo cada comorbidade se existente

        if(comor->AsmaOuDoencaPulmonar){
            textoAuxiliar[0] = EMPTYCHAR;
            textoImpressao[0] = EMPTYCHAR;
            sprintf(textoAuxiliar, "  Asma e/ou Doen%ca Pulmonar.", c_DILHA);
            PadRight(' ', textoImpressao, textoAuxiliar, 82);
            printf(" |%s|\n", textoImpressao);

        }

        if(comor->Diabetico){
            textoAuxiliar[0] = EMPTYCHAR;
            textoImpressao[0] = EMPTYCHAR;
            PadRight(' ', textoImpressao, "  Diabete.", 82);
            printf(" |%s|\n", textoImpressao);

        }

        if(comor->DoencaNoFigado){
            textoAuxiliar[0] = EMPTYCHAR;
            textoImpressao[0] = EMPTYCHAR;
            sprintf(textoAuxiliar, "  Doen%ca no F%cgado.",c_DILHA, i_AGUDO);
            PadRight(' ', textoImpressao, textoAuxiliar, 82);
            printf(" |%s|\n", textoImpressao);

        }

        if(comor->DoencaRenal){
            textoAuxiliar[0] = EMPTYCHAR;
            textoImpressao[0] = EMPTYCHAR;
            sprintf(textoAuxiliar, "  Doen%ca Renal.",c_DILHA);
            PadRight(' ', textoImpressao, textoAuxiliar, 82);
            printf(" |%s|\n", textoImpressao);

        }

        if(comor->FazDialise){
            textoAuxiliar[0] = EMPTYCHAR;
            textoImpressao[0] = EMPTYCHAR;
            sprintf(textoAuxiliar, "  Faz Di%clise.",a_AGUDO);
            PadRight(' ', textoImpressao, textoAuxiliar, 82);
            printf(" |%s|\n", textoImpressao);

        }

        if(comor->GestanteAltoRisco){
            textoAuxiliar[0] = EMPTYCHAR;
            textoImpressao[0] = EMPTYCHAR;
            sprintf(textoAuxiliar, "  Gesta%c%co de Alto Risco.",c_DILHA, a_TILDE);
            PadRight(' ', textoImpressao, textoAuxiliar, 82);
            printf(" |%s|\n", textoImpressao);

        }

        if(comor->Hipertenso){
            textoAuxiliar[0] = EMPTYCHAR;
            textoImpressao[0] = EMPTYCHAR;
            sprintf(textoAuxiliar, "  Hiperten%c%co.",c_DILHA, a_TILDE);
            PadRight(' ', textoImpressao, textoAuxiliar, 82);
            printf(" |%s|\n", textoImpressao);

        }

        if(comor->HIV){
            textoAuxiliar[0] = EMPTYCHAR;
            textoImpressao[0] = EMPTYCHAR;
            sprintf(textoAuxiliar, "  HIV.");
            PadRight(' ', textoImpressao, textoAuxiliar, 82);
            printf(" |%s|\n", textoImpressao);

        }

        if(comor->Obeso){
            textoAuxiliar[0] = EMPTYCHAR;
            textoImpressao[0] = EMPTYCHAR;
            sprintf(textoAuxiliar, "  Obesidade.");
            PadRight(' ', textoImpressao, textoAuxiliar, 82);
            printf(" |%s|\n", textoImpressao);

        }

        if(comor->RealizouAlgumaQuimioterapia){
            textoAuxiliar[0] = EMPTYCHAR;
            textoImpressao[0] = EMPTYCHAR;
            sprintf(textoAuxiliar, "  Realizou/Realiza Quimioterapia.");
            PadRight(' ', textoImpressao, textoAuxiliar, 82);
            printf(" |%s|\n", textoImpressao);

        }

        if(comor->RelizouAlgumTransplante){
            textoAuxiliar[0] = EMPTYCHAR;
            textoImpressao[0] = EMPTYCHAR;
            sprintf(textoAuxiliar, "  Transplante.");
            PadRight(' ', textoImpressao, textoAuxiliar, 82);
            printf(" |%s|\n", textoImpressao);

        }

        if(comor->Tuberculoso){
            textoAuxiliar[0] = EMPTYCHAR;
            textoImpressao[0] = EMPTYCHAR;
            sprintf(textoAuxiliar, "  Tuberculose.");
            PadRight(' ', textoImpressao, textoAuxiliar, 82);
            printf(" |%s|\n", textoImpressao);

        }
    }

    printf(" |==================================================================================|\n\n\n");
}
