#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "utente.h"
#include "operatore.h"
#include "funzioniUtil.h"
#include "richiestaPrenotazione.h"

#include "tamponeEffettuato.h"

#define CHIAVE_REGISTRAZIONE_OPERATORE "123456"

//IN QUESTO FILE SARANNO PRESENTI SOLO LE FUNZIONI PER L'INTERFACCIA UTENTE E LE DUE FUNZIONI PER IL RECUPERO E IL SALVATAGGIO DEI DATI

//INIZIO PROTOTIPI DI FUNZIONE

void interfacciaAccessoOperatore();
void interfacciaAccessoUtente();
void interfacciaElaborazioneTamponi(char *pin);
void interfacciaEliminaAppuntamentoManuale(char *pin);
void interfacciaEliminaAppuntamentoUtente(char *codiceFiscale,bool appuntamentoPresente);
void interfacciaFissaggioAppuntamenti(char *pin);
void interfacciaFissaggioManualeAppuntamento(char *pin);
void interfacciaIniziale();
void interfacciaInserimentoChiaveLaboratorio();
void interfacciaInserimentoCredenzialiOperatore();
void interfacciaInserimentoCredenzialiUtente();
void interfacciaOperatore(char *pin);
void interfacciaPositivi();
void interfacciaRegistrazioneOperatore();
void interfacciaRegistrazioneUtente();
void interfacciaRichiestaAppuntamento(char *codiceFiscale);
void interfacciaUtente(char *codiceFiscale);
void recuperoDati();
void salvataggioDati();

//FINE PROTOTIPI DI FUNZIONE

//VARIABILI GLOBALI
//LISTE CONCATENATE
char scelta;
Utente *utente = NULL;                            //LISTA CONTENENTE GLI UTENTI ISCRITTI ALLA PIATTAFORMA
Operatore *operatore = NULL;                      //LISTA CONTENENTE GLI OPERATORI SANTIARI ISCRITTI ALLA PIATTAFORMA
RichiestaPrenotazione *richiestaPrenotazione = NULL;    //LISTA CONTENETE LE RICHIESTE DI APPUNTAMENTI NON ANCORA PROCESSATE DAGLI OPERATORI
AppuntamentoFissato *appuntamentoFissato = NULL;    //LISTA CONTENENTE GLI APPUNTAMENTI FISSATI PER I TAMPONI
TamponeEffettuato *tamponeEffettuato = NULL;        //LISTA CONTENENTE TUTTI I TAMPONI PROCESSATI

//FILE PER IL SALAVATTAGIO DEI DATI
FILE *fileOperatori;
FILE *fileUtenti;
FILE *fileRichiestePrenotazioni;
FILE *fileAppuntamentiFissati;
FILE *fileTamponiEffettuati;
//FINE VARIABILI GLOBALI

int main()
{
    recuperoDati();         //RICHIAMO LA FUNZIONE PER IL RECUPERO DEI DATI MEMORIZZATI SUI FILE E LI IMMETTO NELLE RISPETTIVE LISTE CONCATENATE

    interfacciaIniziale();  //RICHIAMO L'INTERFACCIA INIZIALE DEL PROGRAMMA

    interfacciaFinale();
    salvataggioDati();      //RICHIAMO LA FUNZIONE PER TRASCRIVERE I DATI DALLE STRUTTURE DINAMICHE AI FILE



    return 0;
}

void interfacciaFinale()
{
    printf("     ___      .______      .______       __  ____    ____  _______  _______   _______ .______        ______  __\n"
            "    /   \\     |   _  \\     |   _  \\     |  | \\   \\  /   / |   ____||       \\ |   ____||   _  \      /      ||  |\n"
            "   /  ^  \\    |  |_)  |    |  |_)  |    |  |  \\   \\/   /  |  |__   |  .--.  ||  |__   |  |_)  |    |  ,----'|  |\n"
            "  /  /_\\  \\   |      /     |      /     |  |   \\      /   |   __|  |  |  |  ||   __|  |      /     |  |     |  |\n"
            " /  _____  \\  |  |\\  \\----.|  |\\  \----. |  |    \\    /    |  |____ |  '--'  ||  |____ |  |\\  \\----.|  `----.|  |\n"
            "/__/     \\__\\ | _| `._____|| _| `._____||__|     \\__/     |_______||_______/ |_______|| _| `._____| \\______||__|\n");

premiTastoPerContinuare();
}

/*
INTERFACCIA PER L'ACCESSO DI UN OPERATORE, PERMETTE DI ACCEDERE OPPURE DI REGISTRARSI SE E' IL PRIMO ACCESSO
*/
void interfacciaAccessoOperatore()
{
    stampaTitolo();
    printf("# --ACCESSO OPERATORE--\n\n");

    printf("# 1--> Accedi\n\n");
    printf("# 2--> Primo accesso? Registrati inserendo la chiave del laboratorio\n\n");
    printf("# 3--> Torna alla schermata principale\n\n");

    scanf("%c",&scelta);
    clear_buffer();
    system("cls");      //PULISCO LO SCHERMO

    if(scelta == '1')
    {
        interfacciaInserimentoCredenzialiOperatore();       //PASSO ALL'INTERFACCIA PER L'INSERIMENTO DELLE CREDENZIALI DI UN OPERATORE
    }
    else if(scelta == '2')
    {
        interfacciaInserimentoChiaveLaboratorio();          //PASSO ALL'INTERFACCIA PER L'INSERIMENTO DELLA CHIAVE NECESSARIA PER LA REGISTRAZIONE DI UN OPERATORE
    }
    else if(scelta == '3')
    {
        interfacciaIniziale();              //TORNO ALL'INTERFACCIA INIZIALE
    }
    else
    {
        interfacciaAccessoOperatore();      //SE INSERISCO UN CARATTERE NON VALIDO, RICARICO L'INTERFACCIA
    }


};

