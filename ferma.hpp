#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <random>
#include <map>
#include <memory>
#include "exceptii.hpp"
#include "bovina.hpp"
#include "vacuta.hpp"

class Istoric {
private:
    std::vector<std::string> loguri{};
public:
    void adaugaEveniment(const std::string& eveniment) { loguri.push_back(eveniment); }
    friend std::ostream& operator<<(std::ostream& os, const Istoric& istoric) {
        os << "\n=== JURNAL FERMA ===\n";
        if (istoric.loguri.empty()) os << " Niciun eveniment inregistrat.\n";
        for (const auto& log : istoric.loguri) os << " > " << log << "\n";
        return os;
    }
};

class Piata {
private:
    int pretLapte = 5;
    int pretCarne = 80;
    std::mt19937 generator{std::random_device{}()};
public:
    void fluctueazaPreturi() {
        std::uniform_int_distribution<int> distLapte(3, 8);
        std::uniform_int_distribution<int> distCarne(50, 120);
        pretLapte = distLapte(generator);
        pretCarne = distCarne(generator);
    }
    [[nodiscard]] int getPretLapte() const { return pretLapte; }
    [[nodiscard]] int getPretCarne() const { return pretCarne; }
    friend std::ostream& operator<<(std::ostream& os, const Piata& p) {
        return os << "[Piata Locala] Lapte: " << p.pretLapte << " bani/L | Carne: " << p.pretCarne << " bani";
    }
};

class Vremea {
private:
    TipVreme stadiuCurent = TipVreme::INSORIT;
    std::mt19937 generator{std::random_device{}()};
public:
    void schimbaVremea() {
        std::uniform_int_distribution<int> dist(0, 3);
        stadiuCurent = static_cast<TipVreme>(dist(generator));
    }
    [[nodiscard]] TipVreme getVremeCurenta() const { return stadiuCurent; }
    [[nodiscard]] std::string getNumeVreme() const {
        switch(stadiuCurent) {
            case TipVreme::INSORIT: return "Insorit";
            case TipVreme::PLOIOS: return "Ploios";
            case TipVreme::FURTUNA: return "Furtuna";
            case TipVreme::CANICULA: return "Canicula";
        }
        return "Necunoscut";
    }
    friend std::ostream& operator<<(std::ostream& os, const Vremea& v) {
        return os << "Vremea curenta este: " << v.getNumeVreme();
    }
};

