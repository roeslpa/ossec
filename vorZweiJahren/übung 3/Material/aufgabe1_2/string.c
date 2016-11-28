#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

  char buffer[512];
  static int value = 987654321;

  if (argc != 2)
    return -1;

  strcpy(buffer, argv[1]);

  printf(buffer);
  printf("\n");
  printf("(-) value @ 0x%08x = %d 0x%08x\n", &value, value, value);
  
  if (value==123129111) {
    printf("Variable wurde korrekt durch einen Formatstring Exploit geändert\n");
  }
  
  return 0;
}