/*
INTERFACCIA PER L'ACCESSO DI UN UTENTE, PERMETTE DI ACCEDERE OPPURE DI REGISTRARSI SE E' IL PRIMO ACCESSO
*/
void interfacciaAccessoUtente()
{
    stampaTitolo();
    printf("# ACCESSO UTENTE\n\n");
    printf("# 1--> Accedi\n\n");
    printf("# 2--> Primo accesso? Registrati\n\n");
    printf("# 3--> Torna alla schermata principale\n\n");

    scanf("%c",&scelta);
    clear_buffer();
    system("cls");

    if(scelta == '1')
    {
        interfacciaInserimentoCredenzialiUtente();      //PASSO ALL'INTERFACCA PER L'INSERIMENTO DELLE CREDENZIALI
    }
    else if(scelta == '2')
    {
        interfacciaRegistrazioneUtente();       //PASSO ALL'INTERFACCIA PER LA REGISTRAZIONE
    }
    else if(scelta == '3')
    {
        interfacciaIniziale();        //TORNO INDIETRO ALL'INTERFACCIA PRECEDENTE
    }
    else
    {
        interfacciaAccessoUtente();     //SE INSERISCO UN CARATTERE NON VALIDO RICARICO L'INTERFACCIA ATTUALE
    }

};

/*
INTERFACCIA PER L'ELABORAZIONE DEI TAMPONI DEL GIORNO
*/
void interfacciaElaborazioneTamponi(char *pin)
{
    char scelta;
    stampaTitolo();
    printf("# ELABORAZIONE TAMPONI\n\n");
    if(!appuntamentiFissatiIsVoid(appuntamentoFissato))           //VERIFICO CHE LA LISTA DEGLI APPUNTAMENTI FISSATI NON SIA VUOTA
    {
        printf("# ATTENZIONE -> NON SONO PRESENTI APPUNTAMENTI FISSATI PER OGGI\n");
        premiTastoPerContinuare();          //CHIAMO UNA FUNZIONE CHE PERMETTE DI FAR CLICCARE UN TASTO PER PROCEDERE
        interfacciaOperatore(pin);          //RITORNO ALL'INTERFACCIA DELL'OPERATORE
    }
    else
    {
        stampaAppuntamentiDelGiorno(appuntamentoFissato);       //STAMPO TUTTI GLI APPUNTAMENTI FISSATI PER IL GIORNO ATTUALE

        printf("# 1--> Elabora i tamponi\n\n");
        printf("# 2--> Torna Indietro\n\n");
        scanf("%c",&scelta);
        clear_buffer();
        system("cls");      //PULISCO LO SCHERMO

        if(scelta=='1')
        {
            stampaTitolo();
            printf("# ELABORAZIONE TAMPONI\n\n");
            printf("%-19s %-15s\n\n","CODICE FISCALE","ESITO" );
            elaboraTamponi(&appuntamentoFissato,&tamponeEffettuato,&utente,pin);        //ELABORO I TAMPONI DEL GIORNO ATTUALE
            premiTastoPerContinuare();
            interfacciaOperatore(pin);      //RITRONO ALL'INTERFACCIA DELL'OPERATORE

        }
        else if(scelta=='2')
        {
            interfacciaOperatore(pin);      //RITORNO ALL'INTERFACCIA PRECEDENTE
        }
        else
        {
            interfacciaElaborazioneTamponi(pin);    //SE INSERISCO UN CARATTERE NON VALIDO, RICARICO L'INTERFACCIA ATTUALE
        }
    }

}

/*
INTERFACCIA PER L'ELIMINAZIONE MANUALE DI UN APPUNTAMENTO DA PARTE DI UN OPERATORE
*/
void interfacciaEliminaAppuntamentoManuale(char *pin)
{
    char codiceFiscale[17];

    stampaTitolo();
    printf("# ELIMINA APPUNTAMENTO\n\n");

    if(appuntamentiFissatiIsVoid(appuntamentoFissato))
    {
        printf("%-18s %-18s %-18s\n","CODICE FISCALE","GRAVITA'","FASCIA ORARIA");
        stampaLinea(52);                                //STAMPO UNA LINEA FORMATA DA 52 '-'
        stampaAppuntamentiFissati(appuntamentoFissato);     //STAMPO TUTTI GLI APPUNTAMENTI FISSATI
        printf("# Inserisci codice fiscale dell'utente a cui vuoi cancellare l'appuntamento\n\n# -1 per tornare indietro\n\n");
        scanf("%16s",codiceFiscale);
        strcpy(codiceFiscale,toUpper(codiceFiscale)); //CONVERTO IL CF IN MAIUSCOLO
        clear_buffer();
        system("cls");

        if(strcmp(codiceFiscale,"-1")==0)
        {
            interfacciaOperatore(pin);
        }
        else
        {
            if(!eliminaAppuntamentoFissatoCodiceFiscale(codiceFiscale,&appuntamentoFissato))     //LA FUNZIONE RITORNA TRUE SE L'ELIMINAZIONE E' ANDATA A BUON FINE
            {
                stampaTitolo();
                printf("# ATTENZIONE-- NON C'E' NESSUN APPUNTAMENTO FISSATO PER QUESTO UTENTE\n");
                premiTastoPerContinuare();
                interfacciaEliminaAppuntamentoManuale(pin);         //
            }
            else        //ENTRO IN QUESTO BLOCCO SE L'APPUNTAMENTO DEL CODICE FISCALE IMMESSO E' STATO ELIMINATO
            {
                stampaTitolo();
                printf("# APPUNTAMENTO ELIMINATO CON SUCCESSO\n\n");
                premiTastoPerContinuare();
                interfacciaOperatore(pin);      //RITORNO ALL'INTERFACCIA PRECEDENTE
            }
        }
    }
    else
    {
        printf("# ATTENZIONE-- NON C'E' NESSUN APPUNTAMENTO FISSATO\n\n");
        premiTastoPerContinuare();
        interfacciaOperatore(pin);         //
    }
}

