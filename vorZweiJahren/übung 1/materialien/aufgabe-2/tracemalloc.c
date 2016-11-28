// small examples that demonstrates the general principle behind LD_PRELOAD
//
// compile via:
// $ gcc -shared -FPIC -o tracemalloc.so tracemalloc.c
//
// usage:
// $ LD_PRELOAD=./tracemalloc.so /bin/ls
//
// => whenever a call to malloc() occurs a small debug info is printed

#define _GNU_SOURCE

#include <sys/types.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>

// Pointer auf die Original-Funktion
static void* (*org_malloc)(size_t size) = NULL;

void* malloc(size_t size)
{
    void* addr = NULL;

    // laden der Funktionsadresse falls nicht schon geschehen
    if(org_malloc == NULL)
        org_malloc = dlsym(RTLD_NEXT, "malloc");
    
    // ausfuehren der richtigen Original-Funktion
    addr = org_malloc(size);

    printf("0x%.8x bytes allocated at %p\n", size, addr);

    return addr;
}

