#include "ferma.h"
#include "vacuta.h"
#include "gaina.h"
#include "exceptii.h"
#include <iostream>
#include <utility>

Ferma::Ferma(std::string nume) : numeFerma(std::move(nume)) {
    if (numeFerma.empty()) {
        throw EroareParametru("Numele fermei nu poate fi gol!");
    }
}

// CC (Deep Copy)
Ferma::Ferma(const Ferma& other) : numeFerma(other.numeFerma) {
    for (const auto* animal : other.animale) {
        animale.push_back(animal->clone());
    }
}

// Destructor (Previne memory leaks cerute de Valgrind/ASan)
Ferma::~Ferma() {
    for (auto* animal : animale) {
        delete animal;
    }
    animale.clear();
}

void swap(Ferma& f1, Ferma& f2) noexcept {
    using std::swap;
    swap(f1.numeFerma, f2.numeFerma);
    swap(f1.animale, f2.animale);
}

// Operator de atribuire safe
Ferma& Ferma::operator=(const Ferma& other) {
    if (this != &other) {
        Ferma temp(other);
        swap(*this, temp);
    }
    return *this;
}

void Ferma::adaugaAnimal(const Animal& a) {
    animale.push_back(a.clone());
}

void Ferma::raporteazaProductia() const {
    int totalLapte = 0;
    int totalOua = 0;

    std::cout << "\n=== Productie: " << numeFerma << " ===\n";
    for (const auto* animal : animale) {
        // DYNAMIC_CAST pt apeluri specifice claselor derivate
        if (const auto* v = dynamic_cast<const Vacuta*>(animal)) {
            totalLapte += v->mulge();
        } else if (const auto* g = dynamic_cast<const Gaina*>(animal)) {
            totalOua += g->adunaOua();
        }
    }
    std::cout << "Lapte: " << totalLapte << " L\nOua: " << totalOua << " bucati\n";
}

void Ferma::catalog() const {
    std::cout << "\n=== Catalog ===\n";
    for (const auto* animal : animale) {
        std::cout << *animal << "\n";
        animal->scoateSunet(); // Apel polimorfic
    }
}