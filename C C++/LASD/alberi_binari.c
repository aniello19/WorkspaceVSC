#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	int inforadice;
	struct nodo *sinistro,*destro;
}Nodo;

int vuoto(Nodo *rad);
int radice(Nodo *rad, int *val);
Nodo *sinistro (Nodo *rad);
Nodo *destro (Nodo *rad);
Nodo * costruisci(Nodo *s, int r, Nodo *d);
void visita_in_preordine(Nodo *radice);
void visita_in_ordine(Nodo *radice);
void visita_in_postordine(Nodo *radice);
int ricerca(Nodo *radice, int r);
int ricerca_ric(Nodo *radice, int r);
Nodo *inserisci (Nodo *radice, int e);
void inserisciDP(Nodo **radice, int e);
int ricerca_minimo (Nodo *radice);
void sottraiMin(Nodo *radice, int min);


//Dato un albero binario di ricerca, i cui nodi sono caratterizzati da chiavi intere, e dato un intero k,
//scrivere una funzione ricorsiva che verifichi che k sia nell’albero, e se c’è restituisca la chiave minima
//del sottoalbero radicato in k

/*int main(void){
	int n,i;
	int elem,min;
	Nodo *rad;
	
	printf("Quanti elementi vuoi inserire? ");
	scanf("%d", &n);
	
	for(i = 0; i<n; i++){
		printf("inserire elemento n. %d : ", i+1);
		scanf("%d", &elem);
		rad = inserisci(rad,elem);
	}
	
	visita_in_ordine(rad);

    return 0;
	
}*/

//Dato un albero binario di ricerca, i cui nodi sono caratterizzati da chiavi intere, scrivere una funzione
//ricorsiva che sottragga ad ogni nodo la chiave minima dell’albero.


int main(void){
	int n,i;
	int elem,min;
	Nodo *rad;
	
	printf("Quanti elementi vuoi inserire? ");
	scanf("%d", &n);
	
	for(i = 0; i<n; i++){
		printf("inserire elemento n. %d : ",i+1);
		scanf("%d",&elem);
		rad = inserisci(rad,elem);
	}
	
	visita_in_ordine(rad);
	
	min = ricerca_minimo(rad);
	
	sottraiMin(rad,min);
	
	puts("");
	visita_in_ordine(rad);
}


void sottraiMin(struct nodo *radice, int min){	
	if(radice){ 
		sottraiMin(radice->sinistro,min);
		radice->inforadice = radice->inforadice - min;
		sottraiMin(radice->destro,min); 
	} 
}

//isEmpty
int vuoto(struct nodo *rad)
{
    if(rad) 
        return 0;
    else 
        return 1;
}

//ritorna 0 se l albero è vuoto, altrimenti memorizza nella variabile val il valore del nodo
int radice(struct nodo *rad, int *val)
{
	int ok=0;
	if(!vuoto(rad))
	{
		*val=rad->inforadice;
		ok=1;
	}
	return ok;
}

//Per avere il punt. al figlio sinistro (destro) di un nodo:
struct nodo *sinistro (struct nodo *rad)
{ 	
	struct nodo *risultato=NULL;
	if (!vuoto(rad)) 
		risultato=rad->sinistro;
	return NULL;
}

struct nodo *destro (struct nodo *rad)
{ 	
	struct nodo *risultato=NULL;
	if (!vuoto(rad)) 
		risultato=rad->destro;
	return NULL;
}

//Per costruire un nodo (o un albero a partire da due sottoalberi):
struct nodo *costruisci(struct nodo *s, int r, struct nodo *d)
{
	struct nodo *aux;
	aux=(struct nodo*)malloc(sizeof(struct nodo));
	if (aux) {
		aux->inforadice=r;
		aux->sinistro=s; 
		aux->destro=d; 
	}
	return aux;
}

void visita_in_preordine(struct nodo *radice) {
	if(radice){ 
		printf("%d ",radice->inforadice);
		visita_in_preordine(radice->sinistro);
		visita_in_preordine(radice->destro); 
	} 
}
		
void visita_in_ordine(struct nodo *radice){
	if(radice){ 
		visita_in_ordine(radice->sinistro);
		printf("%d ",radice->inforadice);
		visita_in_ordine(radice->destro); 
	} 
}
	
void visita_in_postordine(struct nodo *radice) {
	if(radice){ 
		visita_in_postordine(radice->sinistro);
		visita_in_postordine(radice->destro);
		printf("%d ",radice->inforadice); 
	} 
}
	
int ricerca(struct nodo *radice, int r){
	int trovato=0;
	while(radice && trovato==0){
		if(radice->inforadice==r)
			trovato=1; 					/* Trovato */
		else if(radice->inforadice > r)	/* Cerca nel sottoalbero sinistro */
			radice=radice->sinistro;
		else 							/* Cerca nel sottoalbero destro */
			radice=radice->destro;
	}
	return trovato;
}

int ricerca_ric(struct nodo *radice, int r){
	int trovato=0;
	if (!vuoto (radice)){   				/*else non trovato poiché ABR vuoto */
	if(radice->inforadice==r) 
		return 1; 							/* Trovato */
	else if(radice->inforadice > r)			/* Cerca nel sottoalbero sx */
		trovato=ricerca(radice->sinistro,r);
	else 									/* Cerca nel sottoalbero destro */
		trovato=ricerca(radice->destro,r);
	}
	return trovato;
}

//Inserimento di un nuovo nodo in un ABR
Nodo* inserisci(Nodo *radice, int e){
	Nodo *aux;
	if (vuoto(radice)){ /* Creazione di un nuovo nodo */
	
		aux=(Nodo*)malloc(sizeof(Nodo));
		if(aux){ 
			aux->inforadice=e;
			aux->sinistro = aux->destro = NULL;
			radice = aux;
		}
		else printf("Memoria non allocata" );
	}
	else if(e<radice->inforadice) 
		radice->sinistro = inserisci(radice->sinistro, e);
	else if(e>radice->inforadice) 
		radice->destro = inserisci(radice->destro, e);
	/* altrimenti il valore è già nell ABR e non si fa niente */
	return radice;
}

//void inserisciDP(struct nodo **radice, int e){   		//con doppi puntatori
//	struct nodo *aux;
//	if(*radice==NULL){ 									/* Creazione di un nuovo nodo */
//		aux=(struct nodo*)malloc(sizeof(struct nodo));
//		if(aux){ 
//			aux->inforadice=e;
//			aux->sinistro=aux->destro=NULL;
//			*radice=aux;
//		}
//		else 
//			printf( "Memoria non allocata" );
//	}
//	else if((*radice)->inforadice>e) 
//		inserisci(&(*radice)->sinistro,e);
//	else if((*radice)->inforadice<e) 
//		inserisci(&(*radice)->destro,e);
//}

int ricerca_minimo (struct nodo *radice)
{ /* per semplicità assumiamo tutti i valori del ABR positivi*/
	int min=0;
	if (!vuoto(radice)){
		if(radice->sinistro==NULL) 
			min=radice->inforadice;
		else 
			min=ricerca_minimo(radice->sinistro);
	}
	return min;
}
 

