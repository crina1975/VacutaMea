#include "utilitare.h"

// cppcheck-suppress unusedFunction
void Istoric::adaugaEveniment(const std::string& eveniment) {
    loguri.push_back(eveniment);
}

std::ostream& operator<<(std::ostream& os, const Istoric& istoric) {
    if (istoric.loguri.empty()) os << "Niciun eveniment.\n";
    for (const auto& log : istoric.loguri) os << log << "\n";
    return os;
}

Piata::Piata() : generator(std::random_device{}()) {}

// cppcheck-suppress unusedFunction
void Piata::fluctueazaPreturi() {
    std::uniform_int_distribution<int> distLapte(3, 8);
    std::uniform_int_distribution<int> distCarne(50, 120);
    pretLapte = distLapte(generator);
    pretCarne = distCarne(generator);
}

// cppcheck-suppress unusedFunction
int Piata::getPretLapte() const { return pretLapte; }
// cppcheck-suppress unusedFunction
int Piata::getPretCarne() const { return pretCarne; }

std::ostream& operator<<(std::ostream& os, const Piata& p) {
    return os << "Lapte: " << p.pretLapte << " | Carne: " << p.pretCarne;
}

Articol::Articol(std::string n, int p, int sat) : nume(std::move(n)), pret(p), putereSatietate(sat) {}

// cppcheck-suppress unusedFunction
int Articol::getPret() const { return pret; }
// cppcheck-suppress unusedFunction
int Articol::getPutereSatietate() const { return putereSatietate; }
// cppcheck-suppress unusedFunction
const std::string& Articol::getNume() const { return nume; }

std::ostream& operator<<(std::ostream& os, const Articol& a) {
    return os << a.nume << " (" << a.pret << ")";
}

Magazin::Magazin() {
    catalog.emplace_back("Iarba", 10, 20);
}

Magazin::~Magazin() { catalog.clear(); }

Magazin::Magazin(const Magazin& other) : catalog(other.catalog) {}

Magazin& Magazin::operator=(const Magazin& other) {
    if (this != &other) catalog = other.catalog;
    return *this;
}

// cppcheck-suppress unusedFunction
Articol Magazin::cautaArticol(const std::string& numeCautat) const {
    for (const auto& art : catalog) {
        if (art.getNume() == numeCautat) return art;
    }
    return Articol("Eroare", 0, 0);
}

std::ostream& operator<<(std::ostream& os, const Magazin& m) {
    for (const auto& art : m.catalog) os << art << "\n";
    return os;
}