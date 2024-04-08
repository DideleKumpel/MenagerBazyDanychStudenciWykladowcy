#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Tstudent.h"
#include "Twykladowca.h"

#include "ObslugaBleduCin.h"
#include "BazaDanychFunkcje.h"


using namespace std;


template<typename typ>
void menu2(vector<typ> &BazaDanych, string NazwaPliku);

int main() {
    vector<string> NazwyBazDanych;
    vector<Tstudent> studenci;
    vector<Twykladowca> wykladowcy;
    bool CzyWczytany= true;
    string nazwaBazy;
    try {
        BDF::WczytajNazwyBaz(NazwyBazDanych);
        cout<<"Wczytane bazy:"<<endl;
        for(int i=0; i < NazwyBazDanych.size(); i++)
        {
            cout<<i+1<<". "<<NazwyBazDanych[i]<<" ";
            if(!((i+1)%10) and i!=0)
                cout<<endl;
            if(i==NazwyBazDanych.size()-1)
                cout<<endl;
        }
    } catch (BDF::BrakPliku)
    {
        CzyWczytany= false;
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
            if(OBD::ObslugaBleduCinInt(menu1,1,2))
                break;
        }
        ofstream dane;
        system("CLS");
        switch (menu1) {
            case 1:
                nazwaBazy = BDF::NowaBaza(NazwyBazDanych);
                dane.open(nazwaBazy+"S.txt");
                dane.close();
                dane.open(nazwaBazy+"W.txt");
                dane.close();
                break;
            case 2:
                int numer;
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
                    cin >> numer;
                    if (OBD::ObslugaBleduCinInt(numer,1,NazwyBazDanych.size()))
                        break;
                }
                nazwaBazy = NazwyBazDanych[numer - 1];
                break;
            case 3:
                return 0;
        }
        system("CLS");
        BDF::WczytajBaze(studenci, nazwaBazy);
        BDF::WczytajBaze(wykladowcy, nazwaBazy);
        while (true) {
            int odpowiedz;
            while(true) {
                cout << "1. Pracuj na spisie studnetow \n2. Pracuj na spisie wykladowcow\n3. Usun baze danych \n4. Zamknij program" << endl
                     << endl;
                cin >> odpowiedz;
                OBD::ObslugaBleduCinInt(odpowiedz,1, 4);
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
                    BDF::UsunBaze(nazwaBazy, NazwyBazDanych);
                    break;
                case 4:
                    return 0;
            }
            system("CLS");
        }
    }
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
        if (!OBD::ObslugaBleduCinInt(odpowiedz,1,8))
            continue;
        switch (odpowiedz) {
            case 1:
                BDF::WypiszBaze(BazaDanych);
                system("pause");
                break;
            case 2:
                BDF::DodajWpis(BazaDanych, NazwaPliku);
                break;
            case 3:
                BDF::UsunWpis(BazaDanych, NazwaPliku);
                break;
            case 4:
                BDF::Edytuj(BazaDanych, NazwaPliku);
                break;
            case 5:
                BDF::Szukaj(BazaDanych);
                break;
            case 6:
                BDF::Sortuj(BazaDanych);
                break;
            case 7:
                system("CLS");
                break;
            case 8:
                return;
        }
    }
}
