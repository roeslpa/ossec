/*
* Idee bzgl. Zeile 6 und 7 vertauschen:
* Der password_buffer[] kann nicht geflutet werden; das Passwort wird im Nachhinein zugeschnitten?!
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_authentication(char *password) {
	int auth_flag = 0;				// Zeile 6 ?
	char password_buffer[16];		// Zeile 7 ? Mehr Sinn macht wenn dies Zeile 6 ist, und das nächste Zeile 7

	strcpy(password_buffer, password);				 // Kopiert das als Parameter übergebene Passwort in den Buffer => Was wenn pw > 16 ?
	
	if(strcmp(password_buffer, "mysecr3tpass") == 0) // strcmp() == 0 für arg2=funct,NULL,...
		auth_flag = 1;
	if(strcmp(password_buffer, "speakfriend") == 0)  // passwordstring: "auth_flag=1;"
		auth_flag = 1;

	return auth_flag;
}

int main(int argc, char *argv[]) {
	if(argc < 2) {									// Wenn weniger als 2 Argumente verwendet, ...
		printf("Usage: %s <password>\n", argv[0]);	// ... dann gebe Nutzungshinweis
		exit(0);
	}
	if(check_authentication(argv[1])) {
		printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
		printf("      You are allowed to enter!.\n");
		printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	} else {
		printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
                printf("\nYou shall not pass!!.\n");
                printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
   }
}
