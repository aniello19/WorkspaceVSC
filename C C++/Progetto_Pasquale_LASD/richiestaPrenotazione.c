#include "richiestaPrenotazione.h"

/*
RECUPERA RICHIESTE PRENOTAZIONI DALLA STRUTTURA DINAMICA E LI SALVA SUL FILE DI TESTO
*/
void creaFileRichiestePrenotazioni(FILE *fPtr,RichiestaPrenotazione *testa)
{
    if(testa!=NULL)     //ENTRO NEL BLOCCO FINCHE' LA LISTA NON E' TERMINATA
    {
        fprintf(fPtr,"%s %d\n",testa->codiceFiscale,testa->gravita);
        creaFileRichiestePrenotazioni(fPtr,testa->next);    //RICHIAMO RICORSIVAMENTE LA FUNZIONE
    }
}

/*
PRIMA DOMANDA PER CONSTATARE GRAVITA' RICHIESTA DI APPUNTAMENTO, RESTITUISCE UN INTERO CHE SI ANDRA' A SOMMARE AGLI INTERI DELLE ALTRE DOMANDE PER RICAVARE LA GRAVITA' FINALE
*/
int domandaUNO()
{
    char scelta;
    stampaTitolo();
    printf("# RISPONDI ALLE SEGUENTI DOMANDE\n\n");
    printf("# SEI STATO A CONTATTO NEGLI ULTIMI SETTE GIORNI CON UNA PERSONA RISULTATA POSITIVA?\n\n");
    printf("# 0--> NO \n\n");
    printf("# 1--> SI \n\n");

    scanf("%c",&scelta);
    clear_buffer();
    system("cls");

    if(scelta=='0')
    {
        return 0;
    }
    else if(scelta=='1')
    {
        return 1;   //QUESTA DOMANDA HA GRAVITA' 1 IN CASO DI RISPOSTA AFFERMATIVA
    }
    else
    {
        stampaTitolo();
        printf("# ATTENZIONE : HAI INSERITO UN CARATTERE NON VALIDO\n\n");
        premiTastoPerContinuare();
        return domandaUNO();        //RICARICO LA DOMANDA SE E' STATO INSERITO UN CARATTERE NON VALIDO
    }
}

/*
SECONDA DOMANDA PER CONSTATARE GRAVITA' RICHIESTA DI APPUNTAMENTO, RESTITUISCE UN INTERO CHE SI ANDRA' A SOMMARE AGLI INTERI DELLE ALTRE DOMANDE PER RICAVARE LA GRAVITA' FINALE
*/
int domandaDUE()
{
    char scelta;
    stampaTitolo();
    printf("# RISPONDI ALLE SEGUENTI DOMANDE\n\n");
    printf("# PRESENTI UNO O PIU' DEI SEGUENTI SINTOMI GRAVI?\n\n");
    printf("# --difficolta' respiratoria o fiato corto\n");
    printf("# --febbre alta\n");
    printf("# --oppressione  o dolore al petto\n\n");
    printf("# 0--> NO \n");
    printf("# 1--> SI \n");
    scanf("%c",&scelta);
    clear_buffer();
    system("cls");
    if(scelta=='0')
    {
        return 0;
    }

    else if(scelta=='1')
    {
        return 3;   //QUESTA DOMANDA HA GRAVITA' 3 IN CASO DI RISPOSTA AFFERMATIVA
    }

    else
    {
        stampaTitolo();
        printf("# ATTENZIONE : HAI INSERITO UN CARATTERE NON VALIDO\n");
        premiTastoPerContinuare();
        return domandaDUE();    //RICARICO LA DOMANDA SE E' STATO INSERITO UN CARATTERE NON VALIDO
    }
}

