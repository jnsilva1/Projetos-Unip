#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef DATAHORA_H
#define DATAHORA_H
#include "OutrosTipos.h"
#ifndef S_DATAHORA_FORMATO_DATAHORAS
#define S_DATAHORA_FORMATO_DATAHORAS "dd/mm/aaaa hh:mm:ss"
#endif // S_DATAHORA_FORMATO_DATAHORAS
#ifndef S_DATAHORA_FORMATO_DATAHORA
#define S_DATAHORA_FORMATO_DATAHORA "dd/mm/aaaa hh:mm"
#endif // S_DATAHORA_FORMATO_DATAHORA
#ifndef S_DATAHORA_FORMATO_DATA
#define S_DATAHORA_FORMATO_DATA "dd/mm/aaaa"
#endif // S_DATAHORA_FORMATO_DATA
#ifndef S_DATAHORA_FORMATO_HORAS
#define S_DATAHORA_FORMATO_HORAS "hh:mm:ss"
#endif // S_DATAHORA_FORMATO_HORAS
#ifndef S_DATAHORA_FORMATO_HORA
#define S_DATAHORA_FORMATO_HORA "hh:mm"
#endif // S_DATAHORA_FORMATO_HORA

typedef struct _data {
    int Dia;
    int Mes;
    int Ano;
} Data;

typedef struct horario{
    int Hora;
    int Minuto;
    int Segundo;
} Horario;

typedef struct dataHora {
    Data Data;
    Horario Hora;
} DataHora;

DataHora Agora();
void DataHoraToString(char * dataHoraString, DataHora* _dt,const char * formato);
void DataToString(char* destino, Data* _dt);
void HoraToString(char * destino, Horario* _hora);
bool EhAnoBissexto(int ano);
int RetornaQuantidadeDiasNoMes(int mes, int ano);
Data NewData(int dia, int mes, int ano);
Horario NewHorario(int hora, int minuto, int segundo);
DataHora NewDataHora(int dia, int mes, int ano, int hora, int minuto, int segundo);
bool EhUmaDataValida(Data _data);
bool EhUmHorarioValido(Horario _horario);
Data GetData(const char * mensagem);
#endif // DATAHORA_H
