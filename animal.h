#pragma once
#include <string>
#include <iostream>

class Animal {
protected:
    std::string nume;
    int varsta;
    int energie{100}; // Inițializare directă pentru Clang-Tidy
    const int id;

    static int contor_animale; // Atribut static

    // Interfață non-virtuală
    virtual void afisare(std::ostream& os) const;

public:
    Animal(std::string n, int v);

    virtual ~Animal() = default;

    // Regula celor 5 pentru clasa de bază (cerut de lintere moderne)
    Animal(const Animal& other) = default;
    Animal& operator=(const Animal& other) = default;
    Animal(Animal&& other) = default;
    Animal& operator=(Animal&& other) = default;

    // Constructor virtual
    [[nodiscard]] virtual Animal* clone() const = 0;

    virtual void scoateSunet() const = 0;

    static int getTotalAnimale(); // Funcție statică

    friend std::ostream& operator<<(std::ostream& os, const Animal& a);
};