#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct lista
{
    int data;
    struct lista *next;
    struct lista *prev;
}Lista;

typedef struct edge
{
    int key;
    struct edge *next;
}Edge;

typedef struct graph
{
    int numeroVertici;
    Edge **listaAdiacenza;
}Graph;

void inserimentoInTesta(Lista **testa,int data);
void eliminaNodo(Lista **testa, Lista **nodo);
Graph *CreaGrafo(int numeroVertici);
int GrafoVuoto(Graph *G);
void AggiungiArco(Graph *G, int u, int v);

int main(void){

    Lista **testa;
    function()
    return 0;

}

void inserimentoInTesta(Lista **testa,int data) 
{
    Lista *newNode=malloc(sizeof(Lista));

    newNode->data=data;
    newNode->next=(*testa);
    newNode->prev=NULL;

    if(*testa!=NULL)
        (*testa)->prev=newNode;

    (*testa)=newNode;
}

void eliminaNodo(Lista **testa,Lista **nodo) 
{
    Lista *tmp=(*nodo);

    if((*nodo)->prev!=NULL)
    {
        (*nodo)->prev->next=(*nodo)->next;
    }
    else
        (*testa)=(*testa)->next;

    if((*nodo)->next!=NULL)
    {
        (*nodo)->next->prev=(*nodo)->prev;
    }

    free(tmp);

}

void AggiungiArco(Graph *G, int u, int v)
{
    if(GrafoVuoto(G)!=1)
    {
        Edge *new, *e;
        new = (Edge*)malloc(sizeof(Edge));
        if (new==NULL)
        {
            printf("ERRORE: impossibile allocare memoria \n");
        }
        else
        {
            new->key=v;
            new->next=NULL;
            if (G->listaAdiacenza[u]==NULL)
            {
                G->listaAdiacenza[u]=new;
            }
            else
            {
                e=G->listaAdiacenza[u];
                while (e->next!=NULL)
                {
                    e=e->next;
                }
                e->next=new;
            }
         }
    }
    else
    {
        printf("\nATTENZIONE!\n Grafo vuoto\n");
    }
}

int GrafoVuoto(Graph *G)
{
    if(G==NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

Graph *CreaGrafo(int n)
{
    Graph *G; int i;
    G = (Graph*)malloc(sizeof(Graph));
    if (G==NULL)
    {
        printf("ERRORE: impossibile allocare memoria per il grafo\n");
    }
    else
    {
        G->listaAdiacenza=(Edge**)malloc(n*sizeof(Edge*));
        if (G->listaAdiacenza==NULL && n>0)
        {
            printf("ERRORE: imp. allocare mem. per la lista del grafo\n");
            free(G);
            G=NULL;
        }

        else
        {
            G->numeroVertici=n;
            for (i=0;i<n;i++)
            {
                G->listaAdiacenza[i]=NULL;
            }
        }
    }
    return G ;
}

void insert(Lista *testa, int new_data)
{
    // creo il nuovo nodo e gli alloco uno spazio di memoria
    Lista *new_node;
    new_node = (Lista*)malloc(sizeof(Lista));

    // inizializzo il nuovo nodo e gli inserisco il nuovo dato
    new_node->data = new_data;
    new_node->next = NULL;

    // inserisco il nodo all'interno della lista: due casi possibili

    // CASO 1: la lista e' vuota (count e' 0)
    // il nuovo nodo fara' sia da header che da tailer
    if (testa->count == 0)
    {
        new_node->prev = NULL;
        testa->header = testa->tailer = new_node;
    }
    // CASO 2: la lista contiene gia' almeno un elemento
    // aggancio il nuovo nodo alla fine della lista
    // dopo l'inserimento, il nuovo nodo sara' quindi il tailer della lista
    else
    {
        new_node->prev = testa->tailer;
        testa->tailer->next = new_node;
        testa->tailer = new_node;
    }

    // aumento il contatore dei nodi della lista
    testa->count++;
}