/*
INTERFACCIA PER L'ELIMINAZIONE DI UNA RICHIESTA DI UN APPUNTAMENTO O DI UN APPUNTAMENTO GIA' FISSATO DA PARTE DI UN UTENTE
*/
void interfacciaEliminaAppuntamentoUtente(char *codiceFiscale,bool appuntamentoPresente)
{
    if(!appuntamentoPresente)       //VERIFICO CHE CI SIA UN APPUNTAMENTO FISSATO O UNA RICHIESTA DI APPUNTAMENTO
    {
        stampaTitolo();
        printf("# --ATTENZIONE--\n\n");
        printf("# NON E'POSSIBILE ELIMINARE ALCUN APPUNTAMENTO O RICHIESTA DI APPUNTAMENTO");
        premiTastoPerContinuare();
    }
    else        //ENTRO IN QUESTO BLOCCO SE ESISTE UNA RICHIESTA O UN APPUNTAMENTO FISSATO. CERCO PRIAM TRA LE RICHIESTE E POI TRA GLI APPUNTAMENTI GIA' FISSATI
    {
        bool richiestaTrovata=false;
        richiestaTrovata=eliminaRichiestaPrenotazione(codiceFiscale,&richiestaPrenotazione);    //LA FUNZIONE RESTITUISCE TRUE SE LA RICHIESTA DI PRENOTAZIONE DELL'UTENTE E'STATA TROVATA E ELIMINATA

        if(!richiestaTrovata)       //SE RICHIESTA TROVATA E' FALSE VUOL DIRE CHE DOVRO' ELIMINARE UN APPUNTAMENTO GIA' FISSATO
        {
            richiestaTrovata=eliminaAppuntamentoFissatoCodiceFiscale(codiceFiscale,&appuntamentoFissato);
        }
    }
    interfacciaUtente(codiceFiscale);
}

/*
INTERFACCIA PER IL FISSAGGIO AUTOMATICO DEGLI APPUNTAMENTI DA PARTE DI UN OPERATORE
*/
void interfacciaFissaggioAppuntamenti(char *pin)
{
    stampaTitolo();
    if(richiestaPrenotazioneIsVoid(richiestaPrenotazione))      //LA FUNZIONE RESTITUISCE TRUE SE NON CI SONO RICHIESTE DI APPUNTAMENTO
    {
        puts("# --ATTENZIONE-- NON SONO PRESENTI RICHIESTE DI APPUNTAMENTO");
        premiTastoPerContinuare();
        interfacciaOperatore(pin);      //RITORNO ALL'INTERFACCIA PRECEDENTE
    }
    else        //ENTRO IN QUESTO BLOCCO SE SONO PRESENTI DELLE RICHIESTE DI APPUNTAMENTO
    {
        printf("% -25s%-25s\n\n","CODICE FISCALE","GRAVITA' DELLA RICHIESTA (0->BASSA 6->ALTA)");
        stampaLinea(50);
        stampaRichiestePrenotazione(richiestaPrenotazione);     //STAMPO TUTTE LE RICHIESTE DI APPUNTAMENTO
        printf("# FISSARE AUTOMATICAMENTE GLI APPUNTAMENTI?\n\n");
        printf("# 0--> No! Riportami alla schermata iniziale\n\n");
        printf("# 1--> Si!\n\n");

        scanf("%c",&scelta);
        clear_buffer();
        system("cls");

        if(scelta == '0')
        {
            interfacciaOperatore(pin);  //TORNO ALL'INTERFACCIA PRECEDENTE
        }
        else if(scelta == '1')
        {
            /*
            AL FINE DI DETERMINARE LA FASCIA ORARIA DE, DEVO RECUPERARE IL NUMERO DELL'ULTIMO TAMPONE EFFETTUATO
            DIVIDERLO PER 6 PRENDENDO IL RESTO E AGGIUNGERCI 1. IN QUESTO MODO DETERMINERO' CON FACILITA'
            L'ULTIMO TAMPONE DEL GIORNO IN CHE FASCIA ORARIA E'STATO FATTO E FISSERO I NUOVI
            APPUNTAMENTI DI CONSEGUENZA. OGNI GIORNO GLI APPUNTAMENTI HANNO UN NUMERO CHE VA DA 1 A 6.


            */
            if(tamponeEffettuato==NULL)
            {
                /*
                SE LA LISTA DEI TAMPONI E' VUOTA VORRA' DIRE CHE DOVRO' FISSARE GLI APPUNTAMENTI DAL
                PRIMO TAMPONE DELLA GIORNATA,VERIFICO POI ALL'INTERNO DELLA FUNZIONE SE SONO PRESENTI
                GIA' ALTRI APPUNTAMENTI FISSATI E REGOLERO' IL NUMERO DI TAMPONE DI CONSEGUENZA.
                */
                fissaAppuntamenti(pin,&appuntamentoFissato,&richiestaPrenotazione,1);
            }
            else
            {
                fissaAppuntamenti(pin,&appuntamentoFissato,&richiestaPrenotazione,(tamponeEffettuato->numeroTampone)%6+1);
            }
            stampaTitolo();
            printf("# APPUNTAMENTI FISSATI\n\n");
            premiTastoPerContinuare();
            interfacciaOperatore(pin); // RITORNO ALL'INTERFACCIA PRECEDENTE
        }
        else
        {
            interfacciaFissaggioAppuntamenti(pin);      //RICARICO L'INTERFACCIA SE VIENE INSERITO UN CARATTERE NON CONSENTITO
        }
    }

}

