#include "utilizare.h"
#include <algorithm>

// --- ISTORIC ---
void Istoric::adaugaEveniment(const std::string& eveniment) {
    loguri.push_back(eveniment);
}

std::ostream& operator<<(std::ostream& os, const Istoric& istoric) {
    os << "\n=== JURNAL FERMA ===\n";
    if (istoric.loguri.empty()) os << " Niciun eveniment inregistrat.\n";
    for (const auto& log : istoric.loguri) os << " > " << log << "\n";
    return os;
}

// --- PIATA ---
Piata::Piata() : generator(std::random_device{}()) {}

void Piata::fluctueazaPreturi() {
    std::uniform_int_distribution<int> distLapte(3, 8);
    std::uniform_int_distribution<int> distCarne(50, 120);
    pretLapte = distLapte(generator);
    pretCarne = distCarne(generator);
}

int Piata::getPretLapte() const { return pretLapte; }
int Piata::getPretCarne() const { return pretCarne; }

std::ostream& operator<<(std::ostream& os, const Piata& p) {
    return os << "[Piata Locala] Lapte: " << p.pretLapte << " bani/L | Carne: " << p.pretCarne << " bani";
}

// --- VREMEA ---
Vremea::Vremea() : generator(std::random_device{}()) {}

void Vremea::schimbaVremea() {
    std::uniform_int_distribution<int> dist(0, 3);
    stadiuCurent = static_cast<TipVreme>(dist(generator));
}

TipVreme Vremea::getVremeCurenta() const { return stadiuCurent; }

std::string Vremea::getNumeVreme() const {
    switch(stadiuCurent) {
        case TipVreme::INSORIT: return "Insorit";
        case TipVreme::PLOIOS: return "Ploios";
        case TipVreme::FURTUNA: return "Furtuna";
        case TipVreme::CANICULA: return "Canicula";
    }
    return "Necunoscut";
}

std::ostream& operator<<(std::ostream& os, const Vremea& v) {
    return os << "Vremea curenta este: " << v.getNumeVreme();
}

// --- SISTEM REALIZARI ---
void SistemRealizari::verificaAvere(int bani, Istoric& jurnal) {
    if (bani >= 500 && !bogatie) {
        bogatie = true;
        jurnal.adaugaEveniment("🏆 REALIZARE DEBLOCATA: Fermier Bogat!");
    }
}

void SistemRealizari::deblocheazaPui(Istoric& jurnal) {
    if (!primulPui) {
        primulPui = true;
        jurnal.adaugaEveniment("🏆 REALIZARE DEBLOCATA: Miracolul Vietii!");
    }
}

void SistemRealizari::deblocheazaBucatar(Istoric& jurnal) {
    if (!maestruBucatar) {
        maestruBucatar = true;
        jurnal.adaugaEveniment("🏆 REALIZARE DEBLOCATA: MasterChef!");
    }
}

std::ostream& operator<<(std::ostream& os, const SistemRealizari& s) {
    os << "Realizari Deblocate: ";
    if (!s.primulPui && !s.bogatie && !s.maestruBucatar) os << "Niciuna.";
    if (s.primulPui) os << "[Miracolul Vietii] ";
    if (s.bogatie) os << "[Bogat] ";
    if (s.maestruBucatar) os << "[MasterChef] ";
    return os;
}

// --- ARTICOL ---
Articol::Articol(std::string n, int p, int sat) : nume(std::move(n)), pret(p), putereSatietate(sat) {}

int Articol::getPret() const { return pret; }
int Articol::getPutereSatietate() const { return putereSatietate; }
const std::string& Articol::getNume() const { return nume; }

std::ostream& operator<<(std::ostream& os, const Articol& a) {
    return os << a.nume << " (" << a.pret << " bani)";
}

// --- MAGAZIN ---
Magazin::Magazin() {
    catalog.emplace_back("Iarba", 10, 20);
    catalog.emplace_back("Fan_Premium", 25, 50);
    catalog.emplace_back("Concentrate", 50, 100);
}

Magazin::~Magazin() { catalog.clear(); }

Magazin::Magazin(const Magazin& other) : catalog(other.catalog) {
    std::cout << "[Sistem Memorie] Magazin copiat automat.\n";
}

Magazin& Magazin::operator=(const Magazin& other) {
    if (this != &other) {
        catalog = other.catalog;
        std::cout << "[Sistem Memorie] Magazin atribuit automat.\n";
    }
    return *this;
}

Articol Magazin::cautaArticol(const std::string& numeCautat) const {
    for (const auto& art : catalog) {
        if (art.getNume() == numeCautat) return art;
    }
    return Articol("Eroare", 0, 0);
}

