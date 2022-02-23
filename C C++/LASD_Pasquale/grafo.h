/*#ifndef GRAFO
#define GRAFO
*/
#define INFINITO 9999
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "listaDoppiamenteConcatenata.h"
typedef struct edge
{
    int key;
    int capacitaPonte;
    int lunghezzaPonte;
    struct edge *next;
}Edge;

typedef struct graph
{
    int numeroVertici;
    Edge ** listaAdiacenza;
}Graph;

//CREA UN GRAFO DI "numeroVertici" vertici
Graph *CreaGrafo(int numeroVertici);

//RESTITUISCE 1 SE IL GRAFO PASSATO COME ARGOMENTO E' 1
int GrafoVuoto(Graph *G);

//AGGIUNGE UN ARCO DAL VERTICE U AL VERTICE V.
void   AggiungiArco(Graph *G, int u, int v,int capacitaPonte,int lunghezzaPonte);

//STAMPA A SCHERMO L'ARCIPELAGO
void printArcipelago();

//INIZIALIZZA I VETTORI DISTANZA E PREDECESSORE
void inizializzaSingolaSorgente(Graph *grafo,int sorgente,int *distanza,int *predecessore);

//INIZIALIZZA LA LISTA DI VERTICI NON ANCORA OTTIMIZZATI
void inizializzaLista(Lista ** testa,int numeroVertice);

//VERIFICA SE E' SODDISFATTA LA CONDIZIONE DI RILASSAMENTO E NEL CASO LA EFFETTUA
void relax(int vertice1,int vertice2,int lunghezzaPonte, int* distanza, int * predecessore);

//TRA I VERTICI PRESENTI NELAL LISTA TROVA QUELLO CON DISTANZA DALAL SORGENTE MINORE, ELIMINA IL NODO DALAL LISTA E POI RESTITUISCE L'INDICE
int trovaIndiceMinimo(Lista **testa,int *distanza);

//STAMPA IL PERCORSO MINIMO CALCOLATO DA DIJKSTRA
void stampaPercorso(int sorgente,int destinazione,int *predecessore);

//CREA L'ARCIPELAGO INIZIALIZZANDO TUTTI GLI ARCHI TRA LE ISOLE
Graph* CreazioneIsola();

//aLGORITMO PER CALCOLARE IL PERCORSO MINIMO DA SORGENTE A DESTINZAZIONE. NON CALCOLA CONSIDERA GLI ARCHI AVENTI CAPACITA MINORE DI PESOCAMION
int algoritmoDijkstra(Graph *grafo,int sorgente,int destinazione,int pesoCamion);



//#endif // GRAFO

