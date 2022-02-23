/*#ifndef DRIVER
#define DRIVER
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef struct driver
{
    char username[11];
    char password[20];
    int peso;
    int pesoMerce;
    struct driver *prev;
    struct driver *next;
} Driver;

//RECUPERA I DRIVER DAL FILE DI TESTO E LI INSERISCE ALL'INTERNO DELLA STRUTTURA DINAMICA
void riempiListaDriver(FILE * fPtr, Driver * * testa);

//RECUPERA I DRIVER DALLA STRUTTURA DINAMICA E LI SALVA SUL FILE DI TESTO
void creaFileDriver(FILE * fPtr, Driver *testa);

//INSERISCE IL NUOVO DRIVER IN TESTA ALAL LISTA
void inserimentoInTestaDriver(Driver ** testa, char *usernameInput, char *passwordInput, int pesoInput, int pesoMerceInput);

//PRENDE IN INGRESSO IL NUOVO NODO, IL PRECEDENTE, IL SUCCESSIVO E LI COLLEGA
void inserimentoNodoDriver(Driver ** newNode, Driver * prevNode, Driver *nextNode, char *usernameInput, char *passwordInput, int pesoInput, int pesoMerceInput);

//VERIFICA CHE L'USERNAME IMMESSO DURANTE LA REGISTRAZIONE NON SIA GIA' PRESENTE SULLA PIATTAFORMA
bool usernameGiaPresente(Driver *nodo,char* username);

//VERIFICA CHE LE CREDENZIALI IMMESSE DALL'UTENTE SIANO CORRETTE
bool verificaCredenzialiDriver(Driver *testa,char *usernameInput, char *passwordInput);

//RESTITUISCE IL PUNTATORE AL DRIVER AVENTE USERNAME PARI A QUELLO PASSATO COME PARAMETRO
Driver * getDriverByUsername(Driver *testa,char *username);
//#endif // DRIVER

