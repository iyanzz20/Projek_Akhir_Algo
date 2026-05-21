#include <iostream>
#include <cstring> //strcpy,strcmp,stricmp
#include <cstdlib> //system("color 0B") warna biru,system("pause"),system("cls")
#include <windows.h> //

using namespace std;

struct Film {
    char judul[100];
    char genre[50];
    int harga;
    char jam[20];

    Film *next;
};

struct Riwayat {
    char nama[100];
    char film[100];

    Riwayat *next;
    Riwayat *prev;
};

Film *headFilm = NULL;
Film *tailFilm = NULL;

Riwayat *headRiwayat = NULL;
Riwayat *tailRiwayat = NULL;

void loading() {

    cout << "\nLoading";

    for(int i = 0; i < 5; i++) {
        cout << ".";
        Sleep(300);
    }

    cout << endl;
}

void header() {

    cout << "\n";
    cout << "============================================================\n";
    cout << "                  BIOSKOP XXI INDONESIA                     \n";
    cout << "============================================================\n";
    cout << "            PESAN TIKET FILM FAVORITMU DISINI               \n";
    cout << "============================================================\n";
}

void tambahFilm(const char *judul,
                const char *genre,
                int harga,
                const char *jam) {

    Film *baru = new Film;

    strcpy(baru->judul, judul);
    strcpy(baru->genre, genre);
    baru->harga = harga;	
    strcpy(baru->jam, jam);

    baru->next = NULL;

    if(headFilm == NULL) {
        headFilm = tailFilm = baru;
    }
    else {
        tailFilm->next = baru;
        tailFilm = baru;
    }
}

void simpanFile() {

    FILE *fp;

    fp = fopen("film.txt", "w");

    Film *current = headFilm;

    while(current != NULL) {

        fprintf(fp,
                "%s#%s#%d#%s\n",
                current->judul,
                current->genre,
                current->harga,
                current->jam);

        current = current->next;
    }

    fclose(fp);

    cout << "\nData Film Berhasil Disimpan Ke File!\n";
}

void inputFilmBaru() {
    char judul[100], genre[50], jam[6];
    int harga;

    cin.ignore();
    cout << "Judul film    : "; cin.getline(judul, 100);
    cout << "Genre         : "; cin.getline(genre, 50);
    cout << "Harga (Rp)    : "; cin >> harga;
    cin.ignore();
    cout << "Jam tayang    : "; cin.getline(jam, 6);

    tambahFilm(judul, genre, harga, jam);
    cout << "\nFilm berhasil ditambahkan!\n";
}

void tampilFilm() {

    Film *current = headFilm;
    int no = 1;

    cout << "\n====================================================================================\n";
    cout << "| NO | JUDUL FILM                  | GENRE       | HARGA   | JAM TAYANG |\n";
    cout << "====================================================================================\n";

    while(current != NULL) {

        printf("| %-2d | %-28s | %-11s | %-7d | %-11s |\n",
               no,
               current->judul,
               current->genre,
               current->harga,
               current->jam);

        current = current->next;
        no++;
    }

    cout << "====================================================================================\n";
}

// Linear Search
void searchingFilm() {

    char cari[100];
    int ketemu = 0;

    cin.ignore();

    cout << "\nMasukkan Judul Film : ";
    cin.getline(cari, 100);

    Film *current = headFilm;

    while(current != NULL) {

        if(stricmp(current->judul, cari) == 0) {

            cout << "\n========================================\n";
            cout << "           FILM DITEMUKAN               \n";
            cout << "========================================\n";

            cout << "Judul : " << current->judul << endl;
            cout << "Genre : " << current->genre << endl;
            cout << "Harga : " << current->harga << endl;
            cout << "Jam   : " << current->jam << endl;

            ketemu = 1;
        }

        current = current->next;
    }

    if(ketemu == 0) {
        cout << "\nFilm Tidak Ditemukan!\n";
    }
}

void tukarFilm(Film *a, Film *b) {
    swap(a->harga, b->harga);

    char temp[100];

    strcpy(temp, a->judul);
    strcpy(a->judul, b->judul);
    strcpy(b->judul, temp);

    strcpy(temp, a->genre);
    strcpy(a->genre, b->genre);
    strcpy(b->genre, temp);

    strcpy(temp, a->jam);
    strcpy(a->jam, b->jam);
    strcpy(b->jam, temp);
}

