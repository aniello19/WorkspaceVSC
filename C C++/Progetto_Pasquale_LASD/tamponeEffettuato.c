#include "tamponeEffettuato.h"
/*
RECUPERA RICHIESTE PRENOTAZIONI DALLA STRUTTURA DINAMICA E LI SALVA SUL FILE DI TESTO
*/
void creaFileTamponiEffettuati(FILE *fPtr,TamponeEffettuato * testa)
{
    if(testa!=NULL)
    {
        fprintf(fPtr,"%s %s %s %s %d\n",testa->codiceFiscale,testa->pinOperatore,testa->orario,testa->esito,testa->numeroTampone);
        creaFileTamponiEffettuati(fPtr,testa->next);        //RICHIAMO RICORSIVAMENTE LA FUNZIONE
    }
}

/*
INSERISCO IL NUOVO TAMPONE IN FONDO ALLA LISTA
*/
void inserimentoInCodaTamponeEffettuato(TamponeEffettuato **testa,char *codiceFiscale,char *pinOperatore, char *orario, char *esito, int numeroTampone)
{
    if(*testa==NULL)    //ENTRO NEL BLOCCO SE LA LISTA E' VUOTA
    {
        TamponeEffettuato *newNode =malloc(sizeof(TamponeEffettuato));
        inserimentoNodoTamponeEffettuato(&newNode,NULL,NULL,codiceFiscale,pinOperatore,orario,esito,numeroTampone);
        (*testa)=newNode;
    }
    else if((*testa)->next==NULL)   //ENTRO NEL BLOCCO SE SONO ARRIVATO IN FONDO ALLA LISTA
    {
        TamponeEffettuato *newNode =malloc(sizeof(TamponeEffettuato));
        inserimentoNodoTamponeEffettuato(&newNode,(*testa),NULL,codiceFiscale,pinOperatore,orario,esito,numeroTampone);
        (*testa)->next=newNode;
    }
    else
    {
        inserimentoInCodaTamponeEffettuato(&((*testa)->next),codiceFiscale,pinOperatore,orario,esito,numeroTampone);      //RICHIAMO RICORSIVAMENTE LA FUNZIONE
    }
}

/*
VISUALIZZA L'ESITO DELL'ULTIMO TAMPONE EFFETTUATO DAL CODICE FISCALE PASSATO COME PARAMETRO
*/
void visualizzaEsitoUltimoTampone(char *codiceFiscale,TamponeEffettuato *testa)
{
    if(testa==NULL)
    {
        printf("# ATTENZIONE -- NON HAI EFFETTUATO ALCUN TAMPONE\n");
    }
    else if(strcmp(testa->codiceFiscale,codiceFiscale)==0)      //VERIFICO CHE IL CODICE FISCALE SIA PARI A QUELLO NODO ATTUALE
    {
        if(strcmp(testa->esito,"negativo")==0)
            printf("# Il tuo utlimo tampone e' risultato NEGATIVO!\n");
        else
            printf("# Il tuo ultimo tampone e' risultato POSITIVO!\n");
    }
    else
        visualizzaEsitoUltimoTampone(codiceFiscale,testa->next);    //RICHIAMO RICORSIVAMENTE LA FUNZIONE
}

/*
STAMPA TUTTI I TAMPONI EFFETTUATI
*/
void stampaTamponiEffettuati(TamponeEffettuato *testa)
{
    if(testa!=NULL)
    {
        printf("%-18d %-18s %-18s %-18s %-18s\n",testa->numeroTampone,testa->codiceFiscale,testa->pinOperatore,testa->orario,testa->esito);
        stampaLinea(84);
        stampaTamponiEffettuati(testa->next);   //RICHIAMO RICORSIVAMENTE LA FUNZIONE
    }
}

/*
INSERISCO IL NUOVO NODO IN CIMA ALLA LISTA
*/
void inserimentoInTestaTamponeEffettuato(TamponeEffettuato **testa,char *codiceFiscale,char *pinOperatore, char *orario, char *esito, int numeroTampone)
{
    TamponeEffettuato *newNode = malloc(sizeof(TamponeEffettuato));
    if(*testa==NULL)        //ENTRO NEL BLOCCO SE LA LISTA E VUOTA
    {
        inserimentoNodoTamponeEffettuato(&newNode,NULL,NULL,codiceFiscale,pinOperatore,orario,esito,numeroTampone);
        (*testa)=newNode;
    }
    else        //ENTRO NEL BLOCCO SE ESISTE GIA' ALMENO UN TAMOPONE EFFETTUATO
    {
        inserimentoNodoTamponeEffettuato(&newNode,NULL,(*testa),codiceFiscale,pinOperatore,orario,esito,numeroTampone);
        (*testa)->prev=newNode;
        (*testa)=newNode;
    }
}

/*
PRENDE IN INGRESSO IL NUOVO NODO, IL PRECEDENTE, IL SUCCESSIVO E LI COLLEGA
*/
void inserimentoNodoTamponeEffettuato(TamponeEffettuato **newNode,TamponeEffettuato *prev,TamponeEffettuato *next,char *codiceFiscale,char *pinOperatore, char *orario, char *esito, int numeroTampone)
{
    (*newNode)->prev=prev;
    (*newNode)->next=next;
    strcpy((*newNode)->codiceFiscale,codiceFiscale);
    strcpy((*newNode)->pinOperatore,pinOperatore);
    strcpy((*newNode)->orario,orario);
    (*newNode)->numeroTampone=numeroTampone;
    strcpy((*newNode)->esito,esito);
}


/*
RECUPERA I TAMPONI EFFETTUATI DAL FILE DI TESTO E LI INSERISCE ALL'INTERNO DELLA STRUTTURA DINAMICA
*/
void riempiListaTamponiEffettuati(FILE *fPtr,TamponeEffettuato ** testa)
{
    char codiceFiscale[17];
    char pinOperatore[5];
    char orario[11];
    char esito[9];
    int numeroTampone;
    if(fscanf(fPtr,"%16s%4s%10s%8s%d",codiceFiscale,pinOperatore,orario,esito,&numeroTampone)==5)        //FSCANF RESTITUISCE UN INTERO PARI AL NUMERO DI VARIABILI A CUI SONO STATI ASSEGNATI DEI VALORI
    {
        inserimentoInCodaTamponeEffettuato(&(*testa),codiceFiscale,pinOperatore,orario,esito,numeroTampone);
        riempiListaTamponiEffettuati(fPtr,&((*testa)));
    }
}


