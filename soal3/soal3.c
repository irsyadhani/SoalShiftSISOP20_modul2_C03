#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(){
    pid_t child = fork();
    int status;    
    if (child < 0){
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    }
    
    if (child == 0){
        pid_t child_mi = fork(); //membuat fork (program)
        //Soal 3a
        if (child_mi < 0){
            exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
        }
        
        if (child_mi == 0){
            char *argv[] = {"mkdir", "-p", "/home/irsyad/modul2/indomie", NULL}; //membuat folder indomie
            execv("/bin/mkdir", argv); //argumen untuk membuat folder indomie
        }else{
            while ((wait(&status)) > 0); // menggunakan fungsi tersebut agar bisa urut menjalankan prgram
            sleep(5); //program dengan interval waktu 5 detik
            char *argv[] = {"mkdir", "-p", "/home/irsyad/modul2/sedaap", NULL}; //membuat folder sedaap
            execv("/bin/mkdir", argv); //argumen untuk membuat folder indomie
        }
    }else{
        while ((wait(&status)) > 0); // menggunakan fungsi tersebut agar bisa urut menjalankan prgram
        pid_t child_unzip = fork(); //membuat fork (program)
        //Soal 3b
        if (child_unzip < 0){
            exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
        }

        if (child_unzip == 0){
            char* argv[] = {"unzip", "/home/irsyad/modul2/jpg.zip", NULL}; //file jpg.zip di ekstrak 
            execv("/usr/bin/unzip", argv); //argumen untuk mengekstrak zip
        }else{
            //Soal 3c
            while ((wait(&status)) > 0); // menggunakan fungsi tersebut agar bisa urut menjalankan prgram
            chdir("/home/irsyad/modul2/jpg/"); //mengubah path folder
            DIR *directory; // membuat pointer utk mengecek direktori
            directory = opendir("."); //membuka direktori handle
            struct dirent *dir; //pointer untuk ke nama folder
            if(directory){ //mengecek directory
                
while((dir = readdir(directory)) != NULL){ //mengecek directory ada
                    pid_t child_tim = fork(); //membuat fork (program)
                    struct stat st; //status untuk setiap proses
                    stat(dir->d_name, &st); //membuat variabel untuk mengambil nama direktori
                    
                    if(child_tim < 0){
                        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
                    }
            
                    if(child_tim == 0){
                        char path_file[1000]; //membuat string array sebanyak 1000
                        sprintf(path_file, "/home/irsyad/modul2/jpg/%s", dir->d_name); //print direktori
                    
                        if(S_ISDIR(st.st_mode)){ // mengecek apakah sebuah direktori
                            if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0); //perbandingan string untuk string . dan ..
                    
                            else{
                                pid_t child_txt = fork(); //membuat fork (program)
                                
                                if(child_txt < 0){
                                    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
                                }
                                
                                if(child_txt == 0){
                                    char* argv[] = {"mv", path_file, "/home/irsyad/modul2/indomie/", NULL}; //memindahkan path direktori
                                    execv("/bin/mv", argv); // argumen pindah path direktori
                                
                                }
                            }
                        }else{ //pengecualian untuk memindahkan file
                            char* argv[] = {"mv", path_file, "/home/irsyad/modul2/sedaap/", NULL}; //selain sesuai perintah diatas akan dipindah ke folder sedaap
                            execv("/bin/mv", argv); //argumen memindah folder 
                        }
                    }
                }
                closedir(directory); //menutup directory
            }
        }
    }
}