/*
TERZA DOMANDA PER CONSTATARE GRAVITA' RICHIESTA DI APPUNTAMENTO, RESTITUISCE UN INTERO CHE SI ANDRA' A SOMMARE AGLI INTERI DELLE ALTRE DOMANDE PER RICAVARE LA GRAVITA' FINALE
*/
int domandaTRE()
{
    char scelta;
    stampaTitolo();
    printf("# RISPONDI ALLE SEGUENTI DOMANDE\n\n");
    printf("# APPARTIENI A UNA DELLE SEGUENTI CATEGORIE?\n\n");
    printf("# --over 60;\n");
    printf("# --disabili gravi;\n");
    printf("# --cardiopatici;");
    printf("# --persone con problemi all'apparato respiratorio;\n\n");
    printf("# 0--> NO \n");
    printf("# 1--> SI \n");

    scanf("%c",&scelta);
    clear_buffer();
    system("cls");

    if(scelta=='0')
        return 0;
    else if(scelta=='1')
        return 2;       //QUESTA DOMANDA HA GRAVITA' 2 IN CASO DI RISPOSTA AFFERMATIVA
    else
    {
        stampaTitolo();
        printf("# ATTENZIONE : HAI INSERITO UN CARATTERE NON VALIDO\n");
        premiTastoPerContinuare();
        return domandaTRE();    //RICARICO LA DOMANDA SE E' STATO INSERITO UN CARATTERE NON VALIDO
    }
}

/*
FUNZIONE CHE RICHIAMA TUTTE LE DOMANDE, SOMMA I VALORI RITORNATI E RITORNA LA SOMMA ALLA FUNZIONE CHIAMANTE
*/
int domandeRichiestaAppuntamento()
{
    //E' POSSIBILE INDISTINTAMENTE ALTRE DOMANDE IN FUTURO
    return domandaUNO()+domandaDUE()+domandaTRE();      //LA FUNZIONE RESTITUISCE LA SOMMA DEI VALORI DI RITORNO DELLE TRE DOMANDE
}

/*
ELIMINA UN DETERMINATO NODO DALLA LISTA DINAMICA
*/
void eliminaNodoRichiestaPrenotazione(RichiestaPrenotazione ** nodo)
{
    RichiestaPrenotazione *tmp=(*nodo);    //LA VARIABILE TMP SARA' UN PUNTATORE AL NODO PUNTATO DA TESTA

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

    free(tmp);      //LIBERO LO SPAZIO OCCUPATO DA TMP
}

/*
PRENDE IN INGRESSO UN CODICE FISCALE, TROVA IL NODO CON IL CODICE FISCALE E LO ELIMINA. RESTITUISCE TRUE SE L'ELIMINAZIONE E' ANDATA A BUON FINE
*/
bool eliminaRichiestaPrenotazione(char *codiceFiscale, RichiestaPrenotazione **nodo)
{
    if((*nodo)==NULL)
    {
        return false;   //SE LA LISTA E' TERMINATA RESTITUISCE FALSE IN QUANTO IL CODICE FISCALE NON E' STATO TROVATO
    }
    else if(strcmp((*nodo)->codiceFiscale,codiceFiscale)==0) //ENTRO NEL BLOCCO SE IL CODICE FISCALE IN INPUT COINCIDE CON QUELLO DEL NODO ATTUALE
    {
        eliminaNodoRichiestaPrenotazione(&(*nodo)); //ELIMINO IL NODO E RESTITUISCO POI TRUE IN QUANTO IL CODICE FISCALE E' STATO TROVATO
        return true;
    }
    else
    {
        return eliminaRichiestaPrenotazione(codiceFiscale,&((*nodo)->next));    //RICHIAMO LA FUNZIONE RICORSIVAMENTE
    }
}

/*
PRENDE IN INGRESSO LA LISTA DI RICHIESTE E LE PROCESSA METTENDOLE NELLA LISTA DEGLI APPUNTAMENTI FISSATI
*/
void fissaAppuntamenti(char *pinOperatore,AppuntamentoFissato **testaAppuntamento, RichiestaPrenotazione ** testaRichiesta,int numeroAppuntamento)
{
    if((*testaRichiesta)!=NULL)
    {
        inserimentoInCodaAppuntamentoFissato(&(*testaAppuntamento),(*testaRichiesta)->codiceFiscale,pinOperatore,"n",(*testaRichiesta)->gravita,numeroAppuntamento);
        eliminaNodoRichiestaPrenotazione(&(*testaRichiesta));   //ELIMINA LA RICHIESTA APPENA FISSATA, IN QUESTO CASO SARA' SEMPRE LA TESTA DELLA LISTA
        fissaAppuntamenti(pinOperatore,&(*testaAppuntamento),&(*testaRichiesta),numeroAppuntamento);    //RICHIAMO LA FUNZIONE RICORSIVAMENTE
    }

}

