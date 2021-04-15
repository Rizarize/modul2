#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t child_id;

  child_id = fork();

  if (child_id < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }

  if (child_id == 0) {
    // this is child
    char *argv[] = {"wget", "--no-check-certificate","-O","Musik_for_Stevany.zip","https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", NULL};
    execv("/bin/wget", argv);
  } else {
    // this is parent

    char *argv[] = {"wget","--no-check-certificate" ,"-O","Foto_for_Stevany.zip","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download" , NULL};
    execv("/bin/wget", argv);
  }
}
