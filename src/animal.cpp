#include "animal.hpp"
#include "exceptii.hpp"

int Animal::contor_animale = 0;

Animal::Animal(std::string n, int v) : nume(std::move(n)), varsta(v), energie(100), sanatate(StareSanatate::SANATOASA) {
    if (nume.empty()) throw EroareParametru("Animalul trebuie sa aiba un nume.");
    if (varsta < 0) throw EroareParametru("Varsta nu poate fi negativa.");
    contor_animale++;
}

int Animal::getTotalAnimale() { return contor_animale; }

void Animal::afisare(std::ostream& os) const { afisare_(os); }

void Animal::treceTimpul(TipVreme vreme) {
    if (sanatate == StareSanatate::BOLNAVA) energie -= 15;
    treceTimpul_(vreme);
}

int Animal::colecteazaProductie() {
    if (sanatate == StareSanatate::BOLNAVA || energie < 30) {
        throw EroareLogica("Animalul " + nume + " este epuizat sau bolnav. Nu poate produce.");
    }
    return colecteazaProductie_();
}

const std::string& Animal::getNume() const { return nume; }
bool Animal::esteBolnav() const { return sanatate == StareSanatate::BOLNAVA; }
void Animal::vindeca() { sanatate = StareSanatate::SANATOASA; }

std::ostream& operator<<(std::ostream& os, const Animal& a) {
    a.afisare(os);
    return os;
}