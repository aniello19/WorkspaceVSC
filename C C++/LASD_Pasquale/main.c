#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "funzioniUtil.h"
#include "driver.h"
#include "spesa.h"

//PROTOTIPI FUNZIONI
void interfacciaIniziale();
void interfacciaFinale();
void interfacciaRegistrazioneDriver();
void interfacciaInserimentoCredenzialiDriver();
void interfacciaDriver(Driver **driver);
void interfacciaSpedizione(Driver **driver);
void recuperoDati();
void salvataggioDati();
//FINE PROTOTIPI FUNZIONI


//VARIABILI GLOBALI
char scelta;

//GRAFI
Graph *arcipelago=NULL;

//LISTE CONCATENATE
Driver * listaDriver = NULL;
Carrello *carrello = NULL;

//FILE PER IL SALAVATTAGIO DEI DATI
FILE* fileDriver;

//FINE VARIABILI GLOBALI


int main()
{
    recuperoDati();
    interfacciaIniziale();
    salvataggioDati();

    return 0;
}

/*
INTERFACCIA INIZIALE DEL PROGRAMMA
PERMETTE DI DECIDERE SE ACCEDERE COME UTENTE, OPERATORE SANITARIO OPPURE PERMETTE DI VISUALIZZARE LE PERSONE ATTUALMENTE POSITIVE
*/
void interfacciaIniziale()
{
    stampaTitolo();
    printf("# BENVENUTO A I-EATS\n");
    printf("                                             ___________________________________________\n");
    printf("# 1--> Primo accesso? Registrati             |I-EATS, la tua applicazione per viaggiare |\n");
    printf("                                             |in tutta sicurezza nel nostro bellissimo  |\n");
    printf("# 2--> Accedi come driver                    |arcipelago. Fai la spesa direttamente in  |\n");
    printf("                                             |app, seleziona l'isola in cui vuoi        |\n");
    printf("# 3--> Esci                                  |arrivare e lascia che I-EATS calcoli per  |\n");
    printf("                                             |te il percorso piu' veloce                |\n");
    printf("                                             |__________________________________________|\n\n");
    scanf("%c",&scelta);
    clear_buffer();
    system("cls");      //PULISCO LA CONSOLE DI COMANDO

    if(scelta=='1')
    {
        interfacciaRegistrazioneDriver();   //PASSO ALL' INTERFACCIA PER LA REGISTRAZIONE DEL DRIVER
    }
    else if(scelta=='2')
    {
        interfacciaInserimentoCredenzialiDriver();     //PASSO ALL'INTERFACCIA PER L'ACCESSO DI UN OPERATORE DEL LABORATORIO
    }
    else if(scelta=='3')//PASSO ALL' INTERFACCIA PER LA CHIUSURA DEL PROGRAMMA
    {
        interfacciaFinale();
    }
    else if(scelta!='3')
    {
        interfacciaIniziale();              //SE E' STATO IMMESSO UN CARATTERE DIVERSO DA QUELLI CONCESSI, RICARICO L'INTERFACCIA INIZIALE
                                            //SE IL CARATTERE IMMESSO E' '4' ESCO DAL PROGRAMMA
    }
    system("cls");
}

/*
INTERFACCIA PER L'INSERIMENTO DELLE CREDENZIALI DI UN OPERATORE PER ACCEDERE ALLA PIATTAFORMA
*/
void interfacciaInserimentoCredenzialiDriver()
{
    bool credenzialiPresenti;
    char username[11];
    char password[20];

    stampaTitolo();
    printf("# ACCESSO DRIVER\n\n");
    printf("%-20s","# Inserisci username (-1 per tornare indietro): ");
    scanf("%10s",username);
    clear_buffer();

    if(strcmp(username,"-1")==0)
    {
        system("cls");
        interfacciaIniziale();
    }
    else
    {
        printf("%-20s","# Inserisci password (-1 per tornare indietro): ");
        scanf("%19s",password);
        clear_buffer();

        if(strcmp(password,"-1")==0)
        {
            system("cls");
            interfacciaIniziale();
        }
        else
        {
            credenzialiPresenti=verificaCredenzialiDriver(listaDriver,username,password);     //VERIFICO CHE LE CREDENZIALI IMMESSE SIANO CORRETTE

            system("cls");

            if(credenzialiPresenti)
            {
                int pesoCamion;
                int pesoMerce;
                Driver *temp = getDriverByUsername(listaDriver,username);
                interfacciaDriver(&temp);      //SE LE CREDENZIALI SONO CORRETTE PASSO ALL'INTERFACCIA DRIVER
            }
            else
            {
                stampaTitolo();
                puts("# CREDENZIALI NON VALIDE");
                premiTastoPerContinuare();
                interfacciaInserimentoCredenzialiDriver();   //SE LE CREDENZIALI NON SONO CORRETTE RICARICO L'INTERFACCIA ATTUALE
            }
        }

    }
}

