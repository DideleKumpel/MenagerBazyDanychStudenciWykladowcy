//
// Created by CEM on 06.03.2024.
//

#include "Tosoba.h"

#include "ObslugaBleduCin.h"

#include <iostream>
#include <string>
#include <iomanip>


using namespace std;


void Tosoba::wpisz() {
    cout<<"Wpisz imie-"; cin>>imie;
    cout<<"Wpisz nazwisko-"; cin>>nazwisko;
    while (true) {
        cout << "Podaj pesel-";
        cin >> pesel;
        if (OBD::ObslugaBleduCinInt(pesel,9999999999,99999999999))
            break;
    }
}

void Tosoba::wypisz() {
    cout<<" | "<<setw(10)<<imie<<" | "<<setw(15)<<nazwisko<<" | "<<setw(13)<<pesel;
}

Tosoba::Tosoba(std::string i, std::string n, int p) {
    imie=i;
    nazwisko=n;
    pesel=p;
}

std::string Tosoba::PodajString(char b)
{
    std::string  a;
    if(b=='i')
        a=imie;
    else if(b=='n')
        a=nazwisko;
    return a;
}
