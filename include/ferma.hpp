#pragma once
#include <vector>
#include <memory>
#include <string>
#include "animal.hpp"

class Ferma {
private:
    std::string numeFerma;
    std::vector<std::unique_ptr<Animal>> animale;
    int buget;
    int stocProduse;
    int ziuaCurenta;

public:
    Ferma(std::string nume, int bugetInitial);

    Ferma(const Ferma& other);
    Ferma& operator=(Ferma other);
    ~Ferma() = default;

    friend void swap(Ferma& first, Ferma& second) noexcept;

    void adaugaAnimal(std::unique_ptr<Animal> animal);
    void simuleazaZi();
    void hranesteToateAnimalele(const Articol& hrana);
    void colecteazaTot();
    void tundeOile();
    void cheamaVeterinar();

    friend std::ostream& operator<<(std::ostream& os, const Ferma& f);
};