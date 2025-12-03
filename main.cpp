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
    cout << "[0] Berhenti" << endl << endl;
    cout << "pilihan: ";
    cin >> pilihan;
    if(cin.fail())
    return pilihan;
}

int main(){
    int pilihan = 0;
    do {
        tampilkanMenu();
        
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