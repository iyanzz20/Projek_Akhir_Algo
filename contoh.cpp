#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <windows.h>

using namespace std;

struct Film{
    string judul;
    string genre;
    int harga;
    string jam;
    Film *next;
};

struct Riwayat{
    string nama;
    string film;
    int jumlah;
    Riwayat *next;
    Riwayat *prev;
};

Film *headFilm=NULL;
Film *tailFilm=NULL;
Riwayat *headRiwayat=NULL;
Riwayat *tailRiwayat=NULL;


void tambahFilm(string judul,
                string genre,
                int harga,
                string jam){
    Film *baru=new Film;
    baru->judul=judul;
    baru->genre=genre;
    baru->harga=harga;
    baru->jam=jam;
    baru->next=NULL;

    if(headFilm==NULL){
        headFilm=tailFilm=baru;
    }
    else{
        tailFilm->next=baru;
        tailFilm=baru;
    }
}

void simpanFile(){
    FILE *fp;
    fp=fopen("film.txt","w");
    Film *current=headFilm;
    while(current!=NULL){

        fprintf(fp,
                "%s#%s#%d#%s\n",
                current->judul.c_str(),
                current->genre.c_str(),
                current->harga,
                current->jam.c_str());
        current=current->next;
    }

    fclose(fp);
}

void tambahFilmBaru(){
    string judul,genre,jam;
    int harga;
    cin.ignore();
    bool ada;
    do{
        ada=false;
        cout<<"Masukkan Judul film Baru  : ";
        getline(cin,judul);
        Film *current=headFilm;
        while(current!=NULL){
            if(current->judul==judul){
                cout<<"\nJudul Film Sudah Ada!\n";
                ada=true;
            }
            current=current->next;
        }
    }while(ada);
    cout<<"Genre Film      : ";
    getline(cin,genre);

    cout<<"Harga (Rp)      : ";
    cin>>harga;
    cin.ignore();

    cout<<"Jam tayang      : ";
    getline(cin,jam);

    tambahFilm(judul,genre,harga,jam);
    simpanFile();
    cout<<"\nFilm berhasil ditambahkan!\n";
}

void tampilFilm(){
    if(headFilm==NULL){
        cout<<"\nData Film Masih Kosong!\n";
        return;
    }
    Film *current=headFilm;
    int no=1;
    cout<<"\n===============================================================================\n";
    cout<<"| NO | JUDUL FILM                  | GENRE             | HARGA   | JAM TAYANG |\n";
    cout<<"===============================================================================\n";

    while(current!=NULL){

        cout<<"| "
            <<left<<setw(2)<<no<<" | "
            <<setw(27)<<current->judul<<" | "
            <<setw(17)<<current->genre<<" | "
            <<setw(7)<<current->harga<<" | "
            <<setw(10)<<current->jam<<" |\n";

        current=current->next;
        no++;
    }

    cout<<"===============================================================================\n";
}

void searchingFilm(){
    string cari;
    int ketemu=0;
    cin.ignore();
    cout<<"\nMasukkan Judul Film : ";
    getline(cin,cari);
    Film *current=headFilm;

    while(current!=NULL){

        if(current->judul==cari){

            cout<<"\n========================================\n";
            cout<<"           FILM DITEMUKAN               \n";
            cout<<"========================================\n";

            cout<<"Judul : "<<current->judul<<endl;
            cout<<"Genre : "<<current->genre<<endl;
            cout<<"Harga : "<<current->harga<<endl;
            cout<<"Jam   : "<<current->jam<<endl;

            ketemu=1;
        }

        current=current->next;
    }

    if(ketemu==0){
        cout<<"\nFilm Tidak Ditemukan!\n";
    }
}

void tukarFilm(Film *a,Film *b){

    swap(a->judul,b->judul);
    swap(a->genre,b->genre);
    swap(a->harga,b->harga);
    swap(a->jam,b->jam);
}

void sortingJam(){

    if(headFilm==NULL) return;
    int tukar;
    Film *ptr;
    Film *batas=NULL;

    do{
        tukar=0;
        ptr=headFilm;
        while(ptr->next!=batas){

            if(ptr->jam>ptr->next->jam){

                tukarFilm(ptr,ptr->next);
                tukar=1;
            }

            ptr=ptr->next;
        }

        batas=ptr;

    }while(tukar);

    cout<<"\nFilm Berhasil Diurutkan Berdasarkan Jam Tayang!\n";
}

