/*#ifndef FUNZIONIUTIL
#define FUNZIONIUTIL
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//PULISCE L'INPUT BUFFER
void clear_buffer();

//INTERROMPE IL PROGRAMMA
void gestisci_errori();

//STAMPA IL TITOLO PRESENTE IN TUTTE LE INTERFACCE
void stampaTitolo();

//CONVERTE UNA STRINGA IN MAIUSCOLO
const char* toUpper(char *str);

//MOSTRA A SCHERMO UN MESSAGGIO. IL PROGRAMMA CONTINUERA' DOPO CHE L'UTENTE AVRA' PREMUTO UN QUALSIASI TASTO
void premiTastoPerContinuare();


//LA FUNZIONE STAMPA UNA LINEA FORMATA DAL CARATTERE '-' LUNGA QUANTO IL VALORE DEL PARAMTERO FORMALE
void stampaLinea(int lunghezzaLinea);

//#endif // FUNZIONIUTIL

