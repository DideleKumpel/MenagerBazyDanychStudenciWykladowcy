//
// Created by CEM on 27.03.2024.
//

#ifndef BAZADANYCH_BAZADANYCHFUNKCJE_H
#define BAZADANYCH_BAZADANYCHFUNKCJE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <limits>

#include "ObslugaBleduCin.h"
#include "Tstudent.h"
#include "Twykladowca.h"

using namespace std;

namespace BDF
{
    struct BrakPliku{};
    void UsunBaze(std::string nazwaBazy, std::vector<std::string> NazwyBazDanych);
    void WczytajNazwyBaz(std::vector<std::string> &nazwyBaz);
    std::string NowaBaza(std::vector<std::string> &nazwyBaz);
    void WczytajBaze(std::vector<Tstudent> &BazaDanych, std::string NazwaPliku);
    void WczytajBaze(std::vector<Twykladowca> &BazaDanych, std::string NazwaPliku);
    template<typename typ>
    void ZapiszBaze(vector<typ> &BazaDanych, const  string NazwaPliku)
    {
        for(int i=0; i < BazaDanych.size(); i++)
        {
            BazaDanych[i].ZapiszWPliku(NazwaPliku);
        }
    }

    template<typename typ>
    void WypiszBazeW(vector<typ> &BazaDanych)
    {
        if (typeid(typ) == typeid(Twykladowca)) {
            cout<< "| ID  |    IMIE    |     NAZWISKO    |     PESEL     |  TYTUL |                   E-MAIL                 |     WYDZIAL"<<endl;
            for(int i=0; i<121; i++)
                cout<<"-";
            cout<<endl;
        } else if (typeid(typ) == typeid(Tstudent)) {
            cout<< "| ID  |    IMIE    |     NAZWISKO    |     PESEL     |                   E-MAIL                 |    KIERUNEK    |     GRUPY     "<< endl;
            for(int i=0; i<127; i++)
                cout<<"-";
            cout<<endl;
        }
        for(int i=0; i < BazaDanych.size(); i++)
        {
            if((BazaDanych[i].PodajS('i'))=="-1")
                continue;
            BazaDanych[i].wypisz();
        }
    }

