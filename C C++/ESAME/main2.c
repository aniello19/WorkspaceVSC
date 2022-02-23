#include<stdio.h>
#include<stdlib.h>

typedef struct nodo
{
    int data;
    int nR;
    int nC;
    struct nodo *next;

}nodo;

typedef struct dati
{
    int n;

}dati;

int **letturaFile(dati *);
void printM(int **, dati *);
nodo *creaL(int **, dati *);
void printL(nodo *);
nodo *modLista(nodo *);
int **modMat(int **, dati *);
void scritturaFile(int** , dati*);
int **aggMat(int **, dati *, nodo *);
void freeMat(int **, dati *);
void freeLista(nodo *);
void freeNodo(nodo *);

int main(void){

    dati *dim =(dati*)malloc(sizeof(dim)); 

    int **mat = letturaFile(dim); //leggo il file in input e aggiungo i valori nella matrice

    mat = modMat(mat, dim); //ottengo la matrice trasposta
 
    nodo *testa = creaL(mat, dim); //creo la lista

    testa = modLista(testa); //modifico la lista eliminando gli elementi dispari

    mat = aggMat(mat, dim, testa); //aggiorno la matrice

    scritturaFile(mat, dim); //creo e scrivo il file output

    freeMat(mat, dim);

    free(dim);

    freeLista(testa);

    return 0;
}

int **letturaFile(dati *dim){

    FILE *fi = fopen("matrice.txt", "r");
    int n;

    if(!fi) return NULL;

    fscanf(fi,"%d",&dim->n);

    int **mat = (int**)malloc(dim->n*sizeof(int*));

    for(int i=0; i<dim->n; i++)
        mat[i] = (int *)malloc(dim->n*sizeof(int));

    for(int i=0; i<dim->n; i++){

        for(int j=0; j<dim->n; j++){

            fscanf(fi,"%d",&mat[i][j]);
        }
        
    }
    fclose(fi);
    printM(mat, dim);

    return mat;
}

void printM(int **mat, dati *dim){

    printf("\n");
    if(!mat){

        printf("Errore nella scrittura della matrice\n");
        return; 
    }

    for(int i = 0; i <dim->n; i++){

        for(int j = 0; j<dim->n; j++){

           printf(" %d ", mat[i][j] );

        }
        printf("\n");
    }

}

int **modMat(int **mat, dati *dim){

    int temp;

    for(int i = 0; i<dim->n; i++){

        for(int j = i+1; j<dim->n; j++){

            temp = mat[j][i];
            mat[j][i]=mat[i][j];
            mat[i][j]= temp;
            
            //mat[j][i]=mat[i][j];

        }
    }

    printf("\nMatrice trasposta\n");
    printM(mat, dim);
    return mat;
}

nodo *creaL(int **mat, dati * dim){   

    nodo *testa = NULL;
    nodo *nodo_t;
    int count=0;

    for(int i = 0; i <dim->n; i++){

        for(int j = 0; j<dim->n; j++){

            if(mat[i][j] != 0){

                if (!testa){

                    testa = (nodo *)malloc(sizeof(nodo));
                    testa->data = mat[i][j];
                    testa->nR = i;
                    testa->nC = count; 
                    testa->next = NULL; 
                    nodo_t = testa;
                    
                }
                else{

                    nodo *newnodo = (nodo *)malloc(sizeof(nodo));
                    newnodo->data = mat[i][j];
                    newnodo->nR = i;
                    newnodo->nC = j;
                    newnodo->next = NULL;
                    nodo_t->next = newnodo;
                    nodo_t = nodo_t ->next;
                }

            }

        }

    }

    printL(testa);

    return testa;
}

void printL(nodo *slide){

    printf("\n");
    if (!slide) printf("Lista vuota\n");
    else
    while(slide)
    {
        printf("(%d, %d, %d) -> ", slide->nR, slide->nC, slide->data);
        slide = slide->next;
    }
    printf("NULL\n");

}

nodo *modLista(nodo *testa){

    nodo *slide_t = testa;
    while(slide_t){

        if(slide_t->data % 2 != 0) slide_t->data = 0;

        slide_t = slide_t->next;
    }

    printf("\nLista modificata");
    printL(testa);
    return testa;
}

void scritturaFile(int **mat, dati *dim){

    FILE *fp = fopen("matrice2.txt", "w");

    if(!fp){
        printf("\nErrore apertura file\n"); 
        return; 
    }

    fprintf(fp,"%d\n",dim->n);

    for(int i=0; i<dim->n; i++){

        for(int j=0; j<dim->n; j++){

            fprintf(fp,"%d ",mat[i][j]);
        }
        
        fprintf(fp,"\n");
    }

    fclose(fp);
}

int **aggMat(int **mat, dati *dim, nodo *testa){

    nodo *slide_t = testa;

    while(slide_t){

        for(int i = 0; i<dim->n; i++){

            for(int j = 0; j<dim->n; j++){
            mat[i][j]=slide_t->data;
            slide_t = slide_t->next;
            }
        }
    }
    
    printf("\nMatrice aggiornata\n");
    printM( mat, dim );
    return mat;

}

void freeMat(int **mat, dati *dim){

    for(int i=0; i<dim->n; i++)
        free(mat[i]);
    free(mat);

    printf("\nMatrice Deallocata\n");

}

void freeLista(nodo *lista){

    if (lista != NULL) {
        freeLista(lista->next);
        freeNodo(lista);
    }
}

void freeNodo(nodo *nodo){

    free((void *) nodo);

}