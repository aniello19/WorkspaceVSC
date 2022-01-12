/*

Sia dato un file che contiene una matrice rettangolare di interi (massimo
100×200) preceduta dalle sue dimensioni (separate dal carattere X). Come esempio si consideri il seguente
file.
5X6
1 3 4 -8 9 -5
0 0 0 0 0 0
3 -2 5 -2 0 0
2 3 3 3 0 -1
0 -1 1 -1 1 1
Scrivere una funzione C che prenda il nome di un file siffatto e modifichi il file eliminando le righe che
hanno come primo valore 0 ed invertendo l’ordine delle righe. Il numero di righe deve essere riscritto in
modo che corrisponda alle righe della nuova matrice.
Nell’esempio il contenuto del file al termine dell’esecuzione deve essere il seguente.
3X6
2 3 3 3 0 -1
3 -2 5 -2 0 0
1 3 4 -8 9 -5

Suggerimento: per modificare il file `e necessario aprirlo in lettura, leggerne il contenuto, chiuderlo
e successivamente riaprirlo in scrittura.

*/

#include <stdio.h>
#include <stdlib.h>

void letturaFILE(char *);
void printM( int **,int, int);
void scritturaFILE( int **, int, int );

int main( )
{
    letturaFILE("file.txt");

    return 0;
}


void letturaFILE(char * fileName)
{
    FILE * fpi = fopen(fileName,"r");
    int m = 0,n = 0,i = 0,j = 0, val;

    int ** aa;

    if(!fpi ){ printf("errore nella scrittura file."); exit(0);}
    else 
    {
        /*
        5X6
        1 3 4 -8 9 -5
        0 0 0 0 0 0
        3 -2 5 -2 0 0
        2 3 3 3 0 -1
        0 -1 1 -1 1 1
        */
        fscanf(fpi,"%dX%d",&m,&n);

        aa = (int **)malloc(m*sizeof(int*));
        for(int i = 0; i< m; i++)
        aa[i] = (int *)malloc(n*sizeof(int));

        while(!feof(fpi))
        {

            fscanf(fpi,"%d",&val);

            if( val == 0 && j == 0 )
            {
                while( j != n-1)
                {
                    fscanf(fpi,"%d",&val);
                    j++;
                }
                j = 0;
            }
            else
            {
                aa[i][j] = val;
                //printf("%d %d %d\n", i, j , val);
                j++;
            }

            if( j == n ) j = 0, i++;
            
        }
        
        /* qui volevo cancellare le ultime due righe essendo che 
        nel while ho lasciato le righe che iniziavano con lo zero alla fine
        e avevo intenzione di riallocare la matrice righe ma non so se ho fatto
        bene, contattatemi se avete la risposta*/

        m = i;

        aa = realloc(aa,m*sizeof( int *)); 

        printM( aa ,m, n);

        scritturaFILE( aa, m, n);


    }

    fclose(fpi);

}

void scritturaFILE(int ** aa, int m , int n)
{
    FILE *fpo = fopen("fileout.txt","w");

    if(!fpo ) {printf("\nerrore apertura file"); exit(0);}
    else
    {
        for ( int i = m-1; i >= 0; i--)
        {
            for( int j = 0; j< n; j++)
            {
                printf("[%d %d]",i, aa[i][j]);
                fprintf(fpo," %d ",aa[i][j]);
            }
            printf("\n");
            fprintf(fpo,"%s","\n");
        }
    }
    fclose(fpo);
}

void printM( int ** aa, int m, int n)
{
    
    for( int i = 0; i< m; i++)
    {
        for ( int j = 0; j< n; j++)
        {
            printf("%d ", aa[i][j]);
        }
        printf("\n");
    }
}