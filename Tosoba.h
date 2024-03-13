//
// Created by CEM on 06.03.2024.
//

#ifndef BAZADANYCH_TOSOBA_H
#define BAZADANYCH_TOSOBA_H

#include <string>

class Tosoba {
protected:
    std::string imie, nazwisko;
    long long int pesel;
public:
    Tosoba(std::string i="Jan", std::string n="Kowalski", int p=1);
    void wpisz();
    void wypisz();
    std::string PodajString(char b);
    long long int podajPesel() {
        return pesel;
    }
};


#endif //BAZADANYCH_TOSOBA_H
