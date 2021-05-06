#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdfix.h>
//#include "Modulos.h"
#include "Paciente.h"
int main(void)
{
    //Inicializar();

    ListaPaciente * lista = criarListaPaciente();
    AdicionarPaciente(lista, newPaciente());
    AdicionarPaciente(lista, newPaciente());
    AdicionarPaciente(lista, newPaciente());

   // OrdenarListaPorNomeAscendente(lista);

    printf("   ");
    system("pause");
    return 0;
}
