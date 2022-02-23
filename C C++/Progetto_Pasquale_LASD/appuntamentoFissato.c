#include "appuntamentoFissato.h"

/*
RESTITUISCE TRUE SE NON SONO PRESENTI APPUNTAMENTI FISSATI NON ELIMINATI
*/
bool appuntamentiFissatiIsVoid(AppuntamentoFissato *nodo)
{
    if(nodo!=NULL)      //ENTRO NEL BLOCCO SE LA LISTA NON E' TERMINATA
    {
        if(strcmp(nodo->eliminato,"n")==0)  //VERIFICO CHE L'APPUNTAMENTO NON SIA STATO CANCELLATO
            return true;
        else
            return appuntamentiFissatiIsVoid(nodo->next);   //CHIAMATA RICORSIVA DELLA FUNZIONE
    }
    else
        return false;
}

/*
RESTITUISCE TRUE SE E' GIA' PRESENTE UN APPUNTAMENTO PER IL CODICE FISCALE PASSATO IN INPUT
*/
bool appuntamentoGiaPresente(AppuntamentoFissato *testa,char *codiceFiscale)
{
    if(testa==NULL)
        return false;
    else if(strcmp(testa->codiceFiscale,codiceFiscale)==0 && strcmp(testa->eliminato,"n")==0)   //VERIFICO CHE IL CODICE FISCALE COINCIDA E CHE L'APPUNTAMNETO NON SIA STAO ELIMINATO
        return true;
    else
        return appuntamentoGiaPresente(testa->next,codiceFiscale); //RICHIAMO RICORSIVAMENTE LA FUNZIONE
}

/*
RECUPERA APPUNTAMENTI FISSATI DALLA STRUTTURA DINAMICA E LI SALVA SUL FILE DI TESTO
*/
void creaFileAppuntamentiFissati(FILE *fPtr,AppuntamentoFissato * testa)
{
    if(testa!=NULL)     //ENTRO NEL BLOCCO FINCHE' NON TERMINA LA LISTA
    {
        fprintf(fPtr,"%s %s %s %s %d %d\n",testa->codiceFiscale,testa->pinOperatore,testa->orario,testa->eliminato,testa->gravita,testa->numeroAppuntamento);
        creaFileAppuntamentiFissati(fPtr,testa->next);
    }
}

/*
//PRENDE IN INGRESSO LA LISTA DI APPUNTAMENTI FISSATI E ELABORA SOLAMENTE I TAMPONI DEL GIORNO, ELIMINA POI GLI APPUNTAMENTI DALLA LISTA E INSERISCE GLI ESITI NELLA LISTA TAMPONI EFFETTUATI
*/
void elaboraTamponi(AppuntamentoFissato **testaAppuntamenti, TamponeEffettuato **testaTamponi,Utente ** testaUtenti,char *pinTamponatore)
{
    if(strcmp((*testaAppuntamenti)->eliminato,"n")==0)      //VERIFICO CHE L'APPUNTAMENTO NON SIA STATO ELIMINATO
    {
        srand(time(0));    // DO UN SEME ALLA FUNZIONE SRAND

        int tampone;
        tampone = rand()%2;     //L'ESITO DEL TAMPONE E' CALCOLATO RANDOMICAMENTE, 1-->POSITIVO, 0-->NEGATIVO
        char esito[10];
        if(tampone==0)
            strcpy(esito,"negativo");
        else
            strcpy(esito,"positivo");

       cambiaPositivitaUtente((*testaAppuntamenti)->codiceFiscale,tampone,&(*testaUtenti)); //CAMBIO L'ATTRIBUTO POSITIVO DI UTENTE
        if((*testaTamponi)==NULL)
            inserimentoInTestaTamponeEffettuato(&(*testaTamponi),(*testaAppuntamenti)->codiceFiscale,pinTamponatore,(*testaAppuntamenti)->orario,esito,1); //SE LA LISTA DI TAMPONI EFFETUTATI E' VUOTA, IL PROSSIMO TAMPONE SARA' IL NUMERO UNO
        else
            inserimentoInTestaTamponeEffettuato(&(*testaTamponi),(*testaAppuntamenti)->codiceFiscale,pinTamponatore,(*testaAppuntamenti)->orario,esito,(*testaTamponi)->numeroTampone+1); //SE LA LISTA DI TAMPONI NON E' VUOTA IL PROSSIMO TAMPONE SARA' DI NUMERO PARI A QUELLO DELL'ULTIMO PIU' UNO
        printf("%-19s %-15s\n",(*testaAppuntamenti)->codiceFiscale,esito);  //STAMPO CODICE FISCALE E ESITO
    }

    if((*testaAppuntamenti)->next!=NULL)        //ENTRO NEL BLOCCO SE SONO ANCORA PRESENTI APPUNTAMENTI
    {
        if((*testaAppuntamenti)->numeroAppuntamento < (*testaAppuntamenti)->next->numeroAppuntamento) //VERIFICO CHE IL PROSSIMO APPUNTAMENTO SIA DELLA STESSA GIORNATA, I NUEMRI DI APPUNTAMENTI VANNO DA 1 A 6
        {
            sleep(1);   //INTERROMPO L'ELABORAZIONE DEL PROGRAMMA PER UN SECONDO
            elaboraTamponi(&(*testaAppuntamenti)->next,&(*testaTamponi),&(*testaUtenti),pinTamponatore);
        }
    }


    eliminaNodoAppuntamentoFissato(&(*testaAppuntamenti));  //ELIMINO LA TESTA DELLA LISTA DEGLI APPUNTAMENTI
}

