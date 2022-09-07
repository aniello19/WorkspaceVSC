#include<stdio.h>
#define MAX 20

int empty_queue(int Q[]);
int full_queue(int Q[]);
void enqueue(int Q[], int valore);
int dequeue(int Q[]);
void stampa_queue(int Q[]);
void rewerse(int Q[]);
void inizializza_queue(int Q[]);
void new_queue(int Q[]);

int main(void){

    int Q[MAX+2], scelta, valore;

    do{
        printf("\n0-Crea, 1-Stampa, 2-Deq, 3-Enq,, 4-uscita: ");
        scanf("%d", &scelta);
        switch(scelta){
            case 0: 
                new_queue(Q); 
                break;
            case 1: 
                stampa_queue(Q); 
                break;
            case 2: 
                if (!empty_queue(Q)) 
                    printf("\n Head della coda %d ", dequeue(Q)); 
                else 
                    printf("\n spiacente, coda vuoto");
                break;
            case 3: 
                if (!full_queue(Q)){
                    printf("\n Valore da inserire nello stack: ");
                    scanf("%d",&valore);
                    enqueue(Q,valore); 
                }else 
                    printf("\n spiacente, coda piena");
                break;
            case 4:
                break;
            }
    }
    while(scelta==0||scelta==1 ||scelta==2||scelta==3);
}

int empty_queue(int Q[]){

    return Q[0]==0;
}

int full_queue(int Q[]){ 

    return Q[0]==Q[MAX+1];

}

void enqueue(int Q[], int valore){

    Q[Q[MAX+1]] = valore;
    if (Q[0] == 0) 
        Q[0]=1; 
    Q[MAX+1] = (Q[MAX+1] % MAX) + 1; 
}

int dequeue(int Q[]){

    int valore=Q[Q[0]];
    Q[0] = (Q[0] % MAX) + 1;
    if (Q[0] == Q[MAX+1]){
        Q[0]=0; 
        Q[MAX+1]=1; 
    }

    return valore;
}

void stampa_queue(int Q[]){ 

    int val;
    if (!empty_queue(Q)){
        val=dequeue(Q);
        printf(" %d |",val);
        stampa_queue(Q);
        enqueue(Q,val);
    }
}

void rewerse(int Q[]){
    int val;
    if (!empty_queue(Q)){
        val=dequeue(Q);
        rewerse(Q);
        enqueue(Q,val); 
    }
}

void new_queue(int Q[]){
    int num_elementi,valore;
    Q[0]=0;
    Q[MAX+1]=1; 
    printf("\n Quanti elementi (max %d elementi): ", MAX);
    scanf("%d",&num_elementi);
    while (num_elementi >MAX){
        printf("\n max %d elementi: ", MAX);
        scanf("%d",&num_elementi);
    }
    while(num_elementi){
    printf("\n Inserire un valore: ");
    scanf("%d",&valore);
    enqueue(Q, valore);
    num_elementi--;
    }
}