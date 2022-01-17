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
	char sortie[SIZE_BUF] = "enseash4[exit:0]%";
	char signal[SIZE_BUF] = "enseash4[sign:9]%";
	int status;
	char signfils[SIZE_BUF];
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
			wait(&status);
			if(WIFEXITED(status)){  //aucun signal n'a géné l'éxecution de la commande
				write(STDOUT_FILENO,sortie,strlen(sortie));}
			else if(WIFSIGNALED(status)){  //on regarde si un signal à empecher l'execution de la commande et à quel type de signal ça correspond
				signfils[0] = (char)WTERMSIG(status);
				write(STDOUT_FILENO,strcat(signal, &signfils[0]),strlen(signal));
			}		
		}
		write(STDOUT_FILENO, prompt, sizeof(prompt));
	}
	exit(EXIT_SUCCESS);
}

