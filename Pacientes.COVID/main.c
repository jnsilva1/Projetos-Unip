#include <stdio.h>
#include <stdlib.h>
#include <Paciente.h>

void GetPassword(char * _dest);
int main(void)
{
    /*
    Paciente pa = newPaciente();
    ArmazenarPacienteEmArquivo(&pa);

    Paciente pac;
    GetPacienteEmArquivo(&pac, pa.Pessoa.CPF);
    */
    char senha[16];
    GetPassword(senha);

    system("pause");
    return 0;
}

void GetPassword(char * _dest){
    const int maxPasswordLength = 15;
    char password[maxPasswordLength+1],ch;
    int characterPosition = 0;

    printf("Informe a senha. Length 1-%d\n", maxPasswordLength);
    while(1){
        ch = getch();
        if(ch == ENTER_CHAR){
            break;
        }else if( ch == BLANCKSPACE_CHAR){
            if(characterPosition > 0){
                characterPosition--;
                password[characterPosition] = EMPTYCHAR;
                printf("\b \b");
            }
        }else if(ch == 32 || ch == 9){ //When user enters space / tab
            continue;
        }else{
            if(characterPosition < maxPasswordLength){
                password[characterPosition] = ch;
                characterPosition++;
                printf("*");
            }else{
                printf("\nSua senha excede a quantidade maxima de caractreses. Apenas os %d primeiros caracteres serão considerados!", maxPasswordLength);
                break;
            }
        }
    }
    password[characterPosition] = EMPTYCHAR;
    printf("\n");
    if(strlen(password) == 0){
        printf("No Password Entered.");
    }else{
        printf("Your password is %s", password);
    }
    strcpy(_dest, password);
}
