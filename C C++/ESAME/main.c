#include<stdio.h>
#include<stdlib.h>
#include"funzioni.h"

int main(void){

    dati *dim =(dati*)malloc(sizeof(dim)); 

    int **mat = letturaFile(dim); //leggo il file in input e aggiungo i valori nella matrice

    mat = modMat(mat, dim); //ottengo la matrice trasposta
 
    nodo *testa = creaL(mat, dim); //creo la lista

    testa = modLista(testa); //modifico la lista eliminando gli elementi dispari

    mat = aggMat(mat, dim, testa); //aggiorno la matrice

    scritturaFile(mat, dim); //creo e scrivo il file output

    return 0;
}