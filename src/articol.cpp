#include "articol.hpp"
#include "exceptii.hpp"

Articol::Articol(std::string n, int sat) : nume(std::move(n)), putereSatietate(sat) {
    if (nume.empty()) throw EroareParametru("Numele articolului nu poate fi gol!");
    if (sat <= 0) throw EroareParametru("Puterea de satietate trebuie sa fie strict pozitiva!");
}

const std::string& Articol::getNume() const { return nume; }
int Articol::getPutereSatietate() const { return putereSatietate; }

std::ostream& operator<<(std::ostream& os, const Articol& a) {
    return os << a.nume << " (Satietate: " << a.putereSatietate << ")";
}