    template<typename typ>
    void WypiszBaze(vector<typ> &BazaDanych)
    {
        bool poprawnaK= true;
        vector<int> listaKomend;
        while(poprawnaK) {
            cout << "Ktore dane wypisac: " << endl;
            if (typeid(typ) == typeid(Twykladowca)) {
                cout << "1.ID  2.IMIE  3.NAZWISKO  4.PESEL  5.TYTUL  6.E-MAIL  7.WYDZIAL" << endl;
            } else if (typeid(typ) == typeid(Tstudent)) {
                cout << "1.ID  2.IMIE  3.NAZWISKO  4.PESEL  5.E-MAIL  6.KIERUNEK  7.GRUPY" << endl;
            }
            cout<<"Wpisz \"w\" aby wypisac wszystkie dane"<<endl;
            cout << "KOMENDE NALEZY PODAC W FORMIE np. \"1,2,3\"" << endl;
            string komenda;
            cin >> komenda;
            if(komenda[0]=='w')
            {
                WypiszBazeW(BazaDanych);
                return;
            }
            for (int i = 0; i < komenda.size(); i = i + 2)
                listaKomend.push_back((int) komenda[i] - 48);
            for (int i = 0; i < listaKomend.size(); i++) {
                if (listaKomend[i] < 0 or listaKomend[i] > 7)
                {
                    cout<<"Zle podnay argumen: "<<i+1<<"\n Prowadz nowa komende"<<endl;
                    system("pause");
                    listaKomend.clear();
                    system("CLS");
                    break;
                }
                if(i==listaKomend.size()-1)
                    poprawnaK= false;
            }
        }
        int dlugoscTabeli=0;
        for(int i = 0; i < listaKomend.size(); i++)
        {
            cout<<"|";
            switch (listaKomend[i]) {
                case 1:
                    cout<<" ID  ";
                    dlugoscTabeli+=6;
                    break;
                case 2:
                    cout<<"    IMIE    ";
                    dlugoscTabeli+=13;
                    break;
                case 3:
                    cout<<"     NAZWISKO    ";
                    dlugoscTabeli+=18;
                    break;
                case 4:
                    cout<<"     PESEL     ";
                    dlugoscTabeli+=16;
                    break;
                case 5:
                    if (typeid(typ) == typeid(Twykladowca)) {
                        cout<<" TYTUL ";
                        dlugoscTabeli+=8;
                    }else if (typeid(typ) == typeid(Tstudent)) {
                        cout<<"                   E-MAIL                 ";
                        dlugoscTabeli+=43;
                    }
                    break;
                case 6:
                    if (typeid(typ) == typeid(Twykladowca)) {
                        cout<<"                   E-MAIL                 ";
                        dlugoscTabeli+=43;
                    }else if (typeid(typ) == typeid(Tstudent)) {
                        cout<<"    KIERUNEK    ";
                        dlugoscTabeli+=17;
                    }
                    break;
                case 7:
                    if (typeid(typ) == typeid(Twykladowca)) {
                        cout<<"     WYDZIAL";
                        dlugoscTabeli+=17;
                    }else if (typeid(typ) == typeid(Tstudent)) {
                        cout<<"     GRUPY     ";
                        dlugoscTabeli+=17;
                    }
            }
        }
        cout<<endl;
        for(int i=0; i<dlugoscTabeli; i++)
            cout<<"-";
        cout<<endl;
        for(int k=0; k<BazaDanych.size(); k++)
        {
            if(BazaDanych[k].PodajS('i')=="-1")
                continue;
            cout<<"|";
            for(int i = 0; i < listaKomend.size(); i++)
            {
                switch (listaKomend[i]) {
                    case 1:
                        cout<<setw(4)<<BazaDanych[k].PodajN('I');
                        break;
                    case 2:
                        cout<<setw(10)<<BazaDanych[k].PodajS('i');
                        break;
                    case 3:
                        cout<<setw(15)<<BazaDanych[k].PodajS('n');
                        break;
                    case 4:
                        cout<<setw(13)<<BazaDanych[k].PodajN('p');
                        break;
                    case 5:
                        if (typeid(typ) == typeid(Twykladowca)) {
                            cout<<setw(5)<<BazaDanych[k].PodajS('t');
                        }else if (typeid(typ) == typeid(Tstudent)) {
                            cout<<setw(40)<<BazaDanych[k].PodajS('e');
                        }
                        break;
                    case 6:
                        if (typeid(typ) == typeid(Twykladowca)) {
                            cout<<setw(40)<<BazaDanych[k].PodajS('e');
                        }else if (typeid(typ) == typeid(Tstudent)) {
                            cout<<setw(14)<<BazaDanych[k].PodajS('k');
                        }
                        break;
                    case 7:
                        if (typeid(typ) == typeid(Twykladowca)) {
                            cout<<setw(14)<<BazaDanych[k].PodajS('w');
                        }else if (typeid(typ) == typeid(Tstudent)) {
                            cout<<"W"<<setw(2)<<BazaDanych[k].PodajN('w')<<" C"<<setw(2)<<BazaDanych[k].PodajN('c')<<" L"
                                <<setw(2)<<BazaDanych[k].PodajN('l');
                        }
                }
                if(i!=0 or i!=listaKomend.size()-1)
                    cout<<" | ";
            }
            cout<<endl;
        }
    }

    template<typename typ>
    void DodajWpis(vector<typ> &BazaDanych, const string NazwaPliku)
    {
        char petla='t';
        while(petla=='t') {
            typ pomocnicza;
            pomocnicza.wpisz();
            pomocnicza.wypisz();
            cout << "Czy chcesz dodac ten wpis do bazy danych (t-Tak n-Nie)\n";
            char odpowiedz;
            cin >> odpowiedz;
            if (odpowiedz == 't' or odpowiedz == 'T') {
                pomocnicza.dodaj();
                BazaDanych.push_back(pomocnicza);
                pomocnicza.ZapiszWPliku(NazwaPliku);
            }
            cout << "Czy chcesz dokonac nowego wpisu dane? (t-Tak n-Nie)\n";
            char odpowiedz2;
            cin >> odpowiedz2;
            if(odpowiedz2=='t' or odpowiedz2=='T')
                continue;
            else
                break;
        }
    }

