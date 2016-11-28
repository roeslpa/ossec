#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main (int argc, char* argv[])
{
   struct stat st;
   FILE* fp;

   if (argc != 3) {
       fprintf (stderr, "usage : %s file message\n", argv[0]);
       exit(EXIT_FAILURE);
   }
   
   if (stat(argv[1], & st) < 0) {
       fprintf (stderr, "Cannot find %s\n", argv[1]);
       exit(EXIT_FAILURE);
   }
   
   if (st.st_uid != getuid()) {
       fprintf (stderr, "Not the owner of %s \n", argv[1]);
       exit(EXIT_FAILURE);
   }
   
   if (! S_ISREG (st.st_mode)) {
       fprintf (stderr, "%s is not a normal file\n", argv[1]);
       exit(EXIT_FAILURE);
   }
   
   sleep(1);
   
   if ((fp = fopen(argv[1], "a")) == NULL) {
       fprintf (stderr, "Cannot open file\n");
       exit(EXIT_FAILURE);
   }

   fprintf(fp, "%s\n", argv[2]);
   fclose(fp);
   fprintf(stderr, "Write Ok\n");
   exit(EXIT_SUCCESS);
}
