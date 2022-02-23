#include "utente.h"

/*
PRENDE IN INGRESSO L'ESITO DEL TAMPONE DI UN UTENTE, IL SUO CODICE FISCALE, E GLI CAMBIA LA POSITIVITA' AL COVID
*/
void cambiaPositivitaUtente(char *codiceFiscale, int tampone,Utente ** testa)
{
    if(*testa!=NULL)        //ENTRO NEL BLOCCO SOLO SE IL NODO ATTUALE E' DIVERSO DA NULL
    {
        if(strcmp((*testa)->codiceFiscale,codiceFiscale)==0)    //SE IL CODICE FISCALE E' STATO TROVATO CAMBIO IL VALORE DI POSITIVO DEL NODO ATTUALE CON IL NUOVO VALORE
        {
            (*testa)->positivo=tampone;
        }
        else
        {
            cambiaPositivitaUtente(codiceFiscale,tampone,&(*testa)->next); //RICHIAMO LA FUNZIONE RICORSIVAMENTE
        }
    }
}

/*
VERIFICA CHE IL CODICE FISCALE INSERITO SIA PRESENTE SULLA PIATTAFORMA
*/
bool codiceFiscalePresente(Utente *testa,char *codiceFiscale)
{
    if (testa==NULL)
    {
        return false;       //SE LA LISTA E' TERMINATA RITORNO FALSE
    }
    else if (strcmp(testa->codiceFiscale,codiceFiscale)==0)
    {
        return true;        //SE IL CODICE FISCALE E' PRESENTE SULLA PIATTAFORMA RITORNO TRUE
    }
    else
    {
        return codiceFiscalePresente(testa->next,codiceFiscale);       //RICHIAMO LA FUNZIONE RICORSIVAMENTE
    }
}

/*
RECUPERA UTENTI DALLA STRUTTURA DINAMICA E LI SALVA ALL'INTERNO DEL FILE DI TESTO
*/
void creaFileUtenti(FILE * fPtr, Utente *testa)
{
    if(testa!=NULL) //CONTNUO FINCHE' NON RAGGIUNGO LA FIEN DELLA STRUTTURA
    {
        fprintf(fPtr,"%s %s %d\n",testa->codiceFiscale,testa->password,testa->positivo);
        creaFileUtenti(fPtr,testa->next);       //CHIAMATA RICORSIVA DELAL FUNZIONE
    }
}

/*
INSERISCO L'UTENTE IN CIMA ALLA STRUTTURA DINAMICA
*/
void inserimentoInTestaUtente(Utente ** testa, char *codiceFiscaleInput, char *passwordInput,int positivo)
{
    Utente *newNode = malloc(sizeof(Utente));       //CREO UN NUOVO NUOVO E GLI ALLOCO LO SPAZIO NECESSARIO
    if(*testa==NULL)
    {
        inserimentoNodoUtente(&newNode,NULL,NULL,codiceFiscaleInput,passwordInput,positivo);    //SE LA LISTA E' VUOTA PREV E NEXT SARANNO ENTRAMBI NULL

    }
    else
    {
        inserimentoNodoUtente(&newNode,NULL,(*testa),codiceFiscaleInput,passwordInput,positivo);    //SE LA LISTA NON E' VUOTA IL NUOVO NODO SI POSIZIONERA' IN TESTA E AVRA' NEXT UGUALE ALLA VECCHIA TESTA
        (*testa)->prev=newNode;     //IL NODO PRECEDENTE DELLA VECCHIA' TESTA E' DIVENTATO IL NUOVO NODO
    }
    (*testa)=newNode;       //IL NUOVO NODO SARA' LA NUOVA TESTA
}

/*
PRENDE IN INGRESSO IL NUOVO NODO, IL PRECEDENTE, IL SUCCESSIVO E LI COLLEGA
*/
void inserimentoNodoUtente(Utente ** newNode, Utente * prevNode, Utente *nextNode, char *codiceFiscaleInput, char *passwordInput,int positivo)
{
    (*newNode)->prev=prevNode;
    (*newNode)->next=nextNode;
    strcpy((*newNode)->codiceFiscale,codiceFiscaleInput);       //LA FUNZIONE STRCPY COPIA LA SECONDA STRINGA NELLA PRIMA
    strcpy((*newNode)->password,passwordInput);
    (*newNode)->positivo=positivo;
}

/*
RECUPERA UTENTI DA FILE DI TESTO E LI SALVA ALL'INTERNO DELLA STRUTTURA DINAMICA
*/
void riempiListaUtenti(FILE * fPtr, Utente * * testa)
{
    char codiceFiscale[17];
    char password[20];
    int  positivo;
    if(fscanf(fPtr,"%16s %19s %d",codiceFiscale,password,&positivo) == 3)       //FSCANF RESTITUISCE UN INTERO PARI AL NUMERO DI VARIABILI A CUI SONO STATI ASSEGNATI DEI VALORI
    {
        inserimentoInTestaUtente(&(*testa),codiceFiscale,password,positivo);    //INSERISCO L'UTENTE RECUPERATO DAL FILE NELLA TESTA DELLA LISTA UTENTE
        riempiListaUtenti(fPtr,&(*testa));      //RICHIAMO LA FUNZIONE RICORSIVAMENTE
    }
}

/*
STAMPA TUTTI GLI UTENTI ATTUALMENTE POSITIVI
*/
void stampaPositivi(Utente *nodo)
{
    if(nodo!=NULL)             //ENTRO NEL BLOCCO FINCHE' LA LISTA NON E' TERMINATA
    {
        if(nodo->positivo==1)       //STAMPO L'UTENTE SOLO SE E' POSITIVO (1-->POSITIVO , 0--> NEGATIVO)
        {
            printf("%s\n",nodo->codiceFiscale);
            stampaLinea(14);    //STAMPO UNA LINEA DI 10 CARATTERI '-'
        }
        stampaPositivi(nodo->next);     //RICHIAMO LA FUNZIONE RICORSIVAMENTE
    }
}

/*
STAMPA TUTTI GLI UTENTI
*/
void stampaUtenti(Utente * testa)
{
    if(testa!=NULL)     //ENTRO NEL BLOCCO FINCHE' NON TERMINO LA LISTA
    {
        printf("%s %s\n",testa->codiceFiscale,testa->password);
        stampaUtenti(testa->next);      //RICHIAMO RICORSIVAMENTE LA FUNZIONE
    }
}

/*
VERIFICA CHE LE CREDENZIALI D'ACCESSO INSERITE SIANO PRESENTI SULAL PIATTAFORMA
*/
bool verificaCredenzialiUtente(Utente *testa,char *codiceFiscaleInput, char *passwordInput)
{
    if(testa!=NULL)         //ENTRO NEL BLOCCO FINCHE' NON TERMINO LA LISTA
    {
        if(strcmp(testa->codiceFiscale,codiceFiscaleInput)==0  && strcmp(testa->password,passwordInput)==0)
        {
            return true;    //SE CF E PASSWORD IN INPUT COINCIDONO QUELLE DEL NODO ATTUALE ALLORA RITORNO TRUE
        }
        else
            return verificaCredenzialiUtente(testa->next,codiceFiscaleInput,passwordInput); //RICHIAMO LA FUNZIONE RICORSIVAMENTE
    }
    else
        return false;   //RITORNO FALSE SE LA LISTA E' TERMINATA E QUINDI NON SONO STATE TROVATE LE CREDENZIALI INSERITE
}


