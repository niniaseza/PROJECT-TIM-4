#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Struktur data untuk name
struct User
{
    char Nama[50];
    char password[50];
};

// struktur data untuk alat lab
struct AlatLab {
    unsigned int idAlat;
    char namaAlat[50];
    char merek[50];
