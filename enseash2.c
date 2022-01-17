#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#define SIZE_BUF 100

const char bienvenue[] = "Bienvenue dans le Shell ENSEA.\nPour quitter,tapez 'exit'\n";
const char prompt[] = "enseash %";
const char Exit[] = "exit";

int main(){
	char cmd[SIZE_BUF];
	int cmdlength;
	write(STDOUT_FILENO, bienvenue, sizeof(bienvenue));
	while(1){
		write(STDOUT_FILENO, prompt, sizeof(prompt));
		cmdlength=read(STDIN_FILENO, cmd , SIZE_BUF);
		cmd[cmdlength-1] = '\0';
		execlp(cmd, cmd,(char *)NULL);
	}
	exit(EXIT_SUCCESS);
}
