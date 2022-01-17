#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

const char bienvenue[] = "Bienvenue dans le Shell ENSEA.\nPour quitter,tapez 'exit'\n";
const char prompt[] = "enseash %";

int main(){
	write(STDOUT_FILENO, bienvenue, sizeof(bienvenue));
	write(STDOUT_FILENO, prompt, sizeof(prompt));
	exit(EXIT_SUCCESS);
}

	