/*
INTERFACCIA PER IL FISSAGGIO MANUALE DI UN APPUNTAMENTO PER UNO SPECIFICO UTENTE REGISTRATO ALLA PIATTAFORMA
*/
void interfacciaFissaggioManualeAppuntamento(char *pin)
{
    char codiceFiscale[17];
    stampaTitolo();
    printf("# FISSAGGIO MANUALE APPUNTAMENTO\n\n");
    printf("# Inserisci codice fiscale dell'utente a cui vuoi fissare un appuntamento.\n");
    printf("# L'appuntamento sara'fissato nel primo spazio libero\n\n");
    printf("# Inserisci -1 per tornare alla schermata precedente\n\n");

    scanf("%16s",codiceFiscale);
    strcpy(codiceFiscale,toUpper(codiceFiscale)); //CONVERTO IL CF IN MAIUSCOLO
    clear_buffer();
    system("cls");      //PULISCO LA CONSOLE DI COMANDO

    if(strcmp(codiceFiscale,"-1")==0)   //LA FUNZIONE RESTITUISCE 0 SE LE DUE STRINGHE PASSATE COME PARAMETRI SONO UGUALI
    {
        interfacciaOperatore(pin);      //SE VIENE IMMESSO -1 TORNO ALLA SCHERMATA PRECEDENTE
    }
    else if(codiceFiscalePresente(utente,codiceFiscale))    //VERIFICO CHE IL CODICE FISCALE SIA GIA' REGISTRATO ALLA PIATTAFORMA
    {
        if(trovaRichiesta(codiceFiscale,richiestaPrenotazione) || appuntamentoGiaPresente(appuntamentoFissato,codiceFiscale))
        {
            //SE E' GIA' PRESENTE UNA RICHIESTA DI APPUNTAMENTO O UN APPUNTAMENTO FISSATO PER IL CODICE FISCALE IMMESSO, NON PERMETTO DI FISSARE UN NUOVO APPUNTAMENTO
            stampaTitolo();
            printf("# ATTENZIONE-- E'GIA'PRESENTE UN APPUNTAMENTO O UNA RICHIESTA DI APPUNTAMENTO PER QUESTO UTENTE\n");
            premiTastoPerContinuare();
            interfacciaFissaggioManualeAppuntamento(pin);
        }
        else        //ENTRO IN QUESTO BLOCCO SE NON SONO PRESENTI RICHIESTE O APPUNTAMNETI PER IL CF IMMESSO
        {
            //INSERISCO DIRETTAMENTE IN CODA L'APPUNTAMENTO PER L'UTENTE SELEZIONATO
            //LA GRAVITA' DELLA RICHIESTA, BASATA NORMALMENTE SUI SINTOMI PRESENTI, VIENE IMPOSTA AL MASSIMO (6)
            if(tamponeEffettuato==NULL)
            {
                //MAGGIORI INFORMAZIONI NEL REPORT ALLEGATO PER QUANTO RIGUARDA LA GESTIONE DEI GIORNI E DELLE FASCE ORARIE
                inserimentoInCodaAppuntamentoFissato(&appuntamentoFissato,codiceFiscale,pin,"n",6,1);
            }
            else
            {
                //MAGGIORI INFORMAZIONI NEL REPORT ALLEGATO PER QUANTO RIGUARDA LA GESTIONE DEI GIORNI E DELLE FASCE ORARIE
                inserimentoInCodaAppuntamentoFissato(&appuntamentoFissato,codiceFiscale,pin,"n",0,(tamponeEffettuato->numeroTampone)%6+1);
            }
            stampaTitolo();
            printf("# APPUNTAMENTO FISSATO CON SUCCESSO\n");
            premiTastoPerContinuare();
            interfacciaOperatore(pin);
        }
    }
    else //ENTRO IN QUESTO BLOCCO SE IL CODICE FISCALE IMMESSO NON E' PRESENTE SULLA PIATTAFORMA
    {
        stampaTitolo();
        printf("# ATTENZIONE-- CODICE FISCALE NON PRESENTE SULLA PIATTAFORMA\n");
        premiTastoPerContinuare();
        interfacciaFissaggioManualeAppuntamento(pin);
    }
}

/*
INTERFACCIA INIZIALE DEL PROGRAMMA
PERMETTE DI DECIDERE SE ACCEDERE COME UTENTE, OPERATORE SANITARIO OPPURE PERMETTE DI VISUALIZZARE LE PERSONE ATTUALMENTE POSITIVE
*/
void interfacciaIniziale()
{
    stampaTitolo();
    printf("# 1--> Accedi come utente\n\n");
    printf("# 2--> Accedi come operatore del laboratorio\n\n");
    printf("# 3--> Visualizza codice fiscale delle persone attualmente positive\n\n");
    printf("# 4--> Esci\n\n");

    scanf("%c",&scelta);
    clear_buffer();
    system("cls");      //PULISCO LA CONSOLE DI COMANDO

    if(scelta=='1')
    {
        interfacciaAccessoUtente();        //PASSO ALL'INTERFACCIA PER L'ACCESSO DELL'UTENTE
    }
    else if(scelta=='2')
    {
        interfacciaAccessoOperatore();     //PASSO ALL'INTERFACCIA PER L'ACCESSO DI UN OPERATORE DEL LABORATORIO
    }
    else if(scelta=='3')
    {
        interfacciaPositivi();              //PASSO ALL'INTERFACCIA PER LA VISUALIZZAZIONE DEGLI UTENTI ATTUALMENTE POSITIVI
    }
    else if(scelta!='4')
    {
        interfacciaIniziale();              //SE E' STATO IMMESSO UN CARATTERE DIVERSO DA QUELLI CONCESSI, RICARICO L'INTERFACCIA INIZIALE
                                            //SE IL CARATTERE IMMESSO E' '4' ESCO DAL PROGRAMMA
    }
    system("cls");
}