    template<typename typ>
    void UsunWpis(vector<typ> &BazaDanych, const string NazwaPliku)
    {
        long long int Nrwpisu;
        cout<<"Podaj numer Id wpisu ktory chcesz usunac-"; cin>>Nrwpisu;
        cout<<"Czy napewno chcesz usunac wpis: (t-Tak, n-Nie)\n";
        BazaDanych[Nrwpisu-1].wypisz();
        char decyzja='n';
        cin>>decyzja;
        if(decyzja=='t' or decyzja=='T')
        {
            typ pomocznia=BazaDanych[Nrwpisu-1];
            pomocznia.Usun();
            BazaDanych[Nrwpisu-1]=pomocznia;
            if(typeid(typ)== typeid(Twykladowca))
            {
                ofstream plik;
                plik.open(NazwaPliku+"W.txt", ofstream::out | ofstream::trunc);
                plik.close();
            }
            else if(typeid(typ)== typeid(Tstudent))
            {
                ofstream plik;
                plik.open(NazwaPliku+"S.txt", ofstream::out | ofstream::trunc);
                plik.close();
            }
            ZapiszBaze(BazaDanych, NazwaPliku);
        }
    }

    template<typename typ>
    void szukajString(vector<typ> &BazaDanych, char dana, const string &filtr,const string &wartosc)
    {
        if(filtr=="="){
            for(int i=0; i<BazaDanych.size(); i++) {
                if (BazaDanych[i].PodajS(dana) != wartosc)
                    BazaDanych[i].Usun();
            }
        } else if(filtr=="!="){
            for(int i=0; i<BazaDanych.size(); i++) {
                if (BazaDanych[i].PodajS(dana) == wartosc)
                    BazaDanych[i].Usun();
            }
        } else if(filtr=="p"){
            for(int i=0; i<BazaDanych.size(); i++) {
                int gdzie=BazaDanych[i].PodajS(dana).find(wartosc);
                if(gdzie!=0)
                    BazaDanych[i].Usun();
            }
        } else if(filtr=="s"){
            for(int i=0; i<BazaDanych.size(); i++) {
                int gdzie=BazaDanych[i].PodajS(dana).find(wartosc,1);
                if(gdzie==-1 or gdzie==0 or gdzie+wartosc.size()==BazaDanych[i].PodajS(dana).size())
                    BazaDanych[i].Usun();
            }
        } else if(filtr=="k"){
            for(int i=0; i<BazaDanych.size(); i++) {
                int gdzie=BazaDanych[i].PodajS(dana).find(wartosc,1);
                if(gdzie==-1 or gdzie==0 or gdzie+wartosc.size()!=BazaDanych[i].PodajS(dana).size())
                    BazaDanych[i].Usun();
            }
        }
    }

    template<typename typ>
    void szukajInt(vector<typ> &BazaDanych, char dana, const string &filtr,const string &wartosc)
    {
        long long int wartoscInt= stoll(wartosc);
        if(filtr=="="){
            for(int i=0; i<BazaDanych.size(); i++) {
                if(BazaDanych[i].PodajN(dana)!=wartoscInt)
                    BazaDanych[i].Usun();
            }
        } else if(filtr=="!="){
            for(int i=0; i<BazaDanych.size(); i++) {
                if(BazaDanych[i].PodajN(dana)==wartoscInt)
                    BazaDanych[i].Usun();
            }
        } else if(filtr==">"){
            for(int i=0; i<BazaDanych.size(); i++) {
                if(BazaDanych[i].PodajN(dana)<=wartoscInt)
                    BazaDanych[i].Usun();
            }
        } else if(filtr==">="){
            for(int i=0; i<BazaDanych.size(); i++) {
                if(BazaDanych[i].PodajN(dana)<wartoscInt)
                    BazaDanych[i].Usun();
            }
        } else  if(filtr=="<"){
            for(int i=0; i<BazaDanych.size(); i++) {
                if(BazaDanych[i].PodajN(dana)>=wartoscInt)
                    BazaDanych[i].Usun();
            }
        } else  if(filtr=="<="){
            for(int i=0; i<BazaDanych.size(); i++) {
                if(BazaDanych[i].PodajN(dana)>wartoscInt)
                    BazaDanych[i].Usun();
            }
        }
    }

