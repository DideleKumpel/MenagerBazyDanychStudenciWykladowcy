#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

#include "Tstudent.h"
#include "Twykladowca.h"


using namespace std;

template<typename typ>
void menu2(vector<typ> &BazaDanych, const string NazwaPliku);
void WczytajNazwyBaz(vector<string> &nazwyBaz);
string NowaBaza(vector<string> &nazwyBaz);
void WczytajBaze(vector<Tstudent> &BazaDanych, const string NazwaPliku);
void WczytajBaze(vector<Twykladowca> &BazaDanych, string NazwaPliku);
template<typename typ>
void ZapiszBaze(vector<typ> &BazaDanych, string NazwaPliku);
template<typename typ>
void WypiszBaze(vector<typ> &BazaDanych);
template<typename typ>
void DodajWpis(vector<typ> &BazaDanych,const string NazwaPliku);
template<typename typ>
void UsunWpis(vector<typ> &BazaDanych, const string NazwaPliku);
template<typename typ>
void Szukaj(vector<typ>BazaDanych);
template<typename typ>
void Edytuj(vector<typ> &BazaDanych, const string NazwaPliku);
template<typename typ>
void Sortuj(vector<typ> BazaDanych);
template <typename typ>
void SortujLiczby(vector<typ> &BazaDanych, char zmienna);
template <typename typ>
void SortujString(vector<typ> &BazaDanych, char zmienna);

struct BrakPliku{};
struct KoniecPliku{};

int main() {
    vector<string> NazwyBazDanych;
    vector<Tstudent> studenci;
    vector<Twykladowca> wykladowcy;
    bool CzyWczytany=1;
    string nazwaBazy;
    try {
        WczytajNazwyBaz(NazwyBazDanych);
        cout<<"Wczytane bazy:"<<endl;
        for(int i=0; i < NazwyBazDanych.size(); i++)
        {
            cout<<i+1<<". "<<NazwyBazDanych[i]<<" ";
            if(!((i+1)%10) and i!=0)
                cout<<endl;
            if(i==NazwyBazDanych.size()-1)
                cout<<endl;
        }
    } catch (BrakPliku)
    {
        CzyWczytany=0;
        char decyzja='n';
        cout<<"Nie znalozniono spisu istniejacych bazdanych. Czy chcesz kontynulowac? (t-Tak, n-Nie)"<<endl;
        cin>>decyzja;
        if(decyzja!='t')
            return 0;
    }
    while(true) {
        int menu1;
        cout << "Wpisz cyfre odpowiadjaca numerowi opcji." << endl;
        cout << "1. Stworz nowa baze danych" << endl;
        if (CzyWczytany) {
            cout << "2. Wczytaj isniejaca baze" << endl;
        }
        cout << "3. Zamnkij program" << endl;
        cin >> menu1;
        ofstream dane;
        system("CLS");
        switch (menu1) {
            case 1:
                nazwaBazy = NowaBaza(NazwyBazDanych);
                dane.open(nazwaBazy+"S.txt");
                dane.close();
                dane.open(nazwaBazy+"W.txt");
                dane.close();
                break;
            case 2:
                cout << "Wczytane bazy:" << endl;
                for (int i = 0; i < NazwyBazDanych.size(); i++) {
                    cout << i + 1 << ". " << NazwyBazDanych[i] << " ";
                    if (!((i + 1) % 10) and i != 0)
                        cout << endl;
                    if (i == NazwyBazDanych.size() - 1)
                        cout << endl;
                }
                cout << "Podaj numer bazy do wczytania" << endl;
                int numer;
                cin >> numer;
                nazwaBazy = NazwyBazDanych[numer - 1];
                break;
            case 3:
                return 0;
        }
        system("CLS");
        WczytajBaze(studenci, nazwaBazy);
        WczytajBaze(wykladowcy, nazwaBazy);
        while (true) {
            int odpowiedz;
            cout << "1. Pracuj na spisie studnetow \n2. Pracuj na spisie wykladowcow \n3. Zamknij program" << endl<< endl;
            cin >> odpowiedz;
            system("CLS");
            switch (odpowiedz) {
                case 1:
                    menu2(studenci, nazwaBazy);
                    break;
                case 2:
                    menu2(wykladowcy, nazwaBazy);
                    break;
                case 3:
                    return 0;
            }
            system("CLS");
        }
    }
    return 0;
}