/*
INTERFACCIA PER L'INSERIMENTO DELLA CHIAVE PER REGISTRARSI ALLA PIATTAFORMA COME OPERATORE.
LA CHIAVE (123456 AL MOMENTO DELLA STESURA DEL CODICE), FORNITA DA UN SUPERIORE, HA IL FINE DI IMPEDIRE
CHE UN NON ADDETTO, POSSA ISCRIVERSI ALLA PIATTAFORMA COME OPERATORE SANITARIO E ACCEDERE QUINDI A DATI SENSIBILI.
*/
void interfacciaInserimentoChiaveLaboratorio()
{
    char chiaveRegistrazione[30];
    stampaTitolo();
    printf("# INSERIMENTO CHIAVE LABORATORIO\n\n");
    printf("%-40s","# Inserisci chiave per la registrazione come operatore del laboratorio.\n\n# -1 per tornare indietro\n\n# Se non ne sei in possesso, richiedila a un tuo superiore:");
    scanf("%s",chiaveRegistrazione);
    clear_buffer();

    system("cls");      //PULISCO LA CONSOLE DI COMANDO

    if(strcmp(chiaveRegistrazione,"-1")==0)
    {
        interfacciaAccessoOperatore();
    }
    else
    {
        if(strcmp(chiaveRegistrazione,CHIAVE_REGISTRAZIONE_OPERATORE)==0)     //VERIFICO CHE LA CHIAVE IMMESSA SIA UGUALE AL VALORE STATICO
        {
            stampaTitolo();
            printf("# CHIAVE CORRETTA\n\n");
            premiTastoPerContinuare();
            interfacciaRegistrazioneOperatore();        //SE LA CHIAVE IMMMESSA E' CORRETTA PASSO ALL'INTERFACCIA PER LA REGISTRAZIONE DEI UN OPERATORE
        }
        else
        {
            stampaTitolo();
            printf("\n# CHIAVE ERRATA\n\n");              //SE LA CHIAVE E' ERRATA RICARICO L'INTERFACCIA ATTUALE
            premiTastoPerContinuare();
            interfacciaInserimentoChiaveLaboratorio();
        }
    }

}

/*
INTERFACCIA PER L'INSERIMENTO DELLE CREDENZIALI DI UN OPERATORE PER ACCEDERE ALLA PIATTAFORMA
*/
void interfacciaInserimentoCredenzialiOperatore()
{
    bool credenzialiPresenti;
    char pin[5];
    char password[20];

    stampaTitolo();
    printf("%-20s","# Inserisci PIN alfanumerico identificativo (-1 per tornare indietro):");
    scanf("%16s",pin);
    clear_buffer();

    if(strcmp(pin,"-1")==0)
    {
        interfacciaAccessoOperatore();
    }
    else
    {
        printf("%-20s","# Inserisci password (-1 per tornare indietro) : ");
        scanf("%19s",password);
        clear_buffer();

        if(strcmp(password,"-1")==0)
        {
            interfacciaAccessoOperatore();
        }
        else
        {
            credenzialiPresenti=verificaCredenzialiOperatore(operatore,pin,password);     //VERIFICO CHE LE CREDENZIALI IMMESSE SIANO CORRETTE

            system("cls");

            if(credenzialiPresenti)
            {
                interfacciaOperatore(pin);      //SE LE CREDENZIALI SONO CORRETTE PASSO ALL'INTERFACCIA OPERATORE
            }
            else
            {
                stampaTitolo();
                puts("# CREDENZIALI NON VALIDE");
                premiTastoPerContinuare();
                interfacciaInserimentoCredenzialiOperatore();   //SE LE CREDENZIALI NON SONO CORRETTE RICARICO L'INTERFACCIA ATTUALE
            }
        }

    }
}

/*
INTERFACCIA PER L'INSERIMENTO DELLE CREDENZIALI DI UN UTENTE PER ACCEDERE ALAL PIATTAFORMA
*/
void interfacciaInserimentoCredenzialiUtente()
{
    bool credenzialiPresenti;
    char codiceFiscale[17];
    char password[20];

    stampaTitolo();
    printf("%-20s","# Inserisci codice fiscale (-1 per tornare indietro): ");
    scanf("%16s",codiceFiscale);
    strcpy(codiceFiscale,toUpper(codiceFiscale)); //CONVERTO IL CF IN MAIUSCOLO
    printf("%s",codiceFiscale);
    clear_buffer();

    if(strcmp(codiceFiscale,"-1")==0)
    {
        system("cls");
        interfacciaAccessoUtente();
    }
    else
    {
        printf("%-20s","# Inserisci password (-1 per tornare indietro): ");
        scanf("%19s",password);
        clear_buffer();


        if(strcmp(password,"-1")==0)
        {
            system("cls");
            interfacciaAccessoUtente();
        }
        else
        {
            credenzialiPresenti=verificaCredenzialiUtente(utente,codiceFiscale,password);   //VERIFICO CHE LE CREDENZIALI IMMESSE SIANO CORRETTE

            system("cls");      //PULISCO LA CONSOLE DI COMANDO

            if(credenzialiPresenti)
                interfacciaUtente(codiceFiscale);     //SE LE CREDENZIALI SONO CORRETTE PASSO ALL'INTERFACCIA DELL'UTENTE
            else
            {
                stampaTitolo();
                puts("# CREDENZIALI NON VALIDE");
                premiTastoPerContinuare();
                interfacciaInserimentoCredenzialiUtente();  //SE LE CREDENZIALI NON SONO CORRETTE RICARICO L'INTERFACCIA ATTUALE
            }
        }

    }

}

