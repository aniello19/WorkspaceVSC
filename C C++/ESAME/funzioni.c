#include<stdio.h>
#include<stdlib.h>
#include"funzioni.h"


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
    printf("\nMatrice: \n");
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

        }
    }

    printf("\nMatrice trasposta: \n");
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

    printf("\nLista: \n");
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

    printf("\nLista modificata: \n");
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
    
    printf("\nMatrice aggiornata: \n");
    printM(mat, dim);
    return mat;

}