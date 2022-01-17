#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include <sys/wait.h>
#include <time.h>

#define SIZE_BUF 100
#define MILLION 1000000
#define MILLE 1000

const char bienvenue[] = "Bienvenue dans le Shell ENSEA.\nPour quitter,tapez 'exit'\n";
const char prompt[] = "enseash %";
const char Exit[] = "exit";
const char byebye[] = "Bye Bye...\n";
const char *separators = " ";
int result;
int tempsmilli;
struct timespec tp;

int main(){
	char cmd[SIZE_BUF];
	int cmdlength;
	char signal[SIZE_BUF] = "enseash4[sign:";
	int status;
	char signfils[SIZE_BUF];
	int i = 0;
	
	write(STDOUT_FILENO, bienvenue, sizeof(bienvenue));
	write(STDOUT_FILENO, prompt, sizeof(prompt));
	
	while(1){
		
		char *strToken;
		char *cmddup;
		char tempsDebut[SIZE_BUF] = "enseash[exit:0||"; 
		char temps[SIZE_BUF];
		char tempsFin[] = " ms] %";
		
		cmdlength=read(STDIN_FILENO, cmd, SIZE_BUF);
		cmd[cmdlength-1] = '\0';
	
		
		if (strncmp(cmd,Exit, sizeof(Exit))==0 || cmdlength == 0){
			write(STDOUT_FILENO, byebye, sizeof(byebye));
			break;
		}
				
		pid_t pid = fork();
			
		if(pid==0){
			
			result = clock_gettime(CLOCK_REALTIME, &tp);
			if(result != 0){
				exit(EXIT_FAILURE);
			}
			else{
				int a1 = tp.tv_sec;
				int a2 = tp.tv_nsec;
				char *list[20]; //creation d'une liste de caractère 
				cmddup = strdup(cmd); //duplique la commande afin de pouvoir utilisr strtok qui modifie celle-ci sans toucher à la commande principale
				
				for (int j = 0; ; j++, cmddup = NULL) {
					strToken = strtok(cmddup, " "); //enregistre le premier mot de la commande
					if (strToken == NULL)
					break;
				list[j] = strToken; //on ajoute les mots de la commande à chaque indice de la liste
				i+=1;
				}	
				free(cmddup); //permet de libérrer l'allocation de mémoire
				list[i] = (char *)NULL; //le dernier mot de la liste correspond au dernier arguments de la fonction execvp
				
				execvp(list[0],&list[0]); //permet d'executer la commande des differents mots à la suite
				
				result = clock_gettime(CLOCK_REALTIME,&tp);
				int b1 = tp.tv_sec;
				int b2 = tp.tv_nsec;
				tempsmilli = ( b1 - a1 )*MILLE + ( b2 - a2 )/MILLION;
				write(STDOUT_FILENO, prompt, sizeof(prompt));
				exit(EXIT_FAILURE);
			}
		}
		else{
			wait(&status);
			if(WIFEXITED(status)){
				sprintf(temps,"%d", tempsmilli);
				write(STDOUT_FILENO,strcat(strcat(tempsDebut,temps),tempsFin),strlen(strcat(strcat(tempsDebut,temps),tempsFin)));
			}
			else if(WIFSIGNALED(status)){
				signfils[0] = (char)WTERMSIG(status);
				write(STDOUT_FILENO,strcat(strcat(signal, &signfils[0]),strcat(strcat("||",temps),tempsFin)),strlen(signal));
			}		
		}
	}
	exit(EXIT_SUCCESS);
}
