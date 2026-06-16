#include "../include/oaie.hpp"
#include <algorithm>

Oaie::Oaie(std::string n, int v) : Animal(std::move(n), v), lungimeLana(5) {}

void Oaie::afisare_(std::ostream& os) const {
    os << "Oaie " << nume << " | Varsta: " << varsta << " | Energie: " << energie
       << " | Lana: " << lungimeLana << "cm";
}

void Oaie::treceTimpul_(TipVreme vreme) {
    int consum = 10;
    energie = std::clamp(energie - consum, 0, 100);
    if (sanatate == StareSanatate::SANATOASA && vreme == TipVreme::INSORIT) {
        lungimeLana += 2;
    }
}

int Oaie::colecteazaProductie_() {
    return 0;
}

void Oaie::hraneste(const Articol& a) {
    energie = std::clamp(energie + a.getPutereSatietate(), 0, 100);
}

int Oaie::tundeLana() {
    if (lungimeLana >= 10) {
        int recoltat = lungimeLana;
        lungimeLana = 2;
        return recoltat;
    }
    return 0;
}

std::unique_ptr<Animal> Oaie::clone() const {
    return std::make_unique<Oaie>(*this);
}