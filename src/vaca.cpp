#include "../include/vaca.hpp"
#include <algorithm>

Vaca::Vaca(std::string n, int v, int lapte) : Animal(std::move(n), v), litriLapteZilnic(lapte) {}

void Vaca::afisare_(std::ostream& os) const {
    os << "Vaca " << nume << " | Varsta: " << varsta << " | Energie: " << energie
       << " | Lapte: " << litriLapteZilnic << "L/zi";
}

void Vaca::treceTimpul_(TipVreme vreme) {
    int consum = (vreme == TipVreme::FURTUNA) ? 30 : 15;
    energie = std::clamp(energie - consum, 0, 100);
    if (energie < 20) {
        sanatate = StareSanatate::BOLNAVA;
    }
}

int Vaca::colecteazaProductie_() {
    energie = std::clamp(energie - 20, 0, 100);
    return litriLapteZilnic;
}

void Vaca::hraneste(const Articol& a) {
    energie = std::clamp(energie + a.getPutereSatietate(), 0, 100);
}

std::unique_ptr<Animal> Vaca::clone() const {
    return std::make_unique<Vaca>(*this);
}