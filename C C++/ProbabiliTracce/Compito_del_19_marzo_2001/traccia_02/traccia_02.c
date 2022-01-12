/*
Si consideri il seguente gioco a due giocatori. In una partita vengono
lanciati un dado per ogni giocatore ed una sola moneta. Se il lancio della moneta `e testa, la partita `e
vinta dal giocatore che ha ottenuto il punteggio pi`u alto nel lancio del proprio dado. Se invece esce croce,
la partita `e vinta dal giocatore che ha ottenuto il punteggio pi`u basso. Se i dadi hanno lo stesso valore la
partita `e un pareggio.
Si consideri la seguente definizione di tipo
struct Partita
{
char moneta;
int ris_dado1;
int ris_dado2;
};
che rappresenta il risultato dei lanci associati ad una partita. I campi ris dado1 e ris dado2 hanno un
valore compreso tra 1 e 6, e il campo moneta ha valore ’t’ (testa) oppure ’c’ (croce).

Si scriva una funzione C che dati come parametri un vettore di partite e la sua lunghezza restituisca:
1 se il giocatore 1 ha vinto pi`u partite del giocatore 2
-1 se il giocatore 2 ha vinto pi`u partite del giocatore 1
0 in caso di pari numero di vittorie.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Partita
{
    char moneta;
    int ris_dado1;
    int ris_dado2;
    struct Partita * next;
}partita;

partita * creaL( );
int de_winner_is( partita* );
void printL ( partita* );
char head_cross (  int );

int main ( )
{
    partita * first = creaL( );

    int winner = de_winner_is ( first );

    printL( first );

    if(winner == 1) printf("\n\nil vincitore e' il primo giocatore.");
    else if(winner == -1)  printf("\n\nil vincitore e' il secondo giocatore.");
    else  printf("\n\nPartita pareggiata. :P");

    

    return 0;

}

partita * creaL( )
{
    partita * testa = NULL;
    partita * nodo_t;
    char c = 'a';

    time_t t;
    srand((unsigned) time(&t));

    while( c!='f')
    {
        if( !testa )
        {
            testa = ( partita *) malloc(sizeof ( partita ));
            testa->moneta = head_cross( rand() % 2 );
            testa->ris_dado1 = rand() % 6+1;
            testa->ris_dado2 = rand() % 6+1;
            testa->next = NULL;
            nodo_t = testa;
        }
        else
        {
            partita* new_nod = ( partita *) malloc(sizeof ( partita ));  
            new_nod->moneta = head_cross( rand() % 2);
            new_nod->ris_dado1 = rand() % 6+1;
            new_nod->ris_dado2 = rand() % 6+1;
            new_nod ->next = NULL;
            nodo_t->next = new_nod;
            nodo_t = nodo_t->next;
        } 

        printf("\nPer finire inserisci 'f': ");
        scanf("%c",&c);

        fflush(stdin);
    }

    return testa;
}

void printL( partita * testa )
{
    partita * slide = testa;

    printf("\n\n*********TABELLONE PUNTI*********\n");
    while ( slide )
    {
        printf("\n moneta->%c; dado/pg1-> %d; dado/pg2-> %d ",slide->moneta,slide->ris_dado1,slide->ris_dado2);
        slide = slide->next;
    }
}

char head_cross( int rand )
{
    if( rand == 1) return 't';
    else return 'c';

}

int de_winner_is( partita* testa)
{
    partita* slide = testa;

    int pg1 = 0, pg2 = 0;

    while( slide )
    {
        if( slide->ris_dado1 != slide->ris_dado2)
        {
            if( slide->moneta == 'c' )
            {
                if( slide->ris_dado1 < slide->ris_dado2) pg1++;
                else pg2++;
            }
            else
            {
                if( slide->ris_dado1 > slide->ris_dado2) pg1++;
                else pg2++;
            }

        }
        slide = slide->next;
    }

    if( pg1 == pg2) return 0;

    if( pg1 > pg2 ) return 1;
    else return -1;
    
}