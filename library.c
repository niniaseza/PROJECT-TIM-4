#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

//Fungsi untuk membersihkan layar
void clearScreen() {
    system("cls"); 
}

//Fungsi untuk menyimpan data pengguna ke dalam file txt
void dataUserKeFile(const char *filename, struct User *user) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Gagal membuka file untuk menyimpan pengguna");
        return;
    }
    fprintf(file, "%s %s\n", user->Nama, user->password);
    fclose(file);
    printf("Data pengguna berhasil disimpan.\n");
}


//Fungsi untuk membaca dan menampilkan data alat lab dari file
void bacaDataAlatLab(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Gagal membuka file: %s\n", filename);
        return;
    }

    struct AlatLab alat;
    char buffer[200];

    fgets(buffer, sizeof(buffer), file); // Membaca header
    printf("\n=== Daftar Alat Lab ===\n");
    printf("%-5s %-20s %-15s %-15s %-10s %-10s\n", "ID", "Nama Alat", "Merek", "Model", "Tahun", "Jumlah");
    printf("----------------------------------------------------------------------------\n");

    //membuat tabel alat lab
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%u, %49[^,], %49[^,], %49[^,], %u, %u", //format garis tabel
               &alat.idAlat, alat.namaAlat, alat.merek, alat.model, &alat.tahunProduksi, &alat.jumlahUnit);
        printf("%-5u %-20s %-15s %-15s %-10u %-10u\n",
               alat.idAlat, alat.namaAlat, alat.merek, alat.model, alat.tahunProduksi, alat.jumlahUnit);
    }

    fclose(file);
}

// fungsi login user
int loginUser(const char *filename, struct User *user) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Gagal membuka file untuk login");
        return 0;
    }

    char storedUsername[50];
    char storedPassword[50]; //menyimpan data password
    while (fscanf(file, "%s %s", storedUsername, storedPassword) != EOF) {
        if (strcmp(user->Nama, storedUsername) == 0 && strcmp(user->password, storedPassword) == 0) {
            fclose(file);
            return 1; // Login berhasil
        }
    }

    fclose(file);
    return 0; // Login gagal
}


// Fungsi untuk menyimpan riwayat peminjaman
void saveRiwayatPeminjaman(const char *filename, struct RiwayatPeminjaman *riwayat) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        printf("Gagal membuka file untuk menyimpan riwayat peminjaman.\n");
        exit(1);
    }
    fprintf(file, "%s,%u,%s,%u,%s\n", riwayat->Nama, riwayat->idAlat, riwayat->namaAlat, riwayat->jumlah, riwayat->tanggal);
    fclose(file);
}

//Fungsi untuk meminjam alat
void pinjamAlat(const char *alatLabFile, const char *riwayatFile, struct User *user) {
    FILE *file = fopen(alatLabFile, "r+");
    if (!file) {
        perror("Gagal membuka file alat lab");
        return;
    }

    //struktur alatlab dan riwayat peminjaman
    struct AlatLab alat;
    struct RiwayatPeminjaman riwayat;
    char buffer[200];
    unsigned int idAlat, jumlahPinjam;
    char tanggal[50];

    // Mencatat waktu sekarang dari laptoop dengan fungsi time
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(tanggal, sizeof(tanggal), "%Y-%m-%d %H:%M:%S", tm_info);

    printf("\nMasukkan ID alat yang ingin dipinjam: ");
    scanf("%u", &idAlat);
    printf("Masukkan jumlah alat yang ingin dipinjam: ");
    scanf("%u", &jumlahPinjam);

    // Menampilkan alat lab dan mengurangi stok
    rewind(file); // Kembali ke awal file
    fgets(buffer, sizeof(buffer), file); // Skip header
    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        perror("Gagal membuat file sementara");
        fclose(file);
        return;
    }

    //menyimpan data sementara
    fprintf(tempFile, "ID,Nama,Merek,Model,Tahun,Jumlah\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%u, %49[^,], %49[^,], %49[^,], %u, %u",
               &alat.idAlat, alat.namaAlat, alat.merek, alat.model, &alat.tahunProduksi, &alat.jumlahUnit);

    //data peminjaman
    if (alat.idAlat == idAlat) {
            if (alat.jumlahUnit >= jumlahPinjam) {
                alat.jumlahUnit -= jumlahPinjam;
                strcpy(riwayat.Nama, user->Nama);
                riwayat.idAlat = alat.idAlat;
                strcpy(riwayat.namaAlat, alat.namaAlat);
                riwayat.jumlah = jumlahPinjam;
                strcpy(riwayat.tanggal, tanggal);
                saveRiwayatPeminjaman(riwayatFile, &riwayat);
                printf("Peminjaman berhasil!\n");
            } else {
                printf("Stok alat tidak mencukupi!\n");
            }
        }
        fprintf(tempFile, "%u, %s, %s, %s, %u, %u\n", alat.idAlat, alat.namaAlat, alat.merek, alat.model, alat.tahunProduksi, alat.jumlahUnit);
    }

    fclose(file);
    fclose(tempFile);
    remove(alatLabFile); //menghapus unit yang dipinjam
    rename("temp.txt", alatLabFile);// write data unit baru
}

