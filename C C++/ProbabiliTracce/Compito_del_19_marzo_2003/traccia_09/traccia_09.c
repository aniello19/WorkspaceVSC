/*

Una matrice si dice sparsa se la maggior parte dei suoi elementi ha uno
stesso unico valore, detto valore dominante. Ad esempio la seguente matrice di dimensione 6× 4 `e sparsa
con valore dominante 3.
3 3 3 2
3 0 3 3
5 3 3 4
1 0 3 3
3 3 3 3
3 3 3 3
Si consideri un file che memorizza una matrice sparsa (di dimensione massima 100×100) nel seguente
modo: la prima riga contiene il numero di righe, il numero di colonne e il valore dominante della matrice.
Le righe successive contengono la riga, la colonna ed il valore di ciascun elemento diverso dal valore
dominante. Ad esempio, il file corrispondente alla matrice precedente `e quello riportato in figura 1.
Si scriva una funzione C che prenda come parametro il nome di un file contenente una matrice
memorizzata come spiegato e scriva la stessa matrice nel file matrice.dat in forma estesa. Nell’esempio
precedente, al termine dell’esecuzione il file matrice.dat dovr`a avere il contenuto di figura 2.
6 4 3       3 3 3 2
0 3 2       3 0 3 3
1 1 0       5 3 3 4
2 0 5       1 0 3 3
2 3 4       3 3 3 3
3 0 1       3 3 3 3
3 1 0
FIGURA 1 FIGURA 2

*/

#include <stdlib.h>
#include <stdio.h>

void letturaFILE( char *);

int main( )
{
    letturaFILE("file.txt");

    return 0;
}

void letturaFILE( char * fileName )
{
    int r,c,dom;
    FILE * fpi = fopen(fileName,"r");
    FILE *fpo = fopen("fileOut.txt","w");

    if(!fpi || !fpo ) {printf("errore nella lettura file"); exit(0);}
    else
    {
        fscanf(fpi,"%d %d %d",&r,&c,&dom);
        
        int rVal, cVal, val;
        fscanf(fpi,"%d %d %d",&rVal,&cVal,&val);

        for(int i = 0; i<r; i++)
        {
            for(int j = 0; j<c; j++)
            {
                if(rVal == i && cVal == j)
                {
                    fprintf(fpo,"%d ",val);

                    fscanf(fpi,"%d %d %d",&rVal,&cVal,&val);
                }
                else 
                {
                    fprintf(fpo,"%d ",dom);
                }
            }
            fprintf(fpo,"\n");
        }

        
    }

    fclose(fpo);
    fclose(fpi);
}
