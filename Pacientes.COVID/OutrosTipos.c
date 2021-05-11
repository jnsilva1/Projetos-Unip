#include "OutrosTipos.h"
void GoToXY(int x, int y) {
    COORD c;
    c.X = (SHORT)x;
    c.Y = (SHORT)y;
    printf("                                                                                                                                                                                       ");
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE), c);
    printf("                                                                                                                                                                                       ");
    fflush(stdin);
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE), c);
}

void AddCursorPosition(int x, int y){
    COORD* position = GetCursorPosition();
    x += position->X;
    y += position->Y;
    GoToXY(x, y);
}

void LimparTelaAtePontoDeterminado(COORD* posInicial){
    while(GetCursorPosition()->Y > posInicial->Y){
            while(GetCursorPosition()->X > posInicial->X){
                AddCursorPosition(-1,0);
            }
        AddCursorPosition(0,-1);
    }
}

void LimparTela(){
    system("cls");
}

COORD* GetCursorPosition(){
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE), &cbsi);
    COORD* POS = &cbsi.dwCursorPosition;
    return POS;
}

void PadLeft(char preencher, char *_destino, char * original, int limite){
    int strSize = (limite - Length(original)), t = limite + 1;
    int i;
    char copia[t];
    strcpy(copia, original);
    for(i=0; i < strSize; i++){
        _destino[i]=preencher;
    }
    _destino[strSize]= '\0';
    strcat(_destino, copia);
}

void PadRight(char preencher, char * _destino, char * original, int limite){
    int i, tamanho = Length(original);
    strcpy(_destino, original);

    for(i = tamanho; i < limite; i++){
        _destino[i] = preencher;
    }
    _destino[i] = '\0';
}

int Length(char str[]){
    int len = 0;

    while(str[len] != '\0'){
        len++;
    }
    return len;
}

void CentralizarString(char * destino, char * original, int limite){
    char stringAuxiliar[limite];
    PadLeft(' ', stringAuxiliar, original, QuantidadeCaracteresPadLeftParaCentralizar(limite,original));
    PadRight(' ', destino, stringAuxiliar, limite);
}

void StringUpperCase(char * str){
    char OFFSET = 'a' - 'A';
    int tamanho = 0;

    while(str[tamanho] != '\0'){
        if((str[tamanho] >= 'a' && str[tamanho] <= 'z') || (str[tamanho] >= 'à' && str[tamanho] <= 'ý')){
            str[tamanho] -= OFFSET;
        }
        tamanho++;
    }
}

void StringLowerCase(char * str){
    char OFFSET = 'a' - 'A';
    int tamanho = 0;

    while(str[tamanho] != '\0'){
        if((str[tamanho] >= 'A' && str[tamanho] <= 'Z') || (str[tamanho] >= 'À' && str[tamanho] <= 'Ý')){
            str[tamanho] += OFFSET;
        }
        tamanho++;
    }
}

void StringCapitalize(char * str){
    char OFFSET = 'a' - 'A';
    int tamanho = 0;
    while(str[tamanho] != '\0'){
        if(((tamanho == 0 && str[tamanho] != BLANKCHAR) || (str[tamanho - 1] == BLANKCHAR)) && ((str[tamanho] >= 'a' && str[tamanho] <= 'z') || (str[tamanho] >= 'à' && str[tamanho] <= 'ý'))){
            str[tamanho] -= OFFSET;
        }else if((str[tamanho] >= 'A' && str[tamanho] <= 'Z') || (str[tamanho] >= 'À' && str[tamanho] <= 'Ý')){
            str[tamanho] += OFFSET;
        }
        tamanho++;
    }
}

bool EhNumerico(int valor){
    /*Caso seja em char*/
    int valor2 = valor - 48;
    if((valor >= 0 && valor <= 9) || (valor2 >= 0 && valor2 <= 9)){
        return true;
    }
    return false;
}

bool ContemApenasNumero(char * valores){
    bool resultado = true;
    int i = 0;
    while(valores[i] != '\0'){
        resultado = resultado && EhNumerico((int)valores[i]);
        i++;
    }
    return resultado;
}

bool EhApenasLetra(char character){
        char EH = 'é';

    if(((character >= 'a' || character >= 'A') && (character <= 'z' || character <= 'Z')) ||
       character == 'Ç' ||
       character == 'ü' ||
       character == 'é' ||
       character == 'É'
       ){
        return true;
    }
    return false;
}