/*
PRENDE IN INGRESSO IL NUOVO NODO, IL PRECEDENTE, IL SUCCESSIVO E LI COLLEGA
*/
void inserimentoNodoRichiestaPrenotazione(RichiestaPrenotazione ** newNode, RichiestaPrenotazione * prevNode, RichiestaPrenotazione *nextNode, char *codiceFiscaleInput, int gravita)
{
    (*newNode)->prev=prevNode;
    (*newNode)->next=nextNode;
    strcpy((*newNode)->codiceFiscale,codiceFiscaleInput);
    (*newNode)->gravita=gravita;
}

/*
INSERISCE LE NUOVE RICHIESTE NELLA LISTA IN ORDINE DECRESCENTE IN BASE ALLA GRAVITA'
*/
void inserimentoRichiestaPrenotazioneGravitaDecrescente(RichiestaPrenotazione ** nodo,char *codiceFiscaleInput, int gravita )
{
    if(*nodo==NULL)     //SE LA LISTA E' VUOTA INSERISCO Il NODO IN TESTA
    {
        RichiestaPrenotazione *newNode = malloc(sizeof(RichiestaPrenotazione));
        inserimentoNodoRichiestaPrenotazione(&newNode,NULL,NULL,codiceFiscaleInput,gravita);
        (*nodo)=newNode;
    }
    else if(gravita>(*nodo)->gravita)   //SE LA GRAVITA' DEL NUOVO NODO E' MAGGIORE DEL NODO ATTUALE, INSERISCO IL NUOVO NODO PRIMA DEL NODO ATTUALE
    {
        RichiestaPrenotazione *newNode = malloc(sizeof(RichiestaPrenotazione));
        inserimentoNodoRichiestaPrenotazione(&newNode,(*nodo)->prev,(*nodo),codiceFiscaleInput,gravita);
        (*nodo)->prev=newNode;
        (*nodo)=newNode;

    }
    else if((*nodo)->next==NULL)    //SE IL NODO ATTUALE E' L'ULTIMO, INSERISCO IL NUOVO NODO IN FONDO ALLA LISTA
    {
        RichiestaPrenotazione *newNode = malloc(sizeof(RichiestaPrenotazione));
        inserimentoNodoRichiestaPrenotazione(&newNode,(*nodo),NULL,codiceFiscaleInput,gravita);
        (*nodo)->next=newNode;
    }
    else
        inserimentoRichiestaPrenotazioneGravitaDecrescente(&((*nodo)->next),codiceFiscaleInput,gravita);    //RICHIAMO RICORSIVAMENTE LA FUNZIONE
}

/*
MOSTRA LO STATO DELLA PROPRIA RICHIESTA DI APPUNTAMENTO. SE L'APPUNTAMENTO E' STATO FISSATO, VERRANO INDICATI TRA QUANTI GIORNI PRESENTARSI AL LABORATORIO
*/
bool mostraStatoRichiestaPrenotazione(char *codiceFiscale,RichiestaPrenotazione *nodoRichiesta,AppuntamentoFissato *nodoAppuntamento )
{
    bool richiestaGiaPresente=false;
    richiestaGiaPresente=trovaRichiesta(codiceFiscale,nodoRichiesta); //TROVA RICHIESTA RESTITUISCE TRUE SE VIENE TROVATA UNA RICHIESTA DI PRENOTAZIONE DEL CODICE FISCALE PASSATO COME PARAMETRO
    if(richiestaGiaPresente)        //ENTRO NEL BLOCCO SE LA RICHIESTA DI PRENOTAZIONE E'STATA TROVATA
    {
        printf("# La tua richiesta di appuntamento non e'stata ancora elaborata.\n  Ti sara comunicata una data al piu' presto\n\n");
    }
    else    //ENTRO NEL BLOCCO SE LA RICHIESTA DI PRENOTAZIONE NON E' STATA TROVATA
    {
        if(nodoAppuntamento==NULL)
            richiestaGiaPresente=false;
        else
        {
            //VERIFICO ADESSO SE E' PRESENTE TRA GLI APPUNTAMENTI FISSATI
            richiestaGiaPresente=trovaAppuntamento(codiceFiscale,nodoAppuntamento,nodoAppuntamento->numeroAppuntamento-1);
        }

    }

    if(!richiestaGiaPresente)//ENTRO NEL BLOCCO SE NON E'PRESENTE ALCUNA RICHIESTA O APPUNTAMENTO FISSATO PER IL CODICE FISCALE PASSATO IN INPUT
        printf("# Non e' stato fissato alcun appuntamento ne' e' stata inoltrata alcuna richiesta di tampone\n\n");

    return richiestaGiaPresente;
}

