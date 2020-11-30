#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <unistd.h>
#include  <sys/types.h>
 
// int  main () { //creates process
	
// 	if (fork() == 0)  
// 		printf("This is the child process\n");
// 	else  
// 		printf("I am the parent process\n");
	
// 	printf("Both parent and child reach here.\n");
	
// 	return  0;
//}

int  main(void){
	int      fd[2],gd[2],  nbytes; //fd[0]->reading, fd[1] writing
	pid_t    childpid, childpid2;	
	char     integer; //assign 1byte integer
	char     recieve_integer, recieve_integer2 ;
	char	 running_total=0; //keeps track of overall sum

	pipe(fd);
	pipe(gd);
	if (( childpid = fork()) ==  -1) { //checking for fork error
		perror("fork");
		exit (0);
	}
	
	if(childpid  == 0){ //child
		while(integer != -1){
			close(fd[0]); //close read
			printf("please enter 1 byte number: "); //user inputs 1 byte number
			scanf("%d", &integer); //reads 1 byte number
			write(fd[1], &integer , 1);//sends 1 byte number through the pipe
	
		}
		close(gd[1]);// set up to read result and print
		nbytes = read(gd[0],  &recieve_integer2 , sizeof(recieve_integer2));
		printf("Child Total: %d\n",recieve_integer2);
		exit(0);
	}

	else{ //parent
		while(recieve_integer!= -1){
			close(fd[1]); //close write 
			nbytes = read(fd[0],  &recieve_integer , sizeof(recieve_integer));
			running_total= running_total+recieve_integer;
			
		
		}
		running_total=running_total+1; // adds one to compensate for -1 running througuh the while
		printf("Sum: %d\n", running_total);//NOT NECESSARY
		close(gd[0]); //set up to send result
		write(gd[1],&running_total,sizeof(running_total));
	}

	//----------------------------------------------------------------------------\\
	
	return 0;
}