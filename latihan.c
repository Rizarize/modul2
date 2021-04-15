#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
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


  while (1) {
    // Tulis program kalian di sini
	pid_t child_id;
	int status;
	
	child_id = fork();
	if(child_id == 0){
	char *argv[] = {"mkdir", "Musik_for_Stevany", NULL};
    	execv("/bin/mkdir", argv);
	}
	else{
	while((wait(&status) > 0));
	char *argv[] = {"mkdir", "Foto_for_Stevany", NULL};
        execv("/bin/mkdir", argv);
	}
    sleep(30);
  }
}