/*
INTERFACCIA OPERATORE. SI ACCEDE A QUESTA INTERFACCIA INSERENDO CREDENZIALI OPERATORE CORRETTE.
*/
void interfacciaOperatore(char *pin)
{
    stampaTitolo();
    printf("# ID OPERATORE: %s\n\n",pin);

    printf("# 1--> Visualliza storico tamponi effettuati\n\n");
    printf("# 2--> Cancella appuntamento\n\n");
    printf("# 3--> Fissa appuntamenti per le richieste di tamponi\n\n");
    printf("# 4--> Fissa manualmente un appuntamento per un utente registrato alla piattaforma\n\n");
    printf("# 5--> Elabora i tamponi del giorno\n\n");
    printf("# 6--> Esci\n\n");

    scanf("%c",&scelta);
    clear_buffer();
    system("cls");

    if(scelta=='1')
    {
        stampaTitolo();
        printf("%-18s %-18s %-18s %-18s %-18s\n","NUMERO TAMPONE","CODICE FISCALE","PIN OPERATORE","FASCIA ORARIA","ESITO");
        stampaLinea(84);        //STAMPO UNA LINEA DI 84 '-'
        stampaTamponiEffettuati(tamponeEffettuato); //STAMPO A SCHERMO TUTTI I TAMPONI EFFETTUATI SINO A QUESTO MOMENTO
        premiTastoPerContinuare();
        interfacciaOperatore(pin);      //RITORNO ALL'INTERFACCIA OPERATORE

    }
    else if(scelta=='2')
    {
        interfacciaEliminaAppuntamentoManuale(pin);     //PASSO ALL'INTERFACCIA PER ELIMINARE MANUALMENTE UN APPUNTAMENTO FISSATO
    }
    else if(scelta=='3')
    {
        interfacciaFissaggioAppuntamenti(pin);      //PASSO ALL'INTERFACCIA PER FISSARE AUTOMATICAMENTE GLI APPUNTAMENTI
    }
    else if(scelta=='4')
    {
        interfacciaFissaggioManualeAppuntamento(pin);   //PASSO ALL'INTERFACCIA PER FISSARE MANUALMENTE UN APPUNTAMENTO A UN UTENTE REGISTRATO ALLA PIATTAFORMA
    }
    else if(scelta=='5')
    {
        interfacciaElaborazioneTamponi(pin);        //PASSO ALL'INTERFACCIA PER L'ELABORAZIONE AUTOMATICA DEI TAMPONI GIORNALIERI
    }
    else if(scelta=='6')
    {
        interfacciaIniziale();          //ESCO DALLA SESSIONE E RITORNO ALL'INTERFACCIA INIZIALE
    }
    else
    {
        interfacciaOperatore(pin);      //RICARICO L'INTERFACCIA ATTUALE SE INSERISCO UN CARATTERE NON VALIDO
    }

}

/*
INTERFACCIA POSITIVI. ACCESSIBILE SENZA L'INSERIMENTO DI CREDENZIALI. PERMETTE DI VISUALIZZARE GLI ATTUALMENTE POSITIVI.
*/
void interfacciaPositivi()
{
    stampaTitolo();
    printf("## PERSONE ATTUALMENTE POSITIVE  ##\n\n");
    printf("CODICE FISCALE\n");
    stampaLinea(14);
    stampaPositivi(utente);     //STAMPO A SCHERMO I CODICI FISCALI DEGLI UTENTI ATTUALMENTE POSITIVI
    premiTastoPerContinuare();
    interfacciaIniziale();
}

/*
INTERFACCIA PER LA REGISTRAZIONE DI UN OPERATORE. PERMETTE A UN OPERATORE, DOPO AVER INSERITO LA CHIAVE DI LABORATORIO, DI REGISTRARE LE PROPRIE CREDENZIALI.
*/
void interfacciaRegistrazioneOperatore()
{
    char pin[5];
    char password[20];
    stampaTitolo();
    printf("# REGISTRAZIONE OPERATORE\n\n");
    printf("%-20s","# INSERISCI PIN ALFANUMERICO (4 CARATTERI) (-1 PER TORNARE INDIETRO): ");
    scanf("%5s",pin);
    clear_buffer();

    if(strcmp(pin,"-1")==0)
    {
        system("cls");
        interfacciaAccessoOperatore();
    }
    else if(strlen(pin)!=4)
    {

        printf("\n\PIN ALFANUMERICO NON VALIDO (IL PIN DEVE ESSERE FORMATO DA 4 CARATTERI)\n\n");
        premiTastoPerContinuare();
        interfacciaRegistrazioneOperatore();
    }
    else
    {
        if(!pinGiaPresente(operatore,pin))
        {
            printf("%-20s","\n# INSERISCI PASSWORD, MAX 19 CARATTERI (-1 PER TORNARE INDIETRO): ");
            scanf("%20s",password);
            clear_buffer();

            if(strcmp(password,"-1")==0)
            {
                system("cls");
                interfacciaAccessoOperatore();
            }
            else if(strlen(password)>19)
            {
                printf("\n\nPASSWORD NON VALIDA (MASSIMA LUNGHEZZA 19 CARATTERI)\n\n");
                premiTastoPerContinuare();
                interfacciaRegistrazioneOperatore();
            }
            else
            {
                inserimentoInTestaOperatore(&operatore,pin,password);   //INSERISCO L'OPERATORE IN TESTA ALLA LISTA DEGLI OPERATORI
                stampaTitolo();
                printf("\n# REGISTRAZIONE AVVENUTA CON SUCCESSO\n");
                premiTastoPerContinuare();
                interfacciaAccessoOperatore();  //PASSO ALL'INTERFACCIA DI ACCESSO OPERATORE
            }
        }

        else
        {
            stampaTitolo();
            printf("# ATTENZIONE-- PIN IDENTIFICATIVO GIA' PRESENTE SULLA PIATTAFORMA\n\n");
            premiTastoPerContinuare();
            return interfacciaRegistrazioneUtente();
        }
    }

}

