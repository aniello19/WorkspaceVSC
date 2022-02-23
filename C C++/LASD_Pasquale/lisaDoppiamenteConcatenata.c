#include "listaDoppiamenteConcatenata.h"


void inserimentoInTesta(Lista **testa,int data) //FUNZIONE CHE INSERISCE IN TESTA NELLA LISTA
{
    Lista *newNode=malloc(sizeof(Lista));

    newNode->data=data;
    newNode->next=(*testa);
    newNode->prev=NULL;

    if(*testa!=NULL)
        (*testa)->prev=newNode;

    (*testa)=newNode;
}

void eliminaNodo(Lista **testa,Lista **nodo) //FUNZIONE CHE ELIMINA UN NODO DALLA LISTA
{
    Lista *tmp=(*nodo);

    if((*nodo)->prev!=NULL)
    {
        (*nodo)->prev->next=(*nodo)->next;
    }
    else
        (*testa)=(*testa)->next;

    if((*nodo)->next!=NULL)
    {
        (*nodo)->next->prev=(*nodo)->prev;
    }

    free(tmp);

}
