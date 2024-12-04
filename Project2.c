#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Fungsi untuk membersihkan tanda baca dan mengubah kata menjadi huruf kecil
void bersihkan_kata(char *kata) {
    int j = 0;
    for (int i = 0; kata[i] != '\0'; i++) {
        if (isalnum(kata[i]) || kata[i] == '\'') { 
            kata[j++] = tolower(kata[i]);         
        }
    }
    kata[j] = '\0';
}

// Fungsi untuk memeriksa apakah kata sudah ada di daftar kata unik
int kata_unik(char *kata, char daftar[][100], int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        if (strcmp(kata, daftar[i]) == 0) {
            return 0; // Kata sudah ada
        }
    }
    return 1; // Kata belum ada
}

// Fungsi utama untuk memproses file lirik
void proses_lirik() {
    FILE *input = fopen("lirik.txt", "r");
    FILE *output = fopen("kosa-kata.word", "w");

    if (input == NULL || output == NULL) {
        printf("Error membuka file.\n");
        return;
    }

    char baris[200];
    char daftar_kata[1000][100];
    int jumlah_kata = 0;

    // Baca judul lagu dari baris pertama
    if (fgets(baris, sizeof(baris), input)) {
        fprintf(output, "%s", baris); 
    }

    // Proses setiap baris dari lirik
    while (fgets(baris, sizeof(baris), input)) {
        char *kata = strtok(baris, " \n\r\t");
        while (kata != NULL) {
            bersihkan_kata(kata);
            if (strlen(kata) > 0 && kata_unik(kata, daftar_kata, jumlah_kata)) {
                strcpy(daftar_kata[jumlah_kata++], kata); 
            }
            kata = strtok(NULL, " \n\r\t"); // Ambil kata berikutnya
        }
    }

    // Tulis kata-kata unik ke file output
    for (int i = 0; i < jumlah_kata; i++) {
        fprintf(output, "%s=\n", daftar_kata[i]);
    }

    fclose(input);
    fclose(output);
    printf("Kosa kata berhasil dibuat di file 'kosa-kata.word'\n");
}

int main() {
    proses_lirik();
    return 0;
}
