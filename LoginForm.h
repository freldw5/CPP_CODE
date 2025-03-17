#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>
#include <cstdlib>
#include <iomanip>
#include <vector>

using namespace std;

// Struktur untuk menyimpan data konversi
struct ConversionData {
    string username;
    string status;
    double rupiah;
    double dollar;
    double kurs;
};

class UserSystem {
private:
    string filename;
    string conversionFile;
    map<string, pair<string, string>> users; // username -> {password, gender}
    vector<ConversionData> conversions;
    string currentUser; // Untuk menyimpan username pengguna yang sedang login

    void loadUsers() {
        ifstream file(filename);
        if (file.is_open()) {
            string username, password, status;
            while (getline(file, username)) {
                getline(file, password);
                getline(file, status);
                users[username] = make_pair(password, status);
            }
            file.close();
        }
    }

    void saveUsers() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& user : users) {
                file << user.first << endl;              // username
                file << user.second.first << endl;       // password
                file << user.second.second << endl;      // gender/status
            }
            file.close();
        }
    }

    void loadConversions() {
        ifstream file(conversionFile);
        if (file.is_open()) {
            ConversionData data;
            string line;
            
            while (getline(file, data.username)) {
                getline(file, data.status);
                file >> data.rupiah;
                file >> data.dollar;
                file >> data.kurs;
                file.ignore(); // Untuk menghapus newline
                
                conversions.push_back(data);
            }
            file.close();
        }
    }

    void saveConversions() {
        ofstream file(conversionFile);
        if (file.is_open()) {
            for (const auto& conv : conversions) {
                file << conv.username << endl;
                file << conv.status << endl;
                file << conv.rupiah << endl;
                file << conv.dollar << endl;
                file << conv.kurs << endl;
            }
            file.close();
        }
    }

    void pressEnterToContinue() {
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

public:
    UserSystem(const string& fname, const string& convFile) 
        : filename(fname), conversionFile(convFile) {
        loadUsers();
        loadConversions();
    }
    
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void registerUser() {
        clearScreen();
        cout << "\n=== REGISTRASI ===\n";
        
        string username, password, confirmPass, status;

        while (true) {
            cout << "Masukkan username: ";
            cin >> username;
            
            if (users.find(username) != users.end()) {
                cout << "Username sudah digunakan. Silakan pilih username lain.\n";
                continue;
            }

            while (true) {
                cout << "Masukkan password: ";
                cin >> password;
                cout << "Konfirmasi password: ";
                cin >> confirmPass;

                if (password != confirmPass) {
                    cout << "Password tidak cocok. Silakan coba lagi.\n";
                    continue;
                }
                break;
            }

            cout << "Status anda: ";
            cin >> status;

            users[username] = make_pair(password, status);
            saveUsers();

            cout << "\nRegistrasi berhasil!\n";
            pressEnterToContinue();
            break;
        }
    }

    bool login() {
        clearScreen();
        cout << "\n=== LOGIN ===\n";
        
        string username, password;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        auto it = users.find(username);
        if (it != users.end() && it->second.first == password) {
            currentUser = username; // Simpan username yang sedang login
            cout << "\nLogin berhasil!\n";
            cout << "Selamat datang, " << username << "!\n";
            pressEnterToContinue();
            return true;
        } else {
            cout << "\nUsername atau password salah.\n";
            pressEnterToContinue();
            return false;
        }
    }
    
    void convertRupiah() {
        clearScreen();
        cout << "\n=== KONVERSI RUPIAH KE DOLLAR ===\n";
        
        ConversionData newData;
        newData.username = currentUser;
        newData.status = users[currentUser].second; // Ambil status dari data user
        
        cout << "Masukkan kurs Dollar saat ini (1 USD = ? IDR): ";
        cin >> newData.kurs;
        
        cout << "Masukkan jumlah Rupiah: Rp. ";
        cin >> newData.rupiah;
    
        // Proses konversi Rupiah ke Dollar
        newData.dollar = newData.rupiah / newData.kurs;
        
        // Output hasil konversi
        cout << fixed << setprecision(2);
        cout << "\nHasil Konversi:" << endl;
        cout << "Rp. " << newData.rupiah << " = USD " << newData.dollar << endl;
        
        // Simpan data konversi
        conversions.push_back(newData);
        saveConversions();
        
        pressEnterToContinue();
    }
    
    void lihatData() {
        clearScreen();
        cout << "\n=== DATA KONVERSI ===\n";
        
        if (conversions.empty()) {
            cout << "Tidak ada data konversi sebelumnya!\n";
            pressEnterToContinue();
            return;
        }
        
        cout << fixed << setprecision(2);
        for (size_t i = 0; i < conversions.size(); i++) {
            cout << "Data konversi " << (i+1) << ":\n";
            cout << "Username: " << conversions[i].username << endl;
            cout << "Status: " << conversions[i].status << endl;
            cout << "Kurs: 1 USD = " << conversions[i].kurs << " IDR" << endl;
            cout << "Rupiah: Rp. " << conversions[i].rupiah << endl;
            cout << "Dollar: USD " << conversions[i].dollar << endl;
            cout << "------------------------------\n";
        }
        
        pressEnterToContinue();
    }
    
    void editData() {
        clearScreen();
        cout << "\n=== EDIT DATA KONVERSI ===\n";
        
        if (conversions.empty()) {
            cout << "Tidak ada data konversi untuk diedit!\n";
            pressEnterToContinue();
            return;
        }
        
        // Tampilkan data yang ada
        cout << "Data konversi yang tersedia:\n";
        for (size_t i = 0; i < conversions.size(); i++) {
            cout << (i+1) << ". " << conversions[i].username 
                 << " - Rp. " << conversions[i].rupiah 
                 << " = USD " << conversions[i].dollar << endl;
        }
        
        int pilihan;
        cout << "\nPilih nomor data yang ingin diedit (1-" << conversions.size() << "): ";
        cin >> pilihan;
        
        if (pilihan < 1 || pilihan > (int)conversions.size()) {
            cout << "Pilihan tidak valid!\n";
            pressEnterToContinue();
            return;
        }
        
        int index = pilihan - 1;
        
        // Cek apakah user hanya bisa mengedit datanya sendiri
        if (conversions[index].username != currentUser) {
            cout << "Anda hanya dapat mengedit data konversi milik Anda sendiri!\n";
            pressEnterToContinue();
            return;
        }
        
        cout << "\nMasukkan kurs Dollar baru (1 USD = ? IDR): ";
        cin >> conversions[index].kurs;
        
        cout << "Masukkan jumlah Rupiah baru: Rp. ";
        cin >> conversions[index].rupiah;
        
        // Hitung ulang konversi
        conversions[index].dollar = conversions[index].rupiah / conversions[index].kurs;
        
        cout << "\nData berhasil diperbarui!\n";
        cout << "Hasil konversi baru: Rp. " << conversions[index].rupiah 
             << " = USD " << conversions[index].dollar << endl;
        
        // Simpan perubahan
        saveConversions();
        
        pressEnterToContinue();
    }
    
    void hapusData() {
        clearScreen();
        cout << "\n=== HAPUS DATA KONVERSI ===\n";
        
        if (conversions.empty()) {
            cout << "Tidak ada data konversi untuk dihapus!\n";
            pressEnterToContinue();
            return;
        }
        
        // Tampilkan data yang ada
        cout << "Data konversi yang tersedia:\n";
        for (size_t i = 0; i < conversions.size(); i++) {
            cout << (i+1) << ". " << conversions[i].username 
                 << " - Rp. " << conversions[i].rupiah 
                 << " = USD " << conversions[i].dollar << endl;
        }
        
        int pilihan;
        cout << "\nPilih nomor data yang ingin dihapus (1-" << conversions.size() << "): ";
        cin >> pilihan;
        
        if (pilihan < 1 || pilihan > (int)conversions.size()) {
            cout << "Pilihan tidak valid!\n";
            pressEnterToContinue();
            return;
        }
        
        int index = pilihan - 1;
        
        // Cek apakah user hanya bisa menghapus datanya sendiri
        if (conversions[index].username != currentUser) {
            cout << "Anda hanya dapat menghapus data konversi milik Anda sendiri!\n";
            pressEnterToContinue();
            return;
        }
        
        // Hapus data
        conversions.erase(conversions.begin() + index);
        
        cout << "\nData berhasil dihapus!\n";
        
        // Simpan perubahan
        saveConversions();
        
        pressEnterToContinue();
    }
    
    void printData() {
        clearScreen();
        cout << "\n=== PRINT DATA KONVERSI ===\n";
        
        if (conversions.empty()) {
            cout << "Tidak ada data konversi untuk dicetak!\n";
            pressEnterToContinue();
            return;
        }
        
        // Simulasi printing dengan menulis ke file
        ofstream printFile("print_data.pdf");
        if (!printFile.is_open()) {
            cout << "Error: Tidak dapat membuat file print!\n";
            pressEnterToContinue();
            return;
        }
        
        printFile << "===== LAPORAN KONVERSI RUPIAH KE DOLLAR =====\n\n";
        printFile << fixed << setprecision(2);
        
        for (size_t i = 0; i < conversions.size(); i++) {
            printFile << "Data konversi " << (i+1) << ":\n";
            printFile << "Username: " << conversions[i].username << endl;
            printFile << "Status: " << conversions[i].status << endl;
            printFile << "Kurs: 1 USD = " << conversions[i].kurs << " IDR" << endl;
            printFile << "Rupiah: Rp. " << conversions[i].rupiah << endl;
            printFile << "Dollar: USD " << conversions[i].dollar << endl;
            printFile << "------------------------------\n";
        }
        
        printFile.close();
        
        cout << "Data berhasil dicetak ke file 'print_data.pdf'\n";
        pressEnterToContinue();
    }
    
    void mainMenu() {
        while (true) {
            clearScreen();
            int pilihan;
            
            cout << "============Selamat datang di converter rupiah!!============\n";
            cout << "\n1. Konvert rupiah ke dollar\n";
            cout << "2. Lihat data\n";
            cout << "3. Edit data\n";
            cout << "4. Hapus data\n";
            cout << "5. Print data\n";
            cout << "6. Keluar\n";
            
            cout << "\nPilihan anda (1-6): ";
            cin >> pilihan;
            
            switch(pilihan) {
                case 1:
                    convertRupiah();
                    break;
                case 2:
                    lihatData();
                    break;
                case 3:
                    editData();
                    break;
                case 4:
                    hapusData();
                    break;
                case 5:
                    printData();
                    break;
                case 6:
                    cout << "\nTerima kasih telah menggunakan aplikasi converter rupiah!\n";
                    return;
                default:
                    cout << "\nPilihan tidak valid. Silakan coba lagi.\n";
                    pressEnterToContinue();
                    break;
            }
        }
    }
};
