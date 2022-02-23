#ifndef OPERATORE
#define OPERATORE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef struct operatore
{
    char pin[5];
    char password[20];
    struct operatore *prev;
    struct operatore *next;
} Operatore;

//INSERISCE IL NUOVO OPERATORE IN TESTA ALLA LISTA
void inserimentoInTestaOperatore(Operatore ** testa, char *pinInput, char *passwordInput);

//PRENDE IN INGRESSO IL NUOVO NODO, IL PRECEDENTE, IL SUCCESSIVO E LI COLLEGA
void inserimentoNodoOperatore(Operatore ** newNode, Operatore * prevNode, Operatore *nextNode, char *pinInput, char *passwordInput);

//RECUPERA GLI OPERATORI DAL FILE DI TESTO E LI INSERISCE ALL'INTERNO DELLA STRUTTURA DINAMICA
void riempiListaOperatori(FILE * fPtr, Operatore * * testa);

//RECUPERA OPERATORI DALLA STRUTTURA DINAMICA E LI SALVA SUL FILE DI TESTO
void creaFileOperatori(FILE * fPtr, Operatore *testa);

//VERIFICA CHE LE CREDENZIALI OPERATORE INSERITE DALL'UTENTE SIANO CORRETTE
bool verificaCredenzialiOperatore(Operatore *testa,char *pinInput, char *passwordInput);

bool pinGiaPresente(Operatore *nodo,char* pin);

#endif // OPERATORE
