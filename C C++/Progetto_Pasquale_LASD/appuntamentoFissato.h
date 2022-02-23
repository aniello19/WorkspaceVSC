#ifndef APPUNTAMENTOFISSATO

#define APPUNTAMENTOFISSATO

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "tamponeEffettuato.h"
#include "utente.h"

typedef struct appuntamentoFissato
{
    char codiceFiscale[17];
    char pinOperatore[5];
    char orario[11];
    char eliminato[2]; //attributo ausiliario utile a determinare in maniera corretta la data degli appuntamenti
    int gravita;
    int numeroAppuntamento;             //attributo ausiliario utile a determinare la fascia oraria dell'appuntamento, assume valore da 0 a 5, 1 è il primo appuntamento del giorno, 0 l'ultimo (viene dopo il 5), asssume valore -1 se l'appuntamento è stato eliminato
    struct appuntamentoFissato *prev;
    struct appuntamentoFissato *next;
}AppuntamentoFissato;

//RESTITUISCE TRUE SE NON SONO PRESENTI APPUNTAMENTI FISSATI NON ELIMINATI
bool appuntamentiFissatiIsVoid(AppuntamentoFissato *nodo);

//RESTITUISCE TRUE SE E' GIA' PRESENTE UN APPUNTAMENTO PER IL CODICE FISCALE PASSATO IN INPUT
bool appuntamentoGiaPresente(AppuntamentoFissato *testa,char *codiceFiscale);

//RECUPERA APPUNTAMENTI FISSATI DALLA STRUTTURA DINAMICA E LI SALVA SUL FILE DI TESTO
void creaFileAppuntamentiFissati(FILE *fPtr,AppuntamentoFissato * testa);

//PRENDE IN INGRESSO LA LISTA DI APPUNTAMENTI FISSATI E ELABORA SOLAMENTE I TAMPONI DEL GIORNO, ELIMINA POI GLI APPUNTAMENTI DALLA LISTA E INSERISCE GLI ESITI NELLA LISTA TAMPONI EFFETTUATI
void elaboraTamponi(AppuntamentoFissato **testaAppuntamenti, TamponeEffettuato **testaTamponi,Utente **testaUtenti,char *pinTamponatore);

//CAMBIA IL VALORE DELLA VARIABILE ELIMINATO DEL NDO AVENTE CODICE FISCALE PARI A QUELLO PASSATO COME PARAMETRO
bool eliminaAppuntamentoFissatoCodiceFiscale(char *codiceFiscale,AppuntamentoFissato ** testa);

//ELIMINA UNO SPECIFICO NODO DALLA LISTA DEGLI APPUNTAMENTI
void eliminaNodoAppuntamentoFissato(AppuntamentoFissato ** nodo);

//INSERISCE UN NUOVO NODO IN FONDO ALLA LISTA DEGLI APPUNTAMENTI
void inserimentoInCodaAppuntamentoFissato(AppuntamentoFissato **testa, char *codiceFiscale,char *pinOperatore,char *eliminato,int gravita,int numeroAppuntamento);

//PRENDE IN INGRESSO IL NUOVO NODO, IL PRECEDENTE, IL SUCCESSIVO E LI COLLEGA
void inserimentoNodoAppuntamentoFissato(AppuntamentoFissato **newNode,AppuntamentoFissato *prev, AppuntamentoFissato *next,char *codiceFiscale, char *pinOperatore,char *eliminato,int gravita,int numeroAppuntamento);

//RECUPERA GLI APPUNTAMENTI DAL FILE DI TESTO E LI INSERISCE ALL'INTERNO DELLA STRUTTURA DINAMICA
void riempiListaAppuntamentiFissati(FILE *fPtr,AppuntamentoFissato ** testa);

//STAMPA A SCHERMO GLI APPUNTAMENTI DEL GIORNO
void stampaAppuntamentiDelGiorno(AppuntamentoFissato *testa);

//FUNZIONE COMPLEMENTARE A STAMPAAPPUNTAMENTIDELGIORNOI
void stampaAppuntamentiDelGiornoPrivate(AppuntamentoFissato *testa);

//STAMPA TUTTI GLI APPUNTAMENTI FISSATI NON ELIMINATI
void stampaAppuntamentiFissati(AppuntamentoFissato *testa);


#endif // APPUNTAMENTOFISSATO
