#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<syslog.h>
#include<string.h>
#include<time.h>
#include<wait.h>
#include<sys/prctl.h>
#include<stdbool.h>

void program_daemon(){
	pid_t pid;
    pid_t sid;
    pid = fork();

    if(pid < 0) {
        exit(EXIT_FAILURE);
    }

    if(pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
   
    if(sid < 0){
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main(int argc, char* argv[]){

    if(argc != 2 || (argv[1][1] != 'a' && argv[1][1] != 'b')){ 
        
        printf("Invalid argumen, Input -a  or -b\n");
        exit(0);
    }
    
    int status;
    FILE* kill;
    
    kill = fopen("killer.sh", "w");
    fprintf(kill, "#!/bin/bash\nkill %d\nkill %d\necho \'Killed program.\'\nrm \"$0\"", getpid() + 2, getpid() + 3);
    fclose(kill);
    
    pid_t child;
    child = fork();
    
    if(child < 0){
        exit(0);
    }

    if(child = 0){
        char *argv[] = {"chmod", "u+x", "killer.sh", NULL};
        execv("/bin/chmod", argv);
    }

    while(wait(&status) > 0);

    program_daemon();

    while(1){
        
        char currenttime[50];
        time_t now = time(NULL);
        struct tm* local = localtime(&now);
        strftime(currenttime, 30, "%Y-%m-%d_%H:%M:%S", local);

        pid_t child;
        child = fork();

        if(child < 0){
            exit(0);
        }

        if(child == 0){
            char *argv[] = {"mkdir", currenttime, NULL};
            execv("/bin/mkdir", argv);
        }

        int status1;
        while(wait(&status1) > 0);

        pid_t child2;
        child2 = fork();
        
        if(child2 < 0){
            exit(0);
        }
        
        if(child2 == 0){
            if(argv[1][1] == 'a') prctl(PR_SET_PDEATHSIG, SIGHUP); 

            chdir(currenttime);
    	    int i;

            for(i = 0; i < 20; i++){
                char currenttime2[50];
                time_t now2 = time(NULL);
                struct tm* local2 = localtime(&now2);
                strftime(currenttime2, 30, "%Y-%m-%d_%H:%M:%S", local2);

                char link[50];
                sprintf(link, "https://picsum.photos/%ld", (now2 % 1000) + 100);

                pid_t child3;
                child3 = fork();

                if(child3 < 0){
                    exit(0);
                }

                if(child3 == 0){
                    char *argv[] = {"wget", link, "-O", currenttime2, "-o", "/dev/null", NULL}; 
                    execv("/usr/bin/wget", argv);
                }
                sleep(5);
            }

            int status2;

            while(wait(&status2) > 0);
            chdir("..");
            char currenttime3[50];
            strcpy(currenttime3, currenttime);
            strcat(currenttime3, ".zip");

            pid_t child4;
            child4 = fork();
            
            if(child4 < 0){
                exit(0);
            }

            if(child4 == 0){
                char *argv[] = {"zip", "-r", currenttime3, currenttime, NULL};
                execv("/usr/bin/zip", argv);
            }

            int status3;
            while(wait(&status3) > 0);

            pid_t child5;
            child5 = fork();

	        if(child5 < 0){
                exit(0);
            }

            if(child5 == 0){
                char *argv[] = {"rm", "-r", currenttime, NULL};
            	execv("/bin/rm", argv);
            }
        }
        sleep(30);
    }
}