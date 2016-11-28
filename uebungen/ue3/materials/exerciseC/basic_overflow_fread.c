#include <stdio.h>

int main(int argc, char *argv[])
{

    char buff[100];

    if(argc < 2)
    {
        printf("Syntax: %s <fileToRead>\n", argv[0]);
        exit (0);
    }

    FILE *fd = fopen(argv[1], "r");
    fseek(fd, 0, SEEK_END);
    unsigned int size = ftell(fd);
    printf("%u\n", size);
    fseek(fd, 0, SEEK_SET);

    fread(buff, size, 1, fd);
    return 0;
}
