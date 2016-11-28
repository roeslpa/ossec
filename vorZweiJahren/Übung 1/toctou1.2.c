/**
*
* Gruppe:
* Dennis R�llke 108 012 233 235
* Jan Kaiser 108 012 211 505
* Phillip M�ller 108 012 236 929
*
* Ziel ist es an allen If-Cases vorbeizukommen. 
* Schafft man es nach der Letzt Zugriffs�berpr�fung  einen symbolischen Link einzuschleusen wird die angegeben Datei ungepr�ft ge�ffnet. 
* Das ist hier m�glich, da Sleep verwendet wird und der Programmablauf in dem Moment von anderen Prozessen unterbrochen werden kann, 
* dann aber nicht nochmal pr�ft, sondern, nach dem Sleep weiterl�uft.
*
* Der Angrif selbst k�nnte mit Hilfe eines Shell Scripts geschehen:
* 1. Eine beliebige Datei zB Namens "dummy" erstellen mit �touch dummy�
* 2. Einen Softlink auf "dummy" erstellen mit "ln �s dummy ptr"
* 3. Ein Angriffs Script als parallelen Prozess ausf�hren mittels Shell Operator "&": ./attack.sh & ./toctou ptr �hello�
* In der attack.sh steht dabei der Befehl zum Ersetzen des Softlinks: "rm ptr; ln -s /etc/passwd ptr"
* 4. �berpr�fen ob der Angriff geklappt hat, also das wort "hello" in "passwd" steht mit "tail /etc/passwd"
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
					// Auff�llig !!!
   sleep(1);		// SLEEP, unterbricht den Programmablauf 
					// Hier ist es m�glich, dass ein anderer Prozess ausgef�hrt wird
					// Hier Angreifen
					// Warum wird das hier eigentlich gemacht?
   if ((fp = fopen(argv[1], "a")) == NULL) { // Wenn Datei nicht ge�ffnet werden kann
       fprintf (stderr, "Cannot open file\n");
       exit(EXIT_FAILURE);
   }
   // Auff�llig !!!
   // Wenn keiner der F�lle eintritt
   // Wird direkt in die Datei geschrieben und "Write OK" ausgegeben
   // Man muss also "nur" alle obigen If-Clauses umgehen,
   // Der Schreibzugriff selbst ist offensichtlich nicht gesch�tzt
   fprintf(fp, "%s\n", argv[2]);
   fclose(fp);
   fprintf(stderr, "Write Ok\n");
   exit(EXIT_SUCCESS);
}
