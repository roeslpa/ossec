#include "stdio.h"
#include "string.h"


// please do not recompile the binary
// to compile: gcc -m32 -fno-stack-protector -zexecstack vuln.c -o vuln



void helpFunction(char *inputString) {

	puts("Not yet finished, should display the help of the given string");

}




void printFunction(char *inputString) {

	puts(inputString);

}


void checkFunction(char *inputString) {

	puts("Not yet finished, should check the given string");

}





void registerFunctions(void (**ptrAddrs)(char *)) {
	
	ptrAddrs[0] = helpFunction;			//initialisiert, also schreibt Function auf Stack?
	ptrAddrs[1] = printFunction;		//initialisiert, also schreibt Function auf Stack?
	ptrAddrs[2] = checkFunction;		//initialisiert, also schreibt Function auf Stack?

}




int main(int argc, char* argv[]) {

	void (*ptrAddrs[3])(char *);		//3 stelliges Array mit Inhalt vom Typ void (char *)
	char buff[100];						//100 stelliges chararray
	char cmd[5];						//5 stelliges chararray

	registerFunctions(ptrAddrs);		//array initialisieren (jeder Index eine Funktion)

	if(argc < 3) {						//was passiert bei >= 3 argumenten?
		printf("Syntax: %s <input cmd> <cmd argument>\n", argv[0]);
		exit(0);
	}


	if(!(strlen(argv[1]) < 5)) {		//WENN  cmd length > 4
		puts("Wrong size of cmd");
		exit(0);
	}
	strcpy(cmd, argv[1]);				// <<<<---- CRASHBAR ???
	if(!(strlen(argv[2]) <= 100 + strlen(argv[1]))) { // Hier hat man 100 Zeichen Platz um in buff zu schreiben Buff wird dann aufgerufen!!! Man sollte PrintFunction also PRIN verwenden!!!
		puts("Wrong size of argument");
		exit(0);
	}
	strcpy(buff, argv[2]);				// <<<<---- CRASHBAR !!!


	if(strcmp(cmd, "HELP") == 0) {
		ptrAddrs[0](buff);
	}
	else if(strcmp(cmd, "PRIN") == 0) {
		ptrAddrs[1](buff);
	}
	else if(strcmp(cmd, "CHEC") == 0) {
		ptrAddrs[2](buff);
	}
	else {
		puts("Illegal cmd");
		exit(0);
	}

}