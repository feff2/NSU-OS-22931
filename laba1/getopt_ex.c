#include <stdlib.h>
#include <stdio.h>
#define _POSIX_SOURCE
#include <unistd.h>
#include <limits.h>
#include <sys/resource.h>
#include <getopt.h>

extern char **environ;


int main(int argc, char *argv[]){
    char options[ ] = "ispucdvU:C:V:";  /* valid options */
    char working_dir[PATH_MAX];
    int c;
	long ulim, core_size;
    struct rlimit rlim;
	char* sym;
	char var_name[100], var_value[100];
	int str_ind = 0;
    while ((c = getopt(argc, argv, options)) != EOF) {
        switch (c) {
            case 'i':
                printf("REAL UID : %d\n", getuid());
                printf("EFF. UID : %d\n", geteuid());
                printf("REAL GID : %d\n", getgid());
                printf("EFF. GID : %d\n", getegid());
                break;
            case 's':
                if (setpgid(0, 0) == 0){
					printf("successfully set process as group leader\n");
				}else{
					fprintf(stderr, "ERROR: setpgid returns -1\n");
				}
                break;
            case 'p':
                printf("process id : %d\n", getpid());
                printf("parent id  : %d\n", getppid());
                printf("group id   : %d\n", getpgrp());
                break;
			case 'u':
                if (getrlimit(RLIMIT_FSIZE, &rlim) == -1){
					fprintf(stderr, "ERROR: getrlimit returns -1\n");
				}
                printf("FSIZE Soft Lim. : %ju\n", (uintmax_t)rlim.rlim_cur);
                printf("FSIZE Hard Lim. : %ju\n", (uintmax_t)rlim.rlim_max);
                printf("\n");
                break;
			case 'U':
				ulim = atol(optarg);
				if (ulim <= 0){
					fprintf(stderr, "Invalid ULIM value\n");
				} else {
					rlim.rlim_cur = ulim;
					rlim.rlim_max = ulim;
					if (setrlimit(RLIMIT_FSIZE, &rlim) == -1){
						fprintf(stderr, "ERROR: setrlimit returns -1\n");
					}
				}
				break;
            case 'c':
				if (getrlimit(RLIMIT_CORE, &rlim) == -1){
					fprintf(stderr, "ERROR: getrlimit returns -1\n");
				} else {
					printf("Core Soft Lim. : %d\n", rlim.rlim_cur);
					printf("Core Hard Lim. : %d\n", rlim.rlim_max);
					printf("\n");
				}
				break;
			case 'C':
                core_size = atol(optarg);
				if (core_size <= 0){
					fprintf(stderr, "Invalid ULIM value\n");
				} else {
					rlim.rlim_cur = core_size;
					rlim.rlim_max = core_size;
					if (setrlimit(RLIMIT_CORE, &rlim) == -1){
						fprintf(stderr, "ERROR: setrlimit returns -1\n");
					}
				}
				break;
            case 'd':
                if (getcwd(working_dir, sizeof(working_dir)) != NULL) {
                    printf("Current working dir: %s\n", working_dir);
                } else {
                    fprintf(stderr, "ERROR: getcwd() returns NULL");
                }
                break;
            case 'v':
                for (int i=0; environ[i]!=NULL; i++) {
                    printf("%d: %s\n", i, environ[i]);
                }
               	break;
			case 'V':
                printf("V get %s\n", optarg);
				putenv(optarg);
//				sym = optarg;
//				while ((char)*sym != '='){
//					var_name[str_ind++] = (char)*sym;
//					sym++;
//				}
//				var_name[str_ind] = '\0';
//				sym++;
//				str_ind = 0;
//				while ((char)*sym != '\0'){
//					var_value[str_ind++] = (char)*sym;
//					sym++;
//				}
//				var_value[str_ind] = '\0';
//				printf("1 %s \n2 %s \n", &var_name, &var_value);
				break;
			case '?':
                printf("UNKNOWN ARGUMENT\n");
				break;
        }
    }
    return 0;
}