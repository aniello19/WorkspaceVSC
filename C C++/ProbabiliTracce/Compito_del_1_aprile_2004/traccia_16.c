/*
Un file contiene le informazioni sui recapiti di una serie di persone, ciascuno
su di una riga, secondo il formato dell’esempio seguente

Pietro Savorgnan di Brazza’, Via Brazzaville, 33030 Brazzacco; UD
Giacomo Leopardi, Via Ginestra 123/A, 62019 Recanati; AN
Galileo Galilei, Campo dei miracoli 1, 56100 Pisa; PI
Carlo Goldoni, Calle Marco Polo 2A, 30100 Venezia; VE

in cui la sigla della provincia `e preceduta da un punto e virgola ed uno spazio.
Si scriva una funzione C che prenda come parametri il nome di un file siffatto, una stringa p contenente
una serie di sigle di provincia separate da spazi ed il nome di un file di output. La funzione dovr`a scrivere
nel file di output solo i recapiti di quelle persone che abitano in una delle province contenute nella stringa
p.
Ad esempio, nel caso del file precedente e della stringa p con valore "VE UD MI", la funzione deve
produrre il file seguente:

Pietro Savorgnan di Brazza’, Via Brazzaville, 33030 Brazzacco; UD
Carlo Goldoni, Calle Marco Polo 2A, 30100 Venezia; VE
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct indirizzi
{
    char * address;
    char place[3];
    struct indirizzi * next;
}lista;

lista * letturaFILE( char *);
lista * creaLista( lista *, lista *);

lista * creaL2( lista * , char * );


void printL( lista * testa )
{
    lista *slide = testa;

    if (!slide) printf("\nlista vuota :P");
    while( slide )
    {
        printf("\n|%s|-->|%s|\n",slide->address,slide->place);
        slide = slide ->next;
    }
}


int main( )
{
    lista * testa = letturaFILE( "file.txt");
    
    printL( testa );

    char * strin = (char * )malloc(( 11+1)*sizeof( char ));
    printf("\nInserisci delle sigle di alcune province separate da spazi : ");
    gets(strin);

    lista *  testa2 = creaL2( testa, strin);
    
    printL( testa2 );

    return 0;
}

lista * letturaFILE( char * filename)
{
    lista * testa = NULL;
    lista * newNodo;
    lista * nodo_t;

    bool check = false;
    FILE * fpi = fopen(filename,"r");

    if( !fpi ){printf("\nErrore lettura file"); exit(0);}
    else
    {
        char * strin = (char *)malloc(80*sizeof(char));
        int i = 0;
        int k = 0;

        while(!feof(fpi))
        {
            char c = fgetc(fpi);

            if(c == ';')
            {
                strin[i] = '\0';
                i = 0;

                newNodo = (lista*)malloc(sizeof(lista));
                newNodo->address = (char *)malloc((strlen(strin)+1) * sizeof(char));
                strcpy(newNodo->address, strin );
                newNodo->next = NULL;

                check = true;

                c = fgetc ( fpi );
                printf("|%c|\n",c);
            }
            
            if(c == '\0' || c == '\n' )
            {
                check = false;
                strcpy(newNodo->place, strin );

                if(!testa)
                {
                    testa = newNodo;
                    nodo_t = testa;
                }
                else 
                {
                    nodo_t->next = newNodo;
                    nodo_t = nodo_t->next;
                }

                k = 0;
            }

            if( check )
            {
                if( c != ' ')
                {
                    strin[k] = c;
                    k++;
                    strin[k] = '\0';
                }
            }
            else 
            {
                strin[i] = c;

                i++;
            }
        }
    }
    fclose(fpi);
    return testa;
}

lista * creaL2( lista * testa, char strin[])
{
    lista * slide = testa;
    lista *testa2 = NULL;
    lista * nodo_t;
    int i = 0;
    bool check = true;
    char msclean[3];
    //aliasing copio solo l'idirizzo se avviene una modifica viene modificato tutto

    while( check )
    {
        int k = 0;

        while( strin[i] != ' ' )
        {
            msclean[k] = strin[i];
            
            if(strin[i+1] != '\0') i++;
            else strin[i] = ' ', check = false;
            
            k++;
            msclean[k] = '\0';
    
            if( k > 2 ){printf("\nHai inserito un cap sbagliato deve essere max due lettere,"
                                    " mi hai fatto buggare il code, addio :angryface:"); return NULL;}
            
        }
        if(check) i++;

        
        while( slide )
        {
            printf("\n|%s|",msclean);
            printf(" ->|%s|\n",slide->place);
            if( !strcmp(slide->place,msclean) ) 
            {
                printf("ok");
                if( !testa2 ) 
                {
                    printf("testa -> vuota\n");
                    testa2 = (lista *)malloc (sizeof( lista));
            
                    *testa2 = *testa;

                    testa2->next = NULL;

                    nodo_t = testa2;
                }
                else
                {
                    printf("aggiungo nodo\n");
                    lista* new_n = (lista *)malloc (sizeof( lista));
                    
                    *new_n = *testa;

                    new_n->next  = NULL;

                    nodo_t->next = new_n;

                    nodo_t = nodo_t->next;
                }
            }

            slide = slide->next;
        }

        slide = testa;
    }
    
    return testa2;
}