/*
INTERFACCIA REGISTRAZIONE UTENTE. PERMETTE A UN UTENTE DI REGISTRARE LE PROPRIE CREDENZIALI E ISCRIVERSI ALLA PIATTAFORMA
*/
void interfacciaRegistrazioneUtente()
{
    char codiceFiscale[17];
    char password[20];

    stampaTitolo();
    printf("# REGISTRAZIONE UTENTE\n\n");
    printf("%-20s","# INSERISCI CODICE FISCALE (-1 PER TORNARE INDIETRO): ");
    scanf("%17s",codiceFiscale);
    strcpy(codiceFiscale,toUpper(codiceFiscale)); //CONVERTO IL CF IN MAIUSCOLO
    clear_buffer();


    if(strcmp(codiceFiscale,"-1")==0)
    {
        system("cls");
        interfacciaAccessoUtente();
    }
    else
    {
        if(strlen(codiceFiscale)!=16)
        {
            printf("\n\nCODICE FISCALE NON VALIDO (UN CODICE FISCALE E' FORMATO DA 16 CARATTERI)\n\n");
            premiTastoPerContinuare();
            interfacciaRegistrazioneUtente();
        }
        else if(!codiceFiscalePresente(utente,codiceFiscale))
        {
            printf("%-20s","# INSERISCI PASSWORD, MAX 19 CARATTERI (-1 PER TORNARE INDIETRO): ");
            scanf("%20s",password);
            clear_buffer();

            if(strcmp(password,"-1")==0)
            {
                system("cls");
                interfacciaAccessoUtente();
            }
            else if(strlen(password)>19)
            {
                printf("\n\nPASSWORD NON VALIDA (MASSIMA LUNGHEZZA 19 CARATTERI)\n\n");
                premiTastoPerContinuare();
                interfacciaRegistrazioneUtente();
            }
            else
            {
                inserimentoInTestaUtente(&utente,codiceFiscale,password,false);     //INSERISCO L'UTENTE IN TESTA ALLA LISTA, IL FALSE STA A INDICARE LA POSITIVITA' AL COVID, CHE AL MOMENTO DELLA REGISTRAZIONE E' NULLA
                printf("\nREGISTRAZIONE AVVENUTA CON SUCCESSO\n");
                premiTastoPerContinuare();
                interfacciaAccessoUtente();     //PASSO ALL'INTERFACCIA DI ACCESSO UTENTE
            }
        }
        else
        {
            printf("# ATTENZIONE-- CODICE FISCALE GIA' PRESENTE SULLA PIATTAFORMA\n\n");
            premiTastoPerContinuare();
            system("cls");
            return interfacciaRegistrazioneUtente();
        }
    }
}


/*
INTERFACCIA RICHIESTA APPUNTAMENTO. PERMETTE A UN UTENTE DI INOLTRARE LA PORPRIA RICHIESTA DI APPUNTAMENTO.
PRIMA DI ESSERE INOLTRATA, L'UTENTE DOVRA' RISPONDERE AD ALCUNE DOMANDE AL FINE DI VALUTARE LA GRAVITA' DEL PROPRIO CASO.
RICHIESTE CON GRAVITA' ALTE AVRANNO LA PRECEDENZA IN FASE DI FISSAGGIO DEGLI APPUNTAMENTI.
*/
void interfacciaRichiestaAppuntamento(char *codiceFiscale)
{
    stampaTitolo();
    int gravitaRichiesta=0;
    printf("# Le verranno fatte alcune domande prima di inoltrare la sua richiesta:\n");
    premiTastoPerContinuare();
    gravitaRichiesta=domandeRichiestaAppuntamento();    //LA FUNZIONE MOSTRA A SCHERMO LE DOMANDE, RESTITUIRA' POI UN INTERO PARI ALLA GRAVITA' DEL CASO.
    stampaTitolo();
    inserimentoRichiestaPrenotazioneGravitaDecrescente(&richiestaPrenotazione,codiceFiscale,gravitaRichiesta);  //INSERISCO LA RICHIESTA DI APPUNTAMENTO IN LISTA PRIMA DI ALTRE RICHIESTE CON GRAVITA' PIU' BASSE.
    printf("# LA SUA RICHIESTA E' STATA INOLTRATA. UN OPERATORE LA ELABORERA' AL PIU' PRESTO;");
    premiTastoPerContinuare();
    interfacciaUtente(codiceFiscale);   //PASSO ALL'INTERFACCIA UTENTE


}

/*
INTERFACCIA UTENTE. ACCESSIBILE DOVE AVER IMMESSO CORRETTAMENTE CREDENZIALI UTENTE. MOSTRA A SCHERMO TUTTE LE
FUNZIONI ESEGUIBILI DA UN UTENTE REGISTRATO ALLA PIATTAFORMA.
*/
void interfacciaUtente(char *codiceFiscale)
{
    bool appuntamentoGiaFissato;
    stampaTitolo();
    printf("# BENTORNATO: %s\n\n",codiceFiscale);
    puts("# APPUNTAMENTI FISSATI:");
    //MOSTRO LO STATO DELLA PROPRIA RICHIESTA DI APPUNTAMENTO. SE L'APPUNTAMENTO E' STATO FISSATO, VERRANO INDICATI TRA QUANTI GIORNI PRESENTARSI AL LABORATORIO
    appuntamentoGiaFissato=mostraStatoRichiestaPrenotazione(codiceFiscale,richiestaPrenotazione,appuntamentoFissato);
    printf("# 1--> Richiedi un appuntamento\n\n");
    printf("# 2--> Cancella appuntamento\n\n");
    printf("# 3--> Visualizza esito tampone\n\n");
    printf("# 4--> Esci\n\n");

    scanf("%c",&scelta);
    clear_buffer();
    system("cls");

    if(scelta=='1')
    {
        //VERIFICA CHE NON SIANO GIA' STATI FISSATI DEGLI APPUNTAMENTI O CHE NON CI SIANO RICHIESTE DI APPUNTAMENTO PRIMA DI INOLTRARE UN ALTRA RICHIESTA
        if(!appuntamentoGiaFissato)

            interfacciaRichiestaAppuntamento(codiceFiscale);    //PASSO ALL'INTERFACCIA PER LA RICHIESTA DI UN NUOVO APPUNTAMENTO
        else    //ENTRO IN QUESTO BLOCCO SE E' STATO GIA' FISSATO UN APPUNTAMENTO O SE HO GIA' UNA RICHIESTA IN CORSO
        {
            stampaTitolo();
            printf("# --ATTENZIONE--\n\n");
            printf("# HAI GIA' FATTO RICHIESTA PER UN APPUNTAMENTO\n");
            premiTastoPerContinuare();
            interfacciaUtente(codiceFiscale);   //TORNO ALL'INTERFACCIA PRECEDENTE
        }
    }
    else if(scelta=='2')
    {
        interfacciaEliminaAppuntamentoUtente(codiceFiscale,appuntamentoGiaFissato); //PASSO ALL'INTERFACCIA PER ELIMINARE UNA APPUNTAMENTO O UNA RICHIESTA DI APPUNTAMENTO
    }
    else if(scelta=='3')
    {
        stampaTitolo();
        printf("# VISUALIZZAZIONE REFERTO ULTIMO TAMPONE\n\n");
        visualizzaEsitoUltimoTampone(codiceFiscale,tamponeEffettuato);  //PASSO ALL'INTERFACCIA DI VISUALIZZAZIONE DEL REFERTO DELL'ULTIMO TAMPONE ELABORATO
        premiTastoPerContinuare();
        interfacciaUtente(codiceFiscale);   //TORNO ALL'INTERFACCIA PRECEDENTE

    }
    else if(scelta=='4')
    {
        interfacciaIniziale();      //TORNO ALL'INTERFACCIA INIZIALE
    }
    else
    {
        interfacciaUtente(codiceFiscale);       //SE IMMETTO UN CARATTERE NON CONSENTITO, RICARICO L'INTERFACCIA ATTUALE
    }
}

