
#include "grafo.h"

/*
CREA L'ARCIPELAGO INIZIALIZZANDO TUTTI GLI ARCHI TRA LE ISOLE
*/
Graph* CreazioneIsola()
{
    Graph* g=CreaGrafo(9);
    AggiungiArco(g,0,1,2000,3);
    AggiungiArco(g,1,0,2000,3);
    AggiungiArco(g,0,4,4000,7);
    AggiungiArco(g,4,0,4000,7);
    AggiungiArco(g,0,2,6000,4);
    AggiungiArco(g,2,0,6000,4);
    AggiungiArco(g,1,4,5000,5);
    AggiungiArco(g,4,1,5000,5);
    AggiungiArco(g,4,8,3000,5);
    AggiungiArco(g,8,4,3000,5);
    AggiungiArco(g,8,5,4000,2);
    AggiungiArco(g,5,8,4000,2);
    AggiungiArco(g,8,7,5000,6);
    AggiungiArco(g,7,8,5000,6);
    AggiungiArco(g,5,7,6000,4);
    AggiungiArco(g,7,5,6000,4);
    AggiungiArco(g,5,6,3000,1);
    AggiungiArco(g,6,5,3000,1);
    AggiungiArco(g,7,6,3000,3);
    AggiungiArco(g,6,7,3000,3);
    AggiungiArco(g,2,6,6000,11);
    AggiungiArco(g,6,2,6000,11);
    AggiungiArco(g,2,3,4500,5);
    AggiungiArco(g,3,2,4500,5);
    AggiungiArco(g,3,6,4000,6);
    AggiungiArco(g,6,3,4000,6);

return g;
}


/*
STAMPA A SCHERMO L'ARCIPELAGO
*/
void printArcipelago()
{
    printf("      ___               ___                    ___\n"
           "     / 0 \\______4000___/ 4 \\___________3000___/ 8 \\              Accanto ad ogni ponte sono indicate\n"
           "     \\___/        7km  \\___/             5km  \\___/              capacita' del ponte in kg e lunghezza del ponte.\n"
           "     |   \\             /                      /   \\     \n"
           "     |    \\        5km/5000              4000/2km  \\5000-6km\n"
           "     |  3km\\2000     /                   ___/       \\\n"
           "     |      \\       /                   / 5 \\__6000__\\___\n"
           "     |       \\     /                    \\___/  4km   / 7 \\\n"
           "  4km|6000    \\___/                     /            \\___/\n"
           "     |        / 1 \\                3000/1km    _____/\n"
           "     |        \\___/                   /        /     \n"
           "     |___                       _____/   _3000/3km                             N\n"
           "     / 2 \\_______6000__________/  6  \\__/                                      ^\n"
           "     \\___/        11km         \\_____/                                         |\n"
           "         \\                     /                                               |\n"
           "       5km\\4500               /                                          W <-------> E\n"
           "           \\              6km/4000                                             |\n"
           "            \\_______________/                                                  |\n"
           "            /       3       \\                                                  v\n"
           "            \\_______________/                                                  S\n\n");
}


/*
AGGIUNGE UN ARCO DAL VERTICE U AL VERTICE V.
*/
void AggiungiArco(Graph *G, int u, int v,int p,int l)
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
            new->capacitaPonte=p;
            new->lunghezzaPonte=l;
            if (G->listaAdiacenza[u]==NULL)//u non ha archi uscenti //
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

/*
RESTITUISCE 1 SE IL GRAFO PASSATO COME ARGOMENTO E' 1
*/
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

