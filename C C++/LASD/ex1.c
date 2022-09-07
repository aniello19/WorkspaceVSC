#include<stdio.h>
#include<stdlib.h>

typedef struct albero{

    int valore;
    struct albero* sinistro;
    struct albero* destro;

}albero;

albero* newNode(int val);
int isABRUtil(albero* a, int min, int max);
int isABR(albero* a);

int main(void){

    albero* a = newNode(7);
    a->sinistro = newNode(1);
    a->destro = newNode(10);
    a->sinistro->sinistro = newNode(0);
    a->sinistro->destro= newNode(5);

    if(isABR(a))
        printf("IS ABR\n");
    else    
        printf("IS NOT A ABR\n");

    return 0;
}

albero* newNode(int val){

    albero* a=(albero*)malloc(sizeof(albero));
    a->valore=val;
    a->destro=NULL;
    a->sinistro=NULL;

    return a;
}

int isABR(albero* a){
    return(isABRUtil(a, INT_MIN, INT_MAX));
}

int isABRUtil(albero* a, int min, int max){

    if(a==NULL)
        return 1;

    if(a->valore < min || a->valore > max)
        return 0;

    return isABRUtil(a->sinistro, min, a->valore) && isABRUtil(a->destro, a->valore, max);

}