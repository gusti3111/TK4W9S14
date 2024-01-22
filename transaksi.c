#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk menyimpan informasi buku
struct Book {
    char kode[20];
    char nama[50];
    char jenis[30];
    int harga;
};

// Fungsi untuk membaca data buku dari file
void read_books(struct Book *books, int *numBooks) {
    FILE *file = fopen("databuku.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %s %s %d", books[*numBooks].kode, books[*numBooks].nama,
                      books[*numBooks].jenis, &books[*numBooks].harga) != EOF) {
            (*numBooks)++;
        }
        fclose(file);
    }
}

// Fungsi untuk menulis data buku ke file
void write_books(struct Book *books, int numBooks) {
    FILE *file = fopen("databuku.txt", "w");
    for (int i = 0; i < numBooks; i++) {
        fprintf(file, "%s %s %s %d\n", books[i].kode, books[i].nama, books[i].jenis, books[i].harga);
    }
    fclose(file);
}

// Fungsi untuk menampilkan data buku
void view_books(struct Book *books, int numBooks) {
    printf("Data Buku:\n");
    for (int i = 0; i < numBooks; i++) {
        printf("%d. Kode: %s, Nama: %s, Jenis: %s, Harga: %d\n", i + 1, books[i].kode, books[i].nama,
               books[i].jenis, books[i].harga);
    }
}

// Fungsi untuk menampilkan data transaksi
void view_history() {
    FILE *file = fopen("history.txt", "r");
    if (file != NULL) {
        char history[1000];
        while (fgets(history, sizeof(history), file) != NULL) {
            printf("%s", history);
        }
        fclose(file);
    } else {
        printf("Belum ada transaksi.\n");
    }
}

// Fungsi untuk input data buku
void input_book(struct Book *books, int *numBooks) {
    printf("Masukkan Kode Buku: ");
    scanf("%s", books[*numBooks].kode);
    printf("Masukkan Nama Buku: ");
    scanf("%s", books[*numBooks].nama);
    printf("Masukkan Jenis Buku: ");
    scanf("%s", books[*numBooks].jenis);
    printf("Masukkan Harga Buku: ");
    scanf("%d", &books[*numBooks].harga);

    (*numBooks)++;
    write_books(books, *numBooks);
    printf("Data Buku berhasil ditambahkan.\n");
}

// Fungsi untuk menghapus data transaksi
void delete_history() {
    FILE *file = fopen("history.txt", "r");
    if (file != NULL) {
        char history[1000];
        int index, count = 0;
        while (fgets(history, sizeof(history), file) != NULL) {
            count++;
            printf("%d. %s", count, history);
        }
        fclose(file);

        if (count > 0) {
            printf("Masukkan index data yang ingin dihapus: ");
            scanf("%d", &index);

            if (index >= 1 && index <= count) {
                file = fopen("history.txt", "r");
                FILE *tempFile = fopen("temp.txt", "w");
                count = 0;

                while (fgets(history, sizeof(history), file) != NULL) {
                    count++;
                    if (count != index) {
                        fprintf(tempFile, "%s", history);
                    }
                }

                fclose(file);
                fclose(tempFile);

                remove("history.txt");
                rename("temp.txt", "history.txt");

                printf("Data Transaksi berhasil dihapus.\n");
            } else {
                printf("Index tidak valid.\n");
            }
        } else {
            printf("Tidak ada data transaksi.\n");
        }
    } else {
        printf("Tidak ada data transaksi.\n");
    }
}

// Fungsi utama
int main() {
    struct Book books[100];
    int numBooks = 0;

    read_books(books, &numBooks);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Input Data Buku\n");
        printf("2. View History Transaksi\n");
        printf("3. View Data Buku\n");
        printf("4. Delete History Transaksi\n");
        printf("5. Exit\n");

        int choice;
        printf("Pilih menu (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                input_book(books, &numBooks);
                break;
            case 2:
                view_history();
                break;
            case 3:
                view_books(books, numBooks);
                break;
            case 4:
                delete_history();
                break;
            case 5:
                write_books(books, numBooks);
                printf("Data Buku berhasil disimpan.\n");
                exit(0);
            default:
                printf("Pilihan tidak valid. Masukkan angka 1-5.\n");
        }
    }

    return 0;
}
