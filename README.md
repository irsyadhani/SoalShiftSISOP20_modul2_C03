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
> Source Code: [Sumber]
### Soal 2
   _**Soal:**_\
### Soal 3

_**Soal 3:**_\
Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia
memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan
(multiprocessing).
> Source Code: [Sumber](https://github.com/irsyadhani22/SoalShiftSISOP20_modul2_C03/blob/master/soal3/soal3.c)

#### Soal 3.a.
_**Soal 3.a.:**_\
a.Program buatan jaya harus bisa membuat dua direktori di
“/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu
lima detik kemudian membuat direktori yang kedua bernama “sedaap”.
