#include<stdio.h>
#include<stdlib.h>

typedef struct nodo
{
    int data;
    int nR;
    int nC;
    struct nodo *next;

}nodo;

typedef struct dati
{
    int n;

}dati;

int **letturaFile(dati *);
void printM(int **, dati *);
nodo *creaL(int **, dati *);
void printL(nodo *);
nodo *modLista(nodo *);
int **modMat(int **, dati *);
void scritturaFile(int** , dati*);
int **aggMat(int **, dati *, nodo *);