bool ContemApenasLetras(char * cadeia){
    bool resultado = true;
    int i = 0;
    while(cadeia[i] != '\0'){
        if(cadeia[i] != BLANKCHAR){
            resultado = resultado && EhApenasLetra(cadeia[i]);
        }
        i++;
    }
    return resultado;
}

void Concatenar(char * destino, const char * cat1, const char * cat2){
    strcat(destino, cat1);
    strcat(destino, cat2);
}

void FormataTelefone(char * destino, int ddd, long numero, bool ehCelular){
    char num[16], tel[26];
    sprintf(num, "%ld", numero);
    if(ehCelular){
        sprintf(tel, "Telefone: (%i) %c.%c%c%c%c-%c%c%c%c", ddd, num[0], num[1], num[2], num[3], num[4], num[5], num[6], num[7], num[8]);
    }else{
        sprintf(tel,"Telefone: (%i) %c%c%c%c-%c%c%c%c", ddd, num[0], num[1], num[2], num[3], num[4], num[5], num[6], num[7]);
    }
    strcpy(destino, tel);
}

void FormataCPF(char * _destino, const char * cpf)
{
    char str[20], cpfFormatado[20];
    int i, j = 0;
    strcpy(str, cpf);
    ReplaceChar(str, '.', EMPTYCHAR);
    ReplaceChar(str, '-', EMPTYCHAR);

    for(i = 0; i < 11; i++){
        if(i == 3 || i == 6){
            cpfFormatado[j] = '.';
            j++;
        }else if(i == 9){
            cpfFormatado[j] = '-';
             j++;
        }
        cpfFormatado[j] = str[i];
        j++;
    }
    cpfFormatado[j] = '\0';
    strcpy(_destino, cpfFormatado);
}

void FormataCEP(char * _destino, const char * cep){
    char str[20], cepFormatado[20];
    int i, j = 0;
    strcpy(str, cep);
    ReplaceChar(str, '-', EMPTYCHAR);
    ReplaceChar(str, '.', EMPTYCHAR);
    PadLeft('0', str, str, 8);

    for(i = 0; i < 10; i++){
        if(i == 5){
            cepFormatado[j] = '-';
            j++;
        }
        cepFormatado[j] = str[i];
        j++;
    }
    cepFormatado[j] = '\0';
    strcpy(_destino, cepFormatado);
}

void ReplaceChar(char * _str, char oQueAlterar, char peloQueAlterar)
{
    int indice = 0;
    while(_str[indice] != '\0'){
            if(_str[indice] == oQueAlterar){
                    if(peloQueAlterar == EMPTYCHAR){
                        int j = indice;
                        while(_str[j] != EMPTYCHAR){
                            _str[j] = _str[j + 1];
                            j++;
                        }
                    }else{
                        _str[indice] = peloQueAlterar;
                    }
            }
        indice++;
    }
}


int QuantidadeCaracteresPadLeftParaCentralizar(int LimiteCaracteres, char* stringParaCentralizar){
    int tamanhoString = Length(stringParaCentralizar);
    return ((LimiteCaracteres - tamanhoString) / 2) + tamanhoString;
}

/**
    Realiza o Cálculo de potência
*/
long long Potencia(int base, int expoente){
    if(expoente == 0)
        return 1; //Quando o expoente é zero, o resultado sempre é 1
    else
        return (long long)(base * Potencia(base, expoente - 1));
}

int ConverteParaInteiro(char * valor){
    //Se não contém apenas número, retorno zero
    if(!ContemApenasNumero(valor))
        return 0;

    int tamanho = Length(valor), percorrido = 0, resultado = 0;
    for(int i = tamanho - 1; i >= 0; i--){
        if(valor[i] != EMPTYCHAR && valor[i] != BLANKCHAR){
            resultado = resultado + (((int)valor[i] - 48) * Potencia(10, percorrido));
            percorrido++;
        }
    }

    return resultado;
}

long ConverteParaLongo(char * valor){
    //Se não contém apenas número, retorno zero
    if(!ContemApenasNumero(valor))
        return 0;

    int tamanho = Length(valor), percorrido = 0;
    long resultado = 0;
    for(int i = tamanho - 1; i >= 0; i--){
        if(valor[i] != EMPTYCHAR && valor[i] != BLANKCHAR){
            resultado = resultado + (((int)valor[i] - 48) * Potencia(10, percorrido));
            percorrido++;
        }
    }

    return resultado;
}

