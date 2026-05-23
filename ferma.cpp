#include "Ferma.hpp"
#include "Vacuta.hpp"
#include "Gaina.hpp"
#include "Exceptii.hpp"
#include <iostream>

Ferma::Ferma(std::string nume, int bugetInitial) : numeFerma(std::move(nume)), buget(bugetInitial) {
    if (buget < 0) throw EroareFonduri("Bugetul initial nu poate fi negativ.");
}

// 1. Constructorul de Copiere (Deep Copy via clone())
Ferma::Ferma(const Ferma& other) : numeFerma(other.numeFerma), buget(other.buget) {
    for (const auto* animal : other.animale) {
        animale.push_back(animal->clone());
    }
}

// 2. Destructorul
Ferma::~Ferma() {
    for (auto* animal : animale) {
        delete animal;
    }
    animale.clear();
}

// Functia de swap definita custom
void swap(Ferma& f1, Ferma& f2) noexcept {
    using std::swap;
    swap(f1.numeFerma, f2.numeFerma);
    swap(f1.buget, f2.buget);
    swap(f1.animale, f2.animale);
}

// 3. Operatorul de Atribuire (Copy-and-Swap)
Ferma& Ferma::operator=(Ferma other) {
    swap(*this, other);
    return *this;
}

void Ferma::adaugaAnimal(const Animal& a) {
    // Apelam clona polimorfica a animalului trimis prin referinta catre baza
    animale.push_back(a.clone());
    std::cout << "-> A fost adaugat un animal nou in ferma " << numeFerma << "\n";
}

void Ferma::colecteazaProductia() const {
    int totalLapte = 0;
    int totalOua = 0;

    for (const auto* animal : animale) {
        // DYNAMIC_CAST: Aflam tipul derivat real la runtime pentru a apela metode specifice
        if (const Vacuta* v = dynamic_cast<const Vacuta*>(animal)) {
            totalLapte += v->mulge();
        }
        else if (const Gaina* g = dynamic_cast<const Gaina*>(animal)) {
            totalOua += g->adunaOua();
        }
    }

    std::cout << "\n=== Productie Colectata ===\n";
    std::cout << "Lapte: " << totalLapte << " litri\n";
    std::cout << "Oua: " << totalOua << " bucati\n";
}

void Ferma::afiseazaAnimale() const {
    std::cout << "\n--- Animale in " << numeFerma << " ---\n";
    for (const auto* animal : animale) {
        std::cout << *animal << "\n"; // Apeleaza operator<< si apoi functia virtuala afisare()
        animal->scoateSunet();        // Apel de functie virtuala pura
    }
}