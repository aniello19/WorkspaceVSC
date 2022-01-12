/*

Due file contengono gli esiti di due parti di un esame universitario e sono
formati da una sequenza di righe ciascuna delle quali contiene il dato relativo ad uno studente. Il formato
di ciascuna riga `e: Cognome Nome, Matricola, Voto, dove Matricola e Voto sono dei valori interi (il voto
espresso in trentesimi), mentre Cognome e Nome delle stringhe (senza spazi).
I file contengono esattamente la stessa sequenza di studenti. Un esempio di due file secondo il formato
descritto `e il seguente:

Bianchi Giulia, 23891, 24 Bianchi Giulia, 23891, 27
Grigi Filiberto, 52342, 27 Grigi Filiberto, 52342, 15
De Rossi Orazio, 34601, 18 De Rossi Orazio, 34601, 16
Verdi Maria Concetta, 12345, 25 Verdi Maria Concetta, 12345, 29

Si scriva una funzione C che prenda come parametri il nome di due file aventi tale formato e il nome
di un file di output, e scriva nel file di output gli studenti che abbiamo ottenuto un voto medio uguale o
superiore a 18 (arrotondato per eccesso).
Gli studenti devono comparire nel file di output nel formato: Nome Cognome: Voto. Nell’esempio, il
file di ouput sar`a il seguente.
Giulia Bianchi: 26
Filiberto Grigi: 21
Maria_Concetta Verdi: 27

*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef struct Lista
{
    char * nome;
    char * cognome;
    int matricola;
    int voto;
    struct Lista *next;

}lista;

lista * letturaFILE( char *);
lista * letturaFILE2( lista *);

char * pulisciSTRINGA( char * , int *, bool);
lista * creaNodo(char * );

lista * aggiornaNodes(lista *, lista* );
lista * deleteDeboli ( lista* );

void printL( lista * );

int main()
{

    lista * testa = letturaFILE("voti1.txt");

    testa = letturaFILE2( testa );

    printL( testa );

    return 0;
}

lista * letturaFILE(char * fileName)
{
    lista * testa  = NULL;
    lista * nodo_t;

    FILE * fp = fopen( fileName, "r");
    if( !fp )
    {
        printf("errore nella lettura del file.");
        return NULL;
    }
    else
    { 
        while( !feof(fp))
        {
            char * uNclean =(char *)malloc( 80*sizeof( char ));

            fgets(uNclean, 80 , fp);

            if( !testa )
            {
                testa = creaNodo( uNclean );
                nodo_t = testa;
            }
            else 
            {
                nodo_t->next = creaNodo( uNclean );
                nodo_t = nodo_t->next;
            }

            free( uNclean );
        }

    }

    fclose( fp );
    return testa;
}


lista * letturaFILE2(lista * testa )
{
    lista * nodo;
    lista * nodo_T = testa;

    FILE * fp2 = fopen( "voti2.txt", "r");
    if( !fp2 )
    {
        printf("errore nella lettura del file.");
        return NULL;
    }
    else
    { 
        while( !feof(fp2))
        {
            char * uNclean =(char *)malloc( 80*sizeof( char ));

            fgets(uNclean, 80 , fp2);

            nodo = creaNodo( uNclean );
            //printf("\n%s-%s-%d-%d-", nodo->cognome, nodo->nome,nodo->matricola, nodo->voto);
            
            nodo_T = aggiornaNodes(nodo, testa );

            free( uNclean );
        }

        nodo_T = deleteDeboli ( nodo_T );
    }

    fclose( fp2 );
    return testa;
}


lista * aggiornaNodes(lista* nodo, lista * testa)
{
    lista * slide_t = testa;
    

    while( slide_t )
    {   
        
        if(slide_t->matricola == nodo->matricola )
        {
            slide_t->voto = (slide_t->voto + nodo->voto)/2;
            
        }
        

        slide_t = slide_t->next;

    }

    return testa;
}

lista * deleteDeboli( lista * testa)
{
    lista * slide_t = testa;
    lista * prec = NULL;

    while( slide_t )
    {
        if ( slide_t->voto < 18 ) // procedo direttamente all'eliminazione del nodo
        {
            if (slide_t == testa) 
            {
                testa = testa->next;
                free(slide_t);
                slide_t= testa;
            }
            else
            {
                prec->next = slide_t->next;
                free(slide_t);
                slide_t = prec->next;
            }
        }
        else 
        {
            prec = slide_t;
            slide_t = slide_t->next;
        }
    }
    return testa;
}

lista * creaNodo(char * uNclean)
{
    int i = 0;
    //printf("%s\n",uNclean);

    lista * new_nodo = (lista * )malloc(sizeof( lista ));

    char * msclean = pulisciSTRINGA ( uNclean,  &i ,false);
    new_nodo->cognome = (char *) malloc( (strlen(msclean)+1)*sizeof(char));
    strcpy( new_nodo->cognome,msclean );
    //printf("ao?");

    msclean = pulisciSTRINGA  ( uNclean,  &i ,true);
    new_nodo->nome = (char *) malloc( (strlen(msclean)+1)*sizeof(char));
    strcpy( new_nodo->nome,msclean );
    //printf("ao?");

    msclean = pulisciSTRINGA ( uNclean,  &i ,true);
    new_nodo->matricola = atoi( msclean );
    //printf("ao?");

    msclean = pulisciSTRINGA ( uNclean,  &i ,true);
    new_nodo->voto = atoi( msclean );

    new_nodo->next = NULL;
    
    free( msclean );
    return new_nodo;
}

char * pulisciSTRINGA( char * uNclean, int *indice , bool controllo)
{
    int i = *indice; 
    char * clean  = ( char* )malloc ( 64 *sizeof( char));
    int j = 0;
    bool stop = true;

    while ( stop )
    {
        if( controllo )
        {
            clean[j] = uNclean[i];
            //printf("\nclean -> %c ,, unclean -> %c i->%d j->%d",clean[j],uNclean[i],i,j);

            i++ , j++;

            if( uNclean[i] == 44 || uNclean[i] == '\n')
            {
                clean[j] = 0 ;
                stop = false;
            }
                      
        }
        else
        {

            if(uNclean[i] == 0 || uNclean[i] == '\n')
            {
                clean[j] =  0 ;
                return clean;
            }
            clean[j] = uNclean[i];
            //printf("\nclean -> %c , unclean -> %c i->%d j->%d",clean[j],uNclean[i],i,j);
            i++ , j++;

            if( uNclean[i] == 32)
            {
                clean[j] = 0 ;
                stop = false;
            }
        }
        
    
    }
    i++;
    *indice = i;

    return clean;
}

void printL( lista * testa)
{
    lista * slide = testa;

    printf("\nStampo la lista dei studenti promossi:");
    while( slide )
    {
        printf("\n%s-%s-%d-%d-", slide->cognome, slide->nome,slide->matricola, slide->voto);
        slide = slide->next;
    }

}