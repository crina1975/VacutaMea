#ifndef UTILITARE_H
#define UTILITARE_H

#include <string>
#include <vector>
#include <iostream>
#include <random>

enum class StareCarne { NEFACUTA, PERFECTA, ARSA };
enum class TipVreme { INSORIT, PLOIOS, FURTUNA, CANICULA };

class Istoric {
private:
    std::vector<std::string> loguri;
public:
    void adaugaEveniment(const std::string& eveniment);
    friend std::ostream& operator<<(std::ostream& os, const Istoric& istoric);
};

class Piata {
private:
    int pretLapte = 5;
    int pretCarne = 80;
    std::mt19937 generator;
public:
    Piata();
    void fluctueazaPreturi();
    int getPretLapte() const;
    int getPretCarne() const;
    friend std::ostream& operator<<(std::ostream& os, const Piata& p);
};

class Articol {
private:
    std::string nume;
    int pret;
    int putereSatietate;
public:
    explicit Articol(std::string n = "Nimic", int p = 0, int sat = 0);
    int getPret() const;
    int getPutereSatietate() const;
    const std::string& getNume() const;
    friend std::ostream& operator<<(std::ostream& os, const Articol& a);
};

class Magazin {
private:
    std::vector<Articol> catalog;
public:
    Magazin();
    ~Magazin();
    Magazin(const Magazin& other);
    Magazin& operator=(const Magazin& other);
    Articol cautaArticol(const std::string& numeCautat) const;
    friend std::ostream& operator<<(std::ostream& os, const Magazin& m);
};

#endif