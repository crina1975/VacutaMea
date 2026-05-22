#include "Ferma.h"
#include <utility>

Ferma::Ferma(std::string nf) : numeF(std::move(nf)), bani(250) {}

Ferma::~Ferma() {
    for (auto* a : animale) {
        delete a;
    }
}

Ferma::Ferma(const Ferma& other) : numeF(other.numeF), bani(other.bani) {
    for (const auto* a : other.animale) {
        animale.push_back(a->clone());
    }
}

void swap(Ferma& f1, Ferma& f2) {
    using std::swap;
    swap(f1.numeF, f2.numeF);
    swap(f1.bani, f2.bani);
    swap(f1.animale, f2.animale);
}

Ferma& Ferma::operator=(Ferma other) {
    swap(*this, other);
    return *this;
}

void Ferma::adaugaAnimal(Animal* animalNou) {
    animale.push_back(animalNou);
}

void Ferma::adunaResurse() {
    int lapteTotal = 0;
    int ouaTotal = 0;

    for (auto* animal : animale) {
        animal->scoateSunet();

        if (auto* vaca = dynamic_cast<Vacuta*>(animal)) {
            lapteTotal += vaca->mulge();
        }
        else if (auto* gaina = dynamic_cast<Gaina*>(animal)) {
            ouaTotal += gaina->adunaOua();
        }
    }
    std::cout << "S-au adunat: " << lapteTotal << "L lapte si " << ouaTotal << " oua.\n";
}

void Ferma::plateste(int cost) {
    if (bani < cost) {
        throw EroareFaliment(std::to_string(cost) + " bani necesari");
    }
    bani -= cost;
}

void Ferma::afisareDetalii() const {
    std::cout << "=== " << numeF << " ===\nBani: " << bani << "\nAnimale:\n";
    for (const auto* a : animale) {
        std::cout << *a << "\n";
    }
}