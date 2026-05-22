#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>
#include "Exceptii.h"

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

    int getId() const;
    Sex getSex() const;
    bool esteAdult() const;
    const std::string& getNume() const;

    friend std::ostream& operator<<(std::ostream& os, const Animal& a);
};

#endif