#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <cstdbool>
using namespace std;

void UI(){
    cout << "============================\n";
    cout << "\tABSEN MURID-MURID\n";
    cout << "============================\n";
    }
class Siswa{
    public:
        char absen;
    };

int main(){
    int mrd;
    Siswa murid;
    UI();
    cout << "1.Aduy\n";
    cout << "2.Bajigur\n";
    cout << "3.Aca\n";
    cout << "4.Tuktuk\n";
    cout << "5.Patin\n";

    cout << "Murid yang ingin anda pilih : ";cin >> mrd;

switch(mrd){
case 1:
system("cls");
cout << "Apakah aduy hadir? : ";cin >> murid.absen;
if(murid.absen == 'Y'){
    cout <<"\nhadir!!";
    return true;
}
else if(murid.absen == 'T'){
    cout << "\ntidak hadir !!";
    return true;
}
else{
    break;
    return 0;
}

case 2:
system("cls");
cout << "Apakah Bajigur hadir? : ";cin >> murid.absen;
if(murid.absen == 'Y'){
    cout <<"\nhadir!!";
    return true;
}
else if(murid.absen == 'T'){
    cout << "\ntidak hadir !!";
    return true;
}
else{
    break;
    return 0;
}

case 3:
system("cls");
cout << "Apakah Aca hadir? : ";cin >> murid.absen;
if(murid.absen == 'Y'){
    cout <<"\nhadir!!";
    return true;
}
else if(murid.absen == 'T'){
    cout << "\ntidak hadir !!";
    return true;
}
else{
    break;
    return 0;
}

case 4:
system("cls");
cout << "Apakah Tuktuk hadir? : ";cin >> murid.absen;
if(murid.absen == 'Y'){
    cout <<"\nhadir!!";
    return true;
}
else if(murid.absen == 'T'){
    cout << "\ntidak hadir !!";
    return true;
}
else{
    break;
    return 0;
}

case 5:
system("cls");
cout << "Apakah Patin hadir? : ";cin >> murid.absen;
if(murid.absen == 'Y'){
    cout <<"\nhadir!!";
    return true;
}
else if(murid.absen == 'T'){
    cout << "\ntidak hadir !!";
    return true;
}
else{
    break;
    return 0;
}
default:
    cout << "Absen tidak tersedia!";
    break;
}

    }
