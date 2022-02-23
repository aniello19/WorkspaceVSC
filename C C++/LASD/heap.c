#include<stdio.h>
#define MAX 20

int ArraySize, HeapSize, tot;

int left(int i){ 
    return 2*i+1;
}
int right(int i){ 
    return 2*i+2;
}
int parent (int i){
    return (i-1)/2;
}

void swap(int A[MAX], int i, int j);
void Heapify(int A[MAX], int i);
void BuildHeap(int A[MAX]);
void HeapSort(int A[MAX]);

int main(){
    int A[MAX], k;
    printf("\nQuanti elementi deve contenere l'array: ");
    scanf("%d", &tot);
    while(tot>MAX){
        printf("\n Max 20 elementi: "); 
        scanf("%d", &tot);
    }
    for(k=0;k<tot;k++) {
        printf("\nInserire il %d elemento: ", k+1);
        scanf("%d", &A[k]); 
    }
    HeapSize=ArraySize=tot;
    HeapSort(A);
    printf("\nArray Ordinato:");
    for(k=0;k<tot;k++)
        printf(" %d",A[k]);
}

void Heapify(int A[MAX], int i){

    int l,r,largest;
    l = left(i);
    r = right(i);
    if (l < HeapSize && A[l] > A[i])
        largest = l;
    else 
        largest = i;
    if (r < HeapSize && A[r] > A[largest])
        largest = r;
    if (largest != i) {
        swap(A, i, largest);
        Heapify(A, largest);
    }
}

void BuildHeap(int A[MAX]){
    int i;
    HeapSize = ArraySize;
    for (i=ArraySize/2; i>=0; i--)
        Heapify(A, i);
}

void HeapSort(int A[MAX]){
    int i;
    BuildHeap(A);
    for (i=ArraySize-1; i>=1; i--) {
        swap(A, 0, i);
        HeapSize--;
        Heapify(A, 0);
    }
}

void swap(int A[MAX], int i, int j){
    int tmp = A[i];
    A[i] = A[j]; 
    A[j] =tmp;
}