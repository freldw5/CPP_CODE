//This is a code that mimic an Enigma machine. Im not built this alone.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


class Enigma {
private:
    
    vector<string> rotors = {
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
        "AJDKSIRUXBLHWTMCQGZNPYFVOE", 
        "BDFHJLCPRTXVZNYEIWGAKMUSQO"  
    };
    
   
    string reflector = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
    
    
    vector<int> rotorPositions;
    
    
    vector<int> notchPositions = {17, 5, 22}; // Q, E, V dalam alfabet 0-indexed
    
public:
    Enigma(int pos1, int pos2, int pos3) {
        rotorPositions = {pos1, pos2, pos3};
    }
    
  
    void rotate() {
        rotorPositions[0] = (rotorPositions[0] + 1) % 26;
        
       
        if (rotorPositions[0] == notchPositions[0]) {
            rotorPositions[1] = (rotorPositions[1] + 1) % 26;
        }
        
      
        if (rotorPositions[1] == notchPositions[1]) {
            rotorPositions[2] = (rotorPositions[2] + 1) % 26;
        }
    }
    
    
    char throughRotor(char c, const string& rotor, int position) {
        int shift = position;
        int idx = (c - 'A' + shift) % 26;
        return rotor[idx];
    }
    
   
    char throughRotorReverse(char c, const string& rotor, int position) {
        int shift = position;
        int idx = rotor.find(c);
        return 'A' + (idx - shift + 26) % 26;
    }
    
   
    char encryptChar(char c) {
        if (!isalpha(c) || !isupper(c)) {
            return c; // Hanya enkripsi huruf besar
        }
        
        rotate(); 
        
      
        char encrypted = c;
        for (int i = 0; i < 3; i++) {
            encrypted = throughRotor(encrypted, rotors[i], rotorPositions[i]);
        }
        
       
        int reflectorIdx = encrypted - 'A';
        encrypted = reflector[reflectorIdx];
        
       
        for (int i = 2; i >= 0; i--) {
            encrypted = throughRotorReverse(encrypted, rotors[i], rotorPositions[i]);
        }
        
        return encrypted;
    }
    
   
    string encrypt(const string& message) {
        string result = "";
        
        for (char c : message) {
            if (isalpha(c)) {
               
                char upperC = toupper(c);
                result += encryptChar(upperC);
            } else {
               
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
    
    cin.ignore();
    
    cout << "Masukkan pesan yang ingin dienkripsi: ";
    getline(cin, pesan);
    
   
    Enigma enigma(pos1, pos2, pos3);
    
   
    string encrypted = enigma.encrypt(pesan);
    cout << "Pesan terenkripsi: " << encrypted << endl;
    
    cout << "\nUntuk mendekripsi, gunakan posisi rotor yang sama: " << endl;
    cout << "Rotor 1: " << pos1 << ", Rotor 2: " << pos2 << ", Rotor 3: " << pos3 << endl;
    
   
    Enigma decryptor(pos1, pos2, pos3);
    
   
    string decrypted = decryptor.encrypt(encrypted);
    cout << "Pesan terdekripsi: " << decrypted << endl;
    
    return 0;
}