/*
CAMBIA IL VALORE DELLA VARIABILE ELIMINATO DEL NDO AVENTE CODICE FISCALE PARI A QUELLO PASSATO COME PARAMETRO
*/
bool eliminaAppuntamentoFissatoCodiceFiscale(char *codiceFiscale,AppuntamentoFissato ** testa)
{
    if((*testa)==NULL)  //SE LA LISTA E' TERMINATA RESTITUISCO FALSE
    {
        return false;
    }
    else if(strcmp((*testa)->codiceFiscale,codiceFiscale)==0)   //VERIFICO CHE IL CODICE FISCALE PASSATO COME PARAMETRO COINCIDA CON QUELLO DEL NODO ATTUALE
    {
        strcpy((*testa)->eliminato,"s");        //CAMBIO LA STRINGA ELIMINATO CON "S"
        return true;
    }
    else
    {
        return eliminaAppuntamentoFissatoCodiceFiscale(codiceFiscale,&((*testa)->next));    //RICHIAMO RICORSIVAMENTE LA FUNZIONE
    }
}

/*
ELIMINA UNO SPECIFICO NODO DALLA LISTA DEGLI APPUNTAMENTI
*/
void eliminaNodoAppuntamentoFissato(AppuntamentoFissato ** nodo)
{
   AppuntamentoFissato *tmp=(*nodo);    //LA VARIABILE TMP SARA' UN PUNTATORE AL NODO PUNTATO DA TESTA

    if((*nodo)->next!=NULL)            //ENTRO NEL BLOCCO SE IL NODO E' DIVERSO DALL'ULTIMO
    {
        (*nodo)->next->prev=(*nodo)->prev;
        if((*nodo)->prev!=NULL)    //ENTRO NEL BLOCCO SE IL NODO NON E' IL PRIMO DELLA LISTA
        {
            (*nodo)->prev->next=(*nodo)->next;
        }
        else
        {
            (*nodo)=(*nodo)->next;    //SE IL NODO E' IL PRIMO DELLA LISTA CAMBIO LA TESTA CON IL NODO SUCCESSIVO
        }
    }
    else
    {
        (*nodo)=NULL;
    }
    free(tmp);      //LIBERO LO SPAZIO OCCUPATO DA TMP
}

/*
INSERISCE UN NUOVO NODO IN FONDO ALLA LISTA DEGLI APPUNTAMENTI
*/
void inserimentoInCodaAppuntamentoFissato(AppuntamentoFissato **testa, char *codiceFiscale,char *pinOperatore,char *eliminato,int gravita,int numeroAppuntamento)
{
    if(*testa==NULL)    //ENTRO NEL BLOCCO SE LA LISTA E' VUOTA
    {
        AppuntamentoFissato *newNode =malloc(sizeof(AppuntamentoFissato));
        inserimentoNodoAppuntamentoFissato(&newNode,NULL,NULL,codiceFiscale,pinOperatore,eliminato,gravita,numeroAppuntamento);
        (*testa)=newNode;       //CAMBIO LA TESTA DELLA LISTA
    }
    else if((*testa)->next==NULL)   //ENTRO NEL BLOCCO SE IL NODO ATTUALE E' L'ULTIMO DELLA LISTA
    {
        AppuntamentoFissato *newNode =malloc(sizeof(AppuntamentoFissato));
        inserimentoNodoAppuntamentoFissato(&newNode,(*testa),NULL,codiceFiscale,pinOperatore,eliminato,gravita,((*testa)->numeroAppuntamento)+1);
        (*testa)->next=newNode;
    }
    else
    {
        inserimentoInCodaAppuntamentoFissato(&((*testa)->next),codiceFiscale,pinOperatore,eliminato,gravita,((*testa)->numeroAppuntamento)+1);
    }
}

