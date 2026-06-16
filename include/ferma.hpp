#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "animal.hpp"
#include "utilitare.hpp"

class Ferma {
private:
    std::string numeF;
    std::string numeP;

    std::vector<std::unique_ptr<Animal>> animale;

    std::vector<Angajat> echipa{};
    std::vector<Contract> contracte{};
    std::vector<CladireAuxiliara> anexe{};

    Piata piataLocala{};
    Istoric jurnal{};
    Vremea meteo{};
    Hambar hambarCentral{};

    int bani{250};
    int stocResurse{0};
    int capacitateMaxima{10};
    int ziuaCurenta{1};

public:
    explicit Ferma(std::string nf, std::string np, int buget = 250);

    Ferma(const Ferma& other);
    Ferma& operator=(Ferma other);
    friend void swap(Ferma& a, Ferma& b) noexcept;
    ~Ferma() = default;

    void adaugaAnimal(std::unique_ptr<Animal> animal);
    void angajeaza(const std::string& numeAngajat, int salariu);
    void adaugaContract(const std::string& companie, int necesar, int recompensa, int zile);
    void construiesteAnexa(const std::string& numeAnexa, int bonus, int intretinere, int pret);

    void proceseazaZiua();
    void proceseazaVanzari();
    void platesteCheltuieli();
    void cumparaProvizii(const Magazin& magazin, const std::string& numeProdus, int cantitate);

    void cheamaVeterinarSpecialist();

    [[nodiscard]] const Istoric& getIstoric() const { return jurnal; }
    [[nodiscard]] const Hambar& getHambar() const { return hambarCentral; }
    [[nodiscard]] const Piata& getPiata() const { return piataLocala; }

    friend std::ostream& operator<<(std::ostream& os, const Ferma& f);
};