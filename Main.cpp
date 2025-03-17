// This is the main program of Dollar converter.
#include "LoginForm.h"

int main() {
    UserSystem system("Acc.txt", "Data.txt");
    int pilihan;
    
    while (true) {
        system.clearScreen();
        cout << "===== SISTEM KONVERSI RUPIAH =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n";
        cout << "Pilihan anda: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                system.registerUser();
                break;
            case 2:
                if (system.login()) {
                    system.mainMenu();
                }
                break;
            case 3:
                cout << "\nTerima kasih telah menggunakan program ini!\n";
                return 0;
            default:
                cout << "\nPilihan tidak valid. Silakan coba lagi.\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
        }
    }
    
    return 0;
}
