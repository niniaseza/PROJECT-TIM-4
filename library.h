#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Struktur data untuk name
struct User {
    char Nama[50];
    char password[50];
};

// struktur data untuk alat lab
struct AlatLab {
    unsigned int idAlat;
    char namaAlat[50];
char merek[50];
    char model[50];
    unsigned int tahunProduksi;
    unsigned int jumlahUnit;
};

// struktur data untuk riwayat peminjaman
struct RiwayatPeminjaman {
    char Nama[50];
unsigned int idAlat;
    char namaAlat[50];
    unsigned int jumlah;
    char tanggal[50];
};

//Fungsi untuk membersihkan layar
void clearScreen();

// Fungsi untuk menyimpan data name ke dalam file name
void dataUserKeFile(const char *filename, struct User *name);

// Fungsi untuk membaca dan menampilkan data alat lab dari file.txt
void bacaDataAlatLab(const char *filename);

// Fungsi untuk login name
int loginUser(const char *filename, struct User *name);

