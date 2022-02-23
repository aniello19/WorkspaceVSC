#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "grafo.h"
#include "funzioniUtil.h"
#include "driver.h"
#include "spesa.h"


/*
    CONVERTE UNA STRINGA IN MAIUSCOLO
*/
const char* toUpper(char *str)
{
   const char *ritorno= str;
    while (*str != '\0')
    {
        *str=toUpper(*str);
        str++;
    }
    return ritorno;
}

/*
PULISCE L'INPUT BUFFER
*/
void clear_buffer()
{
    char c;
    while((c=getchar()!='\n') && (c!= EOF));    //VENGONO ASSEGNATI VALORI A C DALL'INPUT BUFFER FINCHE' NON VIENE TROVATO L'INDICATORE DI END OF FILE
}
/*
FUNZIONE CHIAMATA QUANDO VIENE RICHIESTO DI INTERROMPERE IL PROGRAMMA
*/
void gestisci_errori()
{
    exit(0);
};

void stampaTitolo()
{
    printf(
"8888888                 8888888888        d8888 88888888888 .d8888b.\n"
  "  888                   888              d88888     888    d88P  Y88b           SECONDA PROVA INTERCORSO LASD\n"
  "  888                   888             d88P888     888    Y88b.\n"
  "  888                   8888888        d88P 888     888     \"Y888b.             Pasquale Raimo\n"
  "  888                   888           d88P  888     888        \"Y88b.           Gabriele Oronos        \n"
  "  888  888888           888          d88P   888     888          \"888           Francesco Occhiello    Maggio 2021\n"
  "  888                   888         d8888888888     888    Y88b  d88P\n"
 "8888888                 8888888888 d88P     888     888     \"Y8888P\"\n");

stampaLinea(100);


}

/*
LA FUNZIONE STAMPA UNA LINEA FORMATA DAL CARATTERE '-' LUNGA QUANTO IL VALORE DEL PARAMTERO FORMALE
*/
void stampaLinea(int lunghezzaLinea)
{
    if(lunghezzaLinea!=0)
    {
        printf("-");
        stampaLinea(lunghezzaLinea-1);      //CHIAMATA RICORSIVA
    }
    else
    {
        printf("\n");
    }
}

/*
MOSTRA A SCHERMO UN MESSAGGIO. IL PROGRAMMA CONTINUERA' DOPO CHE L'UTENTE AVRA' PREMUTO UN QUALSIASI TASTO
*/
void premiTastoPerContinuare()
{
    ;
    printf("\nPREMI UN TASTO PER CONTINUARE...\n");
    clear_buffer();
    system("cls");
}

