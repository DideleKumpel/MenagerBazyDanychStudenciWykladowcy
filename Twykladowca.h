//
// Created by CEM on 07.03.2024.
//

#ifndef BAZADANYCH_TWYKLADOWCA_H
#define BAZADANYCH_TWYKLADOWCA_H

#include "Tosoba.h"

class Twykladowca:Tosoba {
    static long long int id;
    std::string tytul, email, wydzial;
    int Pid;
public:
    Twykladowca(void) {}
    Twykladowca(std::string i, std::string n, int p, std::string t, std::string e, std::string w);
    void dodaj();
    void wpisz(bool i=1);
    void wypisz();
    void ZapiszWPliku(std::string nazwaPliku);
    void wczytajZPliku(std::string NazwaPliku);
    std::string PodajS(char co);
    long long int PodajN(char co);
    void Usun(std::string i="-1", std::string n="-1", int p=-1, std::string t="-1", std::string e="-1", std::string w="-1");

    struct BladPliku{};
    struct KoniecPliku{};
};


#endif //BAZADANYCH_TWYKLADOWCA_H
