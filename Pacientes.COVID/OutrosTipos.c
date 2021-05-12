#include "OutrosTipos.h"
/**
 * Responsável por mover a posição do curso para os pontos X,Y informados
 * @param x ponto na posição horizontal
 * @param y ponto na posição vertical
 */
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

/**
 * Responsável incrimentar/decrementar a posição atual do cursor.
 * @param x ponto na posição horizontal
 * @param y ponto na posição vertical
 **/
void AddCursorPosition(int x, int y){
    COORD* position = GetCursorPosition();
    x += position->X;
    y += position->Y;
    GoToXY(x, y);
}

/**
 * Limpa a tela até determinada posição do console.
 * @param posInicial ponteiro para a coordenada
 **/
void LimparTelaAtePontoDeterminado(COORD* posInicial){
    while(GetCursorPosition()->Y > posInicial->Y){
            while(GetCursorPosition()->X > posInicial->X){
                AddCursorPosition(-1,0);
            }
        AddCursorPosition(0,-1);
    }
}

/**
 * Limpa todo o console e posiciona o curso no ponto inicial 0,0
 **/
void LimparTela(){
    system("cls");
}

/**
 * Retorna o ponteiro para a cordenada atual do cursor no console.
 */
COORD* GetCursorPosition(){
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE), &cbsi);
    COORD* POS = &cbsi.dwCursorPosition;
    return POS;
}

/**
 * Responsável por adicionar caracteres a esquerda até que atinja o limite total de caracteres na cadeia
 * @param preencher caracter que será incrementado à esquerda até completar o limite
 * @param _destino ponteiro para a cadeia de caracteres que receberá o preenchimento
 * @param original ponteiro para a cadeira de caracteres original
 * @param limite limite de caracteres no ponteiro de destino
 **/
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

/**
 * Responsável por adicionar caracteres a direita até que atinja o limite total de caracteres na cadeia
 * @param preencher caracter que será incrementado à direita até completar o limite
 * @param _destino ponteiro para a cadeia de caracteres que receberá o preenchimento
 * @param original ponteiro para a cadeira de caracteres original
 * @param limite limite de caracteres no ponteiro de destino
 */
void PadRight(char preencher, char * _destino, char * original, int limite){
    int i, tamanho = Length(original);
    strcpy(_destino, original);

    for(i = tamanho; i < limite; i++){
        _destino[i] = preencher;
    }
    _destino[i] = '\0';
}

/**
 * Conta a quantidade de caracteres existem na cadeia
 * @param str cadeia de caracteres a ser examinado
 * @return quantidade de caracteres
 */
int Length(char str[]){
    int len = 0;

    while(str[len] != '\0'){
        len++;
    }
    return len;
}

/**
 * Centraliza um determinado texto baseando no tamanho total do campo em que ele vá ocupar.
 * @param destino ponteiro para a cadeia de caracteres que receberá o preenchimento
 * @param original ponteiro para a cadeia de caracteres original que será centralizada
 * @param limite limite de caracteres
 **/
void CentralizarString(char * destino, char * original, int limite){
    char stringAuxiliar[limite];
    PadLeft(' ', stringAuxiliar, original, QuantidadeCaracteresPadLeftParaCentralizar(limite,original));
    PadRight(' ', destino, stringAuxiliar, limite);
}

/**
 * Coloca a cadeia de caracteres em Caixa Alta
 * @param str ponteiro para a cadeia de caracteres a ser alterada
 **/
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

/**
 * Coloca a cadeia de caracteres em Caixa Baixa
 * @param str ponteiro para a cadeia de caracteres a ser alterada
 */
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

/**
 * Coloca a cadeia de caracteres em Capitalização
 * @param str ponteiro para a cadeia de caracteres a ser alterada
 **/
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

/**
 * Determina se um determinado caracter representa um valor numérico
 * @param valor carectere a ser verificado
 **/
bool EhNumerico(int valor){
    /*Caso seja em char*/
    int valor2 = valor - 48;
    if((valor >= 0 && valor <= 9) || (valor2 >= 0 && valor2 <= 9)){
        return true;
    }
    return false;
}

/**
 * Determina se uma determinada cadeia de caracteres representam valores numéricos
 * @param valores ponteiro para cadeia de carcateres a serem verificados
 **/
