/*#ifndef SPESA
#define SPESA
*/
#define NUMEROPRODOTTI 6

#include "funzioniUtil.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct prodotto
{
    char nome[20];
    int peso;
}Prodotto;

typedef struct carrello
{
    char nome[20];
    int quantita;
    struct carrello *next;
}Carrello;

//VETTORE STATICO DI PRODOTTI
Prodotto  listaProdotti[NUMEROPRODOTTI];

//INIZIALIZZA IL VETTORE DI PRODOTTI
void riempiVettoreProdotti();

//STAMPA LA LISTA DEI PRODOTTI
void stampaProdotti();

//PERMETTE DI FARE LA SPESA AL DRIVER, RESTITUISCE IL PESO COMPLESSIVO DEGLI ARTICOLI
int faiSpesa(Carrello **nodo,int pesoComplessivoProdotti,int pesoIniziale);

/*
SVUOTA IL CARRELLO
*/
void freeCarrello(Carrello **nodo);

//INSERISCE NEL CARRELLO UN PRODOTTO CON LA QUANTITA' ACQUISTATA, SE IL PRODOTTO E' STATO GIA'
//ACQUISTATO IN PRECEDENZA LA QUANTITA' SI AGGIORNA
void inserisciProdottoCarrello(Carrello **nodo,char *nome,int peso);

//STAMPA IL CARRELLO
void stampaCarrello(Carrello *nodo);

//#endif // SPESA

