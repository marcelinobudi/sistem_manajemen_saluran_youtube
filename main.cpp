#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <cassert>
#include <limits>
#include <ctime>
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
void cinClear(){
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
}
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

void loadFile(){
    ifstream file("youtube.txt");
    
    if(!file){
        showError("File youtube.txt tidak ditemukan");
        exit(-1);
    }
    string line;
    for(int i = 0; i < MAX && getline(file, line); i++){
        stringstream ss(line);
        
        ss >> channels[i].id >> channels[i].nama >> channels[i].negara >> channels[i].jumlahVideo >> channels[i].jumlahPenonton >> channels[i].jumlahLike;
        realSize++;
    }
    file.close();
}

void updateFile(){
    ofstream file("youtube.txt");
    if(!file){
        showError("File youtube.txt tidak ditemukan");
        exit(-1);
    }
    for(int i = 0; i < realSize; i++){
        file << to_string(channels[i].id) << " " << channels[i].nama << " " << channels[i].negara << " " << to_string(channels[i].jumlahVideo) << " " << to_string(channels[i].jumlahPenonton) << " " << to_string(channels[i].jumlahLike) << endl;
    }
    file.close();
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
            cout << channels[i].id << " | " << channels[i].nama << " | " << channels[i].negara << " | " << channels[i].jumlahVideo << " | " << channels[i].jumlahPenonton << " | " << channels[i].jumlahLike << endl;
        }
    } else{
        cout << channels[index].id << " | " << channels[index].nama << " | " << channels[index].negara << " | " << channels[index].jumlahVideo << " | " << channels[index].jumlahPenonton << " | " << channels[index].jumlahLike << endl;
    }
}


void tambahChannel(){
    cinClear();
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
    updateFile();
}

void hapusChannel(int index){
    ofstream file("youtube.txt");
    if(!file){
        showError("File youtube.txt tidak ditemukan");
        exit(-1);
    }
    for(int i = 0; i < realSize; i++){
        if(i == index) continue;
        file << to_string(channels[i].id) << " " << channels[i].nama << " " << channels[i].negara << " " << to_string(channels[i].jumlahVideo) << " " << to_string(channels[i].jumlahPenonton) << " " << to_string(channels[i].jumlahLike) << endl;
    }
    file.close();
    loadFile();
}

void menuCariChannel(){
    int idTarget;
    cout << "===== CARI SALURAN YOUTUBE =====" << endl;
    cout << "Masukkan ID: ";
    cin >> idTarget;
    int index = searchById(idTarget);
    if(index == -1){
        showError("ID tidak ditemukan");
        return;
    } 
    lihatChannel(false, index);
}

void menuHapusChannel(){
    int idTarget;
    cout << "==== HAPUS SALURAN YOUTUBE ====" << endl;
    cout << "Masukkan ID: ";
    cin >> idTarget;
    int index = searchById(idTarget);
    if(index == -1){
        showError("ID tidak ditemukan");
        return;
    } 
    hapusChannel(index);
}

int tampilkanMenu(){
    int pilihan;
    cout << "=====MANAJEMEN SALURAN YOUTUBE=====" << endl;
    cout << "[1] Lihat Saluran" << endl;
    cout << "[2] Tambahkan Saluran" << endl;
    cout << "[3] Cari saluran berdasarkan ID" << endl;
    cout << "[5] Hapus Saluran" << endl;
    cout << "[0] Berhenti" << endl << endl;
    cout << "pilihan: ";
    cin >> pilihan;
    if(cin.fail())
        return -1;
    return pilihan;
}

int main(){
    srand(time(0));
    int pilihan = 0;

    loadFile();
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
            case 5: {
                menuHapusChannel();
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