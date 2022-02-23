#ifndef UTENTE
#define UTENTE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct utente
{
    char codiceFiscale[17];
    char password[20];
    int  positivo;          //INDICA SE L'UTENTE E' POSITIVO O MENO , 1-->POSITIVO , 0-->NEGATIVO
    struct utente *prev;
    struct utente *next;
} Utente;

//PRENDE IN INGRESSO L'ESITO DEL TAMPONE DI UN UTENTE, IL SUO CODICE FISCALE, E GLI CAMBIA LA POSITIVITA' AL COVID
void cambiaPositivitaUtente(char *codiceFiscale, int tampone,Utente ** testa);

//VERIFICA CHE IL CODICE FISCALE INSERITO SIA PRESENTE SULLA PIATTAFORMA
bool codiceFiscalePresente(Utente *testa,char *codiceFiscale);

//RECUPERA UTENTI DALLA STRUTTURA DINAMICA E LI SALVA ALL'INTERNO DEL FILE DI TESTO
void creaFileUtenti(FILE * fPtr, Utente *testa);

//INSERISCO L'UTENTE IN CIMA ALLA STRUTTURA DINAMICA
void inserimentoInTestaUtente(Utente ** testa, char *codiceFiscaleInput, char *passwordInput,int positivo);

//PRENDE IN INGRESSO IL NUOVO NODO, IL PRECEDENTE, IL SUCCESSIVO E LI COLLEGA
void inserimentoNodoUtente(Utente ** newNode, Utente * prevNode, Utente *nextNode, char *codiceFiscaleInput, char *passwordInput,int positivo);

//RECUPERA UTENTI DA FILE DI TESTO E LI SALVA ALL'INTERNO DELLA STRUTTURA DINAMICA
void riempiListaUtenti(FILE * fPtr, Utente * * testa);

//STAMPA TUTTI GLI UTENTI POSITIVI
void stampaPositivi(Utente *testa);

//STAMPA TUTTI GLI UTENTI
void stampaUtenti(Utente * testa);

//VERIFICA CHE LE CREDENZIALI D'ACCESSO INSERITE SIANO PRESENTI SULAL PIATTAFORMA
bool verificaCredenzialiUtente(Utente *testa,char *codiceFiscaleInput, char *passwordInput);



//char* registraCodiceFiscale();

//char* registraPassword();

#endif

