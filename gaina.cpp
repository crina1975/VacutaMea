#include "gaina.h"
#include <iostream>
#include <utility>

// cppcheck-suppress unusedFunction
void Ferma::gatesteVitel(size_t index, int secunde) {
    if (index >= cireada.size()) {
        std::cout << "\n[EROARE] Nu exista nicio vacuta la indexul " << index << "!\n";

Gaina::Gaina(std::string n, int v, int oua_zilnic)
    : Animal(std::move(n), v), ouaZilnic(oua_zilnic) {}

void Gaina::afisare(std::ostream& os) const {
    os << "Gaina ";
    Animal::afisare(os); // Reutilizăm logica din Animal
    os << " -> Ofera: " << ouaZilnic << " oua/zi";
}

std::unique_ptr<Animal> Gaina::clone() const {
    return std::make_unique<Gaina>(*this);
}

void Gaina::scoateSunet() const {
    std::cout << nume << " face: Cotcodac!\n";
}

int Gaina::adunaOua() const {
    return ouaZilnic;
}