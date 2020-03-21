#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>
#include <ctype.h>

int main(int argc, char *argv[]) {

  int err=0, len = strlen(argv[1]);

  if(len > 2){
    err++;
  }
  else if(strcmp(argv[1],"*") != 0){
    if(atoi(argv[1]) > 60 || atoi(argv[1]) < 0){
      err++;
    }
  }

  len = strlen(argv[2]);
  if(len > 2){
      err++;
    }
    else if(strcmp(argv[1],"*") != 0){
      if(atoi(argv[2]) > 60 || atoi(argv[2]) < 0){
        err++;
      }
    }
  len=strlen(argv[3]);
  if(len > 2){
    err++;
  }
  else if(strcmp(argv[1],"*") != 0){
    if(atoi(argv[3]) > 24 || atoi(argv[3]) < 0){
      err++;
    }
  }

  struct stat st = {0};
  if(err > 0){
    printf("ERROR INPUT!\n");
    exit(EXIT_FAILURE);
  }
  if(stat(argv[4],&st) != 0){
    printf("ERROR PATH!\n");
    exit(EXIT_FAILURE);
  }

  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }


  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  } 

  
  
     close(STDIN_FILENO);
     close(STDOUT_FILENO);
     close(STDERR_FILENO);


  while (1) {
    pid_t run;
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    char *program[] = {"bash",argv[4],NULL};

    if(strcmp(argv[1],"*") == 0){
      if(strcmp(argv[2],"*") == 0){

        if(strcmp(argv[3],"*") == 0){
          while(1){
            if(run = fork() == 0){
              execvp("/bin/bash",program);
            }
            sleep(1);
            time(&rawtime);
            timeinfo = localtime (&rawtime);
          }
        }

        else{
          while (1) {
            if(atoi(argv[3]) == timeinfo->tm_hour){
              if(run = fork() == 0){
                execvp("/bin/bash",program);
              }
            }
            sleep(1);
            time(&rawtime);
            timeinfo = localtime (&rawtime);
          }
        }
      }

      else{
        if(strcmp(argv[3],"*") == 0){
          while (1) {
            if(atoi(argv[2]) == timeinfo->tm_min){
              if(run = fork() == 0){
                execvp("/bin/bash", program);
              }
            }
            sleep(1);
            time(&rawtime);
            timeinfo = localtime ( &rawtime );
          }
        }

        else{
          while (1) {
            if(atoi(argv[3]) == timeinfo->tm_hour && atoi(argv[2]) == timeinfo->tm_min){
              if(run = fork() == 0){
                execvp("/bin/bash", program);
              }
            }
            sleep(1);
            time(&rawtime);
            timeinfo = localtime ( &rawtime );
          }
        }
      }
    }



    else {


      if(strcmp(argv[2],"*") == 0){
        if(strcmp(argv[3],"*") == 0){
          while (1) {
            if(atoi(argv[1]) == timeinfo->tm_sec){
              if(run = fork() == 0){
                execvp("/bin/bash", program);
              }
            }
            sleep(1);
            time(&rawtime);
            timeinfo = localtime ( &rawtime );
          }
        }

        else{
          while (1) {
            if(atoi(argv[1]) == timeinfo->tm_sec && atoi(argv[3]) == timeinfo->tm_hour){
              if(run = fork() == 0){
                execvp("/bin/bash", program);
              }
            }
            sleep(1);
            time(&rawtime);
            timeinfo = localtime ( &rawtime );
          }
        }
      }


      else{

        if(strcmp(argv[3],"*") == 0){
          while(1){
            if(atoi(argv[2]) == timeinfo->tm_min && atoi(argv[1]) == timeinfo->tm_sec){
              if(run = fork() == 0){
                execvp("/bin/bash", program);
              }
            }
            sleep(1);
            time(&rawtime);
            timeinfo = localtime ( &rawtime );
          }
        }

        else{
          while (1) {
            if(atoi(argv[3]) == timeinfo->tm_hour && atoi(argv[2]) == timeinfo->tm_min && atoi(argv[1]) == timeinfo->tm_sec){
              if(run = fork() == 0){
                execvp("/bin/bash", program);
              }
            }
            sleep(1);
            time(&rawtime);
            timeinfo = localtime ( &rawtime );
          }
        }
      }
    }
    break;
  }
}
