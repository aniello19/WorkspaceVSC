/*
Un dato linguaggio di programmazione prevede l’inserimento di commenti nel
codice sorgente mediante il carattere ’#’ che deve precedere il testo del commento. Il commento termina
alla fine della riga. Come esempio si consideri il seguente file.

# questo e‘ un commento
start: xor r0 r0 # questo e‘ un altro commento
mv r1 r2 # ecc.
# inizia il ciclo
loop: ldbr r3 r2 # copia in R3 l’i-esimo carattere della stringa
jmpz end # se vale zero (’\0’) la stringa e‘ finita
inc r0 # incrementa il contatore
inc r2 # incrementa il puntatore
jmp loop # ripete
end: ret
# (commento) fine del programma

Si scriva una funzione C che riceva come parametro il nome del file sorgente contenente i commenti,
che ha estensione .tic, e scriva un file con il medesimo nome ma estensione .toc contenente soltanto
tutte le istruzioni e non i commenti. Il file risultante dall’esempio sar`a:
start: xor r0 r0
mv r1 r2
loop: ldbr r3 r2
jmpz end
inc r0
inc r2
jmp loop
end: ret
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void letturaFILE(char *);
char * changeName( char *);

int main( )
{
    letturaFILE("file.tic");

    return 0 ;
}

void letturaFILE(char * filenameIn)
{
    FILE * fpi = fopen(filenameIn,"r");
    
    char * filenameOt = changeName( filenameIn );

    FILE * fpo = fopen(filenameOt,"w");

    if(!fpi) printf("\nerrore scrittura file");
    else
    {

        while(!feof(fpi))
        {
            char c = fgetc(fpi);

            if(c == '#')
            {
                char * garbage= (char *)malloc(80*sizeof(char ));
                fgets(garbage,80,fpi);
                free(garbage);
            }
            else
            {
                fprintf(fpo,"%c",c); //il programma funziona solo che non mette a capo qando deve

            }
        }
    }
    fclose(fpi);
    fclose(fpo);

}

char * changeName( char * filenameIn)
{
    int k = 0;
    bool check = true;
    char * toc = ".toc";
    char *filenameOt = (char *)malloc(10*sizeof (char ));

   for( int i = 0; ; i++)
    {
        if(filenameIn[i] == '.' ) check = false;

        if( check ) filenameOt[i] = filenameIn[i];
        else filenameOt[i] = toc[k],k++; 
        
        if ( k>4)
        {
            filenameOt[i] = '\0';
            
            return filenameOt;
        }
    }
}