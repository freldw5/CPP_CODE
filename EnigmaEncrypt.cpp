#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Implementasi Dasar Mesin Enigma
class Enigma {
private:
    // Rotors (simulasi dari 3 rotor yang digunakan pada mesin Enigma asli)
    vector<string> rotors = {
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ", // Rotor I
        "AJDKSIRUXBLHWTMCQGZNPYFVOE", // Rotor II
        "BDFHJLCPRTXVZNYEIWGAKMUSQO"  // Rotor III
    };
    
    // Reflector (digunakan untuk mengirim sinyal kembali melalui rotors)
    string reflector = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
    
    // Posisi awal untuk setiap rotor (diset oleh pengguna)
    vector<int> rotorPositions;
    
    // Jumlah putaran untuk setiap klik tombol
    vector<int> notchPositions = {17, 5, 22}; // Q, E, V dalam alfabet 0-indexed
    
public:
    Enigma(int pos1, int pos2, int pos3) {
        rotorPositions = {pos1, pos2, pos3};
    }
    
    // Fungsi untuk memutar rotor
    void rotate() {
        rotorPositions[0] = (rotorPositions[0] + 1) % 26;
        
        // Jika rotor pertama mencapai notch, putar rotor kedua
        if (rotorPositions[0] == notchPositions[0]) {
            rotorPositions[1] = (rotorPositions[1] + 1) % 26;
        }
        
        // Jika rotor kedua mencapai notch, putar rotor ketiga
        if (rotorPositions[1] == notchPositions[1]) {
            rotorPositions[2] = (rotorPositions[2] + 1) % 26;
        }
    }
    
    // Melalui satu rotor (maju)
    char throughRotor(char c, const string& rotor, int position) {
        int shift = position;
        int idx = (c - 'A' + shift) % 26;
        return rotor[idx];
    }
    
    // Melalui satu rotor (mundur)
    char throughRotorReverse(char c, const string& rotor, int position) {
        int shift = position;
        int idx = rotor.find(c);
        return 'A' + (idx - shift + 26) % 26;
    }
    
    // Enkripsi satu karakter
    char encryptChar(char c) {
        if (!isalpha(c) || !isupper(c)) {
            return c; // Hanya enkripsi huruf besar
        }
        
        rotate(); // Putar rotor setiap kali sebuah karakter diproses
        
        // Melalui rotors dari kanan ke kiri
        char encrypted = c;
        for (int i = 0; i < 3; i++) {
            encrypted = throughRotor(encrypted, rotors[i], rotorPositions[i]);
        }
        
        // Melalui reflector
        int reflectorIdx = encrypted - 'A';
        encrypted = reflector[reflectorIdx];
        
        // Melalui rotors dari kiri ke kanan
        for (int i = 2; i >= 0; i--) {
            encrypted = throughRotorReverse(encrypted, rotors[i], rotorPositions[i]);
        }
        
        return encrypted;
    }
    
    // Enkripsi seluruh string
    string encrypt(const string& message) {
        string result = "";
        
        for (char c : message) {
            if (isalpha(c)) {
                // Konversi ke huruf besar untuk enkripsi
                char upperC = toupper(c);
                result += encryptChar(upperC);
            } else {
                // Pertahankan karakter non-alfabet
                result += c;
            }
        }
        
        return result;
    }
};

int main() {
    int pos1, pos2, pos3;
    string pesan;
    
    cout << "===== PROGRAM ENKRIPSI ENIGMA =====" << endl;
    cout << "Masukkan posisi awal untuk rotor 1 (0-25): ";
    cin >> pos1;
    cout << "Masukkan posisi awal untuk rotor 2 (0-25): ";
    cin >> pos2;
    cout << "Masukkan posisi awal untuk rotor 3 (0-25): ";
    cin >> pos3;
    
    cin.ignore(); // Membersihkan buffer
    
    cout << "Masukkan pesan yang ingin dienkripsi: ";
    getline(cin, pesan);
    
    // Inisialisasi mesin Enigma dengan posisi rotor yang ditentukan
    Enigma enigma(pos1, pos2, pos3);
    
    // Enkripsi pesan
    string encrypted = enigma.encrypt(pesan);
    cout << "Pesan terenkripsi: " << encrypted << endl;
    
    cout << "\nUntuk mendekripsi, gunakan posisi rotor yang sama: " << endl;
    cout << "Rotor 1: " << pos1 << ", Rotor 2: " << pos2 << ", Rotor 3: " << pos3 << endl;
    
    // Inisialisasi mesin Enigma baru untuk dekripsi
    Enigma decryptor(pos1, pos2, pos3);
    
    // Dekripsi pesan (pada mesin Enigma, enkripsi dan dekripsi menggunakan proses yang sama)
    string decrypted = decryptor.encrypt(encrypted);
    cout << "Pesan terdekripsi: " << decrypted << endl;
    
    return 0;
}