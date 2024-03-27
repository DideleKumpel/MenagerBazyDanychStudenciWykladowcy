//
// Created by CEM on 27.03.2024.
//
#include "BazaDanychFunkcje.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Tstudent.h"
#include "Twykladowca.h"


using namespace std;


void BDF::UsunBaze(string nazwaBazy, vector<string> NazwyBazDanych)
{
    vector<string> NowaListaBaz;
    char odpowiedz='n';
    cout<<"Czy napewno chcesz usunać baze danych o nazwie "<<nazwaBazy<<"\nt-Tak n-Nie"<<endl;
    cin>>odpowiedz;
    if(odpowiedz=='t')
    {
        string PlikW=nazwaBazy+"W.txt";
        string PlikS=nazwaBazy+"S.txt";
        remove(PlikW.c_str());
        remove(PlikS.c_str());
        for(int i=0; i<NazwyBazDanych.size(); i++)
        {
            if(NazwyBazDanych[i]!=nazwaBazy)
                NowaListaBaz.push_back(NazwyBazDanych[i]);
        }
        ofstream plik;
        plik.open("IstniejaceBazy.txt", ofstream::out | ofstream::trunc);
        if (!plik) {
            cout << "plik nie znaleziony" << endl;
        } else {
            for(int i=0; i<NazwyBazDanych.size(); i++)
                plik<<NowaListaBaz[i]<<" ";
        }
        plik.close();
        cout<<"Baza "<<nazwaBazy<<" zostala usunieta"<<endl;
        system("pause");
        exit(0);
    }
}

string BDF::NowaBaza(vector<string> &nazwyBaz)
{
    string nazwa;
    ofstream dane;
    dane.open("IstniejaceBazy.txt", ios::app);
    if (!dane) {
        cout << "plik nie znaleziony" << endl;
    } else {
        bool poprawnaNazwa= true;
        cout<<"Podaj nazwe nowej bazy:"<<endl;
        while (poprawnaNazwa) {
            cin >> nazwa;
            for (int i = 0; i < nazwyBaz.size(); i++) {
                if (nazwyBaz[i] == nazwa) {
                    cout << "Istnieje juz baza danych o tej nazwie. Wpisz inna nazwe." << endl;
                    poprawnaNazwa= true;
                    break;
                }
                if(i==(nazwyBaz.size()-1))
                    poprawnaNazwa= false;
            }
        }
        dane<<" "<<nazwa;
    }
    dane.close();
    return nazwa;
}

void BDF::WczytajNazwyBaz(vector<string> &nazwyBaz)
{
    string pomocnicza;
    ifstream plik;
    plik.open("IstniejaceBazy.txt");
    if(plik.fail())
    {
        BDF::BrakPliku flaga;
        throw flaga;
    }else {
        while(!plik.eof())
        {
            plik>>pomocnicza;
            nazwyBaz.push_back(pomocnicza);
        }
    }
    plik.close();
}

void BDF::WczytajBaze(vector<Tstudent> &BazaDanych, const string NazwaPliku)
{
    Tstudent pomocnicza;
    while (true)
    {
        try {
            pomocnicza.wczytajZPliku(NazwaPliku);
            BazaDanych.push_back(pomocnicza);
        }
        catch (Tstudent::BladPliku)
        {
            cout<<"Nie znaleziono pliku\n";
            system("pause");
            exit(1);
        }
        catch (Tstudent::KoniecPliku)
        {
            break;
        }
    }
}

void BDF::WczytajBaze(vector<Twykladowca> &BazaDanych, const string NazwaPliku)
{
    Twykladowca pomocnicza;
    while (true)
    {
        try {
            pomocnicza.wczytajZPliku(NazwaPliku);
            BazaDanych.push_back(pomocnicza);
        }
        catch (Twykladowca::BladPliku)
        {
            cout<<"Nie znaleziono pliku\n";
            system("pause");
            exit(1);
        }
        catch (Twykladowca::KoniecPliku)
        {
            break;
        }
    }
}