    template<typename typ>
    void Szukaj(vector<typ>BazaDanych) {
        system("CLS");
        string komenda;
        vector<int> listaKomend;
        bool poprawnaK = true;
        while (poprawnaK) {
            if (typeid(typ) == typeid(Twykladowca))
                cout << "Indeks danych 1.ID 2.IMIE 3.NAZWISKO 4.PESEL 5.TYTUL 6.E-MAIL 7.WYDZIAL" << endl;
            if (typeid(typ) == typeid(Tstudent))
                cout << "Indeks danych: 1.ID 2.IMIE 3.NAZWISKO 4.PESEL 5.E-MAIL 6.KIERUNEK 7.GRUPA W 8.GRUPA C 9.GRUPA C"
                     << endl;
            cout << "KOMENDE NALEZY PODAC W FORMIE np. \"1,2,3\"" << endl;
            string komnda;
            cin >> komenda;
            for (int i = 0; i < komenda.size(); i = i + 2)
                listaKomend.push_back((int) komenda[i] - 48);
            for (int i = 0; i < listaKomend.size(); i++) {
                if (typeid(typ) == typeid(Twykladowca)) {
                    if (listaKomend[i] > 7 or listaKomend[i] < 1) {
                        cout << "Wpisano liczbe z poza zakresu. Prowac dane ponownie" << endl;
                        system("pause");
                        system("CLS");
                        listaKomend.clear();
                        continue;
                    }
                } else if (typeid(typ) == typeid(Tstudent)) {
                    if (listaKomend[i] > 9 or listaKomend[i] < 1) {
                        cout << "Wpisano liczbe z poza zakresu. Prowac dane ponownie" << endl;
                        system("pause");
                        system("CLS");
                        listaKomend.clear();
                        continue;
                    }
                }
                if (i == listaKomend.size() - 1)
                    poprawnaK = false;
            }
        }
        poprawnaK = true;
        while (poprawnaK) {
            for (int i = 0; i < listaKomend.size(); i++) {
                string kryterium, filtr, wartosc;
                while (true) {
                    system("CLS");
                    cout << "Wpisz \"h\" aby wyswietlic liste kryteriow." << endl;
                    if (typeid(typ) == typeid(Twykladowca)) {
                        string zmiennaT[]{"ID", "IMIE", "NAZWISKO", "PESEL", "TYTYL", "E-MAIL", "WYDZIAL"};
                        cout << "Podaj kryterium szukania dla " << zmiennaT[listaKomend[i] - 1] << endl;
                    }
                    if (typeid(typ) == typeid(Tstudent)) {
                        string zmiennaT[]{"ID", "IMIE", "NAZWISKO", "PESEL", "E-MAIL", "KIERUNEK", "GRUPA W", "GRUPA C",
                                          "GRUPA L"};
                        cout << "Podaj kryterium szukania dla " << zmiennaT[listaKomend[i] - 1] << endl;
                    }
                    cin >> kryterium;
                    if (kryterium == "h") {
                        int ktore = 0;
                        while (true) {
                            system("CLS");
                            cout << "1. Komendy dla danych tekstowych." << endl;
                            cout << "2. Komendy dla danych liczbowych." << endl;
                            cout << "3. Wroc" << endl;
                            cin >> ktore;
                            if (!OBD::ObslugaBleduCinInt(ktore, 1, 3)) {
                                continue;
                            }
                            switch (ktore) {
                                case 1:
                                    system("CLS");
                                    cout
                                            << "\"=\"-rowne \n\"!=\"-rozne \n\"tekst%\"-zaczyna sie od \"tekst\"\n\"%tekst\"-konczy sie na \"teskt\"\n\"%tekst%\"-zawiera w srodku \"tekst\""
                                            << endl;
                                    system("pause");
                                    break;
                                case 2:
                                    system("CLS");
                                    cout
                                            << "\"=liczba\"-rowne \"liczba\"\n\"!=liczba\"-rozne od \"liczba\"\n\"<liczba\"-mniejsze od \"liczba\"\n\"<=liczba\"-mniejsze rowne od \"liczba\"\n\">liczba\"-wieksze od \"liczba\"\n\">=liczba\"-wieksze rowne od \"liczba\""
                                            << endl;
                                    system("pause");
                                    break;
                            }
                            if (ktore == 3) {
                                i -= 1;
                                break;
                            }
                        }
                    } else if (typeid(typ) == typeid(Twykladowca)) {
                        if (listaKomend[i] == 1 or listaKomend[i] == 4) {
                            if ((kryterium[0] == '!' and kryterium[1]=='=' )or (kryterium[0] == '<' and kryterium[1] == '=' )or (kryterium[0] == '>' and kryterium[1] == '=' )) {
                                filtr.insert(0, kryterium, 0, 2);
                                wartosc.insert(0, kryterium, 2);
                            } else if (kryterium[0] == '=' or kryterium[0] == '<' or kryterium[0] == '>'){
                                filtr.insert(0, kryterium, 0, 1);
                                wartosc.insert(0, kryterium, 1);
                            } else{
                                cout << "Zla forma komendy. Wpisz nowa komende" << endl;
                                system("pause");
                                continue;
                            }
                        }
                        else if (listaKomend[i] == 2 or listaKomend[i] == 3 or listaKomend[i] == 5 or listaKomend[i] == 6 or
                                 listaKomend[i] == 7) {
                            long long int miejsce1 = -1, miejsce2 = -1;
                            if (kryterium[0] == '=') {
                                filtr = "=";
                                wartosc.insert(0, kryterium, 1);
                            } else if (kryterium[0] == '=' or kryterium[0] == '<' or kryterium[0] == '>') {
                                filtr = "!=";
                                wartosc.insert(0, kryterium, 2);
                            } else {
                                miejsce1 = kryterium.find('%');
                                miejsce2 = kryterium.find('%', kryterium.size() - 1);
                                if (miejsce1 == 0 and miejsce2 == -1) {
                                    filtr = "k";
                                    wartosc.insert(0, kryterium, 1);
                                } else if (miejsce2 == kryterium.size() - 1 and miejsce1 == kryterium.size() - 1) {
                                    filtr = "p";
                                    wartosc.insert(0, kryterium);
                                    wartosc.resize(wartosc.size() - 1);
                                } else if (miejsce1 == 0 and miejsce2 == kryterium.size() - 1) {
                                    filtr = "s";
                                    wartosc.insert(0, kryterium, 1);
                                    wartosc.resize(wartosc.size() - 1);
                                } else {
                                    cout << "Zla forma komendy. Wpisz nowa komende" << endl;
                                    system("pause");
                                    continue;
                                }
                            }
                        }
                    } else if (typeid(typ) == typeid(Tstudent)) {
                        if (listaKomend[i] == 1 or listaKomend[i] == 4 or listaKomend[i] == 7 or listaKomend[i] == 8 or
                            listaKomend[i] == 9) {
                            if ((kryterium[0] == '!' and kryterium[1]=='=' )or (kryterium[0] == '<' and kryterium[1] == '=' )or (kryterium[0] == '>' and kryterium[1] == '=' )) {
                                filtr.insert(0, kryterium, 0, 2);
                                wartosc.insert(0, kryterium, 2);
                            } else if (kryterium[0] == '=' or kryterium[0] == '<' or kryterium[0] == '>'){
                                filtr.insert(0, kryterium, 0, 1);
                                wartosc.insert(0, kryterium, 1);
                            } else{
                                cout << "Zla forma komendy. Wpisz nowa komende" << endl;
                                system("pause");
                                continue;
                            }
                        }
                        else if (listaKomend[i] == 2 or listaKomend[i] == 3 or listaKomend[i] == 5 or listaKomend[i] == 6) {
                            int miejsce1 = -1, miejsce2 = -1;
                            if (kryterium[0] == '=') {
                                filtr = "=";
                                wartosc.insert(0, kryterium, 1);
                            } else if (kryterium[0] == '!' and kryterium[1] == '=') {
                                filtr = "!=";
                                wartosc.insert(0, kryterium, 2);
                            } else {
                                miejsce1 = kryterium.find('%');
                                miejsce2 = kryterium.find('%', kryterium.size() - 1);
                                if (miejsce1 == 0 and miejsce2 == -1) {
                                    filtr = "k";
                                    wartosc.insert(0, kryterium, 1);
                                } else if (miejsce2 == kryterium.size() - 1 and miejsce1 == kryterium.size() - 1) {
                                    filtr = "p";
                                    wartosc.insert(0, kryterium);
                                    wartosc.resize(wartosc.size() - 1);
                                } else if (miejsce1 == 0 and miejsce2 == kryterium.size() - 1) {
                                    filtr = "s";
                                    wartosc.insert(0, kryterium, 1);
                                    wartosc.resize(wartosc.size() - 1);
                                } else {
                                    cout << "Zla forma komendy. Wpisz nowa komende" << endl;
                                    system("pause");
                                    continue;
                                }
                            }
                        }
                    }
                    break;
                }
                if (typeid(typ) == typeid(Twykladowca)) {
                    switch (listaKomend[i]) {
                        case 1:
                            szukajInt(BazaDanych, 'I', filtr, wartosc);
                            break;
                        case 2:
                            szukajString(BazaDanych, 'i', filtr, wartosc);
                            break;
                        case 3:
                            szukajString(BazaDanych, 'n', filtr, wartosc);
                            break;
                        case 4:
                            szukajInt(BazaDanych, 'p', filtr, wartosc);
                            break;
                        case 5:
                            szukajString(BazaDanych, 't', filtr, wartosc);
                            break;
                        case 6:
                            szukajString(BazaDanych, 'e', filtr, wartosc);
                            break;
                        case 7:
                            szukajString(BazaDanych, 'w', filtr, wartosc);
                            break;
                    }
                } else if (typeid(typ) == typeid(Tstudent)) {
                    switch (listaKomend[i]) {
                        case 1:
                            szukajInt(BazaDanych, 'I', filtr, wartosc);
                            break;
                        case 2:
                            szukajString(BazaDanych, 'i', filtr, wartosc);
                            break;
                        case 3:
                            szukajString(BazaDanych, 'n', filtr, wartosc);
                            break;
                        case 4:
                            szukajInt(BazaDanych, 'p', filtr, wartosc);
                            break;
                        case 5:
                            szukajString(BazaDanych, 'e', filtr, wartosc);
                            break;
                        case 6:
                            szukajString(BazaDanych, 'k', filtr, wartosc);
                            break;
                        case 7:
                            szukajInt(BazaDanych, 'w', filtr, wartosc);
                            break;
                        case 8:
                            szukajInt(BazaDanych, 'c', filtr, wartosc);
                            break;
                        case 9:
                            szukajInt(BazaDanych, 'l', filtr, wartosc);
                            break;
                    }
                }
                wartosc.clear();
                filtr.clear();
            }
            break;
        }
        WypiszBaze(BazaDanych);
        system("pause");
    }

