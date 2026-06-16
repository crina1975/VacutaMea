#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <random>
#include "animal.hpp"
#include "exceptii.hpp"

class Articol {
private:
    std::string nume;
    int pret;
    int putereSatietate;
public:
    explicit Articol(std::string n = "Nimic", int p = 0, int sat = 0);
    [[nodiscard]] int getPret() const;
    [[nodiscard]] int getPutereSatietate() const;
    [[nodiscard]] const std::string& getNume() const;
    friend std::ostream& operator<<(std::ostream& os, const Articol& a);
};

class Istoric {
private:
    std::vector<std::string> loguri{};
public:
    void adaugaEveniment(const std::string& eveniment);
    friend std::ostream& operator<<(std::ostream& os, const Istoric& istoric);
};

class Piata {
private:
    int pretResurse = 5;
    std::mt19937 generator;
public:
    Piata();
    void fluctueazaPreturi();
    [[nodiscard]] int getPretResurse() const;
    friend std::ostream& operator<<(std::ostream& os, const Piata& p);
};

class Vremea {
private:
    TipVreme stadiuCurent = TipVreme::INSORIT;
    std::mt19937 generator;
public:
    Vremea();
    void schimbaVremea();
    [[nodiscard]] TipVreme getVremeCurenta() const;
    [[nodiscard]] std::string getNumeVreme() const;
    friend std::ostream& operator<<(std::ostream& os, const Vremea& v);
};

class Magazin {
private:
    std::vector<Articol> catalog;
public:
    Magazin();
    ~Magazin() = default;
    Magazin(const Magazin& other);
    Magazin& operator=(const Magazin& other);
    [[nodiscard]] Articol cautaArticol(const std::string& numeCautat) const;
    friend std::ostream& operator<<(std::ostream& os, const Magazin& m);
};

class Hambar {
private:
    std::map<std::string, int> stocuri{};
public:
    void adauga(const std::string& numeArticol, int cantitate);
    bool consuma(const std::string& numeArticol);
    friend std::ostream& operator<<(std::ostream& os, const Hambar& h);
};

class Angajat {
private:
    std::string nume;
    int salariuZilnic{0};
    bool platitAzi{false};
public:
    explicit Angajat(std::string n, int salariu);
    [[nodiscard]] int cerereSalariu() const;
    [[nodiscard]] const std::string& getNume() const;
    void plateste();
    void reseteazaZiua();
    friend std::ostream& operator<<(std::ostream& os, const Angajat& a);
};


class Contract {
private:
    std::string companie;
    int necesarResurse;
    int resurseColectate{0};
    int recompensaBani;
    int zileRamase;
    bool finalizat{false};
public:
    explicit Contract(std::string comp, int necesar, int rec, int zile);
    [[nodiscard]] bool esteFinalizat() const;
    [[nodiscard]] bool esteExpirat() const;
    [[nodiscard]] int getRecompensa() const;
    [[nodiscard]] const std::string& getCompanie() const;
    int adaugaResurse(int cantitate);
    void treceZiua();
    friend std::ostream& operator<<(std::ostream& os, const Contract& c);
};


class CladireAuxiliara {
private:
    std::string nume;
    int bonusProductie;
    int costIntretinere;
public:
    explicit CladireAuxiliara(std::string n, int bonus, int cost);
    [[nodiscard]] int aplicaBonus(int productie) const;
    [[nodiscard]] int getCost() const;
    [[nodiscard]] const std::string& getNume() const;
    friend std::ostream& operator<<(std::ostream& os, const CladireAuxiliara& c);
};