/*
PRENDE IN INGRESSO IL NUOVO NODO, IL PRECEDENTE, IL SUCCESSIVO E LI COLLEGA
*/
void inserimentoNodoAppuntamentoFissato(AppuntamentoFissato **newNode,AppuntamentoFissato *prev, AppuntamentoFissato *next,char *codiceFiscale, char *pinOperatore,char *eliminato,int gravita,int numeroAppuntamento)
{
    (*newNode)->prev=prev;
    (*newNode)->next=next;
    strcpy((*newNode)->codiceFiscale,codiceFiscale);
    strcpy((*newNode)->pinOperatore,pinOperatore);

    numeroAppuntamento=numeroAppuntamento%6;
    if(numeroAppuntamento==0)
        numeroAppuntamento=6;   //SE IL RESTO E' 0 VUOL DIRE CHE IL NUMERO E' 6

    if(numeroAppuntamento==1 || numeroAppuntamento==2)      //I PRIMI DUE APPUNTAMENTI SONO DEL MATTINO
        strcpy((*newNode)->orario,"mattino");
    else if(numeroAppuntamento==3 || numeroAppuntamento==4) //GLI APPUNTAMENTI TRE E QUATTRO SONO DI POMERIGGIO
        strcpy((*newNode)->orario,"pomeriggio");
    else
        strcpy((*newNode)->orario,"sera");      //GLI APPUNTAMENTI CINQUE E SEI SONO DI SERA

    (*newNode)->gravita=gravita;
    (*newNode)->numeroAppuntamento=numeroAppuntamento;
    strcpy((*newNode)->eliminato,eliminato);
}

/*
RECUPERA GLI APPUNTAMENTI DAL FILE DI TESTO E LI INSERISCE ALL'INTERNO DELLA STRUTTURA DINAMICA
*/
void riempiListaAppuntamentiFissati(FILE *fPtr,AppuntamentoFissato ** testa)
{
    char codiceFiscale[17];
    char pinOperatore[5];
    char orario[11];
    char eliminato[2];
    int gravita;
    int numeroAppuntamento;
    if(fscanf(fPtr,"%16s%4s%10s%s%d%d",codiceFiscale,pinOperatore,orario,eliminato,&gravita,&numeroAppuntamento)==6)    //FSCANF RESTITUISCE UN INTERO PARI AL NUMERO DI VARIABILI A CUI SONO STATI ASSEGNATI DEI VALORI
    {
        inserimentoInCodaAppuntamentoFissato(&(*testa),codiceFiscale,pinOperatore,eliminato,gravita,numeroAppuntamento);
        riempiListaAppuntamentiFissati(fPtr,&((*testa)));       //RICHIAMO RICORSIVAMENTE LA FUNZIONE
    }
}

/*
STAMPA A SCHERMO GLI APPUNTAMENTI DEL GIORNO
*/
void stampaAppuntamentiDelGiorno(AppuntamentoFissato *testa)
{
    printf("%-16s %-16s %-16s\n\n","CODICE FISCALE","ORARIO","GRAVITA' DEL CASO(1 a 6)");
    stampaAppuntamentiDelGiornoPrivate(testa);
}

/*
FUNZIONE COMPLEMENTARE A STAMPAAPPUNTAMENTIDELGIORNOI
*/
void stampaAppuntamentiDelGiornoPrivate(AppuntamentoFissato *testa)
{
    if(testa!=NULL)
    {
        if(strcmp(testa->eliminato,"n")==0) //VERIFICO CHE L'APPUNTAMENTO NON SIA STATO ELIMINATO
            printf("%-16s %-16s %-16d\n\n",testa->codiceFiscale,testa->orario,testa->gravita);
        if(testa->next!=NULL)
        {
            if(testa->numeroAppuntamento < testa->next->numeroAppuntamento) //VERIFICO CHE IL PROSSIMO APPUNTAMENTO SIA DELLO STESSO GIORNO
            {
                stampaAppuntamentiDelGiornoPrivate(testa->next);        //RICHIAMO RICORSIVAMENTE LA FUNZIONE
            }
        }
    }
}

/*
STAMPA TUTTI GLI APPUNTAMENTI FISSATI NON ELIMINATI
*/
void stampaAppuntamentiFissati(AppuntamentoFissato *testa)
{
    if(testa!=NULL)     //VERIFICA CHE LA LISTA NON SIA TERMINATA
    {
        if(strcmp(testa->eliminato,"n")==0)     //VERIFICO CHE L'APPUNTAMENTO NON SIA STAO ELIMINATO
        {
            printf(" %-18s %-18d %-18s\n",testa->codiceFiscale,testa->gravita,testa->orario);
            stampaLinea(52);
        }
        stampaAppuntamentiFissati(testa->next);     //RICHIAMO RICORSIVAMENTE LA FUNZIONE
    }
}





