# SoalShiftSISOP20_modul2_C03
Kelompok C03:
* _Irsyadhani Dwi Shubhi (0511184000022)_
* _Reihan Nanda Ramadhan (05111840000132)_

----------------------------------------------------------------
## Soal
* [Soal 1](#soal-1)
* [Soal 2](#soal-2)
* [Soal 3](#soal-3)
  * [Soal 3.a.](#soal-3a)
  * [Soal 3.b.](#soal-3b)
  * [Soal 3.c.](#soal-3c)
  * [Soal 3.d.](#soal-3d)
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

Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia
memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan
(multiprocessing).
> Source Code: [Sumber](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal3/soal3.c)

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
