#pragma once
#include "animal.h"
#include <vector>
#include <string>

class Ferma {
private:
    std::string numeFerma;
    std::vector<Animal*> animale;

public:
    explicit Ferma(std::string nume);

    // Regula celor 3: Copy Constructor, Destructor, Operator=
    Ferma(const Ferma& other);
    ~Ferma();
    Ferma& operator=(const Ferma& other); // Clang-Tidy preferă const ref cu temp copy intern

    // Funcție friend pt Copy and Swap Idiom
    friend void swap(Ferma& f1, Ferma& f2) noexcept;

    void adaugaAnimal(const Animal& a);
    void raporteazaProductia() const; // Utilizare dynamic_cast
    void catalog() const;
};