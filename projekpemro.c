#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

int main(int argc, char *argv[]) {
    struct User currentUser;
    const char *alatLabFile = "alat_lab.txt";
    const char *riwayatFile = "riwayat_peminjaman.txt";
    const char *adminFile = "data_admin.txt";
    const char *userFile = "data_user.txt";

    // Cek jumlah argumen
    if (argc < 2) {
        printf("Cara Penggunaan:\n");
        printf("  Registrasi: register <role> <Nama> <password>\n");
        printf("  Login     : login <role> <Nama> <password>\n");
        return 1;
    }

    const char *action = argv[1];

    // Handle registrasi
    if (strcmp(action, "register") == 0) {
        if (argc != 5) {
            printf("Cara Penggunaan: %s register <role> <Nama> <password>\n", argv[0]);
            return 1;
        }

        const char *role = argv[2];
        const char *Nama = argv[3];
        const char *password = argv[4];
        struct User newUser;

        strcpy(newUser.Nama, Nama);
        strcpy(newUser.password, password);

        if (strcmp(role, "admin") == 0) {
            dataUserKeFile(adminFile, &newUser);
            printf("Admin '%s' berhasil didaftarkan.\n", Nama);
        } else if (strcmp(role, "user") == 0) {
            dataUserKeFile(userFile, &newUser);
            printf("User '%s' berhasil didaftarkan.\n", Nama);
        } else {
            printf("Role tidak valid. Gunakan 'admin' atau 'user'.\n");
        }

    // Handle login
    } else if (strcmp(action, "login") == 0) {
        if (argc != 5) {
            printf("Cara Penggunaan: %s login <role> <Nama> <password>\n", argv[0]);
            return 1;
        }

        const char *role = argv[2];
        const char *Nama = argv[3];
        const char *password = argv[4];
        int loginSuccess;

        strcpy(currentUser.Nama, Nama);
        strcpy(currentUser.password, password);

        if (strcmp(role, "admin") == 0) {
            loginSuccess = loginUser(adminFile, &currentUser);
            if (loginSuccess) {
                printf("Admin '%s' berhasil masuk.\n", Nama);
                menuAdmin(alatLabFile);
            } else {
                printf("Gagal masuk sebagai Admin.\n");
            }
        } else if (strcmp(role, "user") == 0) {
            loginSuccess = loginUser(userFile, &currentUser);
            if (loginSuccess) {
                printf("User '%s' berhasil masuk.\n", Nama);
                menuUser(alatLabFile, riwayatFile, &currentUser);
            } else {
                printf("Gagal masuk sebagai User.\n");
            }
        } else {
            printf("Role tidak valid. Gunakan 'admin' atau 'user'.\n");
        }
    } else {
        printf("Perintah tidak valid. Gunakan 'register' atau 'login'.\n");
    }

    return 0;
}