    template<typename typ>
    void Edytuj(vector<typ> &BazaDanych, const string NazwaPliku) {
        long long int NrWpisu;
        char nadpisac = 'n', petla = 't';
        typ pomocnicza;
        WypiszBaze(BazaDanych);
        while (petla=='t'){
            cout << "Podaj id wpisu do edytowania-";
            cin >> NrWpisu;
            pomocnicza=BazaDanych[NrWpisu - 1];
            pomocnicza.wpisz(0);
            pomocnicza.wypisz();
            cout << "Czy chcesz tym danpisac dane:" << endl;
            BazaDanych[NrWpisu - 1].wypisz();
            cout << "t-Tak n-Nie" << endl;
            cin >> nadpisac;
            if (nadpisac == 't' or nadpisac == 'T') {
                BazaDanych[NrWpisu - 1] = pomocnicza;
                if(typeid(typ)== typeid(Twykladowca))
                {
                    ofstream plik;
                    plik.open(NazwaPliku+"W.txt", ofstream::out | ofstream::trunc);
                    plik.close();
                }
                else if(typeid(typ)== typeid(Tstudent))
                {
                    ofstream plik;
                    plik.open(NazwaPliku+"S.txt", ofstream::out | ofstream::trunc);
                    plik.close();
                }
                ZapiszBaze(BazaDanych, NazwaPliku);
            }
            cout << "Czy nadal chcesz edytowac dane? (t-Tak, n-Nie)" << endl;
            cin >> petla;
        }
    }

