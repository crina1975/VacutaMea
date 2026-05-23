#include "gaina.h"
#include <utility>

Gaina::Gaina(std::string n, int v, int oua_zilnic)
    : Animal(std::move(n), v), oua(oua_zilnic) {}

void Gaina::afisare(std::ostream& os) const {
    os << "Gaina ";
    Animal::afisare(os);
    os << " -> Ofera: " << oua << " oua/zi";
}

Animal* Gaina::clone() const {
    return new Gaina(*this);
}

void Gaina::scoateSunet() const {
    std::cout << nume << " face: Cotcodac!\n";
}

int Gaina::adunaOua() const {
    return oua;
}