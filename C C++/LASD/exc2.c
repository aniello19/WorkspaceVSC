#include<stdio.h>
#include<stdlib.h>

typedef struct Lista{

    int val;
    struct Lista *next;
    struct Lista *prec;

}Lista;

typedef struct edge
{
    int key;
    struct edge *next;
}edge;

typedef struct graph
{
    int nv;
    edge **listaAdiacenza;
}graph;


void function(Lista *l, graph *G){

    Lista *new_node = l;
    l= (Lista*)malloc(sizeof(Lista));

    int c=0;

    while(new_node->val %2 == 0 && new_node->val < G->nv){
        if(new_node->val %2 != 0 || new_node->val > G->nv){
            l=new_node->next;
            new_node->prec=NULL;
            new_node->next=new_node->next->next;
        }
    }

    while(new_node){
        if(new_node->next->val %2 != 0 || new_node->next->val > G->nv){
            new_node->next = new_node->next->next;
            new_node->next->next->prec=new_node->next;
            new_node=new_node->next;
        }
    }
    while(new_node && G){
        if(new_node->val == G->listaAdiacenza[new_node->val]->key)
            c++;
        else   
            new_node=new_node->next;
        new_node=new_node->next;
    }
    if(c==G->listaAdiacenza[new_node->val]){
        printf("percorso trovato");
        G->listaAdiacenza[new_node->val]= NULL;
    }

}