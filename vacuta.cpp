#include "Vacuta.h"

Vacuta::Vacuta(std::string n, int v, Sex s)
    : Animal(std::move(n), v, s), nivelFoame(30), nivelEnergie(100), sanatate(StareSanatate::SANATOASA) {}

// cppcheck-suppress unusedFunction
Animal* Vacuta::clone() const {
    return new Vacuta(*this);
}
Animal* Vacuta::clone() const {
    return new Vacuta(*this);
}

void Vacuta::scoateSunet() const {
    std::cout << nume << " face: Muuuuu!\n";
}

int Vacuta::mulge() {
    if (sanatate == StareSanatate::SANATOASA && esteAdult() && sex == Sex::FEMELA) {
        return 10;
    }
    return 0;
}

void Vacuta::afisare(std::ostream& os) const {
    Animal::afisare(os);
    os << " | Vacuta | Foame: " << nivelFoame << " | Energie: " << nivelEnergie;
}