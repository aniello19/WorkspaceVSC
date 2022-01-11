#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct azienda{

    char NomeAzienda[30];
    int Dipendenti;
    int Dipartimenti;
    int Sedi;
    struct azienda *next;

}azienda;

void gestioneErrore();
azienda *nuovoNodo(char *nomeAzienda, int dipendenti, int dipartimenti, int sedi);
azienda *leggiFile(FILE *fp, azienda *lista);
void scriviLista(azienda *lista);
azienda *rimuoviazienda(azienda *lista, int soglia);
void scriviFile(FILE *fp, azienda *lista);
void freeLista(azienda *lista);

int main(void){

    FILE *fp;
    azienda *lista = NULL;

    fp = fopen("dati.txt", "r");
    if(fp==NULL) gestioneErrore();
    lista=leggiFile(fp,lista);
    fclose(fp);

    scriviLista(lista);

    printf("\n");

    lista=rimuoviazienda(lista,300);
    scriviLista(lista);

    fp = fopen("dati2.txt", "w");
    scriviFile(fp, lista);
    fclose(fp);

    freeLista(lista);

    return 0;
}

void gestioneErrore(){

    printf("Errore!\n");
    exit(0);

}

azienda *nuovoNodo(char *nomeAzienda, int dipendenti, int dipartimenti, int sedi){

    azienda *nodo;

    nodo = (azienda*)malloc(sizeof(azienda));
    if (nodo==NULL) return NULL;

    strcpy(nodo->NomeAzienda, nomeAzienda);
    nodo->Dipendenti=dipendenti;
    nodo->Dipartimenti=dipartimenti;
    nodo->Sedi=sedi;
    nodo->next=NULL;

    return nodo;

}

static void freeNodo(azienda *nodo){

    free((void *) nodo);

}

azienda *inserisciLista(azienda *nodo, azienda *lista){

    if (lista==NULL) return nodo;
    lista->next=inserisciLista(nodo, lista->next);
    return lista;

}

azienda *rimuoviNodo(azienda *lista, azienda *nodo){

    azienda *tmp;
  
    if (lista == nodo) {
        tmp = lista->next;
        freeNodo(lista);
        return tmp;
    }

    lista->next = rimuoviNodo(lista->next,nodo);
}

void freeLista(azienda *lista){

    if (lista != NULL) {
        freeLista(lista->next);
        freeNodo(lista);
    }
}


void scriviLista(azienda *lista){

    int i;
  
    while (lista!=NULL) {
        printf("%s %d %d %d ",lista->NomeAzienda,lista->Dipendenti, lista->Dipartimenti, lista->Sedi);
        printf("\n");
        lista = lista->next;
    }
}

azienda *leggiFile(FILE *fp, azienda *lista)
{
  char nome[30];
  int dipendenti, dipartimenti, sedi;
  azienda *nodo;

  while(fscanf(fp,"%s%d%d%d",nome,&dipendenti,&dipartimenti,&sedi)==4){
    nodo = nuovoNodo(nome,dipendenti,dipartimenti,sedi);
    if (nodo==NULL) gestioneErrore();
    lista = inserisciLista(nodo, lista);
  }
  return lista;
}


void scriviFile(FILE *fp, azienda *lista)
{
  int dipendenti, dipartimenti, sedi;
  
  while (lista!=NULL) {
    dipendenti = lista->Dipendenti;
    dipartimenti = lista->Dipartimenti;
    sedi = lista->Sedi;
    fprintf(fp,"%s %d %d %d ", lista->NomeAzienda, dipendenti, dipartimenti, sedi);

    fprintf(fp,"\n");
    lista = lista->next;
  }
}
azienda *rimuoviazienda(azienda *lista, int soglia)
{
  if (lista==NULL) return lista;
  if (lista->Dipendenti<soglia) {
    lista = rimuoviNodo(lista, lista);
    lista = rimuoviazienda(lista, soglia);
  } else lista->next = rimuoviazienda(lista->next, soglia);
  
  return lista;
}



