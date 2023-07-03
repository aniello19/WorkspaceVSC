#include <stdio.h>
#define MAX 20

int emptyQueue(int Q[]);
int fullQueue(int Q[]);
void enqueue(int Q[], int valore);
int dequeue(int Q[]);
void stampaQueue(int Q[]);
void reverse(int Q[]);
void newQueue(int Q[]);
void initQueue(int Q[]);


int main() {
    int Q[MAX + 2];
    int scelta, valore, elemento;
    do{
        printf("\nScegli quale operazione effettuare:\n"
               "0 - Crea\n"
               "1 - Stampa\n"
               "2 - Dequeue\n"
               "3 - Enqueue\n"
               "4 - Exit\n"
               "Inserire valore: ");
        scanf(" %d", &scelta);
        switch (scelta) {
            case 0:
                printf("\n!--- CREAZIONE CODA ---!");
                newQueue(Q);
                break;
            case 1:
                printf("\n!--- STAMPA CODA ---!\nCODA: ");
                stampaQueue(Q);
                reverse(Q);
                break;
            case 2:
                printf("\n!--- DEQUEUE CODA ---!");
                if(!emptyQueue(Q))
                    printf("\nHead della coda: %d", dequeue(Q));
                else
                    printf("\nCoda vuota!");
                break;
            case 3:
                printf("\n!--- ENQUEUE CODA ---!\n");
                if(emptyQueue(Q)){
                    printf("\nCoda non creata!");
                }
                else if(!fullQueue(Q)){
                    printf("Inserire valore da inserire: ");
                    scanf(" %d", &valore);
                    enqueue(Q, valore);
                }
                else
                    printf("\nCoda piena!");
                break;

        }
    } while (scelta == 0 || scelta == 1 || scelta == 2 || scelta == 3);

    return 0;
}

int emptyQueue(int Q[]){
    return Q[0] == 0;
}

int fullQueue(int Q[]){
    return Q[0] == Q[MAX + 1];
}

void enqueue(int Q[], int valore){
    Q[Q[MAX + 1]] = valore;
    if(Q[0] == 0)
        Q[0] = 1;
    Q[MAX + 1] = (Q[MAX + 1] % MAX) + 1;
}

int dequeue(int Q[]){
    int valore = Q[Q[0]];
    Q[0] = (Q[0] % MAX) + 1;

    if(Q[0] == Q[MAX + 1]){
        Q[0] = 0;
        Q[MAX + 1] = 1;
    }
    return valore;
}

void stampaQueue(int Q[]){
    int valore;
    if(!emptyQueue(Q)){
        valore = dequeue(Q);
        printf(" %d |", valore);
        stampaQueue(Q);
        enqueue(Q, valore);
    }
}

void reverse(int Q[]){
    int valore;
    if(!emptyQueue(Q)){
        valore = dequeue(Q);
        reverse(Q);
        enqueue(Q, valore);
    }
}

void newQueue(int Q[]){
    int numeroElementi, valore;
    initQueue(Q);
    printf("\nQuanti elementi vuoi inserire? Massimo %d elementi: ", MAX);
    scanf(" %d", &numeroElementi);
    while(numeroElementi > MAX){
        printf("\nMassimo %d elementi", MAX);
        scanf(" %d", &numeroElementi);
    }
    while(numeroElementi){
        printf("Inserisci un valore: ");
        scanf(" %d", &valore);
        enqueue(Q, valore);
        numeroElementi--;
    }
}

void initQueue(int Q[]){
    Q[0] = 0;
    Q[MAX + 1] = 1;
}