void hapusFilm(){
if(headFilm==NULL){
    cout<<"\nData Film Masih Kosong!\n";
    return;
}

string judul;
tampilFilm();
cin.ignore();

cout<<"\nMasukkan Judul Film Yang Ingin Dihapus : ";
getline(cin,judul);

Film *current=headFilm;
Film *prev=NULL;

while(current!=NULL && current->judul!=judul){
    prev=current;
    current=current->next;
}

if(current == NULL){
    cout<<"\nFilm Tidak Ditemukan!\n";
    return;
}

if(current == headFilm && current == tailFilm){
    headFilm = tailFilm = NULL;
}
else if(current == headFilm){
    headFilm = headFilm->next;
}
else if(current == tailFilm){
    tailFilm = prev;
    tailFilm->next = NULL;
}
else{
    prev->next = current->next;
}

delete current;
simpanFile();

cout<<"Film Berhasil Dihapus!\n";
}
void tambahRiwayat(string nama,
                   string film, int jumlah){

    Riwayat *baru=new Riwayat;
    baru->nama=nama;
    baru->film=film;
    baru->jumlah=jumlah;
    baru->next=NULL;
    baru->prev=NULL;

    if(headRiwayat==NULL){
        headRiwayat=tailRiwayat=baru;
    }
    else{
        tailRiwayat->next=baru;
        baru->prev=tailRiwayat;
        tailRiwayat=baru;
    }
}

void pesanTiket(){
    if(headFilm==NULL){
        cout<<"\nData Film Masih Kosong!\n";
        return;
    }
    string nama, film;
    int jumlah;
    tampilFilm();
    cin.ignore();
    cout<<"\nMasukkan Nama Pemesan : ";
    getline(cin, nama);
    Film *current;
    bool ketemu;
    int hargaFilm;
    do{
        ketemu = false;
        cout<<"Masukkan Judul Film   : ";
        getline(cin, film);
        current = headFilm;
        while(current != NULL){
            if(current->judul == film){
                ketemu = true;
                hargaFilm = current->harga; // simpan harga film
                break;
            }
            current = current->next;
        }
        if(!ketemu){
            cout<<"\nJudul film tidak tersedia, coba lagi!\n";
        }
    }while(!ketemu);
    cout<<"Jumlah Tiket          : ";
    cin >> jumlah;
    int total = hargaFilm * jumlah;
    tambahRiwayat(nama, film, jumlah);

    cout<<"\n========================================\n";
    cout<<"             TIKET BIOSKOP              \n";
    cout<<"========================================\n";
    cout<<"Nama Pemesan : "<<nama<<endl;
    cout<<"Film         : "<<film<<endl;
    cout<<"Harga Satuan : "<<hargaFilm<<endl;
    cout<<"Jumlah Tiket : "<<jumlah<<endl;
    cout<<"TOTAL BAYAR  : "<<total<<endl;
    cout<<"========================================\n";
}

void tampilRiwayat(){
    Riwayat *current=headRiwayat;
    int no=1;
    cout<<"\n====================================================\n";
    cout<<"              RIWAYAT PEMESANAN                     \n";
    cout<<"====================================================\n";

    while(current!=NULL){

        cout<<"\nRiwayat "<<no<<endl;
        cout<<"Nama         : "<<current->nama<<endl;
        cout<<"Film         : "<<current->film<<endl;
        cout<<"Jumlah Tiket : "<<current->jumlah<<endl;

        current=current->next;
        no++;
    }
}

int loadDataFilm(){

    FILE *fp=fopen("film.txt","r");

    if(fp==NULL){
        return 0;
    }

    char judul[100];
    char genre[50];
    char jam[20];

    int harga;
    int jumlah=0;

    while(fscanf(fp,
                 " %99[^#]#%49[^#]#%d#%19[^\n]\n",
                 judul,
                 genre,
                 &harga,
                 jam)!=EOF){

        tambahFilm(judul,genre,harga,jam);

        jumlah++;
    }

    fclose(fp);

    return jumlah;
}

int main(){

    int pilih;
    loadDataFilm();

    do{

        cout<<"\n=========================================\n";
        cout<<"|     SELAMAT DATANG DI BIOSKOP SCBD    |\n";
        cout<<"=========================================\n";
        cout<<"| [1] Tampilkan Daftar Film             |\n";
        cout<<"| [2] Tambah Film Baru                  |\n";
        cout<<"| [3] Cari Film (Linear Search)         |\n";
        cout<<"| [4] Urutkan Jam Film (Bubble Sort)    |\n";
        cout<<"| [5] Hapus Daftar Film                 |\n";
        cout<<"| [6] Pesan Tiket                       |\n";
        cout<<"| [7] Tampilkan Riwayat                 |\n";
        cout<<"| [0] Keluar                            |\n";
        cout<<"=========================================\n";
        cout<<"\nPilih Menu : ";
        cin>>pilih;

        switch(pilih){

            case 1:
                tampilFilm();
                break;

            case 2:
                tambahFilmBaru();
                break;

            case 3:
                searchingFilm();
                break;

            case 4:
                sortingJam();
                tampilFilm();
                break;

            case 5:
                hapusFilm();
                break;
   
            case 6:
                pesanTiket();
                break;

            case 7:
                tampilRiwayat();
                break;

            case 0:
                cout<<"\n========================================\n";
                cout<<"        TERIMA KASIH TELAH DATANG       \n";
                cout<<"========================================\n";
                break;

            default:
                cout<<"\nMenu Tidak Tersedia!\n";
        }

        cout<<endl;

        system("pause");
        system("cls");

    }while(pilih!=0);

    return 0;
}