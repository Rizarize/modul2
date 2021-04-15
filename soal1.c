#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
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
	printf("tes");
    // Tulis program kalian di sini
	pid_t pid1, pid2;
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
	
if(strcmp(MY_TIME,first)==0){  
	
  pid1 = fork();
  if(pid1 == 0){
    char *argv1[] = {"wget","--no-check-certificate","-O", "Musik_for_Stevany.zip","https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", NULL};
    execv("/bin/wget", argv1);
    char *argv2[] = {"wget","--no-check-certificate","-O", "Foto_for_Stevany.zip","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", NULL};
    execv("/bin/wget", argv2);
    char *argv3[] = {"wget","--no-check-certificate","-O", "Film_for_Stevany.zip","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", NULL};
    execv("/bin/wget", argv3);
  }
  else{
    while ((wait(&status)) > 0);
    	char *argv1[] = {"unzip", "Musik_for_Stevany.zip", NULL};
        execv("/usr/bin/unzip", argv1);
        char *argv2[] = {"unzip", "Foto_for_Stevany.zip", NULL};
        execv("/usr/bin/unzip", argv2);
        char *argv3[] = {"unzip", "Film_for_Stevany.zip", NULL};
        execv("/usr/bin/unzip", argv3);
        
        pid2 = fork();
        if(pid2 == 0){
        char *argv1[] = {"mkdir", "Musyik", NULL};
    	execv("/bin/mkdir", argv1);
    	char *argv2[] = {"mkdir", "Fylm", NULL};
    	execv("/bin/mkdir", argv2);
    	char *argv3[] = {"mkdir", "Pyoto", NULL};
    	execv("/bin/mkdir", argv3);
    	}
    	else{
        while ((wait(&status2)) > 0);
        char *argv1[] = {"mv", "*.mp3","Musyik", NULL};
        execv("/bin/mv", argv1);
        char *argv2[] = {"mv", "*.mp4","Musyik", NULL};
        execv("/bin/mv", argv2);
        char *argv3[] = {"mv", "*.jpg","Musyik", NULL};
        execv("/bin/mv", argv3);
		}
    }
  }
else if(strcmp(MY_TIME, second)==0){
		char *argv[] = {"zip", "Lopyu_Stevany.zip","Musyik","Fylm","Pyoto", NULL};
        execv("/usr/bin/zip", argv);
	}
	sleep(10);
  }
}
