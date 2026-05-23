#include "gaina.h"

Gaina::Gaina(std::string n, int v, Sex s) : Animal(std::move(n), v, s) {}

// cppcheck-suppress unusedFunction
Animal* Gaina::clone() const {
    return new Gaina(*this);
}

void Gaina::scoateSunet() const {
    std::cout << nume << " face: Cotcodac!\n";
}

// cppcheck-suppress unusedFunction
int Gaina::adunaOua() {
    if (esteAdult() && sex == Sex::FEMELA) {
        return 2;
    }
    return 0;
}

void Gaina::afisare(std::ostream& os) const {
    Animal::afisare(os);
    os << " | Gaina (produce oua)";
}