/*

Un file contiene una sequenza (di lunghezza ignota) di numeri interi positivi,
uno per riga. I numeri sono scritti in lettere cifra per cifra, e sono terminati dalla parola stop. Come
esempio si consideri il seguente file:
otto cinque nove stop
due due stop
sette zero sette stop
Il file contiene i numeri 859, 22 e 707.
Si scriva un programma C, opportunamente organizzato in funzioni, che legga da tastiera il nome del
file e stampi il valore della somma dei numeri ivi contenuti. Nell’esempio il programma deve stampare
1588.
Si assuma che i numeri siano di dimensione tale da essere rappresentabili tramite il tipo int.

*/


#include <stdio.h>
#include <stdlib.h>

int letturaFile( );
int converti( char *);

int main( )
{
    char * filename = (char *)malloc(10*sizeof( char ));

    printf ( "inserisci il nome del file che devo utilizzare : ");
    gets( filename );

    int valore = letturaFile(  );

    if( valore == 0 ) printf("\nIlvalore e' %d oppure non e' riuscito a leggere il file ", valore);
    else printf("\nIl valore e' %d",valore);

    return 0;
}

int letturaFile()
{
    FILE * fp = fopen( "file.txt", "r");
    char * parola = (char * )malloc( 10* sizeof(char ));
    int valore = 0 , n;
    int somma = 0;

    if(!fp)
    {
        printf("\nnon esiste nessun file");
        return 0;
    }

    while( !feof(fp) )
    {
        fscanf(fp,"%s",parola);
        n = converti( parola);
        
        
        if( n == -1 )
        {
            valore /= 10 ;
            somma += valore;
            valore = 0;
        }
        else
        {
            valore += n;
            valore *= 10;
        }

    }
    free(parola);
    fclose(fp);
    return somma;
}


int converti ( char * stringa )
{
    int valore = -1;

    char c = stringa[0];

    switch ( c )
    {
        case 'z' : 
            valore = 0;
            break;
        case 'u' :
            valore = 1;
            break;
        case 'd' : 
            valore = 2;
            break;
        case 't' :
            valore = 3;
            break;
        case 'q' : 
            valore = 4;
            break;
        case 'c' :
            valore = 5;
            break;
        case 'o' : 
            valore = 8;
            break;
        case 'n' :
            valore = 9;
            break;
    }


    if( valore == -1)
    {
        if( stringa[2] == 'i') valore = 6;
        else if ( stringa[3] == 't') valore = 7;
    }


    return valore;
}