#include "DataHora.h"

/**
 * Respons�vel por Instanciar a data e hora atual
 * @return ponteiro para estrutuda de dados do tipo DataHora que cont�m as informa��es atuais
 **/
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

/**
 * Converte a  Data e Hora em uma String de acordo com o formato informado
 * @param dataHoraString ponteiro para a cadeia de caracteres que receber� a data e hora formatada
 * @param _dt ponteiro para a estrutura do tipo data e hora que se quer formatar
 * @param formato formato em que se quer a data/hora: ["dd/mm/aaaa hh:mm:ss", "dd/mm/aaaa hh:mm", "dd/mm/aaaa", "hh:mm:ss"]
 ***/
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

/**
 * Respons�vel por formatar a data informada em um a string
 * @param destino ponteiro para a cadeia de caracteres que ir� receber a data formatada
 * @param _dt ponteiro para a estrutura do tipo Data a ser formatada
 **/
void DataToString(char* destino, Data* _dt){
    DataHora _dts;
    _dts.Data = *_dt;

    DataHoraToString(destino,&_dts, S_DATAHORA_FORMATO_DATA);
}

/**
 * Respons�vel por formatar a hora informada em uma string
 * @param destino ponteiro para a cadeia de caracteres que ir� receber a hora formatada
 * @param _hora ponteiro para a estrutura do tipo Hora a ser formatada
 **/
void HoraToString(char * destino, Horario* _hora){
    DataHora _dts;
    _dts.Hora = *_hora;

    DataHoraToString(destino,&_dts, S_DATAHORA_FORMATO_HORAS);
}

/**
  * Verifica se o ano � bissexto
  * @param ano O Ano a ser comparado
  */
bool EhAnoBissexto(int ano){
    bool resultado = true;
    resultado = resultado && (ano % 4 == 0);
    resultado = (resultado && (ano % 100 > 0)) || (resultado && (ano % 100 == 0) && (ano % 400 == 0));
    return resultado;
}

/**
  * Retorna a quantidade de dias existentes naquele m�s de um determinado ano
  * @param mes o m�s deve estar exatamente como representamos em calend�rio, inicial 1, final 12
  * @param ano para verificar se � bissexto, afim de retornar um dia a mais quando informado m�s 2.
  */
int RetornaQuantidadeDiasNoMes(int mes, int ano){
    switch(mes){
    case 1: //Janeiro
        return 31;
        break;
    case 2: //Fevereiro
        return EhAnoBissexto(ano) ? 29 : 28;
        break;
    case 3: //Mar�o
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

/**
 * Respons�vel por instanciar uma nova estrutura do tipo Data
 * @param dia Dia
 * @param mes M�s
 * @param ano Ano
 * @return Estrutura Data com os valores informados
 **/
Data NewData(int dia, int mes, int ano){
    Data _data;
    _data.Ano = ano;
    _data.Mes = mes;
    _data.Dia = dia;
    return _data;
}

/**
 * Respons�vel por instanciar uma nova estrutura do tipo Horario
 * @param hora Hora
 * @param minuto Minuto
 * @param segundo Segundo
 * @return Estrutura Horario com os valores informados
 ***/
Horario NewHorario(int hora, int minuto, int segundo){
    Horario _horario;
    _horario.Hora = hora;
    _horario.Minuto = minuto;
    _horario.Segundo = segundo;
    return _horario;
}

/**
 * Respons�vel por instanciar uma nova estrutura do tipo DataHora
 * @param dia Dia
 * @param mes M�s
 * @param ano Ano
 * @param hora Hora
 * @param minuto Minuto
 * @param segundo Segundo
 * @return Estrutura DataHora com os valores informados
 ***/
DataHora NewDataHora(int dia, int mes, int ano, int hora, int minuto, int segundo){
    DataHora _dataHora;
    _dataHora.Data = NewData(dia, mes, ano);
    _dataHora.Hora = NewHorario(hora, minuto, segundo);
    return _dataHora;
}

/**
 * Determina se a data informada possui valores v�lidos para o tipo
 **/
bool EhUmaDataValida(Data _data){
    bool res = true;
    int UltimoDiaMes = RetornaQuantidadeDiasNoMes(_data.Mes, _data.Ano);
    res = res  && (_data.Dia > 0 && _data.Dia <= UltimoDiaMes);
    res = res  && (_data.Mes > 0 && _data.Mes <= 12);
    res = res  && _data.Ano > 1900;
    return res;
}

/**
 * Determina se o hor�rio informado possui valores v�lidos para o tipo
 ***/
bool EhUmHorarioValido(Horario _horario){
    bool res = true;
    res = res && _horario.Segundo >= 0 && _horario.Segundo <= 59;
    res = res && _horario.Minuto >= 0 && _horario.Minuto <= 59;
    res = res && _horario.Hora >= 0 && _horario.Hora <= 23;
    return res;
}

/**
 * Respons�vel por obter uma estrutura de data atrav�s da entrada do usu�rio no console
 * @param mensagem mensagem a ser apresentada para o usu�rio afim de auxili�-lo no preenchimento da informa��o desejada
 * @return estrutura Data com os dados obtidos
 **/
Data GetData(const char * mensagem){
    bool primeiroLooping = true, valido = false;
    Data _dt;

    do{
        fflush(stdin);
        if(!primeiroLooping){
            AddCursorPosition(0,-1);
            printf("  Informe uma data valida!\n");
            getch();
            AddCursorPosition(0,-1);
        }

        if(Length(mensagem) > 1)
            printf("%s", mensagem);
        else
            printf("  Informe a data (dd/mm/aaaa): ");

       scanf("%d/%d/%d", &_dt.Dia, &_dt.Mes, &_dt.Ano);
       valido = EhUmaDataValida(_dt);
       primeiroLooping = false;
    }while(!valido);

    return _dt;
}
