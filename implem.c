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
#include <string.h>
#define Size 50


int main() {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
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
    // Tulis program kalian di sini
	pid_t pid1, pid2,pid3,pid4,pid5,pid6;
  int status, status2;
  char first[20]= "09/04 - 16:22";
  char second[20] = "09/04 - 22:22";
	time_t t ;
	struct tm *tmp ;
	char MY_TIME[Size];
	time( &t );
	
	//localtime() uses the time pointed by t ,
	// to fill a tm structure with the
	// values that represent the
	// corresponding local time.
	
	tmp = localtime( &t );
	
	// using strftime to display time
	strftime(MY_TIME, sizeof(MY_TIME), "%d/%m - %H:%M", tmp);
	
  pid1 = fork();
  if(pid1 == 0){
    char *argv[] = {"wget","--no-check-certificate","-O", "Musik_for_Stevany.zip","https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", NULL};
    execv("/bin/wget", argv);
  }
  else{
		pid2 = fork();
		if(pid2 == 0){
			char *argv[] = {"wget","--no-check-certificate","-O", "Foto_for_Stevany.zip","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", NULL};
    		execv("/bin/wget", argv);
		}
		else {
		pid3 = fork();
		if(pid3 == 0){
			char *argv[] = {"wget","--no-check-certificate","-O", "Film_for_Stevany.zip","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", NULL};
    		execv("/bin/wget", argv);	
		}
		else{
		while ((wait(&status)) > 0);
		pid4 = fork();
		if(pid4 == 0){
			char *argv[] = {"unzip", "Musik_for_Stevany.zip", NULL};
        	execv("/bin/unzip", argv);
		}
		else {
		pid5 = fork();
		if(pid5 == 0){
			char *argv[] = {"unzip", "Film_for_Stevany.zip", NULL};
        	execv("/bin/unzip", argv);	
		}
		else {
		pid6 = fork();
		if(pid6 == 0){
			char *argv[] = {"unzip", "Foto_for_Stevany.zip", NULL};
        	execv("/bin/unzip", argv);	
		}
		else{}
		}
		}
		}
		}
    sleep(60);
  }
}
}
