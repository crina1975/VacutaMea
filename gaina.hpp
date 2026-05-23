#pragma once
#include "Animal.hpp"

class Gaina : public Animal {
private:
    int ouaZilnic;

protected:
    void afisare(std::ostream& os) const override {
        os << "Gaina ";
        Animal::afisare(os);
        os << " -> Oua produse: " << ouaZilnic << "/zi";
    }

public:
    Gaina(std::string n, int v, int oua) : Animal(std::move(n), v), ouaZilnic(oua) {}

    Animal* clone() const override {
        return new Gaina(*this);
    }

    void scoateSunet() const override {
        std::cout << nume << " face Cotcodac!\n";
    }

    int adunaOua() const {
        return ouaZilnic;
    }
};