#include "porc.hpp"
#include <algorithm>

Porc::Porc(std::string n, int v) : Animal(std::move(n), v), greutate(30) {}

void Porc::afisare_(std::ostream& os) const {
    os << "Porc: " << nume << " | Varsta: " << varsta << " | Energie: " << energie << " | Greutate: " << greutate << " kg";
}

void Porc::treceTimpul_(TipVreme vreme) {
    int consum = (vreme == TipVreme::CANICULA) ? 30 : 15;
    energie = std::clamp(energie - consum, 0, 100);
    if (energie < 20) sanatate = StareSanatate::BOLNAVA;
}

int Porc::colecteazaProductie_() {
    return 0; // Porcul nu da lapte/oua
}

void Porc::hraneste(const Articol& a) {
    energie = std::clamp(energie + a.getPutereSatietate() + 10, 0, 100);
    greutate += 2; // Porcul se îngrașă când mănâncă
}

std::unique_ptr<Animal> Porc::clone() const { return std::make_unique<Porc>(*this); }
void Porc::scoateSunet() const { std::cout << nume << " face: Guit!\n"; }