/*
RESTITUISCE TRUE SE NON CI SONO RICHIESTE DI PRENOTAZIONI
*/
bool richiestaPrenotazioneIsVoid(RichiestaPrenotazione *testa)
{
    if(testa==NULL)
        return true;
    else
        return false;
}

/*
RECUPERA LE RICHIESTE DI PRENOTAZIONE DAL FILE DI TESTO E LE INSERISCE ALL'INTERNO DELLA STRUTTURA DINAMICA
*/
void riempiListaRichiestePrenotazioni(FILE *fPtr,RichiestaPrenotazione ** testa )
{
    char codiceFiscale[17];
    int gravita;
    if((fscanf(fPtr,"%16s%d",codiceFiscale,&gravita))==2)        //FSCANF RESTITUISCE UN INTERO PARI AL NUMERO DI VARIABILI A CUI SONO STATI ASSEGNATI DEI VALORI
    {
        inserimentoRichiestaPrenotazioneGravitaDecrescente(&(*testa),codiceFiscale,gravita);
        riempiListaRichiestePrenotazioni(fPtr,&((*testa)));
    }
}

/*
STAMPO A SCHERMO TUTTE LE RICHIESTE DI PRENOTAZIONE
*/
void stampaRichiestePrenotazione(RichiestaPrenotazione *testa)
{
    if(testa!=NULL)
    {
        printf("% -25s%-25d\n",testa->codiceFiscale,testa->gravita);
        stampaLinea(50);
        stampaRichiestePrenotazione(testa->next);
    }
}

/*
PRENDE IN INGRESSO UN CODICE FISCALE. SE VIENE TROVATO UN APPUNTAMENTO FISSATO DI QUEL CODICE FISCALE RESTITUISCE TRUE
*/
bool trovaAppuntamento(char *codiceFiscale,AppuntamentoFissato *nodoAppuntamento,int posizione)
{
    if(nodoAppuntamento==NULL)
    {
        return false;
    }
    //ENTRO NEL BLOCCO SE IL CODICE FISCALE COINCIDE CON QUELLO DEL NODO ATTUALE E SE L'APPUNTAMENTO NON E' STATO ELIMINATO
    //QUANDO ELIMINO UN APPUNTAMENTO, IL NODO NON VIENE ELIMINATO PER PERMETTERE IL CONTEGGIO DEI GIORNI
    else if(strcmp(nodoAppuntamento->codiceFiscale,codiceFiscale)==0 && strcmp(nodoAppuntamento->eliminato,"n")==0)
    {
        int giorno = posizione/6;   //RICAVO TRA QUANTI GIORNI C'E' L'APPUNTAMENTO
        printf("# La tua richiesta di tampone e' stata elaborata da un nostro operatore.\n\n");
        if(giorno==0)
            printf("# Presentarsi al laboratorio oggi.\n\n");
        else if(giorno==1)
            printf("# Presentarsi al laboratorio domani.\n\n");
        else
            printf("# Presentarsi al laboratorio tra %d giorni.\n\n",giorno);
        return true;
    }
    else
    {
        posizione+=1;       //INCREMENTO LA POSIZIONE CHE STA AD INDICARE, PARTENDO DA 0, LA POSIZIONE DELL'APPUNTAMENTO ALL'INTERNO DELLA LISTA
        return trovaAppuntamento(codiceFiscale,nodoAppuntamento->next,posizione);       //RICHIAMO RICORSIVAMENTE LA FUNZIONE
    }
}

/*
RESTIUISCE TRUE SE VIENE TROVATA UNA RICHIESTA DI PRENOTAZIONE DEL CODICE FISCALE PASSATO COME PARAMETRO
*/
bool trovaRichiesta(char *codiceFiscale,RichiestaPrenotazione *nodoRichiesta)
{
    if(nodoRichiesta==NULL)
    {
        return false;
    }
    else if(strcmp(nodoRichiesta->codiceFiscale,codiceFiscale)==0)
    {
        return true;
    }
    else
        return trovaRichiesta(codiceFiscale,nodoRichiesta->next);
}

