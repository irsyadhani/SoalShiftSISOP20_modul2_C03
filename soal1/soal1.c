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

int main(int argc, char *argv[]) {

  if (arg[1]>59 || arg[2]>59 || arg[3]>23){

    printf("Input argumen salah!");
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
 time_t rawtime;
 struct tm* timeinfo;
 time(&rawtime);
 timeinfo=localtime(&rawtime);

struct stat = {0};
if(err > 0){
 printf("ERROR INPUT\n");
 exit(EXIT_FAILURE);
}

if(stat(argv[4],&st) != 0){
 printf("ERROR PATH\n");
 exit(EXIT_FAILURE);
 } 
}

sleep(1);
  }
}
