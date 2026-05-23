#pragma once
#include "Animal.hpp"

class Vacuta : public Animal {
private:
    int litriLapteZilnic;

protected:
    void afisare(std::ostream& os) const override {
        os << "Vacuta ";
        Animal::afisare(os);
        os << " -> Lapte produs: " << litriLapteZilnic << "L/zi";
    }

public:
    Vacuta(std::string n, int v, int lapte) : Animal(std::move(n), v), litriLapteZilnic(lapte) {}

    // Suprascrierea constructorului virtual
    Animal* clone() const override {
        return new Vacuta(*this);
    }

    void scoateSunet() const override {
        std::cout << nume << " face Muuuu!\n";
    }

    int mulge() const {
        return litriLapteZilnic;
    }
};