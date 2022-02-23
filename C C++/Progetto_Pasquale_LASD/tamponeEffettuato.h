#ifndef TAMPONEEFFETTUATO
#define TAMPONEEFFETTUATO

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct tamponeEffettuato
{
    char codiceFiscale[17];
    char pinOperatore[5];       //pin alfanumerico operatore di chi ha elaborato il tampone
    char orario[11];            //fascia oraria  del tampone
    char esito[9];
    int numeroTampone;
    struct tamponeEffettuato *prev;
    struct tamponeEffettuato *next;

} TamponeEffettuato;

//RECUPERA TAMPONI EFFETTUATI DALLA STRUTTURA DINAMICA E LI SALVA SUL FILE DI TESTO
void creaFileTamponiEffettuati(FILE *fPtr,TamponeEffettuato * testa);

//INSERISCO IL NUOVO TAMPONE IN FONDO ALLA LISTA
void inserimentoInCodaTamponeEffettuato(TamponeEffettuato **testa,char *codiceFiscale,char *pinOperatore, char *orario, char *esito, int numeroTampone);

//STAMPA A SCHERMO TUTTI I TAMPONI EFFETTUATI
void stampaTamponiEffettuati(TamponeEffettuato *testa);

//RECUPERA I TAMPONI EFFETTUATI DAL FILE DI TESTO E LI INSERISCE ALL'INTERNO DELLA STRUTTURA DINAMICA
void riempiListaTamponiEffettuati(FILE *fPtr,TamponeEffettuato ** testa);

//PRENDE IN INGRESSO IL NUOVO NODO, IL PRECEDENTE, IL SUCCESSIVO E LI COLLEGA
void inserimentoNodoTamponeEffettuato(TamponeEffettuato **newNode,TamponeEffettuato *prev,TamponeEffettuato *next,char *codiceFiscale,char *pinOperatore, char *orario, char *esito, int numeroTampone);

//VISUALIZZA L'ESITO DELL'ULTIMO TAMPONE EFFETTUATO DAL CODICE FISCALE PASSATO COME PARAMETRO
void visualizzaEsitoUltimoTampone(char *codiceFiscale,TamponeEffettuato *testa);

//INSERISCO IL NUOVO NODO IN CIMA ALLA LISTA
void inserimentoInTestaTamponeEffettuato(TamponeEffettuato **testa,char *codiceFiscale,char *pinOperatore, char *orario, char *esito, int numeroTampone);
#endif // TAMPONEEFFETTUATO
