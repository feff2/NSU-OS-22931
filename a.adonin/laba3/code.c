#include <stdlib.h>
#include <stdio.h>
#define _POSIX_SOURCE
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char *argv[]){
    printf("REAL UID : %d\n", getuid());
    printf("EFF. UID : %d\n", geteuid());
	FILE* file_pointer = fopen("file.txt","r");
	if (file_pointer == NULL){
		perror("ERROR while opening FILE");
	} else {
		printf("FILE opened\n");
		if (fclose(file_pointer) == 0){
			printf("FILE successfully closed\n");
		} else {
			printf("ERROR while closing FILE\n");
		}
	}
	
	if (setuid(geteuid()) == 0){
		printf("UID set successfully\n");
		printf("REAL UID : %d\n", getuid());
		printf("EFF. UID : %d\n", geteuid());
	} else {
		perror("ERROR setuid");
	}
	
	file_pointer = fopen("file.txt","r");
	if (file_pointer == NULL){
		perror("ERROR while opening FILE");
	} else {
		printf("FILE opened\n");
		if (fclose(file_pointer) == 0){
			printf("FILE successfully closed\n");
		} else {
			printf("ERROR while closing FILE\n");
		}
	}
	
}