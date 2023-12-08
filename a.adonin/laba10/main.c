#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char* argv[]){
	pid_t pid;
	int process_status;

	pid = fork();

	if(pid < 0){
	    fprintf(stderr, "Error when subprocess was created\n");
	    exit(1);
	} else if(pid == 0){
	    execvp(argv[1], &argv[1]);
	    perror("Error starting command");
	    exit(1);
	} else{
	    waitpid(pid, &process_status, 0);
	    if(WIFEXITED(process_status)){
	        printf("Subprocess exit code: %d\n", WEXITSTATUS(process_status));
	    } else{
	        printf("Subprocess completed incorrect\n");
	    }
	}
	return 0;
}