#include<stdio.h>
#include<stdlib.h>

typedef struct albero{

    int valore;
    struct albero* sinistro;
    struct albero* destro;

}albero;

int isBSTUtil(albero* a, int min, int max);

int isBST(albero* a){
    return(isBSTUtil(a, INT_MIN, INT_MAX));
}

int isBSTUtil(albero* a, int min, int max){

    if(a==NULL)
        return 1;

    if(a->valore < min || a->valore > max)
        return 0;

    return isBSTUtil(a->sinistro, min, a->valore-1) && isBSTUtil(a->destro, a->valore+1, max);

}

albero* newNode(int val){

    albero* a=(albero*)malloc(sizeof(albero));
    a->valore=val;
    a->destro=NULL;
    a->sinistro=NULL;

    return a;
}

int main(void){

    albero* a = newNode(4);
    a->sinistro = newNode(2);
    a->destro = newNode(5);
    a->sinistro->sinistro = newNode(1);
    a->sinistro->destro= newNode(3);

    if(isBST(a))
        printf("IS BST\n");
    else    
        printf("IS NOT A BST\n");

    return 0;
}





