#include<stdio.h>
#define MAX 20

void push(int S[], int valore);
int pop(int S[]);
int empty_stack(int S[]);
int full_stack(int S[]);
void push_c(int S[], int val, int *err);
int pop_c(int S[], int *err);
void new_stack(int S[]);
void stampa_stack(int S[]);

int main(){
    int S[MAX+1], scelta, valore;
    do {
        printf("\nscelta: 0-Crea, 1-Stampa, 2-Pop, 3-Push, 4-uscita : "); 
        scanf("%d",&scelta); 
        switch(scelta) {
            case 0: 
                new_stack(S); 
                break;
            case 1: 
                stampa_stack(S); 
                break;
            case 2: 
                if(!empty_stack(S)) 
                    printf("\nTop dello Stack %d", pop(S)); 
                else 
                    printf("\nspiacente, stack vuoto");
                break;
            case 3: 
                if(!full_stack(S)) {
                    printf("\nvalore da inserire nello stack: ");
                    scanf("%d",&valore);
                    push(S,valore); 
                }else 
                    printf("\nspiacente, stack pieno");
                break;
        }
    }while(scelta==0 || scelta==1 || scelta==2 || scelta==3);
}

void push(int S[], int valore){
    S[0] = S[0]+ 1;
    S[S[0]]= valore;
}

int pop(int S[]){
    S[0] = S[0]-1;
    return S[S[0]+1];
}

int empty_stack(int S[]){
    return S[0]==0;
}
int full_stack(int S[]){
    return S[0]==MAX;
}

void push_c(int S[], int val, int *err){
    if (full_stack(S)) 
        *err=1;
    else {
        S[0] = S[0]+ 1;
        S[S[0]]= val;
        *err=0;
    }
}

int pop_c(int S[], int *err){ 
    int val=0;
    if (empty_stack(S)) 
        *err=1;
    else{
        S[0] = S[0]-1;
        val=S[S[0]+1];
        *err=0;
    }
    return val;
}

void new_stack(int S[]){ 
    int num_elementi, valore;
    //inizializza_stack(S); 
    printf("\nQuanti elementi (max %d elementi): ", MAX);
    scanf("%d", &num_elementi);
    while(num_elementi>MAX){
        printf("\nmax %d elementi: ", MAX);
        scanf("%d", &num_elementi);
    }
    while(num_elementi){
        printf("\nInserire un valore: ");
        scanf("%d", &valore);
        push(S, valore);
        --num_elementi;
    }
}

void stampa_stack(int S[]){
    int valore;
    if (!empty_stack(S)){
        valore=pop(S);
        printf(" %d ",valore);
        stampa_stack(S);
        push(S,valore);
    }
}