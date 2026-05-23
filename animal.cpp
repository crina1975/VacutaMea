#include "animal.h"

int Animal::contorAnimale = 0;

Animal::Animal(std::string n, int v, Sex s)
    : nume(std::move(n)), varsta(v), sex(s), idAnimal(++contorAnimale) {
    if (varsta < 0) {
        throw EroareAnimalInvalid(nume);
    }
}

Animal::~Animal() = default;

void Animal::afisare(std::ostream& os) const {
    os << "[" << idAnimal << "] " << nume << " (V: " << varsta << ")";
}

int Animal::getId() const { return idAnimal; }
Sex Animal::getSex() const { return sex; }
bool Animal::esteAdult() const { return varsta >= 3; }
const std::string& Animal::getNume() const { return nume; }

std::ostream& operator<<(std::ostream& os, const Animal& a) {
    a.afisare(os);
    return os;
}