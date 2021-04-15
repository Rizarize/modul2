#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#define Size 50


int main(){
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
  }
}
