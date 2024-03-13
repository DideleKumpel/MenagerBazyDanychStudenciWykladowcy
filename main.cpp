#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <limits>

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
void WypiszBazeW(vector<typ> &BazaDanych);
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
void SortujLiczby(vector<typ> &BazaDanych, char zmienna, bool kolejnosc);
template <typename typ>
void SortujString(vector<typ> &BazaDanych, char zmienna, bool kolejnosc);
void OblsugaBleduCin();

struct BrakPliku{};
struct BladCin{};

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
        while(true) {
            system("CLS");
            cout << "Wpisz cyfre odpowiadjaca numerowi opcji." << endl;
            cout << "1. Stworz nowa baze danych" << endl;
            if (CzyWczytany) {
                cout << "2. Wczytaj isniejaca baze" << endl;
            }
            cout << "3. Zamnkij program" << endl;
            cin >> menu1;
            try {
                OblsugaBleduCin();
            }
            catch (BladCin)
            {
                continue;
            }
            if(menu1<1 or menu1>3)
            {
                cout<<"Wprowadzono liczbe z poza zakres. Wprowadz ponownie"<<endl;
                system("pause");
                system("CLS");
                continue;
            }
            break;
        }
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
                while(true) {
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
                    try {
                        OblsugaBleduCin();
                    }
                    catch (BladCin)
                    {
                        continue;
                    }
                    if(numer<1 or numer>NazwyBazDanych.size())
                    {
                        cout<<"Wprowadzono liczbe z poza zakres. Wprowadz ponownie"<<endl;
                        system("pause");
                        system("CLS");
                        continue;
                    }
                    nazwaBazy = NazwyBazDanych[numer - 1];
                    break;
                }
                break;
            case 3:
                return 0;
        }
        system("CLS");
        WczytajBaze(studenci, nazwaBazy);
        WczytajBaze(wykladowcy, nazwaBazy);
        while (true) {
            int odpowiedz;
            while(true) {
                cout << "1. Pracuj na spisie studnetow \n2. Pracuj na spisie wykladowcow \n3. Zamknij program" << endl
                     << endl;
                cin >> odpowiedz;
                try {
                    OblsugaBleduCin();
                }
                catch (BladCin) {
                    continue;
                }
                if (odpowiedz < 1 or odpowiedz > 3) {
                    cout << "Wprowadzono liczbe z poza zakres. Wprowadz ponownie" << endl;
                    system("pause");
                    system("CLS");
                    continue;
                }
                break;
            }
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
        try {
            OblsugaBleduCin();
        }
        catch (BladCin) {
            continue;
        }
        if (odpowiedz < 1 or odpowiedz > 3) {
            cout << "Wprowadzono liczbe z poza zakres. Wprowadz ponownie" << endl;
            system("pause");
            system("CLS");
            continue;
        }
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
    bool poprawnaK=1;
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
                break;
            }
            if(i==listaKomend.size()-1)
                poprawnaK=0;
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
void WypiszBazeW(vector<typ> &BazaDanych)
{
    if (typeid(typ) == typeid(Twykladowca)) {
        cout<< "| ID  |    IMIE    |     NAZWISKO    |     PESEL     | TYTUL |                   E-MAIL                 |     WYDZIAL"<<endl;
        for(int i=0; i<120; i++)
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
    int NazwaDanej, sposob;
    while (true){
        while (true) {
            if (typeid(typ) == typeid(Twykladowca))
                cout << "Nazwy danych: 1.IMIE 2.NAZWISKO 3.PESEL 4.TYTUL 5.WYDZIAL" << endl;
            else if (typeid(typ) == typeid(Tstudent))
                cout << "Nazwy danych: 1.IMIE 2.NAZWISKO 3.PESEL 4.KIERUNEK 5.GRUPA W 6.GRUPA C 7.GRUPA L" << endl;
            cout << "Podaj liczbe odpowiadjaca numerowi danej wedlug ktorej ma odbyc sie sortowanie" << endl;
            cin >> NazwaDanej;
            try {
                OblsugaBleduCin();
            }
            catch (BladCin)
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
        koljenosc=1;
    else
        koljenosc=0;
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
    int dlugosc1=0, dlugosc2=0;
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

void OblsugaBleduCin()
{
    if(cin.fail())
    {
        cout<<"Nalezy pisac liczbe. Prowadz dane ponownie"<<endl;
        system("pause");
        system("CLS");
        cin.clear();
        cin.ignore();
        cin.ignore( std::numeric_limits < std::streamsize >::max(), '\n' );
        BladCin flaga;
        throw flaga;
    }
}