//
// Created by CEM on 06.03.2024.
//

#include "Tstudent.h"
#include "ObslugaBleduCin.h"

#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>

using namespace std;


long long int Tstudent::id=0;

void Tstudent::wpisz(bool i) {
    Tosoba::wpisz();
    cout<<"Wpisz e-mail-"; cin>>email;
    cout<<"Wpisz kierunek-"; cin>>kierunek;
    while(true) {
        cout << "Podaj grupe wykladowa-";
        cin >> grupaW;
        if (OBD::ObslugaBleduCinInt(grupaW,1,999))
            break;
    }
    while (true) {
        cout << "Podaj grupe cwiczeniowa-";
        cin >> grupaC;
        if (OBD::ObslugaBleduCinInt(grupaC,1,999))
            break;
    }
    while (true) {
        cout << "Podaj grupe laboratoryjna-";
        cin >> grupaL;
        if (OBD::ObslugaBleduCinInt(grupaL,1,999))
            break;
    }
    if(i)
    Pid=id+1;
}

void Tstudent::dodaj()
{
    id++;
}

void Tstudent::wypisz() {
    cout<<"|"<<setw(4)<<Pid;
    Tosoba::wypisz();
    cout<<" | "<<setw(40)<<email<<" | "<<setw(14)<<kierunek<<" | W"<<setw(2)<<grupaW<<" C"<<setw(2)<<grupaC<<" L"
    <<setw(2)<<grupaL<<endl;
}

void Tstudent::ZapiszWPliku(string nazwaPliku)
{
    ofstream dane;
    dane.open(nazwaPliku+"S.txt", ios::app);
    if (!dane) {
        cout << "plik nie znaleziony" << endl;
    } else {
            dane<<"Id "<<Pid<<" Imie "<<Tosoba::PodajString('i')<<" Nazwisko "<<
            Tosoba::PodajString('n')<<" Pesel "<<Tosoba::podajPesel()<<" E-mial "<<email<<" Kierunek "
            <<kierunek<<" Grupy W "<<grupaW<<" C "<<grupaC<<" L "<<grupaL<<'\n';
    }
    dane.close();
}

Tstudent::Tstudent(string i, string n, int p, string k, string e, int w, int c, int l) {
    imie=i;
    nazwisko=n;
    pesel=p;
    kierunek=k;
    email=e;
    grupaW=w;
    grupaC=c;
    grupaL=l;
}

void Tstudent::wczytajZPliku(string NazwaPliku) {
    string pomocniczy, z;
    ifstream plik;
    plik.open(NazwaPliku+"S.txt");
    if(plik.fail())
    {
        BladPliku flaga;
        throw flaga;
    }else {
        for (int i = 0; i < id; ++i) {
            plik.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        plik >> z >> id >> z >> imie >> z >> nazwisko >> z >> pesel >> z >> email >> z >> kierunek >> z >> z
             >> grupaW >> z
             >> grupaC >> z >> grupaL;
        Pid=id;
        if (plik.eof()) {
            KoniecPliku flaga;
            throw flaga;
        }
    }
    plik.close();
}

string Tstudent::PodajS(char co) {
    switch (co) {
        case 'i':
            return imie;
        case 'n':
            return nazwisko;
        case 'e':
            return email;
        case 'k':
            return kierunek;
    }
}

long long int Tstudent::PodajN(char Co) {
    switch (Co) {
        case 'I':
            return Pid;
        case 'i':
            return id;
        case 'p':
            return pesel;
        case 'w':
            return grupaW;
        case 'c':
            return grupaC;
        case 'l':
            return grupaL;
    }
    return 0;
}

void Tstudent::Usun(string i, string n, int p, string k, string e, int w, int c, int l) {
    imie=i;
    nazwisko=n;
    pesel=p;
    kierunek=k;
    email=e;
    grupaW=w;
    grupaC=c;
    grupaL=l;
}
