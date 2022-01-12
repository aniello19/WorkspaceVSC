/*

Un file contiene una sequenza (di lunghezza ignota) di studenti iscritti per
una prova d’esame. Ogni riga del file contiene la matricola, il nome, il cognome e l’anno di corso di uno
studente, pi`u un eventuale commento. Come esempio si consideri il seguente file.



Si noti che il nome e il cognome possono contenere spazi bianchi e sono seguiti da una virgola. Si
noti inoltre che l’anno di corso `e composto da un numero, uno spazio bianco e i due caratteri FC o RG,
a seconda che lo studente sia fuori corso o regolare, rispettivamente. 
Si assuma infine che il numero di spazi bianchi dopo la virgola sia arbitrario.

Si scriva una funzione C che prenda come parametri il nome del file e un anno di corso (un intero tra
1 e 5), e restituisca il numero di studenti iscritti fuori corso per quell’anno.

Nel caso che il file non esista, oppure l’anno di corso non sia compreso tra 1 e 5 la funzione deve
restituire il valore -1.

Esercizio 2 (punti 4) Si scriva una funzione main necessaria per verificare la correttezza della
funzione dell’esercizio 1. La funzione deve ricevere il nome del file e l’anno di corso sulla linea di comando.

29333 Mario, Rossi, 2 RG
34211 Irene, De Neri, 3 FC
23432 Pier Maria, Bianchi, 3 RG ciao mamma
35211 Giuseppe, Verdi, 4 FC odio questo esame!
22222 Chiara, Blu, 2 RG

*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista
{
    int matricola;
    char * nome;
    char * cognome;
    int anno;
    char * statoS;
    struct Lista *next;

}lista;

lista * letturaFILE( char *);
char * pulisciSTRINGA( char * , int *, bool);
lista * creaNodo(char * );
void printL( lista * );
//esercizio 1
int contaStudenti( lista * , int );


int main ( )
{
    lista * testa = letturaFILE("file.txt");

    printL( testa );

    int anno;
    printf("\ninserisci l'anno da controllare : ");
    scanf("%d", &anno);
    printf("gli studenti fuoricorso sono : %d",contaStudenti( testa, anno ));

    return 0;
}

lista * letturaFILE(char * fileName)
{
    lista * testa  = NULL;
    lista * nodo_t;

    FILE * fp = fopen( fileName, "r");
    if( !fp )
    {
        printf("errore nella lettura del file.");
        return NULL;
    }
    else
    { 
        while( !feof(fp))
        {
            char * uNclean =(char *)malloc( 80*sizeof( char ));

            fgets(uNclean, 80 , fp);

            if( !testa )
            {
                testa = creaNodo( uNclean );
                nodo_t = testa;
            }
            else 
            {
                nodo_t->next = creaNodo( uNclean );
                nodo_t = nodo_t->next;
            }

            free( uNclean );
        }

    }

    fclose( fp );
    return testa;
}

int contaStudenti( lista * testa , int anno )
{
    if( anno > 5 || anno <= 0) return -1;

    int studenti = 0;
    lista * slide = testa;

    while( slide )
    {
        printf("%d %s\n",slide->anno,slide->statoS );

        if( slide->anno == anno )
        {
            if(!strcmp( slide->statoS, "FC"))
            {
                studenti++;
            }
        } 
    
        slide = slide->next;
    }

    return studenti;
}

lista * creaNodo(char * uNclean)
{
    int i = 0;

    lista * new_nodo = (lista * )malloc(sizeof( lista ));

    char * msclean = pulisciSTRINGA ( uNclean,  &i ,false);
    new_nodo->matricola = atoi( msclean );

    msclean = pulisciSTRINGA ( uNclean,  &i ,true);
    new_nodo->nome = (char *) malloc( (strlen(msclean)+1)*sizeof(char));
    strcpy( new_nodo->nome,msclean );

    msclean = pulisciSTRINGA  ( uNclean,  &i ,true);
    new_nodo->cognome = (char *) malloc( (strlen(msclean)+1)*sizeof(char));
    strcpy( new_nodo->cognome,msclean );

    msclean = pulisciSTRINGA ( uNclean ,  &i, false);
    new_nodo->anno  = atoi(msclean )  ;

    msclean = pulisciSTRINGA ( uNclean,  &i ,false);
    new_nodo->statoS = (char *) malloc( (strlen(msclean)+1)*sizeof(char));
    strcpy( new_nodo->statoS,msclean );

    new_nodo->next = NULL;
    
    free( msclean );
    return new_nodo;
}

char * pulisciSTRINGA( char * uNclean, int *indice , bool controllo)
{
    int i = *indice; 
    char * clean  = ( char* )malloc ( 64 *sizeof( char));
    int j = 0;
    bool stop = true;
    
    //23432 Pier Maria, Bianchi, 3 RG ciao mamma

    while ( stop )
    {
        if( controllo )
        {
            clean[j] = uNclean[i];
            
            i++ , j++;

            if( uNclean[i] == 44)
            {
                clean[j] = 0 ;
                stop = false;
            }
                      
        }
        else
        {

            if(uNclean[i] == 0 || uNclean[i] == '\n')
            {
                clean[j] =  0 ;
                return clean;
            }
            clean[j] = uNclean[i];
            //printf("\nclean -> %c ,, unclean -> %c i->%d j->%d",clean[j],uNclean[i],i,j);
            i++ , j++;

            if( uNclean[i] == 32)
            {
                clean[j] = 0 ;
                stop = false;
            }
        }
        
    
    }
    i++;
    *indice = i;

    return clean;
}

void printL( lista * testa)
{
    lista * slide = testa;

    printf("\nStampo la lista dei studenti");
    while( slide )
    {
        printf("\n%d-%s-%s-%d-%s-",slide->matricola, slide->nome, slide->cognome, slide->anno,slide->statoS);
        slide = slide->next;
    }

}