template<typename typ>
void menu2(vector<typ> &BazaDanych, const string NazwaPliku)
{
    int odpowiedz;
    while (true)
    {
        cout<< "Wybierz operacje \n1. Wypisz baze\n2. Dodaj wpis\n3. Usun wpis\n4. Edyduj dane\n5. "
               "Szukaj danych\n6. Sortuj\n7. Wyczysc ekran\n8. Wroc do wyboru bazy danych"
                << endl;
        cin >> odpowiedz;
        switch (odpowiedz) {
            case 1:
                WypiszBaze(BazaDanych);
                system("pause");
                break;
            case 2:
                DodajWpis(BazaDanych, NazwaPliku);
                break;
            case 3:
                UsunWpis(BazaDanych, NazwaPliku);
                break;
            case 4:
                Edytuj(BazaDanych, NazwaPliku);
                break;
            case 5:
                Szukaj(BazaDanych);
                break;
            case 6:
                Sortuj(BazaDanych);
                break;
            case 7:
                system("CLS");
                break;
            case 8:
                return;
        }
    }
}

string NowaBaza(vector<string> &nazwyBaz)
{
    string nazwa;
    ofstream dane;
    dane.open("IstniejaceBazy.txt", ios::app);
    if (!dane) {
    cout << "plik nie znaleziony" << endl;
    } else {
        bool poprawnaNazwa=1;
        cout<<"Podaj nazwe nowej bazy:"<<endl;
        while (poprawnaNazwa) {
            cin >> nazwa;
            for (int i = 0; i < nazwyBaz.size(); i++) {
                if (nazwyBaz[i] == nazwa) {
                    cout << "Istnieje juz baza danych o tej nazwie. Wpisz inna nazwe." << endl;
                    poprawnaNazwa=1;
                    break;
                }
                if(i==(nazwyBaz.size()-1))
                    poprawnaNazwa=0;
            }
    }
        dane<<" "<<nazwa;
}
dane.close();
    return nazwa;
}

void WczytajNazwyBaz(vector<string> &nazwyBaz)
{
    string pomocnicza;
    ifstream plik;
    plik.open("IstniejaceBazy.txt");
    if(plik.fail())
    {
    BrakPliku flaga;
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

void WczytajBaze(vector<Tstudent> &BazaDanych, const string NazwaPliku)
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
            //BazaDanych.push_back(pomocnicza);
            break;
        }
    }
}

void WczytajBaze(vector<Twykladowca> &BazaDanych, const string NazwaPliku)
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

template<typename typ>
void ZapiszBaze(vector<typ> &BazaDanych, const  string NazwaPliku)
{
    for(int i=0; i < BazaDanych.size(); i++)
    {
        BazaDanych[i].ZapiszWPliku(NazwaPliku);
    }
}