/*
CREA UN GRAFO DI "n" vertici
*/
Graph *CreaGrafo(int n)
{
    Graph *G; int i;
    G = (Graph*)malloc(sizeof(Graph));//Alloco memoria per il grafo
    if (G==NULL)
    {
        printf("ERRORE: impossibile allocare memoria per il grafo\n");
    }
    else
    {
        G->listaAdiacenza=(Edge**)malloc(n*sizeof(Edge*));//Alloco memoria per il la lista di adicenza del vertici
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

/*
ALGORITMO PER CALCOLARE IL PERCORSO MINIMO DA SORGENTE A
DESTINZAZIONE. NON CALCOLA CONSIDERA GLI ARCHI AVENTI CAPACITA MINORE DI PESOCAMION
*/
int algoritmoDijkstra(Graph *grafo,int sorgente,int destinazione,int pesoCamion)

{
    int distanza[grafo->numeroVertici];         //DICHIARO I VETTORI DISTANZA E PREDECESSORE AVENTI numeroVertici elementi
    int predecessore[grafo->numeroVertici];
    inizializzaSingolaSorgente(grafo,sorgente,distanza,predecessore);   //INIZIALIZZO I VETTORI
    Lista *verticiNonOttimizzati=NULL;          //DICHIARO UNA LISTA DI VERTICI NON OTTIMIZZATI
    inizializzaLista(&verticiNonOttimizzati,grafo->numeroVertici);      //INIZIALIZZO LA LISTA

    while(verticiNonOttimizzati!=NULL)          //FINCHE' CI SARANNO VERTICI DA OTTIMIZZARE ENTRERo' NEL CICLO
    {
        int vertice;
        vertice = trovaIndiceMinimo(&verticiNonOttimizzati,distanza);       //TRA I VERTICI PRESENTI NELLA LISTA TROVO QUELLO CHE DISTA MENO DALLA SORGENTE
        Edge *edge = grafo->listaAdiacenza[vertice];
        while(edge!=NULL)           //FINCHE CI SARANNO ARACHI USCENTI DAL VERTICE TROVATO, ENTRO NEL BLOCCO
        {
            if(pesoCamion<=edge->capacitaPonte)     //VERIFICO SE L'ARCO E' PERCORRIBILE
            {
                relax(vertice,edge->key,edge->lunghezzaPonte,distanza,predecessore);       //EFFETTUO IL RILASSAMENTO
            }
            edge=edge->next;
        }

    }

    if(distanza[destinazione]==2000)        //2000 sta per infinito, se la distanza di destinazione da sorgente � 2000 vuol dire che il il vertice non � raggiungibile
    {

        printf("Localita' non raggiungibile\n");
        premiTastoPerContinuare();
        return 0;           //restituisco 0 se dijkstra non ha trovato un percorso
    }
    else
    {
        printf("\n# Spedizione avvenuta con successo\n\n");
        printf("# PERCORSO : ");
        stampaPercorso(sorgente,destinazione,predecessore);     //stampo il percorso trovato
        printf("\n\n# DISTANZA PERCORSO : %d Km\n\n",distanza[destinazione]);       //stampo la distanza calcolata
        premiTastoPerContinuare();
        return 1;       //restituisco 1 per indicare che � stato trovato un percorso
    }

}

/*
STAMPA IL PERCORSO MINIMO CALCOLATO DA DIJKSTRA
*/
void stampaPercorso(int sorgente,int destinazione,int *predecessore)
{
    if(predecessore[destinazione]!=sorgente)        //finche il predecessore del vertice destinazione � diverso da sorgente, richiamo la funzione ricorsivamente
    {
        stampaPercorso(sorgente,predecessore[destinazione],predecessore);
        printf("%d -> ",destinazione);
    }
    else
    {
        printf("%d -> %d -> ",sorgente,destinazione);
    }
}


/*
VERIFICA SE E' SODDISFATTA LA CONDIZIONE DI RILASSAMENTO E NEL CASO LA EFFETTUA
*/
void relax(int vertice1,int vertice2,int lunghezzaPonte, int* distanza, int * predecessore)//FUNZIONE CHE SPAZZA LA STELLA USCENTE DEL VERTICE
{
    if(distanza[vertice2]>distanza[vertice1]+lunghezzaPonte)    //verifico se � necessario effettuare il rilassamento
    {
        distanza[vertice2]=distanza[vertice1]+lunghezzaPonte;
        predecessore[vertice2]=vertice1;
    }
}

/*
TRA I VERTICI PRESENTI NELAL LISTA TROVA QUELLO CON DISTANZA DALLA SORGENTE MINORE, ELIMINA IL
 NODO DALAL LISTA E POI RESTITUISCE L'INDICE
*/
int trovaIndiceMinimo(Lista **testa,int *distanza)
{
    int minimo=2000;
    int valoreRitorno;
    Lista * nodoDaEliminare;
    Lista *tmp = (*testa);
    while(tmp!=NULL)
    {
        if(distanza[tmp->data]<=minimo)
        {
            nodoDaEliminare=tmp;
            minimo=distanza[tmp->data];
            valoreRitorno=tmp->data;
        }
        tmp=tmp->next;
    }

    eliminaNodo(&(*testa),&nodoDaEliminare);        //ELIMINO IL NODO DALLA LISTA
    return valoreRitorno;

}


/*
INIZIALIZZA LA LISTA DI VERTICI NON ANCORA OTTIMIZZATI
*/
void inizializzaLista(Lista ** testa,int numeroVertice)
{
    if(numeroVertice!=0)
    {
        inserimentoInTesta(&(*testa),numeroVertice-1);
        inizializzaLista(&(*testa),numeroVertice-1);
    }
}


/*
INIZIALIZZA I VETTORI DISTANZA E PREDECESSORE
*/
void inizializzaSingolaSorgente(Graph *grafo,int sorgente,int *distanza,int *predecessore) //FUNZIONE CHE INIZIALIZZA LA SINGOLA SORGENTE
{
    int i;
    for(i=0;i<grafo->numeroVertici;i++)
    {
        distanza[i]=2000;       //2000 rappresenta infinito
        predecessore[i]=-1;
    }
    distanza[sorgente]=0;   //LA DISTANZA DA SORGENTE ALLA SORGENTE E' 0
}
