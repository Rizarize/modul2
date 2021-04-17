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
#include <time.h>
#include <dirent.h>

//a)Buat folder musyik,pyoto,fylm
void mkfolder(int * status, pid_t child_id, char *folder[]) {
    if((child_id = fork()) == 0) {
        char *argv[] = {"mkdir",folder[0], folder[1], folder[2], NULL};
        execv("/bin/mkdir", argv);
    }
    while(wait(status) > 0);
}
//b)Download musik,foto,film
void download(int * status, pid_t child_id, char link[], char dlzip[]) {
    if((child_id = fork()) == 0) {
        char *argv[] = {"wget","--no-check-certificate",link,"-O",dlzip, NULL};
        execv("/bin/wget", argv);
    }
    while(wait(status) > 0);
}
//c)Extract zip
void unboxing(int * status, pid_t child_id,char dlzip[]) {
    if((child_id = fork()) == 0) {
        char *argv[] = {"unzip", dlzip, NULL};
        execv("/bin/unzip", argv);
    }
    while(wait(status) > 0);
}
//d)Move file
void move(int * status, pid_t child_id, char exzip[], char folder[]) {
    DIR * dp;
    struct dirent * ep;
    dp = opendir(exzip);
    if (dp != NULL) {
        while ((ep = readdir(dp))){
        	if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0){
    			if((child_id = fork()) == 0){
    				char path[100];
    				strcpy(path, exzip);
        			strcat(path, "/");
					strcat(path, ep->d_name);
					
					char *argv[] = {"mv", path, folder, NULL};
        			execv("/bin/mv", argv);
				}
				while(wait(status) > 0);    		
			}     	
		}
        (void) closedir (dp);
    }
	else perror ("Couldn't open the directory"); 
}
//f)Lopyu stevany
void boxing(int * status,pid_t child_id, char *folder[], char *lopyu[]) {
    if((child_id = fork()) == 0) {
        char *argv[] = {"zip", "-rmvq", lopyu[0], folder[0], folder[1], folder[2], NULL};
        execv("/bin/zip", argv);
    }
    while(wait(status) > 0);
}
void hapus(int * status, pid_t child_id, char * exzip[]) {
    if((child_id = fork()) == 0) {
        char *argv[] = {"rm", "-rf", exzip[0], exzip[1], exzip[2], NULL};
        execv("/bin/rm", argv);
    }
    while(wait(status) > 0);
}
int main() {
  time_t t ;
    struct tm *tmp ;
    time( &t );
      
    tmp = localtime( &t );
    //e)h-6jam
   //if((tmp->tm_mday == 9) && (tmp->tm_mon == 4)&& (tmp->tm_hour == 16 )&& (tmp->tm_min == 22) && (tmp->tm_sec == 0)){
    	int status,i;
    	pid_t child_id;
		char *folder[] = {"Musyik", "Pyoto", "Fylm"};
		char *link[] = {
						"https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", //MUSIK
						"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", //FOTO
						"https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"  // FILM
						};
		char *dlzip[] = {"Musik_for_Stevany.zip", "Foto_for_Stevany.zip", "Film_for_Stevany.zip"};
		char *exzip[] = {"MUSIK", "FOTO", "FILM"};
		
		//a)Buat folder musyik,pyoto,fylm
		mkfolder(&status, child_id, folder);
		//b)Download musik,foto,film
		for(i=0;i<3;i++){
			download(&status, child_id, link[i],dlzip[i]);
		}
		//c)Unzipping download file
		for(i=0;i<3;i++)
			unboxing(&status,child_id,dlzip[i]);
		//d)Memindahkan file
	    	for(i=0;i<3;i++){
    		move(&status,child_id,exzip[i],folder[i]);
		}
		
	//persiapanhbd }
	//f)lopyu stevany
	// else if((tmp->tm_mday == 9) && (tmp->tm_mon == 4)&& (tmp->tm_hour == 22 )&& (tmp->tm_min == 22) && (tmp->tm_sec == 0)){
		// int status;
		// pid_t child_id;
		// char *folder[] = {"Musyik", "Pyoto", "Fylm"};
		char *lopyu[]  = {"Lopyu_Stevany.zip"};
		// char *exzip[] = {"MUSIK", "FOTO", "FILM"};
		
		boxing(&status,child_id,folder,lopyu);
		hapus(&status,child_id,exzip);

  
}
