/**
*
Gruppe:
Dennis Röllke 108 012 233 235
Jan Kaiser 108 012 211 505
Phillip Müller 108 012 236 929

Die Schwachstelle kann auf drei Arten behoben werden.
1. Mehr checkst, zum Beispiel zstl. NACH dem Öffnen der Datei; aber auch das kann ausgehebelt werden. 
2. Die Zeit zwischen den Check und Use verkürzen; aber auch da kann man noch zwischen kommen. Letztlich ist 
3. die einzig sichere Möglichkeit: Der Check muss an den User gebunden werden. Dazu gibt es Betriebssystemabhängige Mittel. 
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
   sleep(1);		// <-- Sleeep rausnehmen
   if ((fp = fopen(argv[1], "a")) == NULL) { // Wenn Datei nicht geöffnet werden kann
       fprintf (stderr, "Cannot open file\n");
       exit(EXIT_FAILURE);
   }
   // Öffnen/ Schreiben sollte innerhalb eine If-Clause liegen; hier könnte so eine zstl. Abfrage erfolgen
   fprintf(fp, "%s\n", argv[2]);
   fclose(fp);
   fprintf(stderr, "Write Ok\n");
   exit(EXIT_SUCCESS);
}
