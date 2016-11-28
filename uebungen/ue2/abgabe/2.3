// Paul Rösler 108012225686
// Eduard Hauck 108012207435
// Philipp Markert 108012225264
// small examples that demonstrates the general principle behind LD_PRELOAD
//
// compile via:
// $ gcc -shared -fPIC -o gethostbyname.so gethostbyname.c -ldl
//
// usage:
// $ LD_PRELOAD=./gethostbyname.so ./resolve rub.de
// $ rub.de = 
// $ 127.0.0.1
//

#define _GNU_SOURCE

#include <sys/types.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>

#include <arpa/inet.h>
#include <netinet/in.h>

// Pointer auf die Original-Funktion
struct hostent* (*org_ghbn)(const char *name) = NULL;


struct hostent *gethostbyname(const char *name)
{
    struct hostent* value = NULL;

    // laden der Funktionsadresse falls nicht schon geschehen
    if(org_ghbn == NULL)
        org_ghbn = dlsym(RTLD_NEXT, "gethostbyname");
    
    // ausfuehren der richtigen Original-Funktion
    value = org_ghbn(name);

	if(strcmp(name, "rub.de") == 0){
		inet_aton("127.0.0.1", (struct in_addr*) value->h_addr_list[0]);
		// Konvertiere die IP Adresse von einem dots-and-number String to a struct in_addr
	}

    return value;
}

