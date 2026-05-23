#include "gaina.h"
#include <iostream>
#include <utility>


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
// cppcheck-suppress unusedFunction
int Gaina::adunaOua() const {
    return ouaZilnic;
}