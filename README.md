# SoalShiftSISOP20_modul2_C03
Kelompok C03:
* _Irsyadhani Dwi Shubhi (0511184000022)_
* _Reihan Nanda Ramadhan (05111840000132)_

----------------------------------------------------------------
## Soal
* [Soal 1](#soal-1)
* [Soal 2](#soal-2)
* [Soal 3](#soal-3)
----------------------------------------------------------------

### Soal 1
   _**Soal:**_\
1. Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut:
* Program menerima 4 argumen berupa:
  * Detik: 0-59 atau * (any value)
  * Menit: 0-59 atau * (any value)
  * Jam: 0-23 atau * (any value)
  * Path file .sh
* Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
sesuai
* Program hanya menerima 1 config cron
* Program berjalan di background (daemon)
* Tidak boleh menggunakan fungsi system()

Contoh: ./program \* 34 7 /home/somi/test.sh
Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap
detik pada jam 07:34.
> Source Code: [Sumber](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal1/soal1.c)
### Soal 2
   _**Soal:**_\
### Soal 3

_**Soal 3:**_\

```sh
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(){
    pid_t child = fork(); //membuat fork (program)
    int status; //membuat integer status   
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
                    pid_t child_team = fork(); //membuat fork (program)
                    struct stat st; //status untuk setiap proses
                    stat(dir->d_name, &st); //membuat variabel untuk mengambil nama direktori
                    
                    if(child_team < 0){
                        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
                    }
            
                    if(child_team == 0){
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
                                }else{
                                    //Soal 3d
                                    while((dir = readdir(directory)) != NULL){ //mengecek directory
                                        pid_t child_indomie = fork(); //membuat fork (program)
                                        int kasus; //membuat integer kasus
                                
                                        if(child_indomie == 0){
                                            char target_file[1000]; //string target file yang dituju
                                            FILE *target; //membuat pointer file target
                                            sprintf(target_file, "/home/irsyad/modul2/indomie/%s/coba1.txt", dir->d_name); //print variabel di direktori name
                                            target = fopen(target_file,"w"); // open target_file untuk di-write
                                            fclose(target);//menutup pointer target 
                                        }else{
                                            while((wait(&kasus)) > 0); //agar bisa urut 
                                            sleep(3); //menjalankan program setelah 3 detik
                                            char target_file[1000]; //membuat string array jumlah 100
                                            FILE *target; //membuat file pointer target
                                            sprintf(target_file, "/home/irsyad/modul2/indomie/%s/coba2.txt", dir->d_name); //print variabel di direktori name
                                            target = fopen(target_file,"w");// open target_file untuk di-write
                                            fclose(target);//menutup pointer target 
                                            exit(0); //keluar semua program
                                        }
                                    }
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
```
