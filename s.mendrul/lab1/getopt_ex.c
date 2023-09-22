#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ucred.h>
#include <sys/resource.h>
#include <ulimit.h>
#include <ucred.h>
#include <unistd.h>


void  main(int argc, char *argv[])
  {
      int c;
      char options[ ] = "U:uispdvV:cC:";  /* valid options */
      extern char *optarg;
      extern int optind, optopt;

      extern char **environ;
      long long ulim;
      char *cwd;
     pid_t pid, pgid, ppid;
     ucred_t *cred;
     uid_t euid, ruid;
     gid_t egid, rgid;

     struct rlimit core_lim;

     printf("argc equals %d\n", argc);
     while ((c = getopt(argc, argv, options)) != EOF) {
      switch (c) {
          case 'i':
              pid = getpid();
              cred = ucred_get(pid);
              euid = ucred_geteuid(cred);
              ruid = ucred_getruid(cred);
              egid = ucred_getegid(cred);
              rgid = ucred_getrgid(cred);
              printf("Effective user id = %d\nReal user id = %d\nEffective group id = %d\nReal group id = %d\n",
                     euid, ruid, egid, rgid);
              ucred_free(cred);
              break;
           case 's':
                pid = getpid();
                if (setpgid(pid, pid) == -1) {
                    perror("Failed to set group id");
                }
                break;
            case 'p':
                pid = getpid();
                pgid = getpgrp();
                ppid = getppid();
                printf(
                    "Process id = %d\nParent process id = %d\nProcess group id = %d\n",
                    pid,
                    ppid,
                    pgid
                );
                break;
            case 'u':
                ulim = ulimit(UL_GETFSIZE); 
                if (ulim == -1) {
                    perror("Failed to get ulimit"); 
                    continue;
                }
                printf("ulimit = %ld\n", ulim * 512);
                break;
            case 'U':
                ulim = atol(optarg); 
                if (ulim % 512 != 0) {
                    fprintf(stderr, "New ulimit value is not divisible by 512\n");
                    continue;
                }
                ulim = ulimit(UL_SETFSIZE, ulim / 512);
                if (ulim == -1) {
                    perror("Failed to set ulimit"); 
                    continue;
                }
                break;
            case 'v':
                for (int i = 0; environ[i]; i++) {
                    printf("%s\n", environ[i]);
                }
                break;
            case 'V':
                if (putenv(optarg) != 0) {
                    perror("Failed to put env variable");
                }
                break;
            case 'c':
                if (getrlimit(RLIMIT_CORE, &core_lim) != 0)
                    perror("Failed to get core limit");
                printf("Hard core limit = %lu\nSoft core limit = %lu\n", core_lim.rlim_max, core_lim.rlim_cur);
                break;
            case 'C':
                if (getrlimit(RLIMIT_CORE, &core_lim) != 0)
                    perror("Failed to get core limit");
                core_lim.rlim_cur = atol(optarg); 
                if (setrlimit(RLIMIT_CORE, &core_lim) != 0)
                    perror("Failed to set core limit");
                break;
      }
      
     }
     
}