template<typename typ>
void WypiszBaze(vector<typ> &BazaDanych)
{
    if (typeid(typ) == typeid(Twykladowca)) {
        cout<< "| ID  |    IMIE    |     NAZWISKO    |     PESEL     | TYTUL |                   E-MAIL                 |    KIERUNEK"<<endl;
        for(int i=0; i<120; i++)
            cout<<"-";
        cout<<endl;
    }
        else if (typeid(typ) == typeid(Tstudent)) {
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
void DodajWpis(vector<typ> &BazaDanych, const string NazwaPliku)
{
    char petla='t';
    while(petla='t') {
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
void Szukaj(vector<typ>BazaDanych)
{
    string NazwaDanej;
    while (true) {
        if (typeid(typ) == typeid(Twykladowca))
            cout << "Nazwy danych: id, imie, nazwisko, pesel, tytul, e-mail, wydzial" << endl;
        if (typeid(typ) == typeid(Tstudent))
            cout << "Nazwy danych: id, imie, nazwisko, pesel, e-mail, kierunek, grupaW, grupaC, grupaL" << endl;
        cout << "Podaj nazwe szukanej danej-";
        cin >> NazwaDanej;
        cout << "Podaj szukana wartosc-";
        if (NazwaDanej == "imie") {
            string szukana;
            cin >> szukana;
            cout << endl;
            for (int i = 0; i < BazaDanych.size(); i++) {
                if (BazaDanych[i].PodajS('i') == szukana)
                    BazaDanych[i].wypisz();
            }
            system("pause");
            return;
        } else if (NazwaDanej == "nazwisko") {
            string szukana;
            cin >> szukana;
            cout << endl;
            for (int i = 0; i < BazaDanych.size(); i++) {
                if (BazaDanych[i].PodajS('n') == szukana)
                    BazaDanych[i].wypisz();
            }
            system("pause");
            return;
        } else if (NazwaDanej == "tytul") {
            string szukana;
            cin >> szukana;
            cout << endl;
            for (int i = 0; i < BazaDanych.size(); i++) {
                if (BazaDanych[i].PodajS('t') == szukana)
                    BazaDanych[i].wypisz();
            }
            system("pause");
            return;
        } else if (NazwaDanej == "e-mail") {
            string szukana;
            cin >> szukana;
            cout << endl;
            for (int i = 0; i < BazaDanych.size(); i++) {
                if (BazaDanych[i].PodajS('i') == szukana)
                    BazaDanych[i].wypisz();
            }
            system("pause");
            return;
        } else if (NazwaDanej == "wydzial") {
            string szukana;
            cin >> szukana;
            cout << endl;
            for (int i = 0; i < BazaDanych.size(); i++) {
                if (BazaDanych[i].PodajS('i') == szukana)
                    BazaDanych[i].wypisz();
            }
            system("pause");
            return;
        } else if (NazwaDanej == "kierunek") {
            string szukana;
            cin >> szukana;
            cout << endl;
            for (int i = 0; i < BazaDanych.size(); i++) {
                if (BazaDanych[i].PodajS('k') == szukana)
                    BazaDanych[i].wypisz();
            }
            system("pause");
            return;
        } else if (NazwaDanej == "pesel") {
            long long int szukana;
            cin >> szukana;
            cout << endl;
            for (int i = 0; i < BazaDanych.size(); i++) {
                if (BazaDanych[i].PodajN('p') == szukana)
                    BazaDanych[i].wypisz();
            }
            system("pause");
            return;
        } else if (NazwaDanej == "grupaW") {
            long long int szukana;
            cin >> szukana;
            cout << endl;
            for (int i = 0; i < BazaDanych.size(); i++) {
                if (BazaDanych[i].PodajN('w') == szukana)
                    BazaDanych[i].wypisz();
            }
            system("pause");
            return;
        } else if (NazwaDanej == "grupaC") {
            long long int szukana;
            cin >> szukana;
            cout << endl;
            for (int i = 0; i < BazaDanych.size(); i++) {
                if (BazaDanych[i].PodajN('c') == szukana)
                    BazaDanych[i].wypisz();
            }
            system("pause");
            return;
        } else if (NazwaDanej == "grupaL") {
            long long int szukana;
            cin >> szukana;
            cout << endl;
            for (int i = 0; i < BazaDanych.size(); i++) {
                if (BazaDanych[i].PodajN('l') == szukana)
                    BazaDanych[i].wypisz();
            }
            system("pause");
            return;
        } else if (NazwaDanej == "id") {
            long long int szukana;
            cin >> szukana;
            cout << endl;
            for (int i = 0; i < BazaDanych.size(); i++) {
                if (BazaDanych[i].PodajN('i') == szukana)
                    BazaDanych[i].wypisz();
            }
            system("pause");
            return;
        } else {
            cout << "Zle podana dana" << endl;
            system("pause");
        }
    }
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

template<typename typ>
void Sortuj(vector<typ> BazaDanych) {
    string NazwaDanej;
    while (true){
    if (typeid(typ) == typeid(Twykladowca))
        cout << "Nazwy danych: imie, nazwisko, pesel tytul, wydzial" << endl;
    else if (typeid(typ) == typeid(Tstudent))
        cout << "Nazwy danych: imie, nazwisko, pesel, kierunek, grupaW, grupaC, grupaL" << endl;
    cout << "Wedlug ktorej danej wyswietlic posortowanej-";
    cin >> NazwaDanej;
    if (NazwaDanej == "imie") {
        cout << endl;
        SortujString(BazaDanych, 'i');
        cout << "Posortowane: " << endl;
        WypiszBaze(BazaDanych);
        system("pause");
        return;
    } else if (NazwaDanej == "nazwisko") {
        cout << endl;
        SortujString(BazaDanych, 'n');
        cout << "Posortowane: " << endl;
        WypiszBaze(BazaDanych);
        system("pause");
        return;
    } else if (NazwaDanej == "tytul") {
        cout << endl;
        SortujString(BazaDanych, 't');
        cout << "Posortowane: " << endl;
        WypiszBaze(BazaDanych);
        system("pause");
        return;
    } else if (NazwaDanej == "wydzial") {
        cout << endl;
        SortujString(BazaDanych, 'w');
        cout << "Posortowane: " << endl;
        WypiszBaze(BazaDanych);
        system("pause");
        return;
    } else if (NazwaDanej == "kierunek") {
        cout << endl;
        SortujString(BazaDanych, 'k');
        cout << "Posortowane: " << endl;
        WypiszBaze(BazaDanych);
        system("pause");
        return;
    } else if (NazwaDanej == "pesel") {
        cout << endl;
        SortujLiczby(BazaDanych, 'p');
        cout << "Posortowane: " << endl;
        WypiszBaze(BazaDanych);
        system("pause");
        return;
    } else if (NazwaDanej == "grupaW") {
        cout << endl;
        SortujLiczby(BazaDanych, 'w');
        cout << "Posortowane: " << endl;
        WypiszBaze(BazaDanych);
        system("pause");
        return;
    } else if (NazwaDanej == "grupaC") {
        cout << endl;
        SortujLiczby(BazaDanych, 'c');
        cout << "Posortowane: " << endl;
        WypiszBaze(BazaDanych);
        system("pause");
        return;
    } else if (NazwaDanej == "grupaL") {
        cout << endl;
        SortujLiczby(BazaDanych, 'l');
        cout << "Posortowane: " << endl;
        WypiszBaze(BazaDanych);
        system("pause");
        return;
    } else {
        cout << "Zle podana dana" << endl;
        system("pause");
    }
    }
}

template <typename typ>
void SortujLiczby(vector<typ> &BazaDanych, char zmienna)
{
    typ pomocna;
    for(int i=0; i < BazaDanych.size(); i++)
    {
        for(int j=i; j < BazaDanych.size(); j++)
        {
            if(BazaDanych[i].PodajN(zmienna)>BazaDanych[j].PodajN(zmienna))
            {
                pomocna=BazaDanych[i];
                BazaDanych[i]=BazaDanych[j];
                BazaDanych[j]=pomocna;
                i=0;

            }
        }
    }
}

template <typename typ>
void SortujString(vector<typ> &BazaDanych, char zmienna)
{
    typ pomocnaT;
    string pomocnicza1, pomocnicza2;
    int dlugosc1=0, dlugosc2=0;
    for(int i=0; i < BazaDanych.size(); i++)
    {
        for(int j=i; j < BazaDanych.size(); j++)
        {
            dlugosc1=(BazaDanych[i].PodajS(zmienna)).length();
            dlugosc2=(BazaDanych[j].PodajS(zmienna)).length();
            if(dlugosc1<dlugosc2)
                dlugosc1=dlugosc2;
            for(int k=0; k<dlugosc1; k++)
            {
                if((BazaDanych[i].PodajS(zmienna))[k]==(BazaDanych[j].PodajS(zmienna))[k])
                {
                    continue;
                }
                else if((BazaDanych[i].PodajS(zmienna))[k]<(BazaDanych[j].PodajS(zmienna))[k])
                {
                    break;
                }
                if((BazaDanych[i].PodajS(zmienna))[k]>(BazaDanych[j].PodajS(zmienna))[k])
                {
                    pomocnaT=BazaDanych[i];
                    BazaDanych[i]=BazaDanych[j];
                    BazaDanych[j]=pomocnaT;
                    i=0;
                    break;
                }
            }
        }
    }
}