# SoalShiftSISOP20_modul2_C03
Kelompok C03:
* _Irsyadhani Dwi Shubhi (0511184000022)_
* _Reihan Nanda Ramadhan (05111840000132)_

----------------------------------------------------------------
## Soal
* [Soal 1](#soal-1-(Program-C-Menyerupai-Crontab))
* [Soal 2](#soal-2-(Program-Kiwa))
  * [Soal 2.a.](#soal-2a)
  * [Soal 2.b.](#soal-2b)
  * [Soal 2.c.](#soal-2c)
  * [Soal 2.d.](#soal-2d)
  * [Soal 2.e.](#soal-2e)
* [Soal 3](#soal-3-(Multiprocessing-Jaya))
  * [Soal 3.a.](#soal-3a)
  * [Soal 3.b.](#soal-3b)
  * [Soal 3.c.](#soal-3c)
  * [Soal 3.d.](#soal-3d)
----------------------------------------------------------------

# Soal 1 (Program C Menyerupai Crontab)
   _**Soal:**_
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
> Source Code: [Soal 1](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal1/soal1.c)

#

_**Penyelesaian:**_

* Pertama, membuat code untuk menerima input 4 argumen dimana 3 argumen pertama menerima detik, menit, dan jam
```c 
 len = strlen(argv[1]);
 if(len > 2){
    printf("ERROR INPUT!");
    exit(EXIT_FAILURE);
  }
  else if(strcmp(argv[1],"*") != 0){
    if(atoi(argv[1]) > 60){
      printf("ERROR INPUT!");
      exit(EXIT_FAILURE);
    }
  }

  len = strlen(argv[2]);
  if(len > 2){
    printf("ERROR INPUT!");
    exit(EXIT_FAILURE);
    }
    else if(strcmp(argv[1],"*") != 0){
      if(atoi(argv[2]) > 60){
     printf("ERROR INPUT!");
     exit(EXIT_FAILURE);
      }
    }
  len=strlen(argv[3]);
  if(len > 2){
    printf("ERROR INPUT!");
    exit(EXIT_FAILURE);
  }
  else if(strcmp(argv[1],"*") != 0){
    if(atoi(argv[3]) > 24){
    printf("ERROR INPUT!");
    exit(EXIT_FAILURE);
    }
  }
 ```

* Kedua, membuat error argument. Disini menggunakan flag dimana flagnya adalah err. Jadi, setiap pengecekan 4 argumen yang dideklarasikan di atas akan di cek. Apabila salah input, flag akan bertambah lalu masuk ke dalam if untuk pengecekan error. Hal ini berlaku juga untuk argumen yang ke 4.
```c
  struct stat st = {0};
  if(err > 0){
    printf("ERROR INPUT!\n");
    exit(EXIT_FAILURE);
  }
  if(stat(argv[4],&st) != 0){
    printf("ERROR PATH!\n");
    exit(EXIT_FAILURE);
  }
```
* Ketiga, membuat struct untuk menerima format jam,menit, dan detik.
```c
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
```

* Keempat, membuat fungsi ```exec``` untuk mengecek argumen 1 sampai 3 apakah yang diinputkan merupakan "*" atau angka dan mengecek apakah argumen ke-4 itu ```.sh``` atau bukan.

```c
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
```

* Kelima, semua code diatas dimasukkan ke dalam ```Daemon``` agar bisa berjalan di background. Untuk code ```Daemon``` sesuai dengan template yang ada di dalam ```Modul 2```. Tidak lupa membuat ```int main(int argc, char *argv[])``` untuk menerima argumen integer dan char. Lalu, menambahkan library ```#include <wait.h>``` , ```#include <ctype.h>``` , dan ```#include <time.h>``` . Berikut ```Daemon``` yang sudah disiapkan untuk menjalankan code diatas.

```c
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
  ***
  }
}
```

* Keenam, membuat sebuah program ```.sh``` untuk mencoba program ```Daemon``` yang sudah dibuat. Programnya akan dinamakan ```testing.sh``` berisikan ```date``` .

![alt text](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal1/Praktikum%202/testing.png "Program testing.sh")

* Ketujuh, program ```testing.sh``` dijalankan menggunakan program ```Daemon``` yang kita buat.

![alt text](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal1/Praktikum%202/sukses.png "Hasil eksekusi program Daemon")


# 

# Soal 2 (Program Kiwa)
  
_**Soal 2:**_

Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia
merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat
sebuah program.
> Source Code: [Soal 2](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal2/soal2.c)

#

#### Soal 2.a:
Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat
sebuah program C yang per 30 detik membuat sebuah folder dengan nama
timestamp **[YYYY-mm-dd_HH:ii:ss]**.

_**Penyelesaian:**_

Pertama kita membuat fungsi manipulasi waktu yaitu ```time_t```, kita membuat passing waktu lokal yang sesuai menggunakaan ```localtime```, fungsi ```strftime``` untuk format waktu dan disimpan di string  *_currenttime_* , membuat ```fork``` dan ```exec``` lalu membuat fungsi ```mkdir``` untuk membuat direktori atau folder, dengan selang interval 30 detik maka menggunakan fungsi ```sleep(30)```.
```c
while(1){
        char currenttime[50];
        time_t now = time(NULL);
        struct tm* local = localtime(&now);
        strftime(currenttime, 30, "%Y-%m-%d_%H:%M:%S", local);

        pid_t child;
        child = fork();

        if(child < 0){
            exit(0);
        }

        if(child == 0){
            char *argv[] = {"mkdir", currenttime, NULL};
            execv("/bin/mkdir", argv);
        }
    sleep(30);
}
```
Hasil eksekusi program:
![alt text](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal2/gambar/soal2a.png "Hasil Soal 2a")

#

#### Soal 2.b:
Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari
**https://picsum.photos/**, dimana tiap gambar di download setiap 5 detik. Tiap
gambar berbentuk persegi dengan ukuran _**(t%1000)+100**_ piksel dimana t adalah
detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp **[YYYY-
mm-dd_HH:ii:ss]**.

_**Penyelesaian:**_

Kita membuat fungsi ```chdir``` untuk merubah arah direktori ke *_currenttime_*, membuat perulangan ```for``` agar bisa mengunduh gambar sebanyak 20 gambar, membuat lagi ```strftime``` untuk menyimpan string waktu di *_currenttime2_*, menggunakan ```sprintf``` untuk mengisi string *_link_* dengan format *_(now2 % 1000) + 100_*, lalu kita membuat ```fork``` dan ```exec``` untuk membuat program ```wget``` yang berfungsi untuk mendownload gambar sesuai dengan format waktu yang ditentukan, memberikan ```sleep(5)``` untuk selang interval waktu mengunduh gambar.
```c
chdir(currenttime);
int i;

for(i = 0; i < 20; i++){
    char currenttime2[50];
    time_t now2 = time(NULL);
    struct tm* local2 = localtime(&now2);
    strftime(currenttime2, 30, "%Y-%m-%d_%H:%M:%S", local2);

    char link[50];
    sprintf(link, "https://picsum.photos/%ld", (now2 % 1000) + 100);

    pid_t child3;
    child3 = fork();

    if(child3 < 0){
       exit(0);
    }

    if(child3 == 0){
       char *argv[] = {"wget", link, "-O", currenttime2, "-o", "/dev/null", NULL}; 
       execv("/usr/bin/wget", argv);
    }
    sleep(5);
}
```
Hasil eksekusi program:
![alt text](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal2/gambar/soal2b.png "Hasil Soal 2b")

#

#### Soal 2.c:
Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan
folder akan di delete(sehingga hanya menyisakan .zip).

_**Penyelesaian:**_

Kita mengubah direktori ke folder parent awal menggunakan ```chdir```, ```strcpy``` digunakan untuk menyalin nama folder *_currenttime_* lalu ```strcat``` untuk menambahkan ekstensi *_.zip_* di *_currenttime3_*. Selanjutnya membuat program ```fork``` dan ```exec``` agar folder bisa dimasukkan di zip dengan cara menggunakan fungsi ```zip``` dengan nama *_currenttime3_* kemudian kita membuat program baru lagi untuk menghapus folder yang sudah di zip tadi dengan cara ```rm -r``` yang berdasarkan dari *_currenttime_*.
```c
    int status2;
    while(wait(&status2) > 0);
    chdir("..");
    char currenttime3[50];
    strcpy(currenttime3, currenttime);
    strcat(currenttime3, ".zip");

    pid_t child4;
    child4 = fork();

    if(child4 < 0){
        exit(0);
    }

    if(child4 == 0){
        char *argv[] = {"zip", "-r", currenttime3, currenttime, NULL};
        execv("/usr/bin/zip", argv);
    }

    int status3;
    while(wait(&status3) > 0);

    pid_t child5;
    child5 = fork();

    if(child5 < 0){
        exit(0);
    }

    if(child5 == 0){
        char *argv[] = {"rm", "-r", currenttime, NULL};
        execv("/bin/rm", argv);
    }
 }
```
Hasil eksekusi program:
![alt text](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal2/gambar/soal2c.png "Hasil Soal 2c")

#

#### Soal 2.d:
Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-
generate sebuah program "killer" **yang siap di run(executable)** untuk
menterminasi semua operasi program tersebut. Setelah di run, program yang
menterminasi ini lalu akan mendelete dirinya sendiri.

_**Penyelesaian:**_

Kita membuat pointer kill untuk nantinya membuat file *_killer.sh_* dengan fungsi ```fopen``` yang didalamnya akan di isi dengan bash untuk membunuh program, dengan perintah ```fprintf```, selanjutnya kita membuat program ```fork``` dan ```exec```, menggunakan fungsi ```chmod u+x``` untuk mengganti hak akses file ke user untuk mengeksekusi killer.sh. 
```c
int main(int argc, char* argv[]){
   ...
   int status;
   FILE* kill;

   kill = fopen("killer.sh", "w");
   fprintf(kill, "#!/bin/bash\nkill %d\nkill %d\necho \'killed program.\'\nrm \"$0\"", getpid() + 2, getpid() + 3);
   fclose(kill);

   pid_t child;
   child = fork();

   if(child < 0){
       exit(0);
   }

   if(child = 0){
       char *argv[] = {"chmod", "u+x", "killer.sh", NULL};
       execv("/bin/chmod", argv);
   }
}
```
Hasil eksekusi program:
![alt text](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal2/gambar/soal2d.png "Hasil Soal 2d")

#

#### Soal 2.e:
Kiwa menambahkan bahwa program **utama** bisa dirun dalam dua mode, yaitu
MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan
dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen
-b. Ketika dijalankan dalam MODE_A, program utama akan langsung
menghentikan semua operasinya ketika program killer dijalankan. Untuk
MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi
membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua
folder terisi gambar, terzip lalu di delete).

_**Penyelesaian:**_

Kita mengecek jika argumen char ```argc``` tidak sama dengan 2 atau inputan argumen yang bukan di passing ```argv``` sama dengan a dan b maka muncul tulisan *_Invalid argumen, Input -a  or -b_* , selanjutnya memakai ```prctl``` sebagai system call linux, ```PR_SET_PDEATHSIG``` dan ```SIGHUP``` keduanya untuk menge*_set_* signal death dan memberhentikan program.
```c
if(argc != 2 || (argv[1][1] != 'a' && argv[1][1] != 'b')){
    printf("Invalid argumen, Input -a  or -b\n");
    exit(0); //keluar terminal
}
...
if(argv[1][1] == 'a') prctl(PR_SET_PDEATHSIG, SIGHUP);
```
Hasil eksekusi program:
![alt text](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal2/gambar/soal2e-a.png "Hasil Soal 2e dengan mode -a")
![alt text](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal2/gambar/soal2e-a(result).png "Hasil Soal 2e mode -a dengan melihatkan proses PID")
![alt text](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal2/gambar/soal2e-b.png "Hasil Soal 2e dengan mode -b")
![alt text](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal2/gambar/soal2e-b(result).png "Hasil Soal 2e mode -b dengan melihatkan proses PID")

#

_**Kendala:**_
Dalam interval setelah 30 detik membuat folder sudah berhasil, akan tetapi pada saat membuat folder selanjutnya lagi dibuat dalam interval 1,5 menit yang seharusnya tidak ada di perintah soal.

#


# Soal 3 (Multiprocessing Jaya)

_**Soal 3:**_

Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia
memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan
(multiprocessing).
> Source Code: [Soal 3](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal3/soal3.c)

#

#### Soal 3.a:
Program buatan jaya harus bisa membuat dua direktori di
**“/home/[USER]/modul2/”**. Direktori yang pertama diberi nama **“indomie”**, lalu
lima detik kemudian membuat direktori yang kedua bernama **“sedaap”**.

_**Penyelesaian:**_

Kita menggunakan fungsi ```EXIT_FAILURE``` untuk fungsi program berhenti jika program gagal jalan, menggunakan fungsi ```mkdir``` untuk membuat folder serta argumen ```execv``` dan ```bin/mkdir```, disini kita membuat 2 folder yaitu folder yang bernama **"indomie"** dan **“sedaap”**, fungsi ```sleep(5)``` membuat folder **"sedaap"** setelah 5 detik.
```c
if (child == 0){
   pid_t child_mi = fork();
        
   if (child_mi < 0){
      exit(EXIT_FAILURE);
      }
        
   if (child_mi == 0){
      char *argv[] = {"mkdir", "-p", "/home/irsyad/modul2/indomie", NULL};
      execv("/bin/mkdir", argv);
   }else{
      while ((wait(&status)) > 0);
      sleep(5); //program dengan interval waktu 5 detik
      char *argv[] = {"mkdir", "-p", "/home/irsyad/modul2/sedaap", NULL};
      execv("/bin/mkdir", argv);
   }
}
```
Hasil eksekusi program:
![alt text](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal3/gambar/soal3a.png "Hasil Soal 3a")

#

#### Soal 3.b:
Kemudian program tersebut harus meng-ekstrak file **jpg.zip** di direktori
**“/home/[USER]/modul2/”**. Setelah tugas sebelumnya selesai, ternyata tidak
hanya itu tugasnya.

_**Penyelesaian:**_

Kita membuat ```while ((wait(&status)) > 0);``` untuk melanjutkan urutan programmnya, membuat ```fork``` untuk membuat program baru, ```EXIT_FAILURE``` untuk fungsi program berhenti jika program gagal jalan, fungsi ```unzip``` untuk mengekstrak file **jpg.zip** serta argumen ```execv``` dan ```/usr/bin/unzip```.
```c
while ((wait(&status)) > 0);
pid_t child_unzip = fork();
        
if (child_unzip < 0){
   exit(EXIT_FAILURE);
}

if (child_unzip == 0){
   char* argv[] = {"unzip", "/home/irsyad/modul2/jpg.zip", NULL};
   execv("/usr/bin/unzip", argv);
}
```
Hasil eksekusi program:
![alt text](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal3/gambar/soal3b.png "Hasil Soal 3b")

#

#### Soal 3.c:
Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di
dalam direktori **“home/[USER]/modul2/jpg/”)** harus dipindahkan sesuai dengan
pengelompokan, semua file harus dipindahkan ke
**“/home/[USER]/modul2/sedaap/”** dan semua direktori harus dipindahkan ke
**“/home/[USER]/modul2/indomie/”**.

_**Penyelesaian:**_

Kita membuat ```while ((wait(&status)) > 0);``` untuk melanjutkan urutan programmnya, fungsi ```chdir``` untuk mengubah direktori ke **jpg**, membuat pointer ```DIR```, fungsi ```opendir``` untuk membuka direktori handle, fungsi ```struct``` untuk membuat status di tiap proses, ```if(directory)``` mengecek directory, fungsi ```while``` untuk membuat perulangan sampai nilainya ```NULL```, membuat ```fork``` lagi untuk membuat program, ```dir->d_name``` untuk membuat variabel untuk mengambil nama direktori, ```EXIT_FAILURE``` untuk fungsi program berhenti jika program gagal jalan, ```char``` membuat string name, ```sprintf``` untuk print direktori ke ```dir->d_name```, fungsi ```S_ISDIR``` untuk mengecek apakah sebuah direktori, fungsi ```strcmp``` untuk perbandingan string untuk string . dan .. , jika terdeteksi folder akan dipindahkan ke folder **"indomie"** dengan menggunakan fungsi ```mv``` dan argumen ```/bin/mv```, selain itu (terdeteksi file) maka dipindahkan ke folder **"sedaap"**
```c
while ((wait(&status)) > 0);
chdir("/home/irsyad/modul2/jpg/");
DIR *directory;
directory = opendir(".");
struct dirent *dir;

if(directory){
   while((dir = readdir(directory)) != NULL){
      pid_t child_team = fork();
      struct stat st;
      stat(dir->d_name, &st);
                    
      if(child_team < 0){
         exit(EXIT_FAILURE);
      }
            
      if(child_team == 0){
         char path_file[1000];
         sprintf(path_file, "/home/irsyad/modul2/jpg/%s", dir->d_name);
                    
         if(S_ISDIR(st.st_mode)){
            if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0);
                    
            else{
               pid_t child_txt = fork();
                                
               if(child_txt < 0){
                  exit(EXIT_FAILURE);
               }
                                
               if(child_txt == 0){
                  char* argv[] = {"mv", path_file, "/home/irsyad/modul2/indomie/", NULL};
                  execv("/bin/mv", argv);
               }else{ 
                  char* argv[] = {"mv", path_file, "/home/irsyad/modul2/sedaap/", NULL};
                  execv("/bin/mv", argv); //argumen memindah folder 
               }
```
Hasil eksekusi program:
![alt text](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal3/gambar/soal3c(indomie).png "Hasil Soal 3c(indomie)")
![alt text](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal3/gambar/soal3c(sedaap).png "Hasil Soal 3c(sedaap)")

#

#### Soal 3.d:
Untuk setiap direktori yang dipindahkan ke **“/home/[USER]/modul2/indomie/”**
harus membuat dua file kosong. File yang pertama diberi nama **“coba1.txt”**, lalu
3 detik kemudian membuat file bernama **“coba2.txt”**.

_**Penyelesaian:**_

Kita mengecek direktori ```(dir = readdir(directory)) != NULL```, membuat program baru dan kasus untuk melanjutkan programnya, membuat string untuk print dengan fungsi ```sprintf```, membuat pointer ```FILE``` untuk mengarahkan direktorinya, fungsi ```fopen``` untuk membuat file dan fungsi  ```w``` untuk wrie-only yang hanya bisa membuat file jika belum ada, ```fclose``` untuk menutup ```fopen``` tadi, disini kita membuat 2 file yaitu **coba1.txt** dan menggunakan fungsi ```sleep(3)``` untuk membuat file selanjutnya **coba2,txt**, ```exit(0)``` untuk menutup program, dan fungsi ```closedir``` untuk menutup semua direktori
```c
while((dir = readdir(directory)) != NULL){
   pid_t child_indomie = fork();
   int kasus;
                                
   if(child_indomie == 0){
      char target_file[1000];
      FILE *target;
      sprintf(target_file, "/home/irsyad/modul2/indomie/%s/coba1.txt", dir->d_name);
      target = fopen(target_file,"w");
      fclose(target); 
   }else{
      while((wait(&kasus)) > 0); 
      sleep(3);
      char target_file[1000];
      FILE *target;
      sprintf(target_file, "/home/irsyad/modul2/indomie/%s/coba2.txt", dir->d_name);
      target = fopen(target_file,"w");
      fclose(target);
      exit(0);
   }
}
closedir(directory);
```
Hasil eksekusi program:
![alt text](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal3/gambar/soal3d(744).png "Hasil Soal 3d(744)")
![alt text](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal3/gambar/soal3d(3577).png "Hasil Soal 3d(3577)")

#

_**Kendala:**_
tidak bisa memasukkan file coba1.txt dan coba2.txt ke seluruh folder, hanya bisa memasukkan secara acak ke berbagai folder
