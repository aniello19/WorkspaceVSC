/*
Si consideri un file contenente le informazioni sui voli in partenza da un
determinato aeroporto avente il seguente formato:

aereoporto / compagnia /   N-volo / giorni
FCO             AZ         1252     12345
FCO             AZ         1253     67
CDG             AF         94       1234567
AMS             KL         2348     12357
ZRH             LX         239      1357

I primi tre caratteri del file costituiscono il codice dell’aeroporto di destinazione, i due caratteri
successivi identificano la compagnia aerea ed il valore numerico costituisce il numero del volo. 
I dati suddetti sono separati da un singolo spazio. 
Segue (separata dai dati precedenti da un singolo spazio)
una sequenza di caratteri numerici compresi fra 1 e 7, non separati da spazi, che indica in quali giorni
quel volo `e previsto (il numero 1 corrisponde a luned`ı, il 2 a marted`ı, e cos`ı via fino al numero 7 che
corrisponde a domenica).

Ad esempio, nel file precedente la riga CDG AF 94 1234567 ha come destinazione l’aeroporto CDG, con
il volo AF numero 94, che viene effettuato tutti i giorni della settimana. Il volo ZRH LX 239 1357, invece,
viene effettuato solo nei giorni di luned`ı, mercoled`ı, venerd`ı e domenica.
Si scriva una funzione C che prenda come parametri

1. una stringa contenente il nome di un file siffatto,
2. una stringa di tre caratteri contenente l’aeroporto di destinazione dest,
3. un valore intero giorno, corrispondente ad un giorno della settimana secondo la codifica sopra
descritta.

La funzione deve restituire un record che contenga i seguenti dati relativi al volo verso la destinazione
richiesta nel giorno desiderato:

1. il codice della compagnia,
2. il numero del volo.

Qualora nel file non sia presente un volo verso la destinazione scelta per il giorno desiderato, la funzione
deve restituire un record in cui il codice della compagnia `e vuoto (cio`e la locazione 0 contiene il carattere
\0) e il numero del volo `e -1. Si assuma, inoltre, che nel file non possano essere presenti pi`u voli verso la
destinazione scelta per il giorno desiderato.

Ad esempio, nel caso del file precedente, se dest `e FCO e giorno `e 6, la funzione deve restituire
nell’apposita struct i valori AZ e 1253.
*/

*********************TRACCIA NON FINITA **********************

#include <stdio.h>
#include <stdlib.h>


typedef struct voli
{
    char * plane;
    char * company;
    int n_Plane;
    struct voli * next;

}volo;

typedef struct giorno
{
    int giorno;
    struct voli * volo;
    struct giorno * next;
}week;

week * letturaFILE(week*, char *);

volo * creaNodo ( FILE *, int []);
week * creaWeek ( void );

week * insert_volo( week * day_week,int [],volo *);
 
void printL ( week * );

/*
void printW( week * testa)
{
    week *slide = testa;

    while (slide)
    {
        printf("%d ",slide->giorno);
        slide = slide->next;
    }
    printf("\n");
}
*/

int main()
{

    week * testa = creaWeek();
    //printW( testa );
    testa = letturaFILE(testa, "file.txt" );

    printL(testa); 
    //week biglietto = findVolo( testa );

    return 0;
}

week * creaWeek( )
{
    week * testa = (week*)malloc (sizeof (week));
    week * nodo_t;
    

    testa->giorno = 1;
    testa->next = NULL;
    testa->volo = NULL;
    nodo_t = testa;

    for( int i = 2; i< 8; i++ )
    {
        week * newNode = (week *)malloc(sizeof (week ));
        newNode->giorno = i;
        newNode->next = NULL;
        newNode->volo = NULL;
        nodo_t->next = newNode;
        nodo_t = nodo_t->next;
    }
    
    return testa;
}

week * letturaFILE(week* testa_week ,char * fileName)
{
    week* testa = testa_week;

    FILE * fpi = fopen( fileName, "r");
    if( !fpi )
    {
        printf("errore nella lettura del file.");
        return NULL;
    }
    else
    { 
        while( !feof(fpi))
        {
            int weeks[7];

            volo * nodo_volo = creaNodo(fpi, weeks);

            testa = insert_volo( testa , weeks, nodo_volo);

            free( nodo_volo);
        }

    }

    fclose( fpi );
    return testa_week;
}

volo * creaNodo( FILE * fpi , int weeks[])
{
    volo * newNodo = ( volo * )malloc (sizeof(volo ));

    newNodo->plane = (char *)malloc(4 * sizeof(char));
    fscanf(fpi,"%s",newNodo->plane);

    newNodo->company = (char *)malloc(4 * sizeof(char));
    fscanf(fpi,"%s",newNodo->company);

    fscanf(fpi,"%d",&newNodo->n_Plane);
    
    char * str = (char *)malloc(7*( sizeof(char )));
    fscanf(fpi,"%s",str);

    int k = 0;
    for( int i = 0; i < 7 ; i++)
    {
        if(str[i] > 48 && str[i] < 56 )
        {
            weeks[k] = str[i] -'0' ;
            k++;
        }
        else
        {
            weeks[i] = 0;
        }
    }
    printf("\n%s %s %d\t\t",newNodo->plane,newNodo->company,newNodo->n_Plane);
    for(int i = 0; i<7; i++) printf("%d ",weeks[i]);

    newNodo->next = NULL;

    return newNodo;
}

week * insert_volo( week * day_week, int weeks[], volo * plane)
{
    week * day = day_week; // alias
    volo * insert;
    week * prev = NULL;
    int count = 0;
    // scorro la lista day per cercare quello di interesse
    int i = 0;
     
    while (day)  
    {
        volo * insert = day->volo;
        printf("\n%d %d -> ",day->giorno,weeks[i]);
        if ( weeks[i] == day->giorno )  // il genere esiste
        {
            
            if(!day->volo)
            {
                printf("ae");
                day->volo = plane;
                day->volo->next = NULL;
                insert = day->volo;
            }
            else
            {
                while(insert->next)
                {
                    insert = insert->next;
                    printf("ao?");
                    count++;
                    if (count > 100) exit(0);
                }
                insert->next = plane;
                insert->next = NULL;
            }
            i++;
        }
        
        prev = day; // ultimo genere non nullo a cui attaccare il prossimo genere

        day = day->next;
    }

    return day_week;
}


void printL(week *nodo) {

    if (!nodo) 
    { 

        printf ("lista vuota \n");
        return;
    
    }

    while(nodo) 
    {

        printf ("\ngiorno %d->\n", nodo->giorno);

        if(!nodo->volo) printf("\t\tNon esistono voli in questo giorno");
        else
        while (nodo->volo) 
        {   
            
            printf ("\t\t%s\n ",nodo->volo->plane);

            printf ("\t\t%s\n ",nodo->volo->company);

            printf ("\t\tNumero Volo %d\n ", nodo->volo->n_Plane);

            printf ("\t\t------------------------\n");

            nodo->volo = nodo->volo->next;

        }    

        nodo = nodo->next;
    }
}