//Fungsi untuk melihat riwayat peminjaman
void lihatRiwayatPeminjaman(const char *riwayatFile, struct User *user) {
    FILE *file = fopen(riwayatFile, "r");
    if (!file) {
        printf("Gagal membuka file riwayat peminjaman.\n");
        return;
    }

    char buffer[200];
    struct RiwayatPeminjaman riwayat;// struktur file riwayatpeminjaman

    printf("\n=== Riwayat Peminjaman ===\n");//menampilkan riwayat pinjam
    printf("%-10s %-20s %-10s %-20s\n", "ID Alat", "Nama Alat", "Jumlah", "Tanggal");
    while (fgets(buffer, sizeof(buffer), file)) {
        if (sscanf(buffer, "%49[^,],%u,%49[^,],%u,%49[^\n]", riwayat.Nama, &riwayat.idAlat, riwayat.namaAlat, &riwayat.jumlah, riwayat.tanggal) == 5) {
            if (strcmp(riwayat.Nama, user->Nama) == 0) {
                printf("%-10u %-20s %-10u %-20s\n", riwayat.idAlat, riwayat.namaAlat, riwayat.jumlah, riwayat.tanggal);
            }
        }
    }

    fclose(file);
}

//Fungsi untuk mengembalikan alat
void kembalikanAlat(const char *alatLabFile, const char *riwayatFile, struct User *user) {
    FILE *fileRiwayat = fopen(riwayatFile, "r");
    if (!fileRiwayat) {
        printf("Gagal membuka file riwayat peminjaman.\n");
        return;
    }

    struct RiwayatPeminjaman riwayat;
    struct AlatLab alat;
    char buffer[200];
    unsigned int idAlat, jumlahKembali, totalDipinjam = 0, jumlahDikembalikan = 0;
    
    //input pengembalian alat lab
    printf("\nMasukkan ID alat yang ingin dikembalikan: ");
    scanf("%u", &idAlat);
    printf("Masukkan jumlah alat yang ingin dikembalikan: ");
    scanf("%u", &jumlahKembali);

    // Hitung total alat yang dipinjam
    FILE *tempRiwayat = fopen("temp_riwayat.txt", "w");
    if (!tempRiwayat) {
        printf("Gagal membuat file sementara.\n");
        fclose(fileRiwayat);
        return;
    }

    //looping riwayat alat lab
    int ditemukan = 0;
    while (fgets(buffer, sizeof(buffer), fileRiwayat)) {
        sscanf(buffer, "%49[^,],%u,%49[^,],%u,%49[^\n]",
               riwayat.Nama, &riwayat.idAlat, riwayat.namaAlat, &riwayat.jumlah, riwayat.tanggal);

        if (strcmp(riwayat.Nama, user->Nama) == 0 && riwayat.idAlat == idAlat) {
            totalDipinjam += riwayat.jumlah;
            ditemukan = 1;
        }
    }
    fclose(fileRiwayat);

    // Validasi jumlah yang dikembalikan
    if (!ditemukan) {
        printf("ID alat tidak ditemukan dalam riwayat peminjaman Anda.\n");
        fclose(tempRiwayat);
        return;
    }

    if (jumlahKembali > totalDipinjam) {
        printf("Jumlah yang dikembalikan melebihi jumlah yang dipinjam.\n");
        fclose(tempRiwayat);
        return;
    }

    // Buka ulang file riwayat untuk proses pengembalian
    fileRiwayat = fopen(riwayatFile, "r");
    while (fgets(buffer, sizeof(buffer), fileRiwayat)) {
        sscanf(buffer, "%49[^,],%u,%49[^,],%u,%49[^\n]",
               riwayat.Nama, &riwayat.idAlat, riwayat.namaAlat, &riwayat.jumlah, riwayat.tanggal);

        if (strcmp(riwayat.Nama, user->Nama) == 0 && riwayat.idAlat == idAlat) {
            if (jumlahDikembalikan < jumlahKembali) {
                unsigned int sisaKembali = jumlahKembali - jumlahDikembalikan;
                if (riwayat.jumlah <= sisaKembali) {
                    jumlahDikembalikan += riwayat.jumlah;
                    riwayat.jumlah = 0;
                } else {
                    riwayat.jumlah -= sisaKembali;
                    jumlahDikembalikan = jumlahKembali;
                }
            }
        }

        if (riwayat.jumlah > 0) {
            fprintf(tempRiwayat, "%s,%u,%s,%u,%s\n",
                    riwayat.Nama, riwayat.idAlat, riwayat.namaAlat, riwayat.jumlah, riwayat.tanggal);
        }
    }
    fclose(fileRiwayat);
    fclose(tempRiwayat);

    rename("temp_riwayat.txt", riwayatFile);

    // Update stok alat di file alatLabFile
    FILE *fileAlat = fopen(alatLabFile, "r+");
    if (!fileAlat) {
        printf("Gagal membuka file alat lab.\n");
        return;
    }

    FILE *tempAlat = fopen("temp_alat.txt", "w"); 
    if (!tempAlat) {
        printf("Gagal membuat file sementara.\n");
        fclose(fileAlat);
        return;
    }

    rewind(fileAlat);
    fgets(buffer, sizeof(buffer), fileAlat); // Skip header
    fprintf(tempAlat, "ID,Nama,Merek,Model,Tahun,Jumlah\n");
    while (fgets(buffer, sizeof(buffer), fileAlat)) {
        sscanf(buffer, "%u, %49[^,], %49[^,], %49[^,], %u, %u",
               &alat.idAlat, alat.namaAlat, alat.merek, alat.model, &alat.tahunProduksi, &alat.jumlahUnit);

        if (alat.idAlat == idAlat) {
            alat.jumlahUnit += jumlahKembali;
        }
        fprintf(tempAlat, "%u, %s, %s, %s, %u, %u\n",
                alat.idAlat, alat.namaAlat, alat.merek, alat.model, alat.tahunProduksi, alat.jumlahUnit);
    }

    fclose(fileAlat);
    fclose(tempAlat);
    remove(alatLabFile);
    rename("temp_alat.txt", alatLabFile);

    printf("Pengembalian alat berhasil.\n");
}

//Fungsi untuk menampilkan menu user
void menuUser(const char *alatLabFile, const char *riwayatFile, struct User *user) {
    int pilihan;

    do {
        printf("\n=== Menu User ===\n");
        printf("1. Lihat Daftar Alat Lab\n");
        printf("2. Pinjam Alat\n");
        printf("3. Lihat Riwayat Peminjaman\n");
        printf("4. Kembalikan Alat\n");
        printf("5. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
