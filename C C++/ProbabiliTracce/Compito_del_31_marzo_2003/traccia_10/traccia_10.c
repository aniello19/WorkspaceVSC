/*
Un file indice contiene una sequenza di nome di file di dati (uno per riga). I
nomi hanno tutti il formato datiXX.txt, dove XX sono due caratteri numerici. Come esempio si consideri
il seguente file indice.

dati12.txt
dati05.txt
dati89.txt
dati44.txt
dati32.txt

I file di dati contengono ciascuno una sequenza di valori interi separati da spazi e/o ritorno a capo.
Come esempio si consideri il seguente file

3 47 23 12
45 8
74

Si scriva una funzione C che prenda come parametro il nome di un file indice ed un valore intero k e
restituisca la somma dei valori presenti nei soli file di dati tali che k `e maggiore dell’intero corrispondente
ai caratteri XX nel nome.
Ad esempio, se il file indice `e quello qui sopra e k = 34, la funzione deve restituire la somma dei valori
presenti nei soli file dati89.txt e dati44.txt.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//char * changeName( char * , int ); 
// la funzione changeName l'ho creata perche' avevo capito male la traccia e quindi 
// pensavo di dover trovare in una cartella i vari nomi dei file e quindi ho creato
// sta funzione che incrementa un val da 0 a 100 e cambia nome alla fileName cioe'
// dati(val).txt -> dati0.txt -> dati1.txt -> dati2.txt e cosi via fino a 99 pero' 
// pero' non dovevo fare questo quindi ses :P

int sommaFile(char *, int );
int findNumb( char *);

int main()
{
    int k;
    printf("Inserisci un dato per capire che file devo utilizzare: ");
    scanf("%d",&k);
    
    printf("\nLa somma degli valori dei file e' : %d ",sommaFile("fileData.txt",k));

    return 0;
}

int sommaFile(char * fileData, int k)
{
    char * fileName = ( char * )malloc(10+1 * sizeof(char));

    FILE * fp1, *fp2;
    int numero_file, val, somma = 0;

    fp1 = fopen(fileData,"r");

    while(fscanf(fp1,"%s",fileName) != EOF)
    {
        numero_file = findNumb( fileName);
        //printf("%d %d\n",k,numero_file);

        if (k < numero_file)
        {
            //printf("\nname->file %s numero->file %d\n",fileName, numero_file);

            fp2 = fopen(fileName,"r");
            while (fscanf(fp2,"%d",&val) != EOF) somma += val;

            fclose(fp2);
        }
    }
    fclose(fp1);
    return somma;
}

int findNumb( char * fileName)
{
    char valS[3];
    int k = 0;

    for( int i = 0; fileName[i]!= '\0';i++)
    {
        
        if(fileName[i] > 47 && fileName[i] < 58 )
        {
            
            valS[k] = fileName[i];
            k++;
            valS[k] = '\0';
        }
    }
    return atoi(valS);
}

/*
char * changeName( char * name, int val)
{
    int k = 0;
    char * txt = ".txt";

    char valS[3];
    sprintf(valS, "%d", val);
    
    bool check = true;
    char *newName = (char *)malloc(10*sizeof (char ));

   for( int i = 0; ; i++)
    {
        
        if(name[i-1] == 'i' )
        {
            check = false;

            while(valS[k] != '\0')
            {
                newName[i] = valS[k];
                i++,k++;
            }
            k = 0;
        }

        if( check ) newName[i] = name[i];
        else
        {
            
            newName[i] = txt[k],k++;
        }

        if ( k>4)
        {
            //newName[i] = '\0';
            
            return newName;
        }
        printf("%c %c\n",newName[i],name[i]);
    }
}
*/
