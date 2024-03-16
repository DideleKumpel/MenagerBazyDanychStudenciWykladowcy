//
// Created by CEM on 06.03.2024.
//

#ifndef BAZADANYCH_TSTUDENT_H
#define BAZADANYCH_TSTUDENT_H

#include "Tosoba.h"
#include <string>

class Tstudent:Tosoba {
    static long long int id;
    std::string kierunek, email;
    int grupaW, grupaC, grupaL, Pid;
public:
    Tstudent(void){}
    Tstudent(std::string i, std::string n, int p, std::string k, std::string e, int w, int c, int l);
    void dodaj();
    void wpisz(bool i=1);
    void wypisz();
    void ZapiszWPliku(std::string nazwaPliku);
    void wczytajZPliku(std::string NazwaPliku);
    std::string PodajS(char co);
    long long int PodajN(char Co);
    void Usun(std::string i="-1", std::string n="-1", int p=0, std::string k="-1", std::string e="-1", int w=-1, int c=-1, int l=-1);

    struct BladPliku{};
    struct KoniecPliku{};
};


#endif //BAZADANYCH_TSTUDENT_H
