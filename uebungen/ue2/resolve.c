//how to compile:
//gcc resolve.c -o resolve
//how to run
//./resolve hostname

#define _GNU_SOURCE

#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>

int main(int argc, char* args[])
{
    //print usage
    if(argc < 2)
    {
        printf("Usage: %s hostname\n", args[0]);
        exit(-1);
    }

    //resolve hostname
    struct hostent *hostentry = gethostbyname(args[1]);

    if(hostentry == NULL)
    {
        printf("gethostbyname(%s) failed\n", args[1]);
        exit(-1);
    }

    printf("%s = \n", hostentry->h_name);

    //walking through the struct an print data
    int i;
    for(i = 0; hostentry->h_addr_list[i] != NULL; i++)
    {
        printf("%s\n", (char*)inet_ntoa(*(struct in_addr*)hostentry->h_addr_list[i]));
    }
    exit(0);
}
