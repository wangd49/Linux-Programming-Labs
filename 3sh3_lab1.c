#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

//SIG ALRM HANDLER EVERY 2 SECONDS
void alarm_handler(int signo){
	if(signo== SIGALRM){
		printf("Alarm\n");
	}
}

//SIGINT HANDLER CTRL C
void Ctrl_C_Handler(int signo){
	if(signo == SIGINT){
		printf("CTRL+C pressed!\n");
	}
}

//SIGTSTP HANDLER CTRL Z
void Ctrl_Z_Handler(int signo){
	if(signo == SIGTSTP){
		printf("CTRL+Z pressed!\n");
		exit (0);
	}
}

int main(void){
	if(signal(SIGALRM, alarm_handler)==SIG_ERR){
		printf("failed to register alarm handler.");
		exit(1);
	}

	if(signal(SIGINT, Ctrl_C_Handler)==SIG_ERR){
		printf("failed to register CTRL C handler.");
		exit(1);
	}

	if(signal(SIGTSTP, Ctrl_Z_Handler)==SIG_ERR){
		printf("failed to register CTRL Z handler.");
		exit(1);
	}

	
	while(1) { 
		alarm(2);
		sleep(2); //alarm every 2 seconds. Sleep 2 seconds to prevent layering
	}
}