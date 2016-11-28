#include <unistd.h>

int main(int argc, char *argv[])
{
    char buff[100];					// String der Länge 100; alloziert Speicher?!

    if(argc < 2)					// Wenn weniger als 2 Parameter angegeben, ...
    {
        printf("Syntax: %s <input string>\n", argv[0]); // ... dann gebe Nutzungshinweis
        exit (0);
    }

    strcpy(buff, argv[1]);		// Kopiert den Inputstring in den Buffer 
    return 0;					// Idee: Inputstring > 100 => BufferOverflow
}
