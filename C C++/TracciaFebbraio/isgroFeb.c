

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
/*
	  0 1 2
	  -----
	0|2 7 6
	1|9 5 1
	2|4 3 8
*/

typedef struct info
{
    int ele;
    int posC;
    int posR;
    struct info * next;
}infomat;

// f per le liste
infomat * LeggiFileRic( FILE *);
void printL ( infomat* );
infomat * el_deboli( infomat* , int  );

//f per le mat
int ** creaMat( infomat * , int , int);
bool check_magik(int ** , int, int); //f per controllare se e' magica
void printM( int **, int, int );
void deallocMAT( int **, int );

//f per i file
void scritturaFILE(char * , int, int , infomat*);

int main( )
{

    int nC,nR; //dim mat
    
    FILE * fpi = fopen("mat.txt","r");

    if( !fpi ) {printf("errorescrittura file ciao;"); return 0;} // check errore file

    fscanf(fpi,"%d %d",&nC,&nR);// mi rubo la dim dal file

    infomat * testa = LeggiFileRic(fpi);

    printL( testa );

    int ** mat = creaMat( testa, nR, nC );

    if( nR == nC ) // se la mat e quadrata entro nella f
    {
        if ( check_magik(mat, nR, nC) ) printf("\nla matrice e' magica \n");
        else printf("\nla matrice  non e' magica :c \n");

        int k;
        printf("\nok tutti gli svolgimenti sono andati bene ora inserisci un valore affinche modifchi la lista : ");
        scanf("%d",&k);

        testa = el_deboli( testa, k);

        printL( testa );

        scritturaFILE("fileOut.txt",nR,nC, testa);

    }
    else {printf("\n purtroppo la matrice non e' quadrata quindi non posso utilizzare la funzione :P\n");printM( mat, nC, nR);};

    deallocMAT( mat, nR);
    fclose(fpi);

    printf("\nprogramma FINITO.\n");
    return 0;
}


infomat * LeggiFileRic(FILE *fpi) 
{
    infomat * nodo_t;
    int tmp_ele, tmp_c, tmp_r; // valori temp

    //caso base
    if(fscanf(fpi,"%d %d %d",&tmp_ele,&tmp_r,&tmp_c) != 3) return NULL;
    else // caso ricorsivo
    {
        nodo_t = (infomat *) malloc(sizeof(infomat));

        nodo_t->ele = tmp_ele;

        nodo_t->posC = tmp_c;

        nodo_t->posR = tmp_r;

        nodo_t->next = NULL;

        nodo_t->next=LeggiFileRic(fpi);

        return nodo_t;
    }
}

infomat * el_deboli(infomat * testa, int k )
{
    //caso base
    if ( testa == NULL) return NULL;

    //caso ricorsivo
    infomat   * post = el_deboli( testa->next, k);

    //casi per studiare 
    if(testa->ele > k ) //gli elementi che rispettano questa condizione non vengono eliminati 
    {
        testa->next = post;
        return testa;
    }

    return post;
}

int ** creaMat ( infomat * testa, int nR, int nC)
{
    int ** mat = ( int** )malloc(nR * ( sizeof ( int*))); // alloco la matt
    for( int i = 0; i<nR; i++)
    mat[i] = ( int * )malloc(nC*(sizeof(int)));

    infomat * slide = testa;

    while( slide != NULL )
    {
        mat[slide->posC-1][slide->posR-1] = slide->ele;
        slide = slide->next;
    }

    printM( mat, nR, nC );
    
    return mat;
}

bool check_magik(int **  mat, int nR, int NC)
{
   

    int size = nR ;

    int sum_r = 0;
    int sum_c = 0;

    int t_r = 0; //totale
    int t_c = 0;
    int t_d_l = 0; //tot left diago
    int t_d_r = 0; //tot right diago

    for (int j = 0; j<size; j++)
    {
        for (int k = 0;k< size;k++) 
        {
            //da qui
            //CONTROLLO SE GLI ELEMENTI SONO DIVERSI
            for(int ii = j; ii<size; ii++)
            {
                for(int jj = k+1; jj<size; jj++)
                {
                    if(mat[ii][jj] == mat[j][k])    return false;
                    
                }
            }//a qui

            t_r += mat[j][k]; // agiorno il totale delle righe muovendo le colonne
            t_c += mat[k][j]; // idem ma inverso

            if (j==k) { t_d_l += mat[j][k];} // aggiorno sinistra diago
            if (size- k -1 == j) {t_d_r +=mat[j][k];} // idem ma diago di destra

        }

        sum_r += t_r;
        sum_c += t_c;

        if ( t_r!=t_c )// faccio i controlli per vedere se tutto e' !ok
        {
            printf ("controlli falliti\n");

            return false;
        } 

        // resetto
        t_r = 0;
        t_c = 0;


    }
    
    if (t_d_l != t_d_r && t_d_l != sum_r/(size-1) && sum_r%t_d_l!=0) //la stessa cosa di sopra
    { 
        printf ("controlli falliti\n");
            return false;
    } 
    
    printf ("tutti i controlli superati\n");
    return true;
}

void scritturaFILE(char * fileName, int nR, int nC, infomat* testa)
{
    FILE * fpo = fopen( fileName, "w");

    infomat* slide = testa;

    if( !fpo ){printf("\nerrore nella lettura file ciao\n"); return; }

    fprintf(fpo,"%d %d\n",nR,nC);

    while( slide )
    {   
        fprintf(fpo,"%d %d %d\n",slide->ele,slide->posC,slide->posR);
        slide = slide->next;
    }

    fclose(fpo);
}




void deallocMAT( int ** mat , int nR)
{
    for( int i = 0; i< nR ; i++)// dealloco la mat
    free( mat[i]);
    free( mat );

    printf("\nMatrice deallocata\n");
}

void printL ( infomat* testa)
{
    infomat* slide = testa;

    printf("\nla lista in questione");

    while( slide )
    {
        printf("\n%d %d %d\n",slide->ele,slide->posC ,slide->posR);
        slide = slide->next;
    }
}

void printM( int ** mat, int nR, int nC)
{
    printf("\nla matrice in questione\n");
    for ( int i = 0; i<nR ; i++)
    {
        for(int j = 0; j<nC ; j++)
        {
            printf ("%d ",mat[i][j]);
        }
        printf("\n");
    }
}