#ifndef RICHIESTAPRENOTAZIONE
#define RICHIESTAPRENOTAZIONE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "appuntamentoFissato.h"

typedef struct richiestaPrenotazione
{
    char codiceFiscale[17];
    int gravita;                //STA AD INDICARE LA GRAVITA' DELLA RICHIESTA, AD ESEMPIO UTENTI CON SINTOMI AVRANNO GRAVITA' PIU' ALTE
    struct richiestaPrenotazione *prev;
    struct richiestaPrenotazione *next;
}RichiestaPrenotazione;

//RECUPERA RICHIESTE PRENOTAZIONI DALLA STRUTTURA DINAMICA E LI SALVA SUL FILE DI TESTO
void creaFileRichiestePrenotazioni(FILE *fPtr,RichiestaPrenotazione *testa);

//PRIMA DOMANDA PER CONSTATARE GRAVITA' RICHIESTA DI APPUNTAMENTO, RESTITUISCE UN INTERO CHE SI ANDRA' A SOMMARE AGLI INTERI DELLE ALTRE DOMANDE PER RICAVARE LA GRAVITA' FINALE
int domandaUNO();

//SECONDA DOMANDA PER CONSTATARE GRAVITA' RICHIESTA DI APPUNTAMENTO, RESTITUISCE UN INTERO CHE SI ANDRA' A SOMMARE AGLI INTERI DELLE ALTRE DOMANDE PER RICAVARE LA GRAVITA' FINALE
int domandaDUE();

//TERZA DOMANDA PER CONSTATARE GRAVITA' RICHIESTA DI APPUNTAMENTO, RESTITUISCE UN INTERO CHE SI ANDRA' A SOMMARE AGLI INTERI DELLE ALTRE DOMANDE PER RICAVARE LA GRAVITA' FINALE
int domandaTRE();

//FUNZIONE CHE RICHIAMA TUTTE LE DOMANDE, SOMMA I VALORI RITORNATI E RITORNA LA SOMMA ALLA FUNZIONE CHIAMANTE
int domandeRichiestaAppuntamento();

//ELIMINA UN DETERMINATO NODO DALLA LISTA DINAMICA
void eliminaNodoRichiestaPrenotazione(RichiestaPrenotazione **testa);

//PRENDE IN INGRESSO UN CODICE FISCALE, TROVA IL NODO CON IL CODICE FISCALE E LO ELIMINA. RESTITUISCE TRUE SE L'ELIMINAZIONE E' ANDATA A BUON FINE
bool eliminaRichiestaPrenotazione(char *codiceFiscale, RichiestaPrenotazione **testa);

//PRENDE IN INGRESSO LA LISTA DI RICHIESTE E LE PROCESSA METTENDOLE NELLA LISTA DEGLI APPUNTAMENTI FISSATI
void fissaAppuntamenti(char *pinOperatore,AppuntamentoFissato **testaAppuntamento, RichiestaPrenotazione **testaRichiesta,int numeroAppuntamento);

//PRENDE IN INGRESSO IL NUOVO NODO, IL PRECEDENTE, IL SUCCESSIVO E LI COLLEGA
void inserimentoNodoRichiestaPrenotazione(RichiestaPrenotazione ** newNode, RichiestaPrenotazione * prevNode, RichiestaPrenotazione *nextNode, char *codiceFiscaleInput, int gravita);

//INSERISCE LE NUOVE RICHIESTE NELLA LISTA IN ORDINE DECRESCENTE IN BASE ALLA GRAVITA'
void inserimentoRichiestaPrenotazioneGravitaDecrescente(RichiestaPrenotazione ** testa,char *codiceFiscaleInput, int gravita );

//MOSTRA LO STATO DELLA PROPRIA RICHIESTA DI APPUNTAMENTO. SE L'APPUNTAMENTO E' STATO FISSATO, VERRANO INDICATI TRA QUANTI GIORNI PRESENTARSI AL LABORATORIO
bool mostraStatoRichiestaPrenotazione(char *codiceFiscale,RichiestaPrenotazione *nodoRichiesta,AppuntamentoFissato *nodoAppuntamento );

//RESTITUISCE TRUE SE NON CI SONO RICHIESTE DI PRENOTAZIONI
bool richiestaPrenotazioneIsVoid(RichiestaPrenotazione *testa);

//RECUPERA LE RICHIESTE DI PRENOTAZIONE DAL FILE DI TESTO E LI INSERISCE ALL'INTERNO DELLA STRUTTURA DINAMICA
void riempiListaRichiestePrenotazioni(FILE *fPtr,RichiestaPrenotazione ** testa );

//STAMPO A SCHERMO TUTTE LE RICHIESTE DI PRENOTAZIONE
void stampaRichiestePrenotazione(RichiestaPrenotazione *testa);

//PRENDE IN INGRESSO UN CODICE FISCALE. SE VIENE TROVATO UN APPUNTAMENTO FISSATO DI QUEL CODICE FISCALE RESTITUISCE TRUE
bool trovaAppuntamento(char *codiceFiscale,AppuntamentoFissato *nodoAppuntamento,int posizione);

//RESTIUISCE TRUE SE VIENE TROVATA UNA RICHIESTA DI PRENOTAZIONE DEL CODICE FISCALE PASSATO COME PARAMETRO
bool trovaRichiesta(char *codiceFiscale,RichiestaPrenotazione *nodoRichiesta);

#endif // RICHIESTAPRENOTAZIONE