bool ContemApenasNumero(char * valores){
    bool resultado = true;
    int i = 0;
    while(valores[i] != '\0'){
        resultado = resultado && EhNumerico((int)valores[i]);
        i++;
    }
    return resultado;
}

/**
 * Determina se o caractere informado se refere apenas a literal
 * @param character carectere a ser verificado
 **/
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

/**
 * Determina se a cadeia de caracteres informados se referem apenas a letras
 * @param cadeia ponteiro para cadeia de carcateres a serem verificados
 **/
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

/**
 * Junta duas cadeias de caracteres em uma de destino
 * @param destino poteiro para a cadeia de caracteres que receberá a junção
 * @param cat1 poteiro para a cadeia de caracteres que junção será feita a esquerda
 * @param cat2 poteiro para a cadeia de caracteres que junção será feita a direita
 **/
void Concatenar(char * destino, const char * cat1, const char * cat2){
    strcat(destino, cat1);
    strcat(destino, cat2);
}

/**
 * Forma o telefone para ser apresentado em tela
 * @param destino ponteiro para a cadeia de caracteres que receberá o telefone formatado
 * @param ddd prefixo do telefone
 * @param numero número do telefone
 * @param ehCelular telefone informado é celular?
 **/
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

/**
 * Formata o CPF para ser exibido em tela
 * @param _destino ponteiro para cadeia de caracteres que receberá o CPF formatado
 * @param cpf ponteiro para o CPF a ser formatado
 **/
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

/**
 * Formata o CEP para ser exibido em tela
 * @param _destino ponteiro para cadeia de caracteres que receberá o CEP formatado
 * @param cep ponteiro para o CEP a ser formatado
 **/
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

/**
 * Troca um determinado caracter por outro
 * @param _str ponteiro para a cadeia de caracteres que contem o caracter que deseja alterar
 * @param oQueAlterar caracter que deseja alterar
 * @param peloQueAlterar caracter que será aplicado no lugar do que deseja alterar
 **/
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

/**
 * Determina a quantidade de caracteres que são necessários serem adicionados para centralizar um texto
 * @param LimiteCaracteres o tamanho da cadeia de caracteres que receberá o texto centralizado
 * @param stringParaCentralizar ponteiro para a cadeia de caracteres que será centralizada
 **/
int QuantidadeCaracteresPadLeftParaCentralizar(int LimiteCaracteres, char* stringParaCentralizar){
    int tamanhoString = Length(stringParaCentralizar);
    return ((LimiteCaracteres - tamanhoString) / 2) + tamanhoString;
}

/**
 * Realiza o Cálculo de potência
 * @param base valor base para a exponenciação
 * @param expoente valor expoente
 */
long long Potencia(int base, int expoente){
    if(expoente == 0)
        return 1; //Quando o expoente é zero, o resultado sempre é 1
    else
        return (long long)(base * Potencia(base, expoente - 1));
}

/**
 * Converte uma cadeia de caracteres em um tipo inteiro
 * @param valor ponteiro para a cadeia de caracteres a ser convertida para inteiro
 * @return resultado da conversão
 **/
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

/**
 * Converte uma cadeia de caracteres em um tipo inteiro longo
 * @param valor ponteiro para a cadeia de caracteres a ser convertida para inteiro longo
 * @return resultado da conversão
 **/
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

/**
 * Converte uma cadeia de caracteres em um tipo inteiro muito longo
 * @param valor ponteiro para a cadeia de caracteres a ser convertida para inteiro muito longo
 * @return resultado da conversão
 **/
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

/**
 * Obtem um valor longo da entrada do console
 * @param descricao Descrição a ser exibida para usuário em tela, para auxíliá-lo a passar o valor de entrada conforme o esperado.
 * @return Valor Inteiro Longo
 **/
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

/**
 * Obtem um valor inteiro da entrada do console
 * @param descricao Descrição a ser exibida para usuário em tela, para auxíliá-lo a passar o valor de entrada conforme o esperado.
 * @return Valor Inteiro
 **/
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

/**
 * Obtem um valor inteir muito longo da entrada do console
 * @param descricao Descrição a ser exibida para usuário em tela, para auxíliá-lo a passar o valor de entrada conforme o esperado.
 * @return Valor Inteiro Muito Longo
 **/
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

