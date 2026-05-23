#pragma once
#include <vector>
#include <string>
#include "Animal.hpp"

class Ferma {
private:
    std::string numeFerma;
    int buget;
    std::vector<Animal*> animale; // Pointeri la clasa de bază

public:
    Ferma(std::string nume, int bugetInitial);

    // --- REGULA CELOR 3 / COPY-AND-SWAP IDIOM ---
    Ferma(const Ferma& other);             // CC
    Ferma& operator=(Ferma other);         // OP= (parametrul este luat prin valoare intentionat)
    ~Ferma();                              // Destructor

    // Functie friend pentru swap (esentiala pt copy-and-swap)
    friend void swap(Ferma& f1, Ferma& f2) noexcept;
    // --------------------------------------------

    void adaugaAnimal(const Animal& a);
    void colecteazaProductia() const; // Aici vom folosi dynamic_cast
    void afiseazaAnimale() const;
};