//bubble sort
void sortingJam() {
    if(headFilm == NULL) return;

    int tukar;
    Film *ptr;
    Film *batas = NULL;

    do {
        tukar = 0;
        ptr = headFilm;

        while(ptr->next != batas) {
            if(strcmp(ptr->jam, ptr->next->jam) > 0) {
                tukarFilm(ptr, ptr->next);
                tukar = 1;
            }

            ptr = ptr->next;
        }

        batas = ptr;

    } while(tukar);

    cout << "\nFilm Berhasil Diurutkan Berdasarkan Jam Tayang!\n";
}

void tambahRiwayat(const char *nama,
                   const char *film) {

    Riwayat *baru = new Riwayat;

    strcpy(baru->nama, nama);
    strcpy(baru->film, film);

    baru->next = NULL;
    baru->prev = NULL;

    if(headRiwayat == NULL) {
        headRiwayat = tailRiwayat = baru;
    }
    else {

        tailRiwayat->next = baru;
        baru->prev = tailRiwayat;
        tailRiwayat = baru;
    }
}

void pesanTiket() {

    char nama[100];
    char film[100];

    tampilFilm();

    cin.ignore();

    cout << "\nMasukkan Nama Pemesan : ";
    cin.getline(nama, 100);

    cout << "Masukkan Judul Film   : ";
    cin.getline(film, 100);

    tambahRiwayat(nama, film);

    loading();

    cout << "\n";
    cout << "========================================\n";
    cout << "             TIKET BIOSKOP              \n";
    cout << "========================================\n";
    cout << "Nama Pemesan : " << nama << endl;
    cout << "Film         : " << film << endl;
    cout << "Status       : BERHASIL\n";
    cout << "========================================\n";
}

void tampilRiwayat() {

    Riwayat *current = headRiwayat;
    int no = 1;

    cout << "\n====================================================\n";
    cout << "              RIWAYAT PEMESANAN                     \n";
    cout << "====================================================\n";

    while(current != NULL) {

        cout << "\nRiwayat " << no << endl;
        cout << "Nama : " << current->nama << endl;
        cout << "Film : " << current->film << endl;

        current = current->next;
        no++;
    }
}

int loadDataFilm() {
    FILE *fp = fopen("film.txt", "r");

    if(fp == NULL) {
        return 0;
    }

    char judul[100], genre[50], jam[20];
    int harga;
    int jumlah = 0;

    while(fscanf(fp, " %99[^#]#%49[^#]#%d#%19[^\n]\n",
                 judul, genre, &harga, jam) != EOF) {

        tambahFilm(judul, genre, harga, jam);
        jumlah++;
    }

    fclose(fp);
    return jumlah;
}


int main() {

    int pilih;

    system("color 0B");
    //ini buat nambahin doang kalo diapus gpp
    tambahFilm("Spider-Man Brand New Day", "Action", 60000, "20.00");
    tambahFilm("Danur The Last Chapter", "Horror", 45000, "21.00");
    tambahFilm("The Odyssey", "Adventure", 55000, "18.30");
    tambahFilm("Backrooms", "Horror", 50000, "19.00");
    tambahFilm("Crocodile Tears", "Drama", 40000, "17.00");
    loadDataFilm();

    do {

        header();

        cout << "\n";
        cout << "1. Tampilkan Daftar Film\n";
        cout << "2. Input Film Baru\n";
        cout << "3. Cari Film (Linear Search)\n";
        cout << "4. Urutan Jam Film (Bubble Sort)\n";
        cout << "5. Pesan Tiket\n";
        cout << "6. Tampilkan Riwayat\n";
        cout << "7. Simpan Data Ke File\n";
        cout << "0. Keluar\n";
        cout << "---------------------------------------------------------------\n";
        cout << "\nPilih Menu : ";
        cin >> pilih;

        switch(pilih) {

            case 1:
                tampilFilm();
                break;
			
			case 2:
				inputFilmBaru();
				break;
				
            case 3:
                searchingFilm();
                break;

            case 4:
                sortingJam();
                tampilFilm();
                break;

            case 5:
                pesanTiket();
                break;

            case 6:
                tampilRiwayat();
                break;

            case 7:
                simpanFile();
                break;

            case 0:
                cout << "\n========================================\n";
                cout << "        TERIMA KASIH TELAH DATANG       \n";
                cout << "========================================\n";
                break;

            default:
                cout << "\nMenu Tidak Tersedia!\n";
        }

        cout << endl;
        system("pause");
        system("cls");

    } while(pilih != 0);

    
    return 0;
}