/*
FUNZIONE IL CUI SCOPO E' RECUPERARE I DATI DAI FILE DI TESTO E IMMETTERLI NELLE LISTE CONCATENATE CORRETTE
*/
void recuperoDati()
{
    //RECUPERO UTENTI
    fileUtenti = fopen("utenti.txt","r");       //APRO IL FILE IN MODALITA READ
    if(fileUtenti==NULL)
        gestisci_errori();                      //SE L'APERTURA DEL FILE NON E' RIUSCITA CHIAMO UNA FUNZIONE CHE INTERROMPE IL PROGRAMMA
    riempiListaUtenti(fileUtenti,&utente);      //FUNZIONE PER RIEMPIRE LA LISTA UTENTE
    fclose(fileUtenti);                         //CHIUDO IL PROGRAMMA
    //RECUPERO OPERATORI
    fileOperatori = fopen("operatori.txt","r");
    if(fileOperatori==NULL)
        gestisci_errori();
    riempiListaOperatori(fileOperatori,&operatore); //FUNZIONE PER RIEMPIRE LA LISTA OPERATORE
    fclose(fileOperatori);
    //RECUPERO RICHIESTE PRENOTAZIONI
    fileRichiestePrenotazioni=fopen("richiestePrenotazioni.txt","r");
    if(fileRichiestePrenotazioni==NULL)
        gestisci_errori();
    riempiListaRichiestePrenotazioni(fileRichiestePrenotazioni,&richiestaPrenotazione); //FUNZIONE PER RIEMPIRE LA LISTA RICHIESTA PRENOTAZIONE
    fclose(fileRichiestePrenotazioni);
    //RECUPERO APPUNTAMENTI FISSATI
    fileAppuntamentiFissati=fopen("appuntamentiFissati.txt","r");
    if(fileAppuntamentiFissati==NULL)
        gestisci_errori();
    riempiListaAppuntamentiFissati(fileAppuntamentiFissati,&appuntamentoFissato);   //FUNZIONE PER RIEMPIRE LA LISTA APPUNTAMENTO FISSATO
    fclose(fileAppuntamentiFissati);
     //RECUPERO APPUNTAMENTI FISSATI
    fileTamponiEffettuati=fopen("tamponiEffettuati.txt","r");
    if(fileTamponiEffettuati==NULL)
        gestisci_errori();
    riempiListaTamponiEffettuati(fileTamponiEffettuati,&tamponeEffettuato);     //FUNZIONE PER RIEMPIRE LA LISTA TAMPONE EFFETTUATO
    fclose(fileTamponiEffettuati);
}

/*
FUNZIONE IL CUI SCOPO E' RECUPERARE I DATI DALLE STRUTTURE DINAMICHE E SALVARLI NEI FILE DI TESTO CORRETTI
*/
void salvataggioDati()
{
    //SALVATAGGIO UTENTI
    fileUtenti = fopen("utenti.txt","w");     //APRO IL FILE IN MODALITA' WRITE
    if(fileUtenti==NULL)
        gestisci_errori();                  //SE L'APERTURA DA PROBLEMI CHIAMO UNA FUNZIONE CHE INTERROMPE IL PROGRAMMA
    creaFileUtenti(fileUtenti,utente);      //LA FUNZIONE INSERISCE I DATI DALLA STRUTTURA DINAMICA AL FILE
    fclose(fileUtenti);
    //SALVATAGGIO OPERATORI
    fileOperatori = fopen("operatori.txt","w");
    if(fileOperatori==NULL)
        gestisci_errori();
    creaFileOperatori(fileOperatori,operatore); //LA FUNZIONE INSERISCE I DATI DALLA STRUTTURA DINAMICA AL FILE
    fclose(fileOperatori);
    //SALVATAGGIO RICHIESTE PRENOTAZIONI
    fileRichiestePrenotazioni=fopen("richiestePrenotazioni.txt","w");
    if(fileRichiestePrenotazioni==NULL)
        gestisci_errori();
    creaFileRichiestePrenotazioni(fileRichiestePrenotazioni,richiestaPrenotazione); //LA FUNZIONE INSERISCE I DATI DALLA STRUTTURA DINAMICA AL FILE
    fclose(fileRichiestePrenotazioni);
    //SALVATAGGIO APPUNTAMENTI FISSATI
    fileAppuntamentiFissati=fopen("appuntamentiFissati.txt","w");
    if(fileAppuntamentiFissati==NULL)
        gestisci_errori();
    creaFileAppuntamentiFissati(fileAppuntamentiFissati,appuntamentoFissato);   //LA FUNZIONE INSERISCE I DATI DALLA STRUTTURA DINAMICA AL FILE
    fclose(fileAppuntamentiFissati);
    //SALVATAGGIO TAMPONI EFFETTUATI
    fileTamponiEffettuati=fopen("tamponiEffettuati.txt","w");
    if(fileTamponiEffettuati==NULL)
        gestisci_errori();
    creaFileTamponiEffettuati(fileTamponiEffettuati,tamponeEffettuato); //LA FUNZIONE INSERISCE I DATI DALLA STRUTTURA DINAMICA AL FILE
    fclose(fileTamponiEffettuati);

}




