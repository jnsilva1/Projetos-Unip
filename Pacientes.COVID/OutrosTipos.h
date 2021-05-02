#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
#ifndef DEFAULT_DIR
#define DEFAULT_DIR "C:/Pacientes.Covid/"
#endif // DEFAULT_DIR
#ifndef OUTROSTIPOS_H
#ifndef ENTER_CHAR
#define ENTER_CHAR 13
#endif // ENTER_CHAR
#ifndef BLANCKSPACE_CHAR
#define BLANCKSPACE_CHAR 8
#endif // BLANCKSPACE_CHAR
#define OUTROSTIPOS_H
#define EMPTYCHAR '\0'
#define BLANKCHAR 32
#define NEWLINE '\n'

enum boolean{
    true = 1,
    false = 0
};
typedef enum boolean bool;

typedef struct resultadoBuscaEmArquivo{
    long Posicao;
    bool EncontrouRegistro;

} ResultadoBuscaEmArquivo;

typedef struct {
    char * buffer;
    int i;
    int j;
} SplitString;

int Length(char str[]);
/*
 * Function: PadLeft
 * Usage: PadLeft(preencher, _destino, original, limite); *
 */
void PadLeft(char preencher, char *_destino, char * original, int limite);
void PadRight(char preencher, char * _destino, char * original, int limite);
void CentralizarString(char * destino, char * original, int limite);
void StringUpperCase(char * str);
void StringLowerCase(char * str);
void StringCapitalize(char * str);
bool EhNumerico(int valor);
bool ContemApenasNumero(char * valores);
bool EhApenasLetra(char character);
bool ContemApenasLetras(char * cadeia);
void Concatenar(char * destino, const char * cat1, const char * cat2);
void ReplaceChar(char * _str, char oQueAlterar, char peloQueAlterar);
void FormataCPF(char * _destino, const char * cpf);
void FormataCEP(char * _destino, const char * cep);
void FormataTelefone(char * destino, int ddd, long numero, bool ehCelular);
long long Potencia(int base, int expoente);
int ConverteParaInteiro(char * valor);
long ConverteParaLongo(char * valor);
long long ConverteParaLongoLongo(char * valor);
void Substring(char * _dest, char * _source, int start, int length);
void GetString(const char * descricao, char * destino);
void GetStringLetrasApenas(const char * descricao, char * destino);
long GetLong(const char * descricao);
int GetInteiro(const char * descricao);
long long GetLongLong(const char * descricao);
int QuantidadeCaracteresPadLeftParaCentralizar(int LimiteCaracteres, char* stringParaCentralizar);
bool EhEmail(const char * email);
int StringPrimeiraPosicao(const char * fonte, char oQueProcurar);
int StringUltimaPosicao(const char * fonte, char oQueProcurar);
void GetEmail(const char * descricao, char * destino);
bool GetBool(const char * descricao, char trueChar);
double GetDouble(const char * descricao);
#endif // OUTROSTIPOS_H
