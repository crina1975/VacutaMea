#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>
#include "exceptii.h"

enum class Sex { FEMELA, MASCUL };

class Animal {
protected:
    std::string nume;
    int varsta;
    Sex sex;
    static int contorAnimale;
    int idAnimal;

public:
    Animal(std::string n, int v, Sex s);
    virtual ~Animal() = default;

    virtual Animal* clone() const = 0;
    virtual void scoateSunet() const = 0;
    virtual void afisare(std::ostream& os) const;

    // cppcheck-suppress unusedFunction
    int getId() const;
    // cppcheck-suppress unusedFunction
    Sex getSex() const;
    // cppcheck-suppress unusedFunction
    bool esteAdult() const;
    // cppcheck-suppress unusedFunction
    const std::string& getNume() const;

    friend std::ostream& operator<<(std::ostream& os, const Animal& a);
};

#endif