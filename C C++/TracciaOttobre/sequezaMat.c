

#include <stdio.h>
#include <stdlib.h>
//comunque stu cazz e isgro si alterna tra esame difficile e esame facile esame difficile esami facile che sfaccimm
//questo potrebbe essere un facile per esempio 

typedef struct nodo
{
    int data;
    int indice;
    struct nodo *next;

}nodo;

typedef struct dati
{
    int r;
    int c;
}dati;

int ** letturaFile( char *, dati *);
void printM( int **, dati * );
void trovaSequenza( int **, int  , dati * );
nodo *creaL( int **, dati *);
void printL( nodo *);
nodo * modLista( int , nodo *);
int ** modMat ( nodo * , int **, dati *);


int main( )
{  
    dati * dim =( dati *)malloc(sizeof ( dim ));

    int ** mat = letturaFile( "mat.txt", dim);
    
    trovaSequenza(mat, 8 , dim );

    nodo * testa = creaL( mat , dim );

    testa = modLista ( 6, testa);

    mat = modMat ( testa , mat , dim );

    return 0;
}

int ** letturaFile( char *filename, dati * dim)
{
    FILE * fi = fopen("mat.txt", "r");
    int n, m;

    if( !fi ) return NULL;

    fscanf(fi,"%d %d",&dim->r, &dim->c);

    int ** mat = ( int**)malloc(dim->r *sizeof( int*));
    for(int i = 0; i<dim->r; i++)
    mat[i] = ( int *)malloc( dim->c* sizeof ( int ));

    for( int i = 0; i <dim->r ; i++)
    {
        for( int j = 0; j<dim->c ; j++)
        {
            fscanf(fi,"%d",&mat[i][j]);
        }
        
    }
    fclose( fi );
    printM( mat, dim);

    return mat;
}

void printM( int **mat, dati * dim)
{
    printf("\n");
    if( !mat)
    {
        printf( "Errore nella scrittura della matrice\n");
        return; 
    }

    for( int i = 0; i <dim->r; i++)
    {
        for( int j = 0; j<dim->c; j++)
        {
           printf(" %d ", mat[i][j] );
        }
        printf("\n");
    }

}

void trovaSequenza( int ** mat, int k , dati *dim )
{
    int count = 0;
    int tmp = 0;

    for( int i = 0; i <dim->r; i++)
    {
        for( int j = 0; j<dim->c; j++)
        {
            if( k == mat[i][j]) count ++;
            else if ( count > tmp ) tmp = count ;
            else count = 0;
        }
    }

    printf("\nLa squenza piu' lunga del valore %d e' %d\n",k , tmp);
}

nodo *creaL( int **mat, dati * dim)
{    
    nodo * testa = NULL;
    nodo *nodo_t;

    for( int i = 0; i <dim->r; i++)
    {
        for( int j = 0; j<dim->c; j++)
        {
            if( mat[i][j] != 0 )
            {
        
                if ( !testa ) 
                {
                    testa = ( nodo *)malloc( sizeof( nodo));
                    testa->data = mat[i][j];
                    testa->indice = j; 
                    testa->next = NULL; 
                    nodo_t = testa;
                    
                }
                else
                {
                    nodo * newnodo = ( nodo *)malloc( sizeof( nodo));
                    newnodo->data = mat[i][j];
                    newnodo->indice = j;
                    newnodo->next = NULL;
                    nodo_t->next = newnodo;
                    nodo_t = nodo_t ->next;
                }

            }

        }
    }

    printL ( testa );

    return testa;
}


void printL( nodo * slide)
{

    printf("\n");
    if (!slide) printf("lista vuota\n");
    else
    while( slide )
    {
        printf("%d-> ", slide->data);
        slide = slide->next;
    }
    printf("NULL\n");

}

nodo * modLista( int k, nodo * testa)
{
    nodo *slide_t = testa;
    while( slide_t )
    {
        if( slide_t->data < k ) slide_t->data = 0;

        slide_t = slide_t->next;
    }

    printf("\nlista modificata");
    printL( testa);
    return testa;
}


int ** modMat ( nodo * testa , int ** mat, dati * dim)
{

    int count = 0;
    for( int i = 0; i <dim->r; i++)
    {
        for( int j = 0; j<dim->c; j++)
        {
            count++;
            printf("%d ", count);
            if( testa->indice == j && testa->next  )
            {
                mat[i][j] = testa->data;
                testa = testa->next;
            }

        }
    }
    printf("\nMatrice modificata");
    printM( mat, dim );
    return mat;
}