void interfacciaSpedizione(Driver **driver) //INTERFACCIA DELLA SPEDIZIONE DEL DRIVER
{
    int isola1, isola2;
    stampaTitolo();
    printArcipelago();
    printf("# Inserisci l'isola da cui parti (-1 per tornare indietro): ");
    scanf("%d",&isola1);
    clear_buffer();
    system("cls");
    stampaTitolo();
    printArcipelago();
    if(isola1!=-1)
    {
        if(isola1<arcipelago->numeroVertici)
        {

            printf("# Inserisci l'isola in cui vuoi arrivare (-1 per tornare indietro): ");
            scanf("%d",&isola2);
            clear_buffer();
            system("cls");
            stampaTitolo();
            printArcipelago();
            if(isola2!=-1)
            {
                if(isola2<arcipelago->numeroVertici && isola2!=isola1)
                {
                    int spedizioneAvvenuta=algoritmoDijkstra(arcipelago,isola1,isola2,(*driver)->peso+(*driver)->pesoMerce);

                    if(spedizioneAvvenuta==1)
                    {
                        (*driver)->pesoMerce=0;
                    }

                    interfacciaSpedizione(&(*driver));
                }
                else
                {
                    printf("# ATTENZIONE --> Indice isola non valido");
                    premiTastoPerContinuare();
                    interfacciaSpedizione(&(*driver));
                }
            }
            else
            {
                system("cls");
                interfacciaDriver(&(*driver));
            }
        }
        else
        {
            printf("# ATTENZIONE --> Non esiste un'isola con questo indice\n");
            premiTastoPerContinuare();
            interfacciaSpedizione(&(*driver));

        }
    }
    else
    {
        system("cls");
        interfacciaDriver(&(*driver));
    }
}

/*
INTERFACCIA DRIVER. SI ACCEDE A QUESTA INTERFACCIA INSERENDO CREDENZIALI DRIVER CORRETTE.
*/
void interfacciaDriver(Driver **driver)
{
    stampaTitolo();
    printf("# BENTORNATO: %s %25s %dkg%25s %dkg%25s %dkg\n\n",(*driver)->username,"Peso Camion:",(*driver)->peso,"Peso Merce:",(*driver)->pesoMerce,"Peso Totale",(*driver)->peso+(*driver)->pesoMerce);

    printf("# 1--> Fai la spesa\n\n");
    printf("# 2--> Annulla spesa\n\n");
    printf("# 3--> Parti per una spedizione\n\n");
    printf("# 4--> Esci\n\n");

    scanf("%c",&scelta);
    clear_buffer();
    system("cls");

    if(scelta=='1')
    {
        (*driver)->pesoMerce=faiSpesa(&carrello,(*driver)->pesoMerce,(*driver)->pesoMerce);
        interfacciaDriver(&(*driver));

    }
    else if(scelta=='2')
    {
        (*driver)->pesoMerce=0;
        interfacciaDriver(&(*driver));
    }
    else if(scelta=='3')
    {
        interfacciaSpedizione(&(*driver));
    }
    else if(scelta=='4')
    {
        interfacciaIniziale();          //ESCO DALLA SESSIONE E RITORNO ALL'INTERFACCIA INIZIALE
    }
    else
    {
        interfacciaDriver(&(*driver));      //RICARICO L'INTERFACCIA ATTUALE SE INSERISCO UN CARATTERE NON VALIDO
    }

}

