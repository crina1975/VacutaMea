#pragma once
#include <string>
#include <iostream>
#include <memory>

// Forward declaration pentru a evita includerea inutilă a altor headere
class Articol;

class Animal {
protected:
    std::string nume;
    int varsta;
    int energie{100}; // Inițializare în-clasă (recomandată de Clang-Tidy)
    const int id;

    // Atribut static pentru id-uri unice
    static int contor_animale;

    // Metodă virtuală protected pentru afișare (NVI pattern)
    virtual void afisare(std::ostream& os) const;

public:
    // Constructorul aruncă excepții pentru a preveni obiecte invalide
    Animal(std::string n, int v);

    // Destructor virtual: esențial în ierarhiile polimorfice
    virtual ~Animal() = default;

    // Regula celor 5: asigurăm comportamentul corect la copiere/mutare
    Animal(const Animal& other) = default;
    Animal& operator=(const Animal& other) = default;
    Animal(Animal&& other) noexcept = default;
    Animal& operator=(Animal&& other) noexcept = default;

    // Metodă pentru clonare polimorfă (Constructor virtual)
    [[nodiscard]] virtual std::unique_ptr<Animal> clone() const = 0;

    // Funcție virtuală pură (Animal devine clasă abstractă)
    virtual void scoateSunet() const = 0;

    // Metode getter simple
    [[nodiscard]] int getId() const { return id; }

    // Funcție statică pentru a accesa contorul
    static int getTotalAnimale();

    // Operator << definit ca friend pentru afișare
    friend std::ostream& operator<<(std::ostream& os, const Animal& a);
};