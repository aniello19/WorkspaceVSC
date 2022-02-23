#include "operatore.h"

/*
RECUPERA OPERATORI DALLA STRUTTURA DINAMICA E LI SALVA SUL FILE DI TESTO
*/
void creaFileOperatori(FILE * fPtr, Operatore *testa)
{
    if(testa!=NULL)                 //ENTRO NEL BLOCCO SOLO SE NON HO RAGGIUNTO LA FINE DELLA LISTA
    {
        fprintf(fPtr,"%s %s\n",testa->pin,testa->password);     //STAMPO SU FILE DI TESTO
        creaFileOperatori(fPtr,testa->next);
    }
}

/*
INSERISCE IL NUOVO OPERATORE IN TESTA ALLA LISTA
*/
void inserimentoInTestaOperatore(Operatore ** testa, char *pinInput, char *passwordInput)
{
    Operatore *newNode = malloc(sizeof(Operatore));     //CREO UN NUOVO PUNTATORE A OPERATORE
    if(*testa==NULL)            //SE LA LISTA E' VUOTA VORRA' DIRE CHE PREV E NEXT DI NEWNODE SARANNO NULL
    {
        inserimentoNodoOperatore(&newNode,NULL,NULL,pinInput,passwordInput);
        (*testa)=newNode;
    }
    else        //LA LISTA NON E' VUOTA
    {
        inserimentoNodoOperatore(&newNode,NULL,(*testa),pinInput,passwordInput);    //INSERISCO NEW NODE CON NEXT UGUALE ALLA TESTA ATTUALE
        (*testa)->prev=newNode;     //IL NUOVO NODO INSERITO VIENE PRIMA DELLA VECCHIA TESTA
        (*testa)=newNode;           //IL NUOVO NODO ASSUME IL RUOLO DI TESTA DELLA LISTA
    }
}

/*
PRENDE IN INGRESSO IL NUOVO NODO, IL PRECEDENTE, IL SUCCESSIVO E LI COLLEGA
*/
void inserimentoNodoOperatore(Operatore ** newNode, Operatore * prevNode, Operatore *nextNode, char *pinInput, char *passwordInput)
{
    (*newNode)->prev=prevNode;
    (*newNode)->next=nextNode;
    strcpy((*newNode)->pin,pinInput);               //LA FUNZIONE STCPY COPIA LA SECONDA STRINGA NELLA PRIMA
    strcpy((*newNode)->password,passwordInput);
}

/*
RECUPERA GLI OPERATORI DAL FILE DI TESTO E LI INSERISCE ALL'INTERNO DELLA STRUTTURA DINAMICA
*/
void riempiListaOperatori(FILE * fPtr, Operatore * * testa)
{
    char pin[5];
    char password[20];
    if(fscanf(fPtr,"%4s%19s",pin,password) == 2)        //FSCANF RESTITUISCE UN INTERO PARI AL NUMERO DI VARIABILI A CUI SONO STATI ASSEGNATI DEI VALORI
    {
        //FSCANF HA ANCHE LA FUNZIONE DI FAR AVANZARE IL PUNTATORE ALL'INTERNO DEL FILE
        inserimentoInTestaOperatore(&(*testa),pin,password);        //INSERISCO I VALORI TROVATI ALL'INTERNO DEL FILE NELLA STRUTTURA DINAMICA
        riempiListaOperatori(fPtr,&(*testa));         //RICHIAMO LA FUNZIONE, NON HO BISOGNO DI FAR AVANZARE IL PUNTATORE DEL FILE
    }
}

/*
LA FUNZIONE RESTITUISCE TRUE SE IL PIN E' GIA' PRESENTE SULLA PIATTAFORMA
*/
bool pinGiaPresente(Operatore *nodo,char* pin)
{
    if (nodo==NULL)
    {
        return false;       //SE LA LISTA E' TERMINATA RITORNO FALSE
    }
    else if (strcmp(nodo->pin,pin)==0)
    {
        return true;        //SE IL PIN E' PRESENTE SULLA PIATTAFORMA RITORNO TRUE
    }
    else
    {
        return pinGiaPresente(nodo->next,nodo);       //RICHIAMO LA FUNZIONE RICORSIVAMENTE
    }
}

/*
VERIFICA CHE LE CREDENZIALI OPERATORE INSERITE DALL'UTENTE SIANO CORRETTE
*/
bool verificaCredenzialiOperatore(Operatore *testa,char *pinInput, char *passwordInput)
{
    if(testa!=NULL)     //ENTRO NEL BLOCCO SE LA LITA NON E' TERMINATA
    {
        if(strcmp(testa->pin,pinInput)==0  && strcmp(testa->password,passwordInput)==0)     //VERIFICO CHE CF E PASSWORD COINCIDANO CON QUELLE DEL NODO ATTUALE
        {
            return true;        //RESTITUISCO TURE SE LE CREDENZIALI SONO STATE TROVATE
        }
        else
            return verificaCredenzialiOperatore(testa->next,pinInput,passwordInput);        //SE LE CREDENZIALI NON COINCIDANO RICHIAMO RICORSIVAMENTE LA FUNZIONE
    }
    else
        return false;       //RESTITUISCO FALSE SE LA LISTA E' TERMINATA E QUINDI LE CREDENZIALI NON SONO STATE TROVATE
}

