#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_authentication(char *password) {
	int auth_flag = 0;
	char password_buffer[16];

	strcpy(password_buffer, password);
	
	if(strcmp(password_buffer, "mysecr3tpass") == 0)
		auth_flag = 1;
	if(strcmp(password_buffer, "speakfriend") == 0)
		auth_flag = 1;

	return auth_flag;
}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("Usage: %s <password>\n", argv[0]);
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
