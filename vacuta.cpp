#include "vacuta.h"
#include "exceptii.h"
#include <utility>

Vacuta::Vacuta(std::string n, int v, int lapte)
    : Animal(std::move(n), v), litriLapte(lapte) {}

void Vacuta::afisare(std::ostream& os) const {
    os << "Vacuta ";
    Animal::afisare(os);
    os << " -> Ofera: " << litriLapte << "L/zi";
}

Animal* Vacuta::clone() const {
    return new Vacuta(*this);
}

void Vacuta::scoateSunet() const {
    std::cout << nume << " face: Muuuuu!\n";
}

int Vacuta::mulge() const {
    if (energie < 20) {
        throw EroareLogica(nume + " este prea obosita pentru a fi mulsa.");
    }
    return litriLapte;
}