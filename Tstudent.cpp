//
// Created by CEM on 06.03.2024.
//

#include "Tstudent.h"

#include <iostream>
#include <fstream>
#include <limits>

using namespace std;


long long int Tstudent::id=0;

void Tstudent::wpisz(bool i) {
    Tosoba::wpisz();
    cout<<"Wpisz e-mail-"; cin>>email;
    cout<<"Wpisz kierunek-"; cin>>kierunek;
    cout<<"Podaj grupe wykladowa-"; cin>>grupaW;
    cout<<"Podaj grupe cwiczeniowa-"; cin>>grupaC;
    cout<<"Podaj grupe laboratoryjna-"; cin>>grupaL;
    if(i)
    Pid=id+1;
}

void Tstudent::dodaj()
{
    id++;
}

void Tstudent::wypisz() {
    cout<<"ID "<<Pid;
    Tosoba::wypisz();
    cout<<" E-mial "<<email<<" Kierunek "<<kierunek<<" Grupy W"<<grupaW<<"C"<<grupaC<<"L"<<grupaL<<endl;
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
