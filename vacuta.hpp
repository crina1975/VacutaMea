#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include "bovina.hpp"
#include "animal.h"

// Status este un helper pentru clasa Vacuta
class Status {
private:
    std::string nume{"Parametru"};
    int valoare{100};
public:
    explicit Status(std::string n = "Parametru", int v = 100)
        : nume{std::move(n)}, valoare{v} {}

    void modifica(int delta) { valoare = std::clamp(valoare + delta, 0, 100); }
    [[nodiscard]] int getValoare() const { return valoare; }

    friend std::ostream& operator<<(std::ostream& os, const Status& s) {
        return os << s.nume << ": " << s.valoare << "/100";
    }
};

class Articol {
private:
    std::string nume{"Nimic"};
    int pret{0};
    int putereSatietate{0};
public:
    explicit Articol(std::string n = "Nimic", int p = 0, int sat = 0)
        : nume{std::move(n)}, pret{p}, putereSatietate{sat} {}

    [[nodiscard]] int getPret() const { return pret; }
    [[nodiscard]] int getPutereSatietate() const { return putereSatietate; }
    [[nodiscard]] const std::string& getNume() const { return nume; }

    friend std::ostream& operator<<(std::ostream& os, const Articol& a) {
        return os << a.nume << " (" << a.pret << " bani)";
    }
};

class Vacuta : public Animal {
private:
    std::string nume;
    Status foame{"Foame", 30};
    Status energie{"Energie", 100};
    int varsta{0};
    Sex sex{Sex::FEMELA};
    StareSanatate sanatate{StareSanatate::SANATOASA};
    int contorEnergieMaxima{0};
    bool insarcinata{false};
    int zileSarcina{0};

protected:
    // Implementarea metodei virtuale pentru afișare (NVI pattern)
    void afisare_(std::ostream& os) const override;

public:
    // Constructorul trebuie să fie explicit pentru a evita conversii accidentale
    explicit Vacuta(std::string n, int v, Sex s);

    // Default-urile pentru regula celor 5
    Vacuta(const Vacuta&) = default;
    Vacuta& operator=(const Vacuta&) = default;
    ~Vacuta() override = default;

    // Implementări Bovina API (override obligatoriu)
    [[nodiscard]] bool esteAdult() const override;
    [[nodiscard]] Sex getSex() const override;
    [[nodiscard]] const std::string& getNume() const override;
    [[nodiscard]] bool vreaSaFuga() const override;
    [[nodiscard]] bool esteBolnava() const override;

    void vindeca() override;
    void ramaneInsarcinata() override;
    void treceTimpul_(TipVreme vremeCurenta, std::mt19937& generatorRef) override;
    void hraneste_(const Articol& m) override;
    int mulge() override;
    bool verificaNastere() override;

    // Constructor virtual (clonare)
    [[nodiscard]] std::unique_ptr<Bovina> clone() const override {
        return std::make_unique<Vacuta>(*this);
    }
};