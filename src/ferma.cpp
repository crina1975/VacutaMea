#include "ferma.hpp"
#include "../include/oaie.hpp"
#include "exceptii.hpp"
#include "logger.hpp"
#include <random>

Ferma::Ferma(std::string nume, int bugetInitial) : numeFerma(std::move(nume)), buget(bugetInitial), stocProduse(0), ziuaCurenta(1) {
    if (buget < 0) throw EroareParametru("Bugetul initial nu poate fi negativ.");
    istoricBuget.adauga(buget);
    istoricStoc.adauga(stocProduse);
    Logger::getInstanta().log("Ferma " + numeFerma + " a fost infiintata cu buget: " + std::to_string(buget));
}

Ferma::Ferma(const Ferma& other) : numeFerma(other.numeFerma), buget(other.buget), stocProduse(other.stocProduse), ziuaCurenta(other.ziuaCurenta) {
    animale.reserve(other.animale.size());
    for (const auto& a : other.animale) {
        animale.push_back(a->clone());
    }
}

void swap(Ferma& first, Ferma& second) noexcept {
    using std::swap;
    swap(first.numeFerma, second.numeFerma);
    swap(first.animale, second.animale);
    swap(first.buget, second.buget);
    swap(first.stocProduse, second.stocProduse);
    swap(first.ziuaCurenta, second.ziuaCurenta);
}

Ferma& Ferma::operator=(Ferma other) {
    swap(*this, other);
    return *this;
}

void Ferma::adaugaAnimal(std::unique_ptr<Animal> animal) {
    if (!animal) throw EroareParametru("Pointerul animal este null.");
    Logger::getInstanta().log("A fost adaugat animalul: " + animal->getNume());
    animale.push_back(std::move(animal));
}

void Ferma::simuleazaZi() {
    ziuaCurenta++;
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 3);
    auto vremeAzi = static_cast<TipVreme>(dist(gen));

    std::cout << "\n--- Incepe ziua " << ziuaCurenta << " (Vreme ID: " << static_cast<int>(vremeAzi) << ") ---\n";
    Logger::getInstanta().log("A inceput ziua " + std::to_string(ziuaCurenta));

    for (auto& animal : animale) {
        animal->treceTimpul(vremeAzi);
    }

    istoricBuget.adauga(buget);
    istoricStoc.adauga(stocProduse);
}

void Ferma::hranesteToateAnimalele(const Articol& hrana) {
    std::cout << "[INFO] Ferma hraneste animalele cu " << hrana.getNume() << ".\n";
    for (auto& animal : animale) {
        animal->hraneste(hrana);
    }
}

void Ferma::colecteazaTot() {
    for (auto& animal : animale) {
        try {
            stocProduse += animal->colecteazaProductie();
        } catch (const EroareLogica& e) {
            std::cerr << "[AVERTISMENT] " << e.what() << "\n";
        }
    }
}

void Ferma::tundeOile() {
    for (auto& animal : animale) {
        if (auto* oaie = dynamic_cast<Oaie*>(animal.get())) {
            int lana = oaie->tundeLana();
            if (lana > 0) {
                std::cout << "[INFO] Am tuns " << oaie->getNume() << " si am recoltat " << lana << "cm lana.\n";
                stocProduse += lana;
            }
        }
    }
}

void Ferma::cheamaVeterinar() {
    int costTratament = 50;
    for (auto& animal : animale) {
        if (animal->esteBolnav()) {
            if (buget >= costTratament) {
                buget -= costTratament;
                animal->vindeca();
                std::cout << "[INFO] Veterinarul a vindecat pe " << animal->getNume() << ".\n";
                Logger::getInstanta().log("Veterinarul l-a tratat pe " + animal->getNume());
            } else {
                throw EroareResurse("Fonduri insuficiente pentru a trata pe " + animal->getNume());
            }
        }
    }
}

void Ferma::afiseazaRegistre() const {
    istoricBuget.afiseaza(std::cout, "Evolutie Buget");
    istoricStoc.afiseaza(std::cout, "Evolutie Stoc Produse");
}

std::ostream& operator<<(std::ostream& os, const Ferma& f) {
    os << "\n=== FERMA: " << f.numeFerma << " | Ziua: " << f.ziuaCurenta << " ===\n";
    os << "Buget: " << f.buget << " bani | Stoc Total: " << f.stocProduse << " unitati\n";
    os << "Animale (" << f.animale.size() << "):\n";
    for (const auto& a : f.animale) {
        os << "  - " << *a << "\n";
    }
    return os << "=================================\n";
}