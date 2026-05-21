#include <iostream>
//#include <string>
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
    Riwayat *next;
    Riwayat *prev;
};

Film *headFilm=NULL;
Film *tailFilm=NULL;

Riwayat *headRiwayat=NULL;
Riwayat *tailRiwayat=NULL;

void loading(){
    cout<<"\nLoading";

    for(int i=0;i<5;i++){
        cout<<".";
        Sleep(300);
    }

    cout<<endl;
}

void header(){
    cout<<"\n";
    cout<<"============================================================\n";
    cout<<"                  BIOSKOP XXI INDONESIA                     \n";
    cout<<"============================================================\n";
    cout<<"            PESAN TIKET FILM FAVORITMU DISINI               \n";
    cout<<"============================================================\n";
}

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

    cout<<"\nData Film Berhasil Disimpan Ke File!\n";
}

void inputFilmBaru(){

    string judul,genre,jam;
    int harga;

    cin.ignore();

    cout<<"Judul film    : ";
    getline(cin,judul);

    cout<<"Genre         : ";
    getline(cin,genre);

    cout<<"Harga (Rp)    : ";
    cin>>harga;
    cin.ignore();

    cout<<"Jam tayang    : ";
    getline(cin,jam);

    tambahFilm(judul,genre,harga,jam);

    cout<<"\nFilm berhasil ditambahkan!\n";
}

void tampilFilm(){

    Film *current=headFilm;
    int no=1;

    cout<<"\n====================================================================================\n";
    cout<<"| NO | JUDUL FILM                  | GENRE              | HARGA   | JAM TAYANG |\n";
    cout<<"====================================================================================\n";

    while(current!=NULL){

        cout<<"| "
            <<no<<" | "
            <<current->judul<<" | "
            <<current->genre<<" | "
            <<current->harga<<" | "
            <<current->jam<<endl;

        current=current->next;
        no++;
    }

    cout<<"====================================================================================\n";
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

void tambahRiwayat(string nama,
                   string film){

    Riwayat *baru=new Riwayat;

    baru->nama=nama;
    baru->film=film;

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

    string nama;
    string film;

    tampilFilm();

    cin.ignore();

    cout<<"\nMasukkan Nama Pemesan : ";
    getline(cin,nama);

    cout<<"Masukkan Judul Film   : ";
    getline(cin,film);

    tambahRiwayat(nama,film);

    loading();

    cout<<"\n";
    cout<<"========================================\n";
    cout<<"             TIKET BIOSKOP              \n";
    cout<<"========================================\n";
    cout<<"Nama Pemesan : "<<nama<<endl;
    cout<<"Film         : "<<film<<endl;
    cout<<"Status       : BERHASIL\n";
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
        cout<<"Nama : "<<current->nama<<endl;
        cout<<"Film : "<<current->film<<endl;

        current=current->next;
        no++;
    }
}

int loadDataFilm(){

    FILE *fp=fopen("film.txt","r");

    if(fp==NULL){
        return 0;
    }

    char judul[100],genre[50],jam[20];
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

    tambahFilm("Spider-Man Brand New Day","Action",60000,"20.00");
    tambahFilm("Danur The Last Chapter","Horor",45000,"21.00");
    tambahFilm("The Odyssey","Horor Komedi",55000,"18.30");
    tambahFilm("Tumbal Proyek","Horor",50000,"19.00");
    tambahFilm("Ayah Ini Arahnya Kemana","Drama Keluarga",40000,"17.00");

    loadDataFilm();

    do{

        header();

        cout<<"\n";
        cout<<"1. Tampilkan Daftar Film\n";
        cout<<"2. Input Film Baru\n";
        cout<<"3. Cari Film (Linear Search)\n";
        cout<<"4. Urutan Jam Film (Bubble Sort)\n";
        cout<<"5. Pesan Tiket\n";
        cout<<"6. Tampilkan Riwayat\n";
        cout<<"7. Simpan Data Ke File\n";
        cout<<"0. Keluar\n";

        cout<<"---------------------------------------------------------------\n";

        cout<<"\nPilih Menu : ";
        cin>>pilih;

        switch(pilih){

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