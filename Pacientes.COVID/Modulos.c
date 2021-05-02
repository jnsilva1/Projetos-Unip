#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Modulos.h"
#include "OutrosTipos.h"
#include "Usuario.h"

void Inicializar(){
    char senha[16], login[50];
    GoToXY(0,0);
    printf(" |==================================================================================|\n");
    GoToXY(0,1);
    printf(" |                                LUNICARE - COVID-19                               |\n");
    GoToXY(0,2);
    printf(" |==================================================================================|\n");

    do{

        GoToXY(0,3);
        GetString("\n   Informe o login: ", login);
        if(strlen(login) == 0) printf("   Nenhum login informado.");
    }while(strlen(login) == 0);

    do{

        GoToXY(0,4);
        printf("  ");
        ObtemSenha(senha, true);
    }while(strlen(senha) ==0);

}
