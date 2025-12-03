#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
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



void salinArrayChannelYoutube(ChannelYoutube channels[], ChannelYoutube salinan[]){
    for (int i = 0; i < realSize; i++){
        salinan[i] = channels[i];
    }
}

// Channel
void initializeChannel() {
    ChannelYoutube channels[MAX];
    realSize = 0;
    loadFile();
}
void lihatChannelHeader(){
    cout << "ID | Nama | Negara | Jumlah Video | Jumlah Penonton | Jumlah Like" << endl;
}
void lihatChannel(){
    if(realSize == 0){
        cout << "Tidak ada channel" << endl;
    }
    for(int i = 0; i < realSize; i++){
        cout << channels[i].id << " | " << channels[i].nama << " | " << channels[i].negara << " | " << channels[i].jumlahVideo << " | " << channels[i].jumlahPenonton << " | " << channels[i].jumlahLike << endl;
    }

}
void lihatChannel(int index){
    cout << channels[index].id << " | " << channels[index].nama << " | " << channels[index].negara << " | " << channels[index].jumlahVideo << " | " << channels[index].jumlahPenonton << " | " << channels[index].jumlahLike << endl;
}

void lihatChannel(ChannelYoutube arr[], int N){
    if(realSize == 0){
        cout << "Tidak ada channel" << endl;
    }
    for(int i = 0; i < N; i++){
        cout << arr[i].id << " | " << arr[i].nama << " | " << arr[i].negara << " | " << arr[i].jumlahVideo << " | " << arr[i].jumlahPenonton << " | " << arr[i].jumlahLike << endl;
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

    cout << "Masukkan nama saluran (tanpa spasi): ";
    getline(cin, nama);
    stringstream ss1(nama); 
    ss1 >> nama;// supaya hanya mengambil kata pertama jika pengguna memasukan spasi
    ss1.clear();
    cout << "Masukkan negara saluran (tanpa spasi): ";
    getline(cin, negara);
    stringstream ss2(negara); // supaya hanya mengambil kata pertama jika pengguna memasukan spasi
    ss2 >> negara;
    ss2.clear(); 
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
    ofstream file("youtube.txt", ofstream::out | ofstream::trunc); // untuk menghapus isi file
    if(!file){
        showError("File youtube.txt tidak ditemukan");
        exit(-1);
    }
    for(int i = 0; i < realSize; i++){
        if(i == index) continue;
        file << to_string(channels[i].id) << " " << channels[i].nama << " " << channels[i].negara << " " << to_string(channels[i].jumlahVideo) << " " << to_string(channels[i].jumlahPenonton) << " " << to_string(channels[i].jumlahLike) << endl;
    }
    file.close();
    initializeChannel();
    
}

// PENCARIAN
int searchById(int target, int first = 0, int last = realSize){
    int mid = (first+last)/2;
    if(first > last){
        return -1;
    }
    if(channels[mid].id == target){
        return mid;
    } else if(channels[mid].id < target){
        return searchById(target, mid+1, last);
    } else {
        return searchById(target, first, mid-1);
    }
}

void searchByCountry(string negara){
    lihatChannelHeader();
    for (int i = 0; i < realSize; i++){
        if (channels[i].negara==negara){
            lihatChannel(i);
        }
    }
}

void menuCariChannelBerdasarkanID(){
    int idTarget;
    cout << "===== CARI SALURAN YOUTUBE =====" << endl;
    cout << "Masukkan ID: ";
    cin >> idTarget;
    if(cin.fail()){
        cinClear();
    }
    int index = searchById(idTarget);
    if(index == -1){
        showError("ID tidak ditemukan");
        return;
    } 
    lihatChannel(index);
}

void menuCariChannelBerdasarkanNegara(){
    string negara;
    cout << "===== CARI SALURAN YOUTUBE =====" << endl;
    cout << "Masukkan negara: ";
    cin >> negara;
    if(cin.fail()){
        cinClear();
    }
    searchByCountry(negara);
}


void menuUrutanBerdasarkanJumlahPenonton(){
    int opsi;
    ChannelYoutube salinan[MAX];
    salinArrayChannelYoutube(channels, salinan);
    cout << "===== URUTKAN =====" << endl;
    cout<<"[1] Urutkan Berdasarkan Penonton Terbanyak"<<endl;
    cout<<"[2] Urutkan Berdasarkan Penonton Tersedikit"<<endl;
    cout<<"pilihan: ";
    cin>>opsi;
    cout << endl;

    if(cin.fail() || realSize <= 0){
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Input tidak Valid"<<endl;
        return;
    }
    
    switch (opsi){
        case 1:{
            // Insertion Sort
            for(int i = 0; i < realSize-1;i++){
                for(int j = i+1; j > 0; j--){
                    if(salinan[j].jumlahPenonton > salinan[j-1].jumlahPenonton){
                        swap(salinan[j], salinan[j-1]);
                    }
                }
            }
            break;
        }
        case 2:{
            // Insertion Sort
            for(int i = 0; i < realSize-1;i++){
                for(int j = i+1; j > 0; j--){
                    if(salinan[j].jumlahPenonton < salinan[j-1].jumlahPenonton){
                        swap(salinan[j], salinan[j-1]);
                    }
                }
            }
            break;
        }
        default:
            break;
    }
    lihatChannelHeader();
    lihatChannel(salinan, realSize);
}

void menuUrutanBerdasarkanJumlahLike(){
    int opsi;
    ChannelYoutube salinan[MAX];
    salinArrayChannelYoutube(channels, salinan);
    cout << "===== URUTKAN =====" << endl;
    cout<<"[1] Urutkan Berdasarkan Like Terbanyak"<<endl;
    cout<<"[2] Urutkan Berdasarkan Like Tersedikit"<<endl;
    cout<<"pilihan: ";
    cin>>opsi;
    cout << endl;
    if(cin.fail() || realSize <= 0){
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Input tidak Valid"<<endl;
        return;
    }
    
    switch (opsi){
        case 1:
            // Insertion Sort
            for(int i = 0; i < realSize-1;i++){
                for(int j = i+1; j > 0; j--){
                    if(salinan[j].jumlahLike > salinan[j-1].jumlahLike){
                        swap(salinan[j], salinan[j-1]);
                    }
                }
            }
        break;
        case 2:
            // Insertion Sort
            for(int i = 0; i < realSize-1;i++){
                for(int j = i+1; j > 0; j--){
                    if(salinan[j].jumlahLike < salinan[j-1].jumlahLike){
                        swap(salinan[j], salinan[j-1]);
                    }
                }
            }
            break;
        default:
            break;

    }
    lihatChannelHeader();
    lihatChannel(salinan, realSize);
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

void analisisStatistik(
    double &rataVideo, double &rataPenonton, double &rataLike, 
    int &minVideo,int &minPenonton, int &minLike, 
    int &maxVideo,int &maxPenonton, int &maxLike 
){
    int totalVideo = 0, totalPenonton = 0, totalLike = 0;

    minVideo = channels[0].jumlahVideo;
    maxVideo = channels[0].jumlahVideo;

    minPenonton = channels[0].jumlahPenonton;
    maxPenonton = channels[0].jumlahPenonton;

    minLike = channels[0].jumlahLike;
    maxLike = channels[0].jumlahLike;

    for(int i = 0; i < realSize; i++){
        // akumulasi total
        totalVideo += channels[i].jumlahVideo;
        totalPenonton += channels[i].jumlahPenonton;
        totalLike += channels[i].jumlahLike;

        // min / max video
        if(channels[i].jumlahVideo < minVideo) minVideo = channels[i].jumlahVideo;
        if(channels[i].jumlahVideo > maxVideo) maxVideo = channels[i].jumlahVideo;

        // min / max penonton
        if(channels[i].jumlahPenonton < minPenonton) minPenonton = channels[i].jumlahPenonton;
        if(channels[i].jumlahPenonton > maxPenonton) maxPenonton = channels[i].jumlahPenonton;

        // min / max like
        if(channels[i].jumlahLike < minLike) minLike = channels[i].jumlahLike;
        if(channels[i].jumlahLike > maxLike) maxLike = channels[i].jumlahLike;
    }

    rataVideo = (double)totalVideo / realSize;
    rataPenonton = (double)totalPenonton / realSize;
    rataLike = (double)totalLike / realSize;
}

void menuStatistikSaluran(){
    if(realSize == 0){
        showError("Belum ada data saluran.");
        return;
    }

    double rataVideo, rataPenonton, rataLike;
    int minVideo, minPenonton, minLike;
    int maxVideo, maxPenonton, maxLike;

    analisisStatistik(
        rataVideo, rataPenonton, rataLike,
        minVideo, minPenonton, minLike,
        maxVideo, maxPenonton, maxLike
    );

    cout << "===== STATISTIK SALURAN YOUTUBE =====" << endl;
    cout << "Jumlah saluran: " << realSize << endl << endl;

    cout << "Jumlah Video" << endl;
    cout << "  Rata-rata : " << rataVideo << endl;
    cout << "  Minimum   : " << minVideo << endl;
    cout << "  Maksimum  : " << maxVideo << endl << endl;

    cout << "Jumlah Penonton" << endl;
    cout << "  Rata-rata : " << rataPenonton << endl;
    cout << "  Minimum   : " << minPenonton << endl;
    cout << "  Maksimum  : " << maxPenonton << endl << endl;

    cout << "Jumlah Like" << endl;
    cout << "  Rata-rata : " << rataLike << endl;
    cout << "  Minimum   : " << minLike << endl;
    cout << "  Maksimum  : " << maxLike << endl << endl;
}

int tampilkanMenu(){
    int pilihan;
    cout << "=====MANAJEMEN SALURAN YOUTUBE=====" << endl;
    cout << "[1] Lihat Saluran" << endl;
    cout << "[2] Tambahkan Saluran" << endl;
    cout << "[3] Lihat statistik saluran" << endl;
    cout << "[4] Cari saluran berdasarkan ID" << endl;
    cout << "[5] Cari saluran berdasarkan Negara" << endl;
    cout << "[6] Lihat Urutan Berdasarkan Jumlah Penonton"<< endl;
    cout << "[7] Lihat Urutan Berdasarkan Jumlah Like"<< endl;
    cout << "[8] Hapus Saluran" << endl;
    cout << "[0] Berhenti" << endl << endl;
    cout << "pilihan: ";
    cin >> pilihan;
    if(cin.fail())
        return -1;
    cout << endl;
    return pilihan;
}

int main(){
    srand(time(0));
    initializeChannel();

    int pilihan = 0;
    do {
        pilihan = tampilkanMenu();
        cout << endl;
        switch(pilihan){
            case 1: {
                lihatChannelHeader();
                lihatChannel();
                break;
            }
            case 2: {
                tambahChannel();
                break;
            }
            case 3: {
                menuStatistikSaluran();
                break;
            }
            case 4: {
                menuCariChannelBerdasarkanID();
                break;
            }
            case 5: {
                menuCariChannelBerdasarkanNegara();
                break;
            }case 6: {
                menuUrutanBerdasarkanJumlahPenonton();
                break;
            }case 7: {
                menuUrutanBerdasarkanJumlahLike();
                break;
            }case 8: {
                menuHapusChannel();
                break;
            }
            case 0: {
                return 0;
            }
            default: {
                showError("Pilihan yang dimasukkan tidak tepat.");
                break;
            }
        }
        cout << endl;
    } while(pilihan != 0);
}