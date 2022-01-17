#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include <sys/wait.h>
#define SIZE_BUF 100

const char bienvenue[] = "Bienvenue dans le Shell ENSEA.\nPour quitter,tapez 'exit'\n";
const char prompt[] = "enseash %";
const char Exit[] = "exit";
const char byebye[] = "Bye Bye...\n";

int main(){
	char cmd[SIZE_BUF];
	int cmdlength;
	write(STDOUT_FILENO, bienvenue, sizeof(bienvenue));
	write(STDOUT_FILENO, prompt, sizeof(prompt));
	
	while(1){
		cmdlength=read(STDIN_FILENO, cmd , SIZE_BUF);
		cmd[cmdlength-1] = '\0';
		if (strncmp(cmd,Exit, sizeof(Exit))==0 || cmdlength == 0){
			write(STDOUT_FILENO, byebye, sizeof(byebye));
			break;
		}
		pid_t pid = fork();
		if(pid==0){
			execlp(cmd, cmd,(char *)NULL);
		}
		else{
			wait(NULL);
		}
		write(STDOUT_FILENO, prompt, sizeof(prompt));
	}
	exit(EXIT_SUCCESS);
}
