/*
Si consideri un file contenente una sequenza di quotazioni di borsa con il
seguente formato:

nome_societ`a#val1#val2#val3...#valn$

Su ciascuna riga del file `e presente il nome della societ`a (massimo 20 caratteri senza spazi) a cui si
riferiscono le quotazioni e i valori delle azioni (preceduto dal carattere #, senza spazi) in diversi istanti
della giornata. Il numero di valori rilevati pu`o variare da societ`a a societ`a, ma `e compreso tra 1 e 100.
In tutti i casi la lista `e terminata dal carattere $.
Un esempio di file siffatto `e il seguente:

Axis#12.5#11.8#13.7#11.9#10.7$
BiRom#5.2#4.8#4.9#5.0$
Comeco#24.3#24.4#24.6#24.3#24.2#24.5#24.2#24.3#24.3$

Si scriva una funzione C che prenda come parametri il nome di un file di input nel formato precedente
ed il nome di un file di output, e scriva in quest’ultimo i dati relativi alle quotazioni minima, mediana e
massima registrate per ciascuna societ`a.
La mediana di una lista di valori `e quel valore che ha un numero uguale di valori pi`u grandi e pi`u
piccoli. Nel caso di numero di valori pari, la mediana `e quel valore che ha un numero di valori pi`u grandi
maggiore di uno rispetto a quelli pi`u piccoli.
Nel caso del file precedente, la funzione deve produrre il seguente file:

Axis 10.7 11.8 13.7
BiRom 4.8 4.9 5.2
Comeco 24.2 24.3 24.6
Si consideri gi`a disponibile la funzione
void Ordina(float v[], int n);
che ordina un vettore di n elementi.
*/



/*
    ERI RIMASTO ALLA CREAZIONE DELLA STRUCT DATA CONTINUA CIAO CIAO
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct dati
{
    float min;
    float max; 
    float med; 
    char * company;
}Record;

typedef struct vet
{
    float  data;
    struct vet * next ;
}lista;

void letturaFILE(char * );
Record  find_DATA( char *);
char * pulisciSTRINGA ( char *  , int *);

lista * bubble_lista( lista *);
Record create_DATA(lista *, int , char*);
void freeMemory(lista * );


void printL( lista * testa)
{
    lista * slide = testa;
    while(slide)
    {
        printf(" %3.2f ", slide ->data);
        slide = slide->next;
    }
}


int main ()
{
    letturaFILE("file.txt");

    return 0;
}

void letturaFILE( char * fileName)
{
    FILE * fpi = fopen(fileName,"r");
    FILE * fpo = fopen("FileOut.txt","w");

    Record struct_DATA;

    if(!fpi && !fpo){   printf("\nErrore scrittura FILE ");     exit(0);}
    else
    {
        printf("ao?");
        while( !feof( fpi ))
        {   
            char * uNclean = (char * )malloc(80*sizeof(char ));
            fgets(uNclean,80,fpi);

            struct_DATA = find_DATA( uNclean );

            fprintf(fpo,"%s\t %3.2f %3.2f %3.2f\n",struct_DATA.company,struct_DATA.min,struct_DATA.med,struct_DATA.max );

            free(uNclean);
        }
        
    }

    fclose(fpi);
    fclose(fpo);
}


Record find_DATA( char * uNclean)
{
    int i = 0;
    Record struct_DATA;

    lista * testa = NULL;
    lista * nodo_t;
    int dimLista = 0;

    char * msclean = pulisciSTRINGA ( uNclean , &i);
    char * company = (char *) malloc( (strlen(msclean)+1)*sizeof(char));
    strcpy( company, msclean );

    msclean = pulisciSTRINGA ( uNclean , &i);

    while( msclean[0] != '$' )
    {
        
        if(!testa)
        {
            testa = (lista *)malloc(sizeof(lista ));
            testa->data = atof(msclean);
            testa->next = NULL;
            nodo_t = testa;
        }
        else
        {
            lista * newNodo = (lista *)malloc(sizeof( lista ));
            newNodo->data = atof( msclean );
            newNodo->next = NULL;
            nodo_t->next = newNodo;
            nodo_t = nodo_t ->next;
        }
        dimLista++;
        //printf("\n%f ",nodo_t->data);
        msclean = pulisciSTRINGA ( uNclean , &i);

    }

    testa = bubble_lista(testa);
    printL(testa);
    struct_DATA = create_DATA( testa, dimLista,company);
    //freeMemory( testa );
    free(msclean);
    return struct_DATA;
}


char * pulisciSTRINGA ( char * uNclean , int * indice)
{
    int i = *indice; 
    char * clean  = ( char* )malloc ( 64 *sizeof( char));
    int j = 0;
    bool stop = true;

    //Comeco#24.3#24.4#24.6#24.3#24.2#24.5#24.2#24.3#24.3$
    if(uNclean[i] == '$') return "$";
    else
    while ( stop )
    {

        //if(uNclean[i] == 0) return clean;  

        if( uNclean[i] == '#' || uNclean[i] == '$')
        {
            clean[j] = 0 ;
            stop = false;
        }
        else
        {
           clean[j] = uNclean[i];
           printf("|%c| |%c|\n",uNclean[i],clean[j]);
           i++ , j++;
        }

    }
    printf("\n");
    if( uNclean[i] == '#') i++;

    *indice = i;

    return clean;
}   


void freeMemory(lista  * testa )
{
    lista *punt;
    while(testa)
    {
        punt = testa;
        testa = testa->next;
        free(punt);
    }
}

lista* bubble_lista(lista* testa)
{
    if ( !testa && !testa->next) return testa; //se la lista è vuota o se la lista contiene solo un numero restituisco lista
    
    bool scambio = true;
    lista* bubble;
     
    while (scambio)
    {
    
        scambio = false;
        
        //il primo è speciale
        if ( testa->data > testa->next->data )
        {
            scambio =! scambio;
            //tolgo dalla lista il secondo elemento
            bubble = testa->next;
            testa->next = bubble->next;
            //metto l'elemento tolto in testa alla lista
            bubble->next = testa;
            testa = bubble;
        }
        //tutti gli altri confronto il sucessivo con il sucessivosucessivo
        //in questo modo non perdo il riferimento al precedente
        for(bubble = testa; bubble->next->next; bubble = bubble->next) 
        {
            if ( bubble->next->data > bubble->next->next->data )
            {
                if ( !scambio ) scambio =! scambio;
				
                //tolgo dalla lista l'elemento sucessivosucessivo
                lista* swap = bubble->next->next;
                bubble->next->next = swap->next;
                //swappo
                swap->next = bubble->next;
                bubble->next = swap;
            }       
        }
    }
    
    return testa;
}

Record create_DATA( lista* testa, int dimLista, char * company)
{
    Record struct_DATA;
    lista * slide = testa;

    struct_DATA.company = (char *)malloc(strlen(company)+1* sizeof( char ));
    strcpy( struct_DATA.company, company );

    struct_DATA.min = slide->data;
    int med = (dimLista-1)/2;

    while(slide->next)
    {
        if(dimLista-1 == med )struct_DATA.med = slide->data;
        slide = slide->next;
        dimLista--;
    }
    struct_DATA.max = slide->data;

    return struct_DATA;
}