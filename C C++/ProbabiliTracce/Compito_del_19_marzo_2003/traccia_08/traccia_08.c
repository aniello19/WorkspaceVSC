/*
Un file contiene i dati di un insieme di appuntamenti, organizzati uno per
riga. Ciascuna riga contiene la data, l’ora, la descrizione (massimo 20 caratteri senza spazi) e il luogo
(massimo 10 caratteri senza spazi) dell’appuntamento, separati da un numero arbitrario di spazi bianchi.
Come esempio si consideri il seguente file.

20-3-2003 ore 12 Dentista Udine
22-3-2003 ore 23 Discoteca Portogruaro
19-3-2003 ore 15 Compito_Fondamenti Rizzi
20-3-2003 ore 18 Partita_Pallavolo Feletto

Si consideri inoltre il tipo di record Orario, per la memorizzazione di un istante di tempo (data e
ora):
struct Orario
{
int day;
int month;
int year;
int ora;
};

Si scriva una funzione C che accetti come parametri il nome di un file siffatto, il nome di un file di
output e un record d di tipo Orario. La funzione deve copiare dal file di input a quello di output ciascun
appuntamento che sia successivo all’istante d, sostituendo le sequenze di spazi bianchi con un singolo
spazio bianco.
Ad esempio, nel caso in cui i valori contenuti in d siano 20, 3, 2003 e 13 rispettivamente, il file di
output avrebbe il seguente contenuto:
22-3-2003 ore 23 Discoteca Portogruaro
20-3-2003 ore 18 Partita_Pallavolo Feletto

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct Orario
{
    int day;
    int month;
    int year;
    int ora;
}Orario;

void letturaFILE(char * , Orario );
char * pulisciSTRINGA( char * );

int main ( )
{
    Orario r;
    printf("\nDimmi in che day sei disponibile nel seguente modo day-month,year : ");
    scanf("%d-%d-%d",&r.day,&r.month,&r.year);

    letturaFILE("file.txt",r);

    return 0;
}

void letturaFILE(char * fileName, Orario  record)
{

    int d, m, y; //day , month , year

    FILE * fpi = fopen( fileName, "r");
    FILE * fpo = fopen("fileOut.txt","w");

    if( !fpi || !fpo )
    {
        printf("errore nella lettura del file.");
        exit(0);
    }
    else
    { 
        while( !feof(fpi))
        {
            fscanf(fpi,"%d-%d-%d",&d,&m,&y);
            char * uNclean =(char *)malloc( 80*sizeof( char )); 
            fgets(uNclean,80,fpi);

            if(d == record.day  && m == record.month && y == record.year )
            {
                char * clean = pulisciSTRINGA( uNclean);
                fprintf(fpo,"%d-%d-%d %s\n",d,m,y,clean);
            }
            else free( uNclean );
        }

    }

    fclose( fpi );
    fclose( fpo );
}

char * pulisciSTRINGA( char * uNclean )
{
    char * clean  = ( char* )malloc ( 64 *sizeof( char));
    int i = 0, j = 0;
    bool stop = true;

    // ore 12 Dentista                   Udine

    while ( stop )
    {
        if( uNclean[i] == ' ' && uNclean[i+1] == ' ' ) while ( uNclean[i] == ' ' ) i++; 
        else
        {
            clean[j] = uNclean[i];
            i++;
            j++;
        }

        if( uNclean[i] == 0 || uNclean[i] == '\n')
        {
            clean[j] = 0 ;
            stop = false;
        }

    }

    return clean;
}