/*
INTERFACCIA PER LA REGISTRAZIONE DI UN DRIVER.
*/
void interfacciaRegistrazioneDriver()
{
    char username[11];
    char password[20];
    int peso;
    stampaTitolo();
    printf("# REGISTRAZIONE DRIVER\n\n");
    printf("%-20s","# INSERISCI USERNAME (10 CARATTERI) (-1 PER TORNARE INDIETRO): ");
    scanf("%10s",username);
    clear_buffer();

    if(strcmp(username,"-1")==0)
    {
        system("cls");
        interfacciaIniziale();
    }
    else if(strlen(username)>10)
    {

        printf("\nUSERNAME NON VALIDO (L'USERNAME DEVE ESSERE FORMATO DA MASSIMO 10 CARATTERI)\n\n");
        premiTastoPerContinuare();
        interfacciaRegistrazioneDriver();
    }
    else
    {
        if(!usernameGiaPresente(listaDriver,username))
        {
            printf("%-20s","\n# INSERISCI PASSWORD, MAX 19 CARATTERI (-1 PER TORNARE INDIETRO): ");
            scanf("%20s",password);
            clear_buffer();

            if(strcmp(password,"-1")==0)
            {
                system("cls");
                interfacciaIniziale();
            }
            else if(strlen(password)>19)
            {
                printf("\n\nPASSWORD NON VALIDA (MASSIMA LUNGHEZZA 19 CARATTERI)\n\n");
                premiTastoPerContinuare();
                interfacciaRegistrazioneDriver();
            }
            else
            {
                printf("%-20s","\n# INSERISCI PESO DEL CAMION IN KG (MAX (-1 PER TORNARE INDIETRO): ");
                scanf("%d",&peso);
                clear_buffer();

                inserimentoInTestaDriver(&listaDriver,username,password,peso,0);   //INSERISCO L'OPERATORE IN TESTA ALLA LISTA DEGLI OPERATORI

                system("cls");
                stampaTitolo();
                printf("# REGISTRAZIONE AVVENUTA CON SUCCESSO\n");
                premiTastoPerContinuare();
                interfacciaIniziale();  //PASSO ALL'INTERFACCIA INIZIALE
            }
        }

        else
        {
            printf("# ATTENZIONE-- USERNAME GIA' PRESENTE SULLA PIATTAFORMA\n\n");
            premiTastoPerContinuare();
            interfacciaRegistrazioneDriver();
        }
    }

}

void interfacciaFinale() //INTERFACCIA PER LA CHIUSURA DEL PROGRAMMA
{
    printf("     ___      .______      .______       __  ____    ____  _______  _______   _______ .______        ______  __\n"
            "    /   \\     |   _  \\     |   _  \\     |  | \\   \\  /   / |   ____||       \\ |   ____||   _  \\      /      ||  |\n"
            "   /  ^  \\    |  |_)  |    |  |_)  |    |  |  \\   \\/   /  |  |__   |  .--.  ||  |__   |  |_)  |    |  ,----'|  |\n"
            "  /  /_\\  \\   |      /     |      /     |  |   \\      /   |   __|  |  |  |  ||   __|  |      /     |  |     |  |\n"
            " /  _____  \\  |  |\\  \\----.|  |\\  \\----. |  |    \\    /    |  |____ |  '--'  ||  |____ |  |\\  \\----.|  `----.|  |\n"
            "/__/     \\__\\ | _| `._____|| _| `._____||__|     \\__/     |_______||_______/ |_______|| _| `._____| \\______||__|\n");

premiTastoPerContinuare();
}

/*
FUNZIONE IL CUI SCOPO E' RECUPERARE I DATI DAI FILE DI TESTO E IMMETTERLI NELLE LISTE CONCATENATE CORRETTE
*/
void recuperoDati()
{
    //CREAZIONE ISOLA

    arcipelago=(Graph*)CreazioneIsola();

    //RIEMPIO IL VETTORE STATICO DI PRODOTTI
    riempiVettoreProdotti();

    //RECUPERO DRIVER
    fileDriver = fopen("driver.txt","r");       //APRO IL FILE IN MODALITA READ
    if(fileDriver==NULL)
        gestisci_errori();                      //SE L'APERTURA DEL FILE NON E' RIUSCITA CHIAMO UNA FUNZIONE CHE INTERROMPE IL PROGRAMMA
    riempiListaDriver(fileDriver,&listaDriver);      //FUNZIONE PER RIEMPIRE LA LISTA DRIVER
    fclose(fileDriver);                         //CHIUDO IL PROGRAMMA
}

/*
FUNZIONE IL CUI SCOPO E' RECUPERARE I DATI DALLE STRUTTURE DINAMICHE E SALVARLI NEI FILE DI TESTO CORRETTI
*/
void salvataggioDati()
{
    //SALVATAGGIO DRIVER
    fileDriver = fopen("driver.txt","w");     //APRO IL FILE IN MODALITA' WRITE
    if(fileDriver==NULL)
        gestisci_errori();                  //SE L'APERTURA DA PROBLEMI CHIAMO UNA FUNZIONE CHE INTERROMPE IL PROGRAMMA
    creaFileDriver(fileDriver,listaDriver);      //LA FUNZIONE INSERISCE I DATI DALLA STRUTTURA DINAMICA AL FILE
    fclose(fileDriver);
}

