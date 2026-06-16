#include "../include/ferma.hpp"
#include "../include/oaie.hpp"
#include "../include/exceptii.hpp"

Ferma::Ferma(std::string nume, int bugetInitial) : numeFerma(std::move(nume)), buget(bugetInitial), stocProductie(0) {
    if (buget < 0) {
        throw EroareParametru("Bugetul initial nu poate fi negativ.");
    }
}

Ferma::Ferma(const Ferma& other) : numeFerma(other.numeFerma), buget(other.buget), stocProductie(other.stocProductie) {
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
    swap(first.stocProductie, second.stocProductie);
}

Ferma& Ferma::operator=(Ferma other) {
    swap(*this, other);
    return *this;
}

void Ferma::adaugaAnimal(std::unique_ptr<Animal> animal) {
    if (!animal) throw EroareParametru("Pointerul animal este null.");
    animale.push_back(std::move(animal));
}

void Ferma::simuleazaZi(TipVreme vreme) {
    for (auto& animal : animale) {
        animal->treceTimpul(vreme);
    }
}

void Ferma::hranesteToateAnimalele(const Articol& hrana) {
    for (auto& animal : animale) {
        animal->hraneste(hrana);
    }
}

void Ferma::strangeProductia() {
    for (auto& animal : animale) {
        try {
            stocProductie += animal->colecteazaProductie();
        } catch (const EroareLogica& e) {
            std::cerr << "[Logica] " << e.what() << "\n";
        }
    }
}

void Ferma::tundeOile() {
    for (auto& animal : animale) {
        if (auto* oaie = dynamic_cast<Oaie*>(animal.get())) {
            int lana = oaie->tundeLana();
            if (lana > 0) {
                stocProductie += lana * 2;
            }
        }
    }
}

void Ferma::cheamaVeterinar() {
    int cost = 50;
    for (auto& animal : animale) {
        if (animal->esteBolnav()) {
            if (buget >= cost) {
                buget -= cost;
                animal->vindeca();
            } else {
                throw EroareResurse("Fonduri insuficiente pentru veterinar!");
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Ferma& f) {
    os << "Ferma: " << f.numeFerma << " | Buget: " << f.buget << " | Stoc Productie: " << f.stocProductie << "\n";
    os << "Animale (" << f.animale.size() << "):\n";
    for (const auto& a : f.animale) {
        os << "  - " << *a << "\n";
    }
    return os;
}