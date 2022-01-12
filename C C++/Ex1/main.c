#include <stdio.h>

typedef struct numeri{

    int numeri[30];
    struct numeri *next;
}numeri;

void gestioneErrore();
numeri *nuovoNodo();
numeri *leggiFile(FILE *fp, numeri *lista);
void scriviLista(numeri *lista);
numeri *rimuovinumeri(numeri *lista, int soglia);
void scriviFile(FILE *fp, numeri *lista);
void freeLista(numeri *lista);


int main(){	

    FILE *f;
    char nomeFile[30];

    printf("Inserisci nome file: ");
    scanf("%s", nomeFile);

    f = fopen(nomeFile, "r");



    

}