    template <typename typ>
    void SortujLiczby(vector<typ> &BazaDanych, char zmienna, bool kolejnosc)
    {
        typ pomocna;
        if(kolejnosc) {
            for (int i = 0; i < BazaDanych.size(); i++) {
                for (int j = i; j < BazaDanych.size(); j++) {
                    if (BazaDanych[i].PodajN(zmienna) > BazaDanych[j].PodajN(zmienna)) {
                        pomocna = BazaDanych[i];
                        BazaDanych[i] = BazaDanych[j];
                        BazaDanych[j] = pomocna;
                        i = 0;

                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < BazaDanych.size(); i++) {
                for (int j = i; j < BazaDanych.size(); j++) {
                    if (BazaDanych[i].PodajN(zmienna) < BazaDanych[j].PodajN(zmienna)) {
                        pomocna = BazaDanych[i];
                        BazaDanych[i] = BazaDanych[j];
                        BazaDanych[j] = pomocna;
                        i = 0;

                    }
                }
            }
        }
    }

    template <typename typ>
    void SortujString(vector<typ> &BazaDanych, char zmienna, bool kolejnosc)
    {
        typ pomocnaT;
        string pomocnicza1, pomocnicza2;
        int dlugosc1, dlugosc2;
        if(kolejnosc) {
            for (int i = 0; i < BazaDanych.size(); i++) {
                for (int j = i; j < BazaDanych.size(); j++) {
                    dlugosc1 = (BazaDanych[i].PodajS(zmienna)).length();
                    dlugosc2 = (BazaDanych[j].PodajS(zmienna)).length();
                    if (dlugosc1 < dlugosc2)
                        dlugosc1 = dlugosc2;
                    for (int k = 0; k < dlugosc1; k++) {
                        if ((BazaDanych[i].PodajS(zmienna))[k] == (BazaDanych[j].PodajS(zmienna))[k]) {
                            continue;
                        } else if ((BazaDanych[i].PodajS(zmienna))[k] < (BazaDanych[j].PodajS(zmienna))[k]) {
                            break;
                        }
                        if ((BazaDanych[i].PodajS(zmienna))[k] > (BazaDanych[j].PodajS(zmienna))[k]) {
                            pomocnaT = BazaDanych[i];
                            BazaDanych[i] = BazaDanych[j];
                            BazaDanych[j] = pomocnaT;
                            i = 0;
                            break;
                        }
                    }
                }
            }
        }else{
            for (int i = 0; i < BazaDanych.size(); i++) {
                for (int j = i; j < BazaDanych.size(); j++) {
                    dlugosc1 = (BazaDanych[i].PodajS(zmienna)).length();
                    dlugosc2 = (BazaDanych[j].PodajS(zmienna)).length();
                    if (dlugosc1 < dlugosc2)
                        dlugosc1 = dlugosc2;
                    for (int k = 0; k < dlugosc1; k++) {
                        if ((BazaDanych[i].PodajS(zmienna))[k] == (BazaDanych[j].PodajS(zmienna))[k]) {
                            continue;
                        } else if ((BazaDanych[i].PodajS(zmienna))[k] > (BazaDanych[j].PodajS(zmienna))[k]) {
                            break;
                        }
                        if ((BazaDanych[i].PodajS(zmienna))[k] < (BazaDanych[j].PodajS(zmienna))[k]) {
                            pomocnaT = BazaDanych[i];
                            BazaDanych[i] = BazaDanych[j];
                            BazaDanych[j] = pomocnaT;
                            i = 0;
                            break;
                        }
                    }
                }
            }
        }
    }

    template<typename typ>
    void Sortuj(vector<typ> BazaDanych) {
        int NazwaDanej, sposob;
        while (true){
            while (true) {
                if (typeid(typ) == typeid(Twykladowca))
                    cout << "Indeks danych: 1.IMIE 2.NAZWISKO 3.PESEL 4.TYTUL 5.WYDZIAL" << endl;
                else if (typeid(typ) == typeid(Tstudent))
                    cout << "Indeks danych: 1.IMIE 2.NAZWISKO 3.PESEL 4.KIERUNEK 5.GRUPA W 6.GRUPA C 7.GRUPA L" << endl;
                cout << "Podaj liczbe odpowiadjaca numerowi danej wedlug ktorej ma odbyc sie sortowanie" << endl;
                cin >> NazwaDanej;
                try {
                    OBD::ObslugaBleduCin();
                }
                catch (OBD::BladCin)
                {
                    continue;
                }
                if (typeid(typ) == typeid(Twykladowca)) {
                    if(NazwaDanej>5 or NazwaDanej<1)
                    {
                        cout<<"Wpisano liczbe z poza zakresu. Prowac dane ponownie"<<endl;
                        system("pause");
                        system("CLS");
                        continue;
                    }
                } else if (typeid(typ) == typeid(Tstudent)) {
                    if(NazwaDanej>7 or NazwaDanej<0)
                    {
                        cout<<"Wpisano liczbe z poza zakresu. Prowac dane ponownie"<<endl;
                        system("pause");
                        system("CLS");
                        continue;
                    }
                }
                break;
            }
            while(true) {
                cout << "Podaj sposob sortowania: 1.ROSNACO 2.MALEJACO" << endl;
                cin >> sposob;
                if(cin.fail())
                {
                    cout<<"Nalezy pisac liczbe. Prowadz dane ponownie"<<endl;
                    system("pause");
                    system("CLS");
                    cin.clear();
                    cin.ignore();
                    cin.ignore( std::numeric_limits < std::streamsize >::max(), '\n' );
                    continue;
                }
                if(sposob>2 or sposob<1)
                {
                    cout<<"Wpisano liczbe z poza zakresu. Wprowac dane ponownie"<<endl;
                    system("pause");
                    system("CLS");
                    continue;
                }
                break;
            }
            bool koljenosc;
            if(sposob==1)
                koljenosc= true;
            else
                koljenosc= false;
            cout << "Posortowane: " << endl;
            switch (NazwaDanej) {
                case 1:
                    SortujString(BazaDanych, 'i', koljenosc);
                    WypiszBaze(BazaDanych);
                    break;
                case 2:
                    SortujString(BazaDanych, 'n', koljenosc);
                    WypiszBaze(BazaDanych);
                    break;
                case 3:
                    SortujLiczby(BazaDanych, 'p', koljenosc);
                    WypiszBaze(BazaDanych);
                    break;
                case 4:
                    if (typeid(typ) == typeid(Twykladowca)) {
                        SortujString(BazaDanych, 't', koljenosc);
                        WypiszBaze(BazaDanych);
                    } else if (typeid(typ) == typeid(Tstudent)) {
                        SortujString(BazaDanych, 'k', koljenosc);
                        WypiszBaze(BazaDanych);
                    }
                    break;
                case 5:
                    if (typeid(typ) == typeid(Twykladowca)) {
                        SortujString(BazaDanych, 'w', koljenosc);
                        WypiszBaze(BazaDanych);
                    } else if (typeid(typ) == typeid(Tstudent)) {
                        SortujLiczby(BazaDanych, 'w', koljenosc);
                        WypiszBaze(BazaDanych);
                    }
                    break;
                case 6:
                    SortujLiczby(BazaDanych, 'c', koljenosc);
                    WypiszBaze(BazaDanych);
                    break;
                case 7:
                    SortujLiczby(BazaDanych, 'l', koljenosc);
                    WypiszBaze(BazaDanych);
                    break;
                default:
                    cout << "Zle podana dana" << endl;
                    system("pause");
                    continue;
            }
            break;
        }
        system("pause");
    }


}
#endif //BAZADANYCH_BAZADANYCHFUNKCJE_H
