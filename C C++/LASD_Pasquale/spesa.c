#include "spesa.h"
/*
INIZIALIZZA IL VETTORE DI PRODOTTI
*/
void riempiVettoreProdotti()
{
    strcpy(listaProdotti[0].nome,"Sacco di farina");
    strcpy(listaProdotti[1].nome,"Bancale di cemento");
    strcpy(listaProdotti[2].nome,"Cassa di banane");
    strcpy(listaProdotti[3].nome,"Pescato locale");
    strcpy(listaProdotti[4].nome,"Acqua potabile");
    strcpy(listaProdotti[5].nome,"Bestiame vivo");

    listaProdotti[0].peso=100;
    listaProdotti[1].peso=12000;
    listaProdotti[2].peso=50;
    listaProdotti[3].peso=300;
    listaProdotti[4].peso=1000;
    listaProdotti[5].peso=5000;

}
/*
PERMETTE DI FARE LA SPESA AL DRIVER, RESTITUISCE IL PESO COMPLESSIVO DEGLI ARTICOLI
*/
int faiSpesa(Carrello **nodo,int pesoComplessivoProdotti,int pesoIniziale)
{
    int quantita;
    int scelta;
    int pesoProdotto;
    stampaTitolo();
    stampaProdotti();
    printf("                CARRELLO\n\n");
    printf("# %-30s%-30s\n","NOME PRODOTTO","QUANTITA' ACQUISTATA");
    stampaCarrello(*nodo);
    stampaLinea(100);

    printf("# Inserisci ID del prodotto da acquistare (-1 per tornare indietro , 0 per terminare la spesa)\n\n");
    scanf("%d",&scelta);
    clear_buffer();

    if(scelta==-1)          //SE PREMO -1 ANNULLO LA SPESA E RESTITUISCO IL PESO INIZIALE
    {
        freeCarrello(&(*nodo));
        system("cls");
        return pesoIniziale;
    }
    else if(scelta==0)  //SE PREMO 0 CONFERMO L'ACQUISTO E RESTITUISCO IL PESO DEI PRODOTTI ACQUISTATI
    {
        freeCarrello(&(*nodo));
        system("cls");
        return pesoComplessivoProdotti;
    }
    else if(scelta<=6)
    {
        printf("# Inserisci quantita' del prodotto da acquistare\n\n");
        scanf("%d",&quantita);
        clear_buffer();
        if(quantita>0)
        {
            pesoProdotto=quantita*listaProdotti[scelta-1].peso;
            pesoComplessivoProdotti+=pesoProdotto;
            inserisciProdottoCarrello(&(*nodo),listaProdotti[scelta-1].nome,quantita);
        }
        else
        {
            printf("ATTENZIONE-- VALORE NON VALIDO\n");
            premiTastoPerContinuare();
        }

    }
    system("cls");
    return faiSpesa(&(*nodo),pesoComplessivoProdotti,pesoIniziale);

}

/*
INSERISCE NEL CARRELLO UN PRODOTTO CON LA QUANTITA' ACQUISTATA, SE IL PRODOTTO E' STATO GIA'
ACQUISTATO IN PRECEDENZA LA QUANTITA' SI AGGIORNA
*/
void inserisciProdottoCarrello(Carrello **nodo,char *nome,int quantita)
{
    if(*nodo==NULL)
    {
        Carrello *newNode = malloc(sizeof(Carrello));
        strcpy(newNode->nome,nome);
        newNode->quantita=quantita;
        newNode->next=NULL;
        (*nodo)=newNode;
    }
    else if(strcmp((*nodo)->nome,nome)==0)
    {
        (*nodo)->quantita+=quantita;
    }
    else
    {
        inserisciProdottoCarrello(&(*nodo)->next,nome,quantita);
    }
}


/*
STAMPA A SCHERMO IL CARRELLO
*/
void stampaCarrello(Carrello *nodo)
{
    if(nodo!=NULL)
    {
        printf("# %-30s%-30d\n",nodo->nome,nodo->quantita);
        stampaCarrello(nodo->next);
    }
}

/*
STAMPA LA LISTA DEI PRODOTTI ACQUISTABILI DAL DRIVER
*/
void stampaProdotti()
{
    printf("# %-30s%-30s%-30s\n","ID PRODOTTO","NOME","PESO");
    for(int i=0;i<NUMEROPRODOTTI;i++)
    {
        printf("# %-30d%-30s%-30d\n",i+1,listaProdotti[i].nome,listaProdotti[i].peso);
    }
    stampaLinea(100);
}


/*
SVUOTA IL CARRELLO
*/
void freeCarrello(Carrello **nodo)
{
    if((*nodo!=NULL))
    {
        Carrello *tmp= (*nodo);
        (*nodo)=(*nodo)->next;
        free(tmp);
        freeCarrello(&(*nodo));
    }
}
