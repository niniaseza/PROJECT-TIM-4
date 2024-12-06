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
