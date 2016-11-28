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
#include <netdb.h>
#include <stdlib.h>

// Pointer auf die Original-Funktion
static struct hostent* (*org_gethostbyname)(const char *host) = NULL;

extern struct hostent *gethostbyname(const char *host)
{

	struct hostent* addr = NULL;

    // laden der Funktionsadresse falls nicht schon geschehen
    if(org_gethostbyname == NULL){
        org_gethostbyname = dlsym(RTLD_NEXT, "gethostbyname");
    }
	// ausfuehren der richtigen Original-Funktion
    addr = org_gethostbyname(host);

	if(strcmp(host, "rub.de") == 0){		//Wenn der Hostname "rub.de" lautete, dann ...
		addr->h_addr_list[0] = "127.0.0.1";	//Ersetze die Host Adresse im "hostent" Struct
	}

	return addr;							//Gebe das manipulierte hostent Struct zurück
}