class SistemRealizari {
private:
    bool primulPui = false;
    bool bogatie = false;
    bool maestruBucatar = false;
public:
    void verificaAvere(int bani, Istoric& jurnal) {
        if (bani >= 500 && !bogatie) {
            bogatie = true;
            jurnal.adaugaEveniment("🏆 REALIZARE DEBLOCATA: Fermier Bogat (Ai strans 500+ bani)!");
        }
    }
    void deblocheazaPui(Istoric& jurnal) {
        if (!primulPui) {
            primulPui = true;
            jurnal.adaugaEveniment("🏆 REALIZARE DEBLOCATA: Miracolul Vietii (Primul pui nascut)!");
        }
    }
    void deblocheazaBucatar(Istoric& jurnal) {
        if (!maestruBucatar) {
            maestruBucatar = true;
            jurnal.adaugaEveniment("🏆 REALIZARE DEBLOCATA: MasterChef (Ai gatit perfect un vitel)!");
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const SistemRealizari& s) {
        os << "Realizari Deblocate: ";
        if (!s.primulPui && !s.bogatie && !s.maestruBucatar) os << "Niciuna.";
        if (s.primulPui) os << "[Miracolul Vietii] ";
        if (s.bogatie) os << "[Bogat] ";
        if (s.maestruBucatar) os << "[MasterChef] ";
        return os;
    }
};

class Magazin {
private:
    std::vector<Articol> catalog;
public:
    Magazin() {
        catalog.emplace_back("Iarba", 10, 20);
        catalog.emplace_back("Fan_Premium", 25, 50);
        catalog.emplace_back("Concentrate", 50, 100);
    }
    ~Magazin() { catalog.clear(); }
    Magazin(const Magazin& other) : catalog(other.catalog) {
        std::cout << "[Sistem Memorie] Magazin copiat automat.\n";
    }
    Magazin& operator=(const Magazin& other) {
        if (this != &other) {
            catalog = other.catalog;
            std::cout << "[Sistem Memorie] Magazin atribuit automat.\n";
        }
        return *this;
    }
    [[nodiscard]] Articol cautaArticol(const std::string& numeCautat) const {
        for (const auto& art : catalog) {
            if (art.getNume() == numeCautat) return art;
        }
        std::cout << "\n[EROARE] Articolul " << numeCautat << " nu exista in magazin!\n";
        return Articol{"Eroare", 0, 0};
    }
    friend std::ostream& operator<<(std::ostream& os, const Magazin& m) {
        os << "\n=== CATALOG MAGAZIN ===\n";
        for (const auto& art : m.catalog) {
            os << " - " << art << " | Ofera " << art.getPutereSatietate() << " energie.\n";
        }
        return os;
    }
};

class Hambar {
private:
    std::map<std::string, int> stocuri{};
public:
    void adauga(const std::string& numeArticol, int cantitate) {
        stocuri[numeArticol] += cantitate;
    }
    bool consuma(const std::string& numeArticol) {
        auto it = stocuri.find(numeArticol);
        if (it != stocuri.end() && it->second > 0) {
            it->second--;
            return true;
        }
        return false;
    }
    friend std::ostream& operator<<(std::ostream& os, const Hambar& h) {
        os << "\n=== STOC HAMBAR ===\n";
        if (h.stocuri.empty()) os << " Hambarul este gol!\n";
        for (const auto& [nume, cantitate] : h.stocuri) {
            os << " > " << nume << ": " << cantitate << " portii\n";
        }
        return os;
    }
};

class Angajat {
private:
    std::string nume;
    int salariuZilnic{0};
    bool platitAzi{false};
public:
    explicit Angajat(std::string n, int salariu) : nume{std::move(n)}, salariuZilnic{salariu} {}
    [[nodiscard]] int cerereSalariu() const { return salariuZilnic; }
    [[nodiscard]] const std::string& getNume() const { return nume; }
    void plateste() { platitAzi = true; }
    void reseteazaZiua() { platitAzi = false; }
    friend std::ostream& operator<<(std::ostream& os, const Angajat& a) {
        return os << "Angajat: " << a.nume << " | Salariu: " << a.salariuZilnic << " bani/zi";
    }
};

class Veterinar {
private:
    std::string numeClinica;
    int tarifTratament{40};
public:
    explicit Veterinar(std::string nume) : numeClinica{std::move(nume)} {}
    void trateazaCireada(std::vector<std::unique_ptr<Bovina>>& cireada, int& baniFerma, Istoric& jurnal) const {
        for (auto& b : cireada) {
            if (b->esteBolnava()) {
                if (baniFerma >= tarifTratament) {
                    baniFerma -= tarifTratament;
                    b->vindeca();
                    jurnal.adaugaEveniment("Medic din " + numeClinica + ": " + b->getNume() + " a fost vindecata.");
                } else {
                    jurnal.adaugaEveniment("AVERTISMENT: Nu sunt bani pentru tratament: " + b->getNume());
                }
            }
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const Veterinar& v) {
        return os << "Doctor Veterinar la " << v.numeClinica << " (Tarif: " << v.tarifTratament << " bani)";
    }
};

class Gratar {
private:
    int timpGatireSecunde{0};
public:
    explicit Gratar(int timp = 0) : timpGatireSecunde{timp} {}
    [[nodiscard]] StareCarne verificaStare() const {
        if (timpGatireSecunde < 175) return StareCarne::NEFACUTA;
        if (timpGatireSecunde > 185) return StareCarne::ARSA;
        return StareCarne::PERFECTA;
    }
    int vindeMancare(const std::string& tip, const Piata& piataCurenta, SistemRealizari& ach, Istoric& jurnal) const {
        StareCarne stare = verificaStare();
        if (stare == StareCarne::PERFECTA) {
            ach.deblocheazaBucatar(jurnal);
            return (tip == "ciorba") ? (piataCurenta.getPretCarne() / 2) : piataCurenta.getPretCarne();
        }
        std::cout << "[GRATAR] Atentie: Carnea este " << (stare == StareCarne::ARSA ? "ARSA" : "NEFACUTA") << "!\n";
        return 5;
    }
};

class Contract {
private:
    std::string companie;
    int necesarLapte;
    int lapteColectat{0};
    int recompensaBani;
    int zileRamase;
    bool finalizat{false};
public:
    explicit Contract(std::string comp, int necesar, int rec, int zile)
        : companie{std::move(comp)}, necesarLapte{necesar}, recompensaBani{rec}, zileRamase{zile} {
        if (companie.empty() || necesarLapte <= 0 || recompensaBani <= 0 || zileRamase < 0)
            throw EroareContract("Contract invalid (campuri nevalide)");
    }
    [[nodiscard]] bool esteFinalizat() const { return finalizat; }
    [[nodiscard]] bool esteExpirat() const { return zileRamase <= 0 && !finalizat; }
    [[nodiscard]] int getRecompensa() const { return recompensaBani; }
    [[nodiscard]] const std::string& getCompanie() const { return companie; }
    int adaugaLapte(int cantitate) {
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
    void treceZiua() {
        if (!finalizat && zileRamase > 0) zileRamase--;
    }
    friend std::ostream& operator<<(std::ostream& os, const Contract& c) {
        os << "Contract " << c.companie << " [" << c.lapteColectat << "/" << c.necesarLapte << "L] ";
        if (c.finalizat) os << "- FINALIZAT";
        else if (c.esteExpirat()) os << "- EXPIRAT";
        else os << "- Zile: " << c.zileRamase;
        return os;
    }
};

class CladireAuxiliara {
private:
    std::string nume;
    int bonusProductie;
    int costIntretinere;
public:
    explicit CladireAuxiliara(std::string n, int bonus, int cost)
        : nume{std::move(n)}, bonusProductie{bonus}, costIntretinere{cost} {}
    [[nodiscard]] int aplicaBonus(int productie) const { return productie + bonusProductie; }
    [[nodiscard]] int getCost() const { return costIntretinere; }
    [[nodiscard]] const std::string& getNume() const { return nume; }
    friend std::ostream& operator<<(std::ostream& os, const CladireAuxiliara& c) {
        return os << "Cladire: " << c.nume << " (Bonus: +" << c.bonusProductie << "L lapte)";
    }
};

class Ferma {
private:
    std::string numeF;
    std::string numeP;
    std::vector<std::unique_ptr<Bovina>> cireada{};
    std::vector<Angajat> echipa{};
    std::vector<Contract> contracte{};
    std::vector<CladireAuxiliara> anexe{};
    Piata piataLocala{};
    Istoric jurnal{};
    Vremea meteo{};
    Veterinar doc{"Clinica VetHappy"};
    SistemRealizari trofee{};
    Hambar hambarCentral{};
    int bani{250};
    int stocLapte{0};
    int capacitateMaxima{5};
    int ziuaCurenta{1};
    std::mt19937 generator{std::random_device{}()};

public:
    explicit Ferma(std::string nf, std::string np);
    // Deep copy prin clone; op= copy-and-swap
    Ferma(const Ferma& other);
    Ferma& operator=(Ferma other);
    friend void swap(Ferma& a, Ferma& b);

    void inceputJoc();
    void angajeaza(const std::string& numeAngajat, int salariu);
    void adaugaContract(const std::string& companie, int necesar, int recompensa, int zile);
    void construiesteAnexa(const std::string& numeAnexa, int bonus, int intretinere, int pret);
    void cumparaProvizii(const Magazin& magazin, const std::string& numeProdus, int cantitate);
    void cheamaVeterinarul();
    void platesteCheltuieli();
    void proceseazaBiologie();
    void mulge();
    void proceseazaVanzari();
    void hranesteDinHambar(const Magazin& magazin, const std::string& numeProdus);
    void gatesteVitel(size_t index, int secunde);

    // cppcheck-suppress unusedFunction
    [[nodiscard]] const Istoric& getIstoric() const { return jurnal; }
    // cppcheck-suppress unusedFunction
    [[nodiscard]] const Hambar& getHambar() const { return hambarCentral; }
    // cppcheck-suppress unusedFunction
    [[nodiscard]] const Piata& getPiata() const { return piataLocala; }

    friend std::ostream& operator<<(std::ostream& os, const Ferma& f);
};