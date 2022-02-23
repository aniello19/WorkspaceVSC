#include "driver.h"

/*
RECUPERA I DRIVER DALLA STRUTTURA DINAMICA E LI SALVA SUL FILE DI TESTO
*/
void creaFileDriver(FILE * fPtr, Driver *testa)
{
    if(testa!=NULL)                 //ENTRO NEL BLOCCO SOLO SE NON HO RAGGIUNTO LA FINE DELLA LISTA
    {
        fprintf(fPtr,"%s %s %d %d\n",testa->username,testa->password,testa->peso,testa->pesoMerce);     //STAMPO SU FILE DI TESTO
        creaFileDriver(fPtr,testa->next);
    }
}

/*
VERIFICA CHE LE CREDENZIALI DEL DRIVER INSERITE DALL'UTENTE SIANO CORRETTE
*/
bool verificaCredenzialiDriver(Driver *testa,char *usernameInput, char *passwordInput)
{
    if(testa!=NULL)     //ENTRO NEL BLOCCO SE LA LITA NON E' TERMINATA
    {
        if(strcmp(testa->username,usernameInput)==0  && strcmp(testa->password,passwordInput)==0)     //VERIFICO CHE USERNAME E PASSWORD COINCIDANO CON QUELLE DEL NODO ATTUALE
        {
            return true;        //RESTITUISCO TURE SE LE CREDENZIALI SONO STATE TROVATE
        }
        else
            return verificaCredenzialiDriver(testa->next,usernameInput,passwordInput);        //SE LE CREDENZIALI NON COINCIDANO RICHIAMO RICORSIVAMENTE LA FUNZIONE
    }
    else
        return false;       //RESTITUISCO FALSE SE LA LISTA E' TERMINATA E QUINDI LE CREDENZIALI NON SONO STATE TROVATE
}

/*
RECUPERA I DRIVER DAL FILE DI TESTO E LI INSERISCE ALL'INTERNO DELLA STRUTTURA DINAMICA
*/
void riempiListaDriver(FILE * fPtr, Driver * * testa)
{
    char username[11];
    char password[20];
    int peso;
    int pesoMerce;
    if(fscanf(fPtr,"%10s%19s%d%d",username,password,&peso,&pesoMerce) == 4)        //FSCANF RESTITUISCE UN INTERO PARI AL NUMERO DI VARIABILI A CUI SONO STATI ASSEGNATI DEI VALORI
    {
        //FSCANF HA ANCHE LA FUNZIONE DI FAR AVANZARE IL PUNTATORE ALL'INTERNO DEL FILE
        inserimentoInTestaDriver(&(*testa),username,password,peso,pesoMerce);        //INSERISCO I VALORI TROVATI ALL'INTERNO DEL FILE NELLA STRUTTURA DINAMICA
        riempiListaDriver(fPtr,&(*testa));         //RICHIAMO LA FUNZIONE, NON HO BISOGNO DI FAR AVANZARE IL PUNTATORE DEL FILE
    }
}

/*
INSERISCE IL NUOVO DRIVER IN TESTA ALLA LISTA
*/
void inserimentoInTestaDriver(Driver ** testa, char *usernameInput, char *passwordInput,int pesoInput,int pesoMerceInput)
{
    Driver *newNode = malloc(sizeof(Driver));     //CREO UN NUOVO PUNTATORE A DRIVER
    if(*testa==NULL)            //SE LA LISTA E' VUOTA VORRA' DIRE CHE PREV E NEXT DI NEWNODE SARANNO NULL
    {
        inserimentoNodoDriver(&newNode,NULL,NULL,usernameInput,passwordInput,pesoInput,pesoMerceInput);
        (*testa)=newNode;
    }
    else        //LA LISTA NON E' VUOTA
    {
        inserimentoNodoDriver(&newNode,NULL,(*testa),usernameInput,passwordInput,pesoInput,pesoMerceInput);    //INSERISCO NEW NODE CON NEXT UGUALE ALLA TESTA ATTUALE
        (*testa)->prev=newNode;     //IL NUOVO NODO INSERITO VIENE PRIMA DELLA VECCHIA TESTA
        (*testa)=newNode;           //IL NUOVO NODO ASSUME IL RUOLO DI TESTA DELLA LISTA
    }
}

/*
PRENDE IN INGRESSO IL NUOVO NODO, IL PRECEDENTE, IL SUCCESSIVO E LI COLLEGA
*/
void inserimentoNodoDriver(Driver ** newNode, Driver * prevNode, Driver *nextNode, char *usernameInput, char *passwordInput, int pesoInput, int pesoMerceInput)
{
    (*newNode)->prev=prevNode;
    (*newNode)->next=nextNode;
    strcpy((*newNode)->username,usernameInput);               //LA FUNZIONE STCPY COPIA LA SECONDA STRINGA NELLA PRIMA
    strcpy((*newNode)->password,passwordInput);
    (*newNode)->peso=pesoInput;
    (*newNode)->pesoMerce=pesoMerceInput;
}

/*
RESTITUISCE IL PUNTATORE AL DRIVER AVENTE USERNAME PARI A QUELLO PASSATO COME PARAMETRO
SI PRESUPPONE CHE L'USERNAME SIA PRESENTE SULLA PIATTAFORMA
*/
Driver * getDriverByUsername(Driver *testa,char *username)
{
    if(strcmp(testa->username,username)==0)
        return testa;
    else
        return getDriverByUsername(testa->next,username);
}

/*
LA FUNZIONE RESTITUISCE TRUE SE l'USERNAME E' GIA' PRESENTE SULLA PIATTAFORMA
*/
bool usernameGiaPresente(Driver *nodo,char* username)
{
    if (nodo==NULL)
    {
        return false;       //SE LA LISTA E' TERMINATA RITORNO FALSE
    }
    else if (strcmp(nodo->username,username)==0)
    {
        return true;        //SE L'USERNAME E' PRESENTE SULLA PIATTAFORMA RITORNO TRUE
    }
    else
    {
        return usernameGiaPresente(nodo->next,username);       //RICHIAMO LA FUNZIONE RICORSIVAMENTE
    }
}

