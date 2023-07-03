#include <stdio.h>
#define MAX 20

void push(int S[], int valore);
int pop(int S[]);
int emptyStack(int S[]);
int fullStack(int S[]);
void newStack(int S[]);
void stampaStack(int S[]);
void initStack(int S[]);
void eliminaValoreStack(int S[], int elemento);

int main() {
    int S[MAX + 1];
    int scelta, valore, elemento;
    initStack(S);
    do{
        printf("\nScegli quale operazione effettuare:\n"
               "0 - Crea\n"
               "1 - Stampa\n"
               "2 - Pop\n"
               "3 - Push\n"
               "4 - Elimina Valore\n"
               "5 - Exit\n"
               "Inserire valore: ");
        scanf(" %d", &scelta);
        switch (scelta) {
            case 0:
                printf("\n!--- CREAZIONE STACK ---!");
                newStack(S);
                break;
            case 1:
                printf("\n!--- STAMPA STACK ---!\nSTACK: ");
                stampaStack(S);
                break;
            case 2:
                printf("\n!--- POP STACK ---!");
                if(!emptyStack(S))
                    printf("\nTop dello Stack: %d", pop(S));
                else
                    printf("\nStack vuoto!");
                break;
            case 3:
                printf("\n!--- PUSH STACK ---!\n");
                if(emptyStack(S)){
                    printf("\nStack non creato!");
                }
                else if(!fullStack(S)){
                    printf("Inserire valore da inserire: ");
                    scanf(" %d", &valore);
                    push(S, valore);
                }
                else
                    printf("\nStack pieno!");
                break;
            case 4:
                printf("Inserire valore da eliminare: ");
                scanf(" %d", &elemento);
                eliminaValoreStack(S, elemento);
                break;

        }
    } while (scelta == 0 || scelta == 1 || scelta == 2 || scelta == 3 || scelta == 4);

    return 0;
}

void push(int S[], int valore){
    if(fullStack(S))
        printf("\nERRORE!\n");
    else{
        S[0] = S[0] + 1;
        S[S[0]] = valore;
    }

}

int pop(int S[]){
    int valore = 0;
    if(emptyStack(S))
        printf("\nERRORE\n");
    else{
        S[0] = S[0] - 1;
        valore = S[S[0] + 1];
    }
    return valore;

}

int emptyStack(int S[]){
    return S[0] == 0;
}

int fullStack(int S[]){
    return S[0] == MAX;
}

void newStack(int S[]){
    if(!emptyStack(S)){
        printf("\nStack already created!");
    }else{
        int numeroElementi, valore;
        //initStack(S);
        printf("\nQuanti elementi vuoi inserire? Massimo %d elementi: ", MAX);
        scanf(" %d", &numeroElementi);
        while(numeroElementi > MAX) {
            printf("\nMassimo %d elementi", MAX);
            scanf(" %d", &numeroElementi);
        }
        while(numeroElementi){
            printf("Inserire valore: ");
            scanf(" %d", &valore);
            push(S, valore);
            --numeroElementi;
        }
    }
}

void stampaStack(int S[]){
    int valore;
    if(!emptyStack(S)){
        valore = pop(S);
        printf(" %d ", valore);
        stampaStack(S);
        push(S, valore);
    }
}

void eliminaValoreStack(int S[], int elemento){
    int valore;
    if(!emptyStack(S)){
        valore = pop(S);
        //printf(" %d ", valore);
        eliminaValoreStack(S, elemento);
        if(valore != elemento) {
            push(S, valore);
        }
    }
}

void initStack(int S[]){
    for(int i = 0; i < MAX + 1; i++){
        S[i] = 0;
    }
}