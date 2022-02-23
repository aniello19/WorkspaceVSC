#include "funzioniUtil.h"




/*
    CONVERTE UNA STRINGA IN MAIUSCOLO
*/
const char* toUpper(char *str){
    char *ritorno= str;
    while (*str != '\0')
    {
        *str = toupper(*str);
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
    while(c=getchar()!='\n' && c!= EOF);    //VENGONO ASSEGNATI VALORI A C DALL'INPUT BUFFER FINCHE' NON VIENE TROVATO L'INDICATORE DI END OF FILE
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
    printf(" __           ___      .______            ______   ______   ____    ____  __   _______      __    ___   \n"
            "|  |         /   \\     |   _  \\          /      | /  __  \\  \\   \\  /   / |  | |       \\    /_ |  / _ \\  \n"
            "|  |        /  ^  \\    |  |_)  |        |  ,----'|  |  |  |  \\   \\/   /  |  | |  .--.  |    | | | (_) | \n"
            "|  |       /  /_\\  \\   |   _  <         |  |     |  |  |  |   \\      /   |  | |  |  |  |    | |  \\__, |  Pasquale Raimo\n"
            "|  `----. /  _____  \\  |  |_)  |  __    |  `----.|  `--'  |    \\    /    |  | |  '--'  |    | |    / /   Aprile 2021\n"
            "|_______|/__/     \\__\\ |______/  (__)    \\______| \\______/      \\__/     |__| |_______/     |_|   /_/   \n\n");
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
    char c;
    printf("\nPREMI UN TASTO PER CONTINUARE...\n");
    clear_buffer();
    system("cls");
}
