#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if(pid < 0){
        fprintf(stderr, "Error when subprocess was created\n");
	exit(1);
    } else if(pid == 0){
	execlp("cat", "cat", "file.txt", NULL);
	fprintf(stderr, "Error processing command cat\n");
        printf("pid val : %d\n", pid);
	exit(1);
    } else {
	int status;
        printf("this will print out before our subprocess is done running\n");
        waitpid(pid, &status, 0);
	if(WIFEXITED(status)){
		printf("Subprocess has completed the command \"cat\"\n");
	} else{
		printf("Subprocess has completed with error\n");
	}
        printf("this will print out only after our subprocess is done running\n");
    }
}
