#include "animal.h"
#include "exceptii.h"
#include <utility>

int Animal::contor_animale = 0;

Animal::Animal(std::string n, int v)
    : nume(std::move(n)), varsta(v), id(++contor_animale) {
    // Excepție aruncată în constructor
    if (nume.empty()) {
        throw EroareParametru("Numele nu poate fi gol!");
    }
    if (varsta < 0) {
        throw EroareParametru("Varsta nu poate fi negativa!");
    }
}

void Animal::afisare(std::ostream& os) const {
    os << "[ID: " << id << "] " << nume << " (Varsta: " << varsta << " ani)";
}

int Animal::getTotalAnimale() {
    return contor_animale;
}

std::ostream& operator<<(std::ostream& os, const Animal& a) {
    a.afisare(os);
    return os;
}