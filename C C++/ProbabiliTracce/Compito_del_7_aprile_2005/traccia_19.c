/*
Un file contiene le informazioni sui recapiti di una serie di persone, ciascuno
su di una riga, secondo il seguente formato:
nominativo; indirizzo; capecitta; siglaprovincia
in cui i dati relativi a ciascuna voce possono contenere degli spazi e sono separati da punti e virgola come
nell’esempio seguente:

Pietro Savorgnan di Brazza’; Via del castello; 33030 Brazzacco; UD
Giacomo Leopardi; Via Ginestra 123/A; 62019 Recanati; AN
Galileo Galilei; Campo dei miracoli 1; 56100 Pisa; PI
Carlo Goldoni; Fondamenta Polonese 2A; 30100 Venezia; VE
Marco Polo; Calle Goldoni 3; 30100 Venezia; VE

Si scriva una funzione C che prende come parametri il nome di un file siffatto, una stringa s ed il
nome di un file di output. La funzione dovr`a scrivere nel file di output solo i recapiti di quelle persone
per i quali la stringa s `e contenuta come sottostringa nel campo indirizzo.
Ad esempio, nel caso del file precedente e della stringa s = "lo", la funzione dovrebbe produrre il
file seguente:
Pietro Savorgnan di Brazza’; Via del castello; 33030 Brazzacco; UD
Carlo Goldoni; Fondamenta Polonese 2A; 30100 Venezia; VE
Nota: risulta utile la funzione strstr(char s[], char t[]) che restituisce il valore NULL se la stringa t non `e presente
nella stringa s e un valore diverso da NULL in caso contrario.*/


int main () 
{

    return 0;
}