std::ostream& operator<<(std::ostream& os, const Magazin& m) {
    os << "\n=== CATALOG MAGAZIN ===\n";
    for (const auto& art : m.catalog) {
        os << " - " << art << " | Ofera " << art.getPutereSatietate() << " energie.\n";
    }
    return os;
}

// --- HAMBAR ---
void Hambar::adauga(const std::string& numeArticol, int cantitate) {
    stocuri[numeArticol] += cantitate;
}

bool Hambar::consuma(const std::string& numeArticol) {
    if (stocuri.contains(numeArticol) && stocuri[numeArticol] > 0) {
        stocuri[numeArticol]--;
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Hambar& h) {
    os << "\n=== STOC HAMBAR ===\n";
    if (h.stocuri.empty()) os << " Hambarul este gol!\n";
    for (const auto& [nume, cantitate] : h.stocuri) {
        os << " > " << nume << ": " << cantitate << " portii\n";
    }
    return os;
}

// --- STATUS ---
Status::Status(std::string n, int v) : nume(std::move(n)), valoare(v) {}

void Status::modifica(int delta) {
    valoare = std::clamp(valoare + delta, 0, 100);
}

int Status::getValoare() const { return valoare; }

std::ostream& operator<<(std::ostream& os, const Status& s) {
    return os << s.nume << ": " << s.valoare << "/100";
}

// --- ANGAJAT ---
Angajat::Angajat(std::string n, int salariu) : nume(std::move(n)), salariuZilnic(salariu) {}

int Angajat::cerereSalariu() const { return salariuZilnic; }
const std::string& Angajat::getNume() const { return nume; }
void Angajat::plateste() { platitAzi = true; }
void Angajat::reseteazaZiua() { platitAzi = false; }

std::ostream& operator<<(std::ostream& os, const Angajat& a) {
    return os << "Angajat: " << a.nume << " | Salariu: " << a.salariuZilnic << " bani/zi";
}

// --- CONTRACT ---
Contract::Contract(std::string comp, int necesar, int rec, int zile)
    : companie(std::move(comp)), necesarLapte(necesar), recompensaBani(rec), zileRamase(zile) {}

bool Contract::esteFinalizat() const { return finalizat; }
bool Contract::esteExpirat() const { return zileRamase <= 0 && !finalizat; }
int Contract::getRecompensa() const { return recompensaBani; }
const std::string& Contract::getCompanie() const { return companie; }

int Contract::adaugaLapte(int cantitate) {
    if (finalizat || esteExpirat()) return cantitate;
    int spatiu = necesarLapte - lapteColectat;
    if (cantitate >= spatiu) {
        lapteColectat += spatiu;
        finalizat = true;
        return cantitate - spatiu;
    }
    lapteColectat += cantitate;
    return 0;
}

void Contract::treceZiua() {
    if (!finalizat && zileRamase > 0) zileRamase--;
}

std::ostream& operator<<(std::ostream& os, const Contract& c) {
    os << "Contract " << c.companie << " [" << c.lapteColectat << "/" << c.necesarLapte << "L] ";
    if (c.finalizat) os << "- FINALIZAT";
    else if (c.esteExpirat()) os << "- EXPIRAT";
    else os << "- Zile: " << c.zileRamase;
    return os;
}

// --- CLADIRE AUXILIARA ---
CladireAuxiliara::CladireAuxiliara(std::string n, int bonus, int cost)
    : nume(std::move(n)), bonusProductie(bonus), costIntretinere(cost) {}

int CladireAuxiliara::aplicaBonus(int productie) const { return productie + bonusProductie; }
int CladireAuxiliara::getCost() const { return costIntretinere; }
const std::string& CladireAuxiliara::getNume() const { return nume; }

std::ostream& operator<<(std::ostream& os, const CladireAuxiliara& c) {
    return os << "Cladire: " << c.nume << " (Bonus: +" << c.bonusProductie << "L lapte)";
}

// --- GRATAR ---
Gratar::Gratar(int timp) : timpGatireSecunde(timp) {}

StareCarne Gratar::verificaStare() const {
    if (timpGatireSecunde < 175) return StareCarne::NEFACUTA;
    if (timpGatireSecunde > 185) return StareCarne::ARSA;
    return StareCarne::PERFECTA;
}

int Gratar::vindeMancare(const std::string& tip, const Piata& piataCurenta, SistemRealizari& ach, Istoric& jurnal) const {
    StareCarne stare = verificaStare();
    if (stare == StareCarne::PERFECTA) {
        ach.deblocheazaBucatar(jurnal);
        return (tip == "ciorba") ? (piataCurenta.getPretCarne() / 2) : piataCurenta.getPretCarne();
    }
    std::cout << "[GRATAR] Atentie: Carnea este " << (stare == StareCarne::ARSA ? "ARSA" : "NEFACUTA") << "!\n";
    return 5;
}