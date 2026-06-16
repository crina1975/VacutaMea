#include "../include/gaina.hpp"
#include <algorithm>

Gaina::Gaina(std::string n, int v, int oua) : Animal(std::move(n), v), ouaZilnic(oua) {}

void Gaina::afisare_(std::ostream& os) const {
    os << "Gaina " << nume << " | Varsta: " << varsta << " | Energie: " << energie
       << " | Oua: " << ouaZilnic << "/zi";
}

void Gaina::treceTimpul_(TipVreme vreme) {
    int consum = (vreme == TipVreme::PLOIOS) ? 20 : 10;
    energie = std::clamp(energie - consum, 0, 100);
    if (vreme == TipVreme::FURTUNA) {
        sanatate = StareSanatate::BOLNAVA;
    }
}

int Gaina::colecteazaProductie_() {
    energie = std::clamp(energie - 10, 0, 100);
    return ouaZilnic;
}

void Gaina::hraneste(const Articol& a) {
    energie = std::clamp(energie + a.getPutereSatietate() * 2, 0, 100);
}

std::unique_ptr<Animal> Gaina::clone() const {
    return std::make_unique<Gaina>(*this);
}