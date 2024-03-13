//
// Created by CEM on 07.03.2024.
//

#include "Twykladowca.h"

#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>

using namespace std;

long long int Twykladowca::id=0;

Twykladowca::Twykladowca(std::string i, std::string n, int p, std::string t, std::string e, std::string w) {
    imie=i;
    nazwisko=n;
    pesel=p;
    tytul=t;
    email=e;
    wydzial=w;
}

void Twykladowca::dodaj() {
    id++;
}

void Twykladowca::wpisz(bool i) {
    Tosoba::wpisz();
    cout<<"Wpisz tytul-"; cin>>tytul;
    cout<<"Wpisz e-mail-"; cin>>email;
    cout<<"Wpisz wydzial-"; cin>>wydzial;
    if(i)
    Pid=id+1;
}

void Twykladowca::wypisz() {
    cout<<"|"<<setw(4)<<Pid;
    Tosoba::wypisz();
    cout<<" | "<<setw(5)<<tytul<<" | "<<setw(40)<<email<<" | "<<setw(14)<<wydzial<<endl;
}

void Twykladowca::ZapiszWPliku(std::string nazwaPliku) {
    ofstream dane;
    dane.open(nazwaPliku+"W.txt", ios::app);
    if (!dane) {
        cout << "plik nie znaleziony" << endl;
    } else {
        dane<<"Id "<<Pid<<" Imie "<<Tosoba::PodajString('i')<<" Nazwisko "<<
            Tosoba::PodajString('n')<<" Pesel "<<Tosoba::podajPesel()<<" Tytul "<<tytul<<" E-mail "<<email<<" Wydzial "<<wydzial<<'\n';
    }
    dane.close();
}

void Twykladowca::wczytajZPliku(std::string NazwaPliku) {
    string pomocniczy, z;
    ifstream plik;
    plik.open(NazwaPliku+"W.txt");
    if(plik.fail())
    {
        BladPliku flaga;
        throw flaga;
    }else {
        for (int i = 0; i < id; ++i) {
            plik.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        plik >> z >> id >> z >> imie >> z >> nazwisko >> z >> pesel >> z >> tytul >> z >> email >> z >> wydzial;
        Pid=id;
        if (plik.eof()) {
            KoniecPliku flaga;
            throw flaga;
        }
    }
    plik.close();
}

std::string Twykladowca::PodajS(char co) {
    switch (co) {
        case 'i':
            return imie;
        case 'n':
            return nazwisko;
        case 't':
            return tytul;
        case 'e':
            return email;
        case 'w':
            return wydzial;

    }
    return 0;
}

long long int Twykladowca::PodajN(char co) {
    switch (co) {
        case 'i':
            return id;
        case 'p':
            return pesel;
    }
}

void Twykladowca::Usun(std::string i, std::string n, int p, std::string t, std::string e, std::string w) {
    imie=i;
    nazwisko=n;
    pesel=p;
    tytul=t;
    email=e;
    wydzial=w;
}
