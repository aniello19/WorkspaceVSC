/*
Lo schema di un cruciverba `e memorizzato in un file nel seguente formato: la prima riga contiene due numeri interi
 che indicano, rispettivamente, il numero di righe e il
numero di colonne del cruciverba; le righe successive riportano le righe del cruciverba, con uno spazio in
corrispondenza delle caselle nere. Come esempio si consideri il file seguente.
8 6
SUGLI
ODIATI
TIRI N
TRI CD
IE POI
L MELA
EDISON
CAINO
Come `e noto, `e necessaria una definizione per ogni parola, verticale o orizzontale, lunga almeno due
lettere. Si scriva un programma C che riceva come argomento sulla linea di comando il nome del file
contenente il cruciverba e scriva nel file parole.txt l’elenco delle parole di cui serve una definizione,
suddivise in orizzontali e verticali (separate da una linea vuota). Non si richiede che l’ordine in cui
compaiono le parole nel file sia lo stesso con cui vengono numerate le definizioni dei normali cruciverba.
Si assuma che la dimensione massima di un cruciverba sia 50 × 50. Nell’esempio, il file parole.txt sar`a
il seguente.
SUGLI
ODIATI
TIRI
TRI
CD
IE
POI
MELA
EDISON
CAINO

SOTTILE
UDIRE
DC
GIRI
MIA
LAI
PESI
IT
COLON
INDIANO
Il programma deve essere realizzato in modo modulare, scomponendolo nelle seguenti funzioni:
• la funzione main con passaggio dell’argomento sulla linea di comando (5 punti);
• una funzione di lettura del cruciverba dal file (5 punti);
• una funzione di ricerca delle parole e scrittura sul file (14 punti).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void letturaFILE( char *); //una funzione di lettura del cruciverba dal file (5 punti);
void scritturaFILE( FILE * ,char **,int, int, int ); //una funzione di ricerca delle parole e scrittura sul file (14 punti).
//debug
void printM ( char **, int , int );

int main( )
{

    letturaFILE("cruciverba.txt");

    return 0;
}

void letturaFILE( char * fileName)
{
    FILE * fin = fopen( fileName,"r");
    int n, m, i, j;

    char ** aa = (char **)malloc(n*sizeof (char *));
    for(int i = 0; i < n; i++)
    aa[i] = (char * )malloc( m* sizeof( char ));
    

    if(!fin ) printf("\nErrore nella lettura del file");
    else 
    {
        fscanf(fin,"%d %d",&n, &m);

        for ( int i = 0; i < n; i++)
        {

            for( int j = 0; j< m ; j++)
            {
                char c = fgetc(fin);
                aa[i][j] = c;
            }
        }   
    }
    fclose( fin );

    FILE * fo = fopen("parole.txt","w");

    if(!fo ) printf("\nErrore nella lettura del file");
    else 
    {
        fprintf(fo,"------------------\nparole orizzontali\n");
        scritturaFILE(fo,aa, n, m,1);

        fprintf(fo,"------------------\nparole verticali\n");
        scritturaFILE(fo, aa, m, n,0);

    }
    /*
    for( int i = 0; i < n ; i++)
    free(aa[i]);

    free(aa);   
    
    non so perchè non funziona, se avete la risposta contattatemi 
    */
   
   fclose(fo);
}
void scritturaFILE(FILE * fo, char ** cruci ,int n , int m, int reverse)
{
    int in_parola = 0;
    int g, f;
    char * strin = (char *)malloc( m+1* sizeof( char ));

    for ( int i = 0; i < n; i++)
    {
        int k = 0;
        for (int j = 0; j < m; j++)
        {
            if (reverse)
            {
                f = i;
                g = j;

            }
            else
            {
                f = j;
                g = i;
            }      

            if( cruci[f][g] == ' ')
            {
                strin[k] = '\0';

                if( strlen(strin) > 1 )
                {
                    printf("\n%s -> %d",strin, strlen(strin ));
                    fprintf(fo,"%s\n",strin);                        
                }

                k = 0;
            }
            else
            {
                strin[k] = cruci [f][g];
                k++;
            }
        }
        
        strin[k] = '\0';
        if( strlen(strin) > 1 )
        {
            
            printf("\n%s -> %d",strin, strlen(strin ));
            fprintf(fo,"%s\n",strin);
                
        }

    }

    free(strin);
}


void printM ( char ** mat, int n , int m)
{
    for ( int i = 0; i < n; i++)
    {
        for( int j = 0; j< m ; j++)
        {
            printf("%c",mat[i][j]);
        }
    }
    
}


/*
        for ( int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {   
                if (reverse)
                {
                    f = i;
                    g = j;

                }
                else
                {
                    f = j;
                    g = i;
                }

                if (cruci[f][g] != ' ')
                {   
                    if (!in_parola)
                    {
                        in_parola = 1;
                        strin[k] = cruci[f][g];
                        k++;
                    }   
                    else
                    {
                        strin[k] = cruci[f][g];
                        k++;
                    }
                }
                else
                {
                    if (in_parola)
                    { 
                        in_parola = 0;
                        strin[k] = '\0';
                        printf("\n%s",strin);
                        if (k > 1)
                            fprintf (fo, "%s\n", strin);
                        k = 0;
                    }
                }   
            }
            

            strin [k] = '\0';
            printf("\n%s",strin);
            if (k > 1)
                fprintf (fo, "%s\n", strin);
            k = 0;
        }
*/

/*
    char * strin = (char *)malloc( m+1* sizeof( char ));

    for ( int i = 0; i < n; i++)
    {
        int k = 0;
        for (int j = 0; j < m; j++)
        {
            if( cruci[i][j] == ' ')
            {

                if( k > 2 )
                {
                    strin[k] = '\0';
                    printf("\n%s -> %d",strin, strlen(strin ));
                    fprintf(fo,"%s\n",strin);                        
                }

                k = 0;
            }
            else
            {
                strin[k] = cruci [i][j];
                k++;
            }
        }

        if( k > 1 )
        {
            strin[k] = '\0';
            printf("\n%s -> %d",strin, strlen(strin ));
                
        }

    }

*/