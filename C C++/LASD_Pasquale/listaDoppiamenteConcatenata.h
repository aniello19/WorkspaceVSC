/*#ifndef LISTADOPPIAMENTECONCATENATA
#define LISTADOPPIAMENTECONCATENATA
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct lista
{
    int data;
    struct lista *next;
    struct lista *prev;
}Lista;

void inserimentoInTesta(Lista **testa,int data);
void eliminaNodo(Lista **testa,Lista **nodo);


//#endif // LISTADOPPIAMENTECONCATENATA