/**
 * Responsável por copiar um trecho da cadeia de caracteres a partir de um determinado ponto e numa determinada quantidade de iteracoes
 * @param _dest ponteiro para a cadeia de caracteres de destino
 * @param _source ponteiro para a cadeia de caracteres de onde será obitida o trecho desejado
 * @param length quantidade de iterações/ quantidade de caracteres a serem copiados.
 * @return nada
 **/
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

/**
 * Determina se a cadeia de caracteres informada se refere a um e-mail
 * @param email ponteiro para cadeia de caracteres a ser verificada
 **/
bool EhEmail(const char * email){
    int tamanho = Length(email);
    bool res = true;

    res = res && tamanho > 0;
    res = res && tamanho > StringUltimaPosicao(email, '.') && StringUltimaPosicao(email, '.') > 1;
    res = res && tamanho > StringUltimaPosicao(email, '@') && StringUltimaPosicao(email, '@') > 1;

    return res;
}

/**
 * Responsável por indicar a primeira posição de um caractere na cadeia
 * param fonte cadeia de caractere a ser percorrida a fim de localizar a posição
 * param oQueProcurar o caractere que se deseja encontra
 * return posição do caractere, será -1 quando não encontrado.
 **/
int StringPrimeiraPosicao(const char * fonte, char oQueProcurar){
    int indice = 0;
    do{
        if(fonte[indice] == oQueProcurar) return indice;
        indice++;
    }while(fonte[indice] != '\0');
    return -1;
}

/**
 * Responsável por indicar a última posição de um caractere na cadeia
 * param fonte cadeia de caractere a ser percorrida a fim de localizar a posição
 * param oQueProcurar o caractere que se deseja encontra
 * return posição do caractere, será -1 quando não encontrado.
 **/
int StringUltimaPosicao(const char * fonte, char oQueProcurar){
    int indice = Length(fonte);
    do{
        if(fonte[indice] == oQueProcurar) return indice;
        indice--;
    }while(fonte[indice] != '\0');
    return -1;
}

/**
 * Responsável por obter uma cadeia de caracteres que representa um e-mail
 * @param descricao Descrição a ser exibida para usuário em tela, para auxíliá-lo a passar o valor de entrada conforme o esperado.
 * @param destino ponteiro para a cadeia de caracteres que irá armazenar o e-mail
 */
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

/**
 * Responsavel por obter um valor boleano da entrada do console pelo usuário
 * @param descricao Descrição a ser exibida para usuário em tela, para auxíliá-lo a passar o valor de entrada conforme o esperado.
 * @param trueChar carcatere que representa o valor verdadeiro digitado pelo usuário
 * @return valor resultante da entrada do usuário de acordo com o tipo esperado.
 */
bool GetBool(const char * descricao, char trueChar){
    bool res;
    fflush(stdin);
    printf(descricao);
    char entrada = getchar();
    res = (entrada == trueChar || (entrada - 32) == trueChar);
    return res;
}

/**
 * Responsavel por obter um valor double da entrada do console pelo usuário
 * @param descricao Descrição a ser exibida para usuário em tela, para auxíliá-lo a passar o valor de entrada conforme o esperado.
 * @param min ponteiro para o valor mínimo esperado que o usuário informe. Deve ser NULL quando não se deseja aplicar esta regra.
 * @param max ponteiro para o valor máximo esperado que o usuário informe. Deve ser NULL quando não se deseja aplicar esta regra.
 * @return valor resultante da entrada do usuário de acordo com o tipo esperado.
 **/
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

/**
 * Responsável por criar o ponteiro para um nó de String
 * @param capacidade capacidade que a cadeia de caracteres deve suportar
 * @return ponteiro criado
 **/
IString* criarNoString(int capacidade){
    IString* no = (IString*)malloc(sizeof(IString));
    no->atual = criarString(capacidade);
    no->proximo = NULL;
    return no;
}

/**
 * Responsável por criar o ponteiro para uma String
 * @param capacidade capacidade que a cadeia de caracteres deve suportar
 * @return ponteiro criado
 **/
String criarString(int capacidade){
    String re = (String)malloc((capacidade + 1)*sizeof(char));
    re[0] = EMPTYCHAR;
    return re;
}

/**
 * Responsável por criar o diretório padrão
 **/
void InicializarDiretorioPadrao(){
    mkdir(DEFAULT_DIR);
}
