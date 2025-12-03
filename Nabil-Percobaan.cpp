#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <cassert>
using namespace std;


struct ChannelYoutube{
    string nama;
    string negara;
    int jumlahVideo;
    int jumlahPenonton;
    int jumlahLike;
    int id;
};

const int MAX = 500;
ChannelYoutube channels[MAX];
int realSize = 0;

//utility
void swap(ChannelYoutube &a, ChannelYoutube &b){
    ChannelYoutube temp = a;
    a = b;
    b = temp;
}

int createId(){
    return rand() % 1000000;
}

void showError(string message){
    cout << "[ERROR] " << message << endl;
}

int searchById(int target, int first = 0, int last = realSize){
    int mid = (first+last)/2;
    if(first > last){
        return -1;
    }
    if(channels[mid].id == target){
        return mid;
    } else if(channels[mid].id < target){
        return searchById(target, mid+1, last);
    } else if(channels[mid].id > target) {
        return searchById(target, first, mid-1);
    }
}

// Channel
void lihatChannel(bool showAll = true, int index = -1){
    assert(!(!showAll && index == -1));
    if(showAll)
    {
        for(int i = 0; i < realSize; i++){
            cout << channels[i].nama << endl;
        }
    } else{
        cout << channels[index].nama << " | " << channels[index].negara << " | " << channels[index].jumlahVideo;
    }
}
//Salin supaya urutan berdasarkan id tidak berubah (Nabil)
void salinStruct(ChannelYoutube channels[], ChannelYoutube salinan[]){
    for (int i = 0; i < realSize; i++){
    salinan[i] = channels[i];
    }
}

void sortingView(){
    int opsi;
    ChannelYoutube salinan[MAX];
    salinStruct(channels, salinan);
    cout<<"[1] Urutkan Berdasarkan Penonton Terbanyak"<<endl;
    cout<<"[2] Urutkan Berdasarkan Penonton Tersedikit"<<endl;
    cout<<"Pilih Opsi: ";
    cin>>opsi;
    if(cin.fail() || realSize <= 0){
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Input tidak Valid"<<endl;
        return;
    }
    
    switch (opsi){
        case 1:
            for(int i = realSize-1; i > 0; i--){
                if(channels[i-1].jumlahPenonton > channels[i].jumlahPenonton){
                    swap(channels[i], channels[i-1]);
                }
            }
        break;
        case 2:
            for(int i = realSize-1; i > 0; i--){
                if(channels[i-1].jumlahPenonton < channels[i].jumlahPenonton){
                    swap(channels[i], channels[i-1]);
                }
            }
            break;
        default:
            break;

}
    for (int i = 0; i < realSize; i++){
        cout<<"Urutan ke-"<<(i+1)<<" Channel "<<salinan[i].nama<<" dengan "<<salinan[i].jumlahPenonton<<" penonton"<<endl;
    }
}

void sortingLike(){
    int opsi;
    ChannelYoutube salinan[MAX];
    salinStruct(channels, salinan);
    cout<<"[1] Urutkan Berdasarkan Like Terbanyak"<<endl;
    cout<<"[2] Urutkan Berdasarkan Like Tersedikit"<<endl;
    cout<<"Pilih Opsi: ";
    cin>>opsi;
    if(cin.fail() || realSize <= 0){
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Input tidak Valid"<<endl;
        return;
    }
    
    switch (opsi){
        case 1:
            for(int i = realSize-1; i > 0; i--){
                if(channels[i-1].jumlahLike > channels[i].jumlahLike){
                    swap(channels[i], channels[i-1]);
                }
            }
        break;
        case 2:
            for(int i = realSize-1; i > 0; i--){
                if(channels[i-1].jumlahLike < channels[i].jumlahLike){
                    swap(channels[i], channels[i-1]);
                }
            }
            break;
        default:
            break;

}
    for (int i = 0; i < realSize; i++){
        cout<<"Urutan ke-"<<(i+1)<<" Channel "<<salinan[i].nama<<" dengan "<<salinan[i].jumlahLike<<" Like"<<endl;
    }
}
void cariBerdasarkanNegara(ChannelYoutube x[]){
    int urutan = 0;
    string cariNegara;
    cout<<"Cari Negara: ";
    cin>> cariNegara;
    if(cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Input tidak Valid"<<endl;
        return;
    }

    for (int i = 0; i < realSize; i++){
        if (x[i].negara==cariNegara){
            cout<<"["<<urutan+1<<"] Channel " << x[i].nama<<endl;
            urutan++;
        }
        else{
            continue;
        }
    }
}
//Aku ubah yang di atas 

void tambahChannel(){
    if(realSize >= MAX) {
        cout << "Jumlah saluran penuh" << endl;
        return;
    }
    
    int id = createId();
    string nama;
    string negara;
    int jumlahVideo;
    int jumlahPenonton;
    int jumlahLike;

    cout << "Masukkan nama saluran: ";
    cin.ignore();
    getline(cin, nama);
    cout << "Masukkan negara saluran: ";
    getline(cin, negara);
    cout << "Masukkan jumlah video saluran: ";
    cin >> jumlahVideo;
    cout << "Masukkan jumlah penonton saluran: ";
    cin >> jumlahPenonton;
    cout << "Masukkan jumlah like saluran: ";
    cin >> jumlahLike;

    ChannelYoutube channel = {
        nama, negara, jumlahVideo, jumlahPenonton, jumlahLike, id
    };

    channels[realSize] = channel;
    realSize++;

    // Logika insertion sort
    for(int i = realSize-1; i > 0; i--){
        if(channels[i].id < channels[i-1].id){
            swap(channels[i], channels[i-1]);
        }
    }
}

void menuCariChannel(){
    int idTarget;
    cout << "===== CARI SALURAN YOUTUBE =====" << endl;
    cout << "Masukkan ID: " << endl;
    cin >> idTarget;
    int index = searchById(idTarget);
    if(index == -1){
        showError("ID tidak ditemukan");
        return;
    } 
    lihatChannel(false, index);
}

int tampilkanMenu(){
    int pilihan;
    cout << "=====MANAJEMEN SALURAN YOUTUBE=====" << endl;
    cout << "[1] Lihat Saluran" << endl;
    cout << "[2] Tambahkan Saluran" << endl;
    cout << "[3] Cari saluran berdasarkan ID" << endl;
    cout << "[4] Cari saluran berdasarkan Negara" << endl;
    cout << "[5] Lihat Urutan Berdasarkan Jumlah Penonton"<< endl;
    cout << "[6] Lihat Urutan Berdasarkan Jumlah Like"<< endl;
    cout << "[0] Berhenti" << endl << endl;
    cout << "pilihan: ";
    cin >> pilihan;
    if(cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        return -1;
    }
    return pilihan;
}

int main(){
    int pilihan = 0;
    do {
        pilihan = tampilkanMenu();
        switch(pilihan){
            case 1: {
                lihatChannel();
                break;
            }
            case 2: {
                tambahChannel();
                break;
            }
            case 3: {
                menuCariChannel();
                break;
            }
            case 4: {
                cariBerdasarkanNegara(channels);
                break;
            }
            case 5: {
                sortingView();
                break;
            }
            case 6: {
                sortingLike();
                break;
            }
            case 0: {
                return 0;
            }
            default: {
                showError("Pilihan yang dimasukkan tidak tepat.");
                return 0;
            }
        }
    } while(pilihan != 0);
}