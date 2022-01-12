/*
Un file contiene una sequenza di lunghezza ignota (massimo 20) di risultati di
partite di calcio (uno per riga). I risultati sono scritti nel formato illustrato dal seguente file di esempio.

Genoa - Ascoli 1-2
Ancona - Bari 1-2
Cosenza - Catania 3-1
Siena - Livorno 2-0
Palermo - Napoli 2-1
Triestina - Ternana 4-3
Messina - Venezia 1-1
Lecce - Hellas_Verona 1-1

I nomi delle squadre non contengono spazi e sono separati da uno spazio, un trattino (-) ed un altro
spazio; i nomi e i gol segnati sono separati da uno o pi`u spazi; i gol segnati sono separati tra loro dal
trattino (senza spazi).

Si scriva una funzione C che prenda come parametro il nome di un file nel formato suddetto e modifichi
il file stesso aggiungendo alla fine di ciascuna riga il simbolo del totocalcio corrispondente al risultato (1
ha vinto la prima squadra, 2 ha vinto la seconda squadra, X pareggio, cio`e le squadre hanno segnato lo
stesso numero di gol).
Ad esempio, se il file `e quello qui sopra la funzione deve modificarlo facendogli assumere il seguente
contenuto.
Genoa - Ascoli 1-2 2
Ancona - Bari 1-2 2
Cosenza - Catania 3-1 1
Siena - Livorno 2-0 1
Palermo - Napoli 2-1 1
Triestina - Ternana 4-3 1
Messina - Venezia 1-1 X
Lecce - Hellas_Verona 1-1 X

Suggerimento: per poter scrivere sullo stesso file `e consigliato copiare tutto il contenuto del file in
una opportuna struttura dati in memoria centrale e successivamente ritrasferire i dati dalla memoria al
file (a questo scopo `e necessario aprire e chiudere il file due volta con modalit`a diverse).

*/

typedef struct partite
{
    char * casa;
    char * fuoricasa;
    int gol1;
    int gol2;
    char risultato;
    struct partite * next ;
}lista;

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

lista * letturaFILE(char*);
lista * creaNodo( char * );
char * pulisciSTRINGA( char * , int* );

void scritturaFILE(lista *);

void printL( lista *);


int main()
{
    lista * testa = letturaFILE("file.txt" );

    printL( testa );

    scritturaFILE( testa );

    return 0;
}

lista * letturaFILE(char * fileName)
{
    lista * testa = NULL;
    lista * nodo_t;

    FILE *fpi = fopen(fileName,"r");

    if(!fpi){ printf("\nFile non aperto correttamente;"); return NULL;}
    else
    {
        while(!feof(fpi))
        {
            if(!testa)
            {
                char * strin = (char * )malloc(20*sizeof(char ));
                fgets(strin,80,fpi);

                testa = creaNodo( strin );

                nodo_t = testa;
                free( strin ) ;
            }
            else
            {
                char * strin = (char * )malloc(20*sizeof(char ));
                fgets(strin,80,fpi);
                
                nodo_t->next = creaNodo(strin );      
                nodo_t = nodo_t->next;  

                free( strin ) ;        
            }
        }
    }
    fclose(fpi);
    return testa;
}

lista * creaNodo(char * uNclean )
{
    int i = 0;

    lista * new_nodo = (lista * )malloc(sizeof( lista ));

    char * msclean = pulisciSTRINGA ( uNclean , &i);
    new_nodo->casa = (char *) malloc( (strlen(msclean)+1)*sizeof(char));
    strcpy( new_nodo->casa, msclean );

    msclean = pulisciSTRINGA ( uNclean,  &i );
    new_nodo->fuoricasa = (char *) malloc( (strlen(msclean)+1)*sizeof(char));
    strcpy( new_nodo->fuoricasa,msclean );

    msclean = pulisciSTRINGA ( uNclean ,  &i);
    new_nodo->gol1  = atoi(msclean )  ;

    msclean = pulisciSTRINGA ( uNclean,  &i );
    new_nodo->gol2 = atoi(msclean  ) ;
   
    if(new_nodo->gol1 == new_nodo->gol2) new_nodo->risultato = 120;
    else if(new_nodo->gol1 > new_nodo->gol2) new_nodo->risultato = 49;
    else new_nodo->risultato = 50;

    char * garbage = pulisciSTRINGA ( uNclean,  &i );
    free( garbage );

    new_nodo->next = NULL;
    

    free( msclean );
    return new_nodo;
}
char * pulisciSTRINGA( char * uNclean, int *indice )
{
    int i = *indice; 
    char * clean  = ( char* )malloc ( 64 *sizeof( char));
    int j = 0;
    bool stop = true;

    //Genoa - Ascoli 1-2

    if(uNclean[i] == 45 || uNclean[i] == ' ')
    {
        while(uNclean[i] == 45 || uNclean[i] == ' ' ) i++;
    }

    while ( stop )
    {
        
        clean[j] = uNclean[i];
    

        if(uNclean[i] == 0  || uNclean[i] == '\n' ) 
        {
            clean[i] = 0;
            return clean;
        }
        i++ , j++;

        if( uNclean[i] == 45 || uNclean[i] == ' ')
        {
            clean[j] = 0 ;
            stop = false;
        }
    }
    i++;
    *indice = i;

    return clean;
}

void scritturaFILE(lista * slide)
{
    FILE * fpo = fopen("fileOut.txt","w");
    if(!fpo){ printf("\nErrore apertura file."); exit(0);}
    else
    {
        fprintf(fpo,"\nStampo la lista delle partite:");
        while( slide )
        {
            fprintf(fpo,"\n%s - %s \t\t %d-%d -> %c", slide->casa, slide->fuoricasa,slide->gol1, slide->gol2, slide->risultato);
            slide = slide->next;
        }   
    }
    fclose(fpo);
}

void printL( lista * testa)
{
    lista * slide = testa;

    printf("\nStampo la lista delle partite:");
    while( slide )
    {
        printf("\n%s-%s %d-%d->%c", slide->casa, slide->fuoricasa,slide->gol1, slide->gol2, slide->risultato);
        slide = slide->next;
    }

}