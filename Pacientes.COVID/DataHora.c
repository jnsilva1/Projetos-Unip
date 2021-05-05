#include "DataHora.h"

///Instancia a data e hora atual
DataHora* Agora(){
    time_t tempo;
    tempo = time(NULL);
    DataHora* _dataHora = (DataHora *)malloc(sizeof(DataHora));

    struct tm SysDate = *localtime(&tempo);
    _dataHora->Data.Ano = SysDate.tm_year + 1900;
    _dataHora->Data.Mes = SysDate.tm_mon +1;
    _dataHora->Data.Dia = SysDate.tm_mday;

    _dataHora->Hora.Hora = SysDate.tm_hour;
    _dataHora->Hora.Minuto = SysDate.tm_min;
    _dataHora->Hora.Segundo = SysDate.tm_sec;

    return _dataHora;
}

/// Converte a  Data e Hora em uma String de acordo com o formato informado: ["dd/mm/aaaa hh:mm:ss", "dd/mm/aaaa hh:mm", "dd/mm/aaaa", "hh:mm:ss"]
void DataHoraToString(char * dataHoraString, DataHora* _dt,const char * formato){

        if(strcmp("dd/mm/aaaa hh:mm:ss", formato) == 0){
            sprintf(dataHoraString, "%.2d/%.2d/%d %.2d:%.2d:%.2d", _dt->Data.Dia, _dt->Data.Mes, _dt->Data.Ano, _dt->Hora.Hora, _dt->Hora.Minuto, _dt->Hora.Segundo);
        }else if(strcmp("dd/mm/aaaa hh:mm", formato) == 0){
            sprintf(dataHoraString, "%.2d/%.2d/%d %.2d:%.2d",  _dt->Data.Dia, _dt->Data.Mes, _dt->Data.Ano, _dt->Hora.Hora, _dt->Hora.Minuto);
        }else if(strcmp("dd/mm/aaaa", formato) == 0){
            sprintf(dataHoraString, "%.2d/%.2d/%d", _dt->Data.Dia, _dt->Data.Mes, _dt->Data.Ano);
        }else if(strcmp("hh:mm:ss", formato)){
            sprintf(dataHoraString, "%.2d:%.2d:%.2d", _dt->Hora.Hora, _dt->Hora.Minuto, _dt->Hora.Segundo);
        }else if(strcmp(S_DATAHORA_FORMATO_HORA, formato)){
            sprintf(dataHoraString, "%.2d:%.2d", _dt->Hora.Hora, _dt->Hora.Minuto);
        }else{
            dataHoraString[0]= '\0';
        }
}

///Retorna a data formadata para string
void DataToString(char* destino, Data* _dt){
    DataHora _dts;
    _dts.Data = *_dt;

    DataHoraToString(destino,&_dts, S_DATAHORA_FORMATO_DATA);
}

///Retorna a hora formadata para string
void HoraToString(char * destino, Horario* _hora){
    DataHora _dts;
    _dts.Hora = *_hora;

    DataHoraToString(destino,&_dts, S_DATAHORA_FORMATO_HORAS);
}

/**
  * Verifica se o ano é bissexto
  * @param ano O Ano a ser comparado
  */
bool EhAnoBissexto(int ano){
    bool resultado = true;
    resultado = resultado && (ano % 4 == 0);
    resultado = (resultado && (ano % 100 > 0)) || (resultado && (ano % 100 == 0) && (ano % 400 == 0));
    return resultado;
}

/**
  * Retorna a quantidade de dias existentes naquele mês de um determinado ano
  * @param mes o mês deve estar exatamente como representamos em calendário, inicial 1, final 12
  * @param ano para verificar se é bissexto, afim de retornar um dia a mais quando informado mês 2.
  */
int RetornaQuantidadeDiasNoMes(int mes, int ano){
    switch(mes){
    case 1: //Janeiro
        return 31;
        break;
    case 2: //Fevereiro
        EhAnoBissexto(ano) ? 29 : 28;
        break;
    case 3: //Março
        return 31;
        break;
    case 4: //Abril
        return 30;
        break;
    case 5: //Maio
        return 31;
        break;
    case 6: //Junho
        return 30;
        break;
    case 7: //Julho
        return 31;
        break;
    case 8: //Agosto
        return 31;
        break;
    case 9: //Setembro
        return 30;
        break;
    case 10: //Outubro
        return 31;
        break;
    case 11: //Novembro
        return 30;
        break;
    case 12: //Desembro
        return 31;
        break;
    default:
        return 0;
        break;
    }
}

Data NewData(int dia, int mes, int ano){
    Data _data;
    _data.Ano = ano;
    _data.Mes = mes;
    _data.Dia = dia;
    return _data;
}
Horario NewHorario(int hora, int minuto, int segundo){
    Horario _horario;
    _horario.Hora = hora;
    _horario.Minuto = minuto;
    _horario.Segundo = segundo;
    return _horario;
}
DataHora NewDataHora(int dia, int mes, int ano, int hora, int minuto, int segundo){
    DataHora _dataHora;
    _dataHora.Data = NewData(dia, mes, ano);
    _dataHora.Hora = NewHorario(hora, minuto, segundo);
    return _dataHora;
}

bool EhUmaDataValida(Data _data){
    bool res = true;
    res = res  && (_data.Dia > 0 && _data.Dia <= RetornaQuantidadeDiasNoMes(_data.Mes, _data.Ano));
    res = res  && (_data.Mes > 0 && _data.Mes <= 12);
    res = res  && _data.Ano > 1900;
    return res;
}

bool EhUmHorarioValido(Horario _horario){
    bool res = true;
    res = res && _horario.Segundo >= 0 && _horario.Segundo <= 59;
    res = res && _horario.Minuto >= 0 && _horario.Minuto <= 59;
    res = res && _horario.Hora >= 0 && _horario.Hora <= 23;
    return res;
}

Data GetData(const char * mensagem){
    bool primeiroLooping = true, valido = false;
    Data _dt;

    do{
        fflush(stdin);
        if(!primeiroLooping) printf("\n  Informe uma data valida!\n");

        if(Length(mensagem) > 1)
            printf("\n%s", mensagem);
        else
            printf("\n  Informe a data (dd/mm/aaaa): ");

       scanf("%d/%d/%d", &_dt.Dia, &_dt.Mes, &_dt.Ano);
       valido = EhUmaDataValida(_dt);
       primeiroLooping = false;
    }while(!valido);

    return _dt;
}
