#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "articol.hpp"

enum class StareSanatate { SANATOASA, BOLNAVA };
enum class TipVreme { INSORIT, PLOIOS, FURTUNA };

class Animal {
protected:
    std::string nume;
    int varsta;
    int energie;
    StareSanatate sanatate;
    static int contor_animale;

    virtual void afisare_(std::ostream& os) const = 0;
    virtual void treceTimpul_(TipVreme vreme) = 0;
    virtual int colecteazaProductie_() = 0;

public:
    Animal(std::string n, int v);
    virtual ~Animal() = default;
    Animal(const Animal&) = default;
    Animal& operator=(const Animal&) = default;

    static int getTotalAnimale();

    void afisare(std::ostream& os) const;
    void treceTimpul(TipVreme vreme);
    int colecteazaProductie();

    virtual void hraneste(const Articol& a) = 0;
    [[nodiscard]] virtual std::unique_ptr<Animal> clone() const = 0;

    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] bool esteBolnav() const;
    void vindeca();

    friend std::ostream& operator<<(std::ostream& os, const Animal& a);
};