long long ConverteParaLongoLongo(char * valor){
    //Se não contém apenas número, retorno zero
    if(!ContemApenasNumero(valor))
        return 0;

    int tamanho = Length(valor), percorrido = 0;
    long long resultado = 0;
    for(int i = tamanho - 1; i >= 0; i--){
        if(valor[i] != EMPTYCHAR && valor[i] != BLANKCHAR){
            resultado = (long long)(resultado + (((int)valor[i] - 48) * Potencia(10, percorrido)));
            percorrido++;
        }
    }

    return resultado;
}

/**
  * Obtém uma string da entrada do usuário
  * @param descricao Texto a ser exibido para usuário, auxiliando-o a entender o que se pede.
  * @param destino Buffer/Ponteiro de destino da string obtida da entrada
  */
void GetString(const char * descricao, char * destino, int maxLength){
    if(maxLength <= 0) maxLength = (sizeof(*destino)/sizeof(destino[0]));
    fflush(stdin);
    printf("%s", descricao);
    int input, len = -1;
    while((input = getchar()) != EOF && len <= maxLength){
        len++;
        if(input == NEWLINE)
            break;

        destino[len] = (char)input;
    }
    //scanf("%[^\n]s", destino);
    destino[len] = '\0';

}
/**
  * Obtém uma string da entrada do usuário e realiza a validação se contém apenas letras válidas
  * @param descricao Texto a ser exibido para usuário, auxiliando-o a entender o que se pede.
  * @param destino Buffer/Ponteiro de destino da string obtida da entrada
  */
void GetStringLetrasApenas(const char * descricao, char * destino, int maxLength){
    bool primeiroLooping = true, valido = false;
    do{
        if(!primeiroLooping){
            AddCursorPosition(0,-1);
            printf("   Informe apenas letras (sem acentos)!\n");
            getch();
            AddCursorPosition(0,-1);
        }

        GetString(descricao, destino, maxLength);
        valido = ContemApenasLetras(destino);
        primeiroLooping = false;
    }while(!valido);
}

long GetLong(const char * descricao){
    char stringLong[16];
    bool primeiroLooping = true, valido = false;
    do{
        if(!primeiroLooping){
            AddCursorPosition(0,-1);
            printf("   Informe apenas numeros!\n");
            getch();
            AddCursorPosition(0,-1);
        }
        GetString(descricao, stringLong, 15);
        ReplaceChar(stringLong, '-', EMPTYCHAR);
        ReplaceChar(stringLong, '.', EMPTYCHAR);
        ReplaceChar(stringLong, ',', EMPTYCHAR);
        valido = ContemApenasNumero(stringLong);
        primeiroLooping = false;
    }while(!valido);
    return ConverteParaLongo(stringLong);
}

int GetInteiro(const char * descricao){
     char stringInteiro[6];
    bool primeiroLooping = true, valido = false;
    do{
        if(!primeiroLooping){
            AddCursorPosition(0,-1);
            printf("   Informe apenas numeros!\n");
            getch();
            AddCursorPosition(0,-1);
        }
        GetString(descricao, stringInteiro, 5);
        ReplaceChar(stringInteiro, '-', EMPTYCHAR);
        ReplaceChar(stringInteiro, '.', EMPTYCHAR);
        ReplaceChar(stringInteiro, ',', EMPTYCHAR);
        valido = ContemApenasNumero(stringInteiro);
        primeiroLooping = false;
    }while(!valido);
    return ConverteParaInteiro(stringInteiro);
}

long long GetLongLong(const char * descricao){
    char stringLong[16];
    bool primeiroLooping = true, valido = false;
    do{
        if(!primeiroLooping){
            AddCursorPosition(0,-1);
            printf("   Informe apenas numeros!\n");
            getch();
            AddCursorPosition(0,-1);
        }
        GetString(descricao, stringLong, 15);
        ReplaceChar(stringLong, '-', EMPTYCHAR);
        ReplaceChar(stringLong, '.', EMPTYCHAR);
        valido = ContemApenasNumero(stringLong);
        primeiroLooping = false;
    }while(!valido);
    return ConverteParaLongoLongo(stringLong);
}

void Substring(char * _dest, char * _source, int start, int length){
    _dest[0] = EMPTYCHAR;
    if(length < 0) length = strlen(_source);
    int pos = 0;
    for(int i = 0; i < length; i++){
        if(_source[start + i] != '\0'){
            _dest[i] = _source[start + i];
            pos++;
        }
    }
    _dest[pos] = '\0';
}

bool EhEmail(const char * email){
    int tamanho = Length(email);
    bool res = true;

    res = res && tamanho > 0;
    res = res && tamanho > StringUltimaPosicao(email, '.') && StringUltimaPosicao(email, '.') > 1;
    res = res && tamanho > StringUltimaPosicao(email, '@') && StringUltimaPosicao(email, '@') > 1;

    return res;
}

int StringPrimeiraPosicao(const char * fonte, char oQueProcurar){
    int indice = 0;
    do{
        if(fonte[indice] == oQueProcurar) return indice;
        indice++;
    }while(fonte[indice] != '\0');
    return -1;
}

int StringUltimaPosicao(const char * fonte, char oQueProcurar){
    int indice = Length(fonte);
    do{
        if(fonte[indice] == oQueProcurar) return indice;
        indice--;
    }while(fonte[indice] != '\0');
    return -1;
}

void GetEmail(const char * descricao, char * destino){
    bool primeiroLooping = true, valido = true;

    do{
        if(!primeiroLooping) {
            AddCursorPosition(0,-1);
            printf("   Informe um e-mail valido!\n");
            getch();
            AddCursorPosition(0,-1);
        }

        GetString(descricao, destino, 59);
        valido = EhEmail(destino);

        primeiroLooping = false;
    }while(!valido);
}

bool GetBool(const char * descricao, char trueChar){
    bool res;
    fflush(stdin);
    printf(descricao);
    char entrada = getchar();
    res = (entrada == trueChar || (entrada - 32) == trueChar);
    return res;
}

double GetDouble(const char * descricao, double* min, double* max){
    char sDouble[16];
    String parteInteira = criarString(10), parteDecimal=criarString(10);
    bool valido = true, primeiroLooping = true;
    do{
        valido = true;
        if(!primeiroLooping){
            AddCursorPosition(0,-1);
            printf("   Valor informado inv%clido.\n",160);
            getch();
            AddCursorPosition(0,-1);
        }
        GetString(descricao, sDouble, 16);
        ReplaceChar(sDouble, ',', '.');
        Substring(parteInteira, sDouble, 0, StringPrimeiraPosicao(sDouble, '.'));
        if(StringPrimeiraPosicao(sDouble, '.') >= 0)
            Substring(parteDecimal, sDouble, StringPrimeiraPosicao(sDouble, '.') + 1, 4);
        valido = ContemApenasNumero(parteInteira) && (ContemApenasNumero(parteDecimal) || StringPrimeiraPosicao(sDouble, '.') == -1);
        primeiroLooping = false;
    }while(!valido);

    int tamanhoDecimal = strlen(parteDecimal);
    double valor = 0;
    valor += (double)ConverteParaInteiro(parteDecimal) / (double)Potencia(10,tamanhoDecimal);
    valor += ConverteParaInteiro(parteInteira);

    /**
        Valido o valor mínimo e o valor máximo.
    */
    if(min != NULL || max != NULL){

        if(min != NULL && max != NULL){ //Valida máximo e mínimo
            if(!(valor >= *min && valor <= *max)){
                AddCursorPosition(0,-1);
                printf("   Informe um valor entre %.2f e $.2f.\n", *min, *max);
                getch();
                AddCursorPosition(0,-1);
                valor = GetDouble(descricao, min, max);
            }
        }else if(min != NULL && max == NULL){//valida valor mínimo
            if(!(valor >= *min)){
                AddCursorPosition(0,-1);
                printf("   Informe um valor maior ou igual a %.2f.\n", *min);
                getch();
                AddCursorPosition(0,-1);
                valor = GetDouble(descricao, min, max);
            }
        }else if(min == NULL && max != NULL){//valida valor máximo
            if(!(valor <= *max)){
                AddCursorPosition(0,-1);
                printf("   Informe um valor menor ou igual a %.2f.\n", *max);
                getch();
                AddCursorPosition(0,-1);
                valor = GetDouble(descricao, min, max);
            }
        }
    }

    return valor;
}

IString* criarNoString(int capacidade){
    IString* no = (IString*)malloc(sizeof(IString));
    no->atual = criarString(capacidade);
    no->proximo = NULL;
    return no;
}

String criarString(int capacidade){
    String re = (String)malloc((capacidade + 1)*sizeof(char));
    re[0] = EMPTYCHAR;
    return re;
}

void InicializarDiretorioPadrao(){
    mkdir(DEFAULT_DIR);
}
