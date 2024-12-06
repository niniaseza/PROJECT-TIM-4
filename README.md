# PROJECT-TIM-4
UAS PRAKTIKUM PEMOGRAMAN

Anggota Kelompok 4:
1. Rozatun Nabila     2408107010010
2. Niswatul 'Azimah   2408107010003
3. Azira Kania        2408107010025
4. Illiza Khairamisa  2408107010017
5. Putroe Fatimah Azzahra 2408107010002
6. Andre Alfaridzi 2408107010011
7. Mahda Annisa 2408107010036
   
***PENJELASAN PROGRAM PROBLEM 1***<br>
   Program ini merupakan program Sistem Peminjaman Alat Laboratorium, dimana dalam program ini pengguna dapat memilih untuk masuk sebagai admin atau user,kemudian jika pengguna masuk sebagai admin maka pengguna dapat mengubah, menambah, menghapus, dan melihat alat lab dalam sistem, jika pengguna masuk sebagai user maka pengguna dapat melihat, meminjam, mengembalikan, melihat riwayat pinjam, alat lab dalam sistem.<br>
   
   Program ini dirancang untuk mengelola inventaris alat laboratorium, menyediakan fitur pendaftaran dan login bagi pengguna. Data yang disimpan mencakup informasi tentang alat laboratorium, termasuk ID alat, nama, model, dan jumlah yang tersedia. Struktur data utama terdiri dari dua bagian: User untuk informasi pengguna dan Alat untuk data alat.<br>
File user.txt menyimpan semua informasi pengguna, sedangkan alat.txt menyimpan rincian alat laboratorium. Pengguna dapat melakukan pendaftaran dan login untuk mengakses sistem. Alur kerja program meliputi pendaftaran pengguna, login, pengelolaan data alat, dan peminjaman alat.<br>
File user.txt menyimpan semua informasi pengguna, sedangkan alat.txt menyimpan rincian alat laboratorium. Pengguna dapat melakukan pendaftaran dan login untuk mengakses sistem. Alur kerja program meliputi pendaftaran pengguna, login, pengelolaan data alat, dan peminjaman alat.<br>

***PENJELASAN PROGRAM BONUS***<br>
   Program ini merupakan program yang kami susun untuk membantu Pengguna memahami kosakata per lirik pada sebuah lagu, jadi saat lirik lagu di input nantinya output akan menghasilkan kosakata yang tidak berulang dari potongan lagu yang diinput, berurut sesuai lirik lagunya, setiap kata akan menjadi huruf kecil, dan tanda baca akan dihapus kecuali tanda penghubung seperti weren't, i'm dan sejenisnya. <br>

Program ini memiliki dua fungsi tambahan yang membantu sebelum fungsi utama. Fungsi *bersihkan_kata(char kata) menghapus tanda baca (kecuali apostrof) dan mengubah huruf besar menjadi huruf kecil. Fungsi *kata_unik(char kata, char daftar[][100], int jumlah) memeriksa apakah sebuah kata sudah ada dalam daftar. Jika belum, kata tersebut dianggap unik.

Di fungsi utama proses_lirik, program membuka file lirik.txt yang berisi lirik lagu dan file output kosa-kata.word untuk menulis daftar kata unik. Jika ada masalah saat membuka file, program akan menampilkan pesan error. Program membaca judul lagu dari baris pertama dan menuliskannya ke file output. Kemudian, setiap baris lirik dibaca dan dipisahkan menjadi kata-kata.

Setiap kata dibersihkan dan dicek apakah sudah ada di daftar. Jika belum, kata tersebut ditambahkan. Setelah semua lirik diproses, program menulis kata-kata unik ke file output dengan format kata=. Terakhir, file ditutup, dan fungsi main hanya memanggil fungsi proses_lirik untuk menjalankan semua proses.
