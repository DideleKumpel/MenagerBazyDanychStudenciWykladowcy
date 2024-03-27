//
// Created by CEM on 27.03.2024.
//
#include "ObslugaBleduCin.h"

#include <iostream>
#include <cmath>

    void OBD::ObslugaBleduCin() {
        if (std::cin.fail()) {
            std::cout << "Nalezy pisac liczbe. Prowadz dane ponownie" << std::endl;
            system("pause");
            system("CLS");
            std::cin.clear();
            std::cin.ignore();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            OBD::BladCin flaga;
            throw flaga;
        }
    }

    bool OBD::ObslugaBleduCinInt(long long int odpowiedz, long long int zakresP, long long int zakresK) {
        try {
            OBD::ObslugaBleduCin();
        }
        catch (OBD::BladCin) {
            return false;
        }
        if (odpowiedz < zakresP or odpowiedz > zakresK) {
            std::cout << "Wprowadzono liczbe z poza zakres. Wprowadz ponownie" << std::endl;
            system("pause");
            system("CLS");
            return false;
        }
        return true;
    }