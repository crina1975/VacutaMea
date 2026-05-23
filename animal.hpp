#pragma once
#include <string>
#include <iostream>

class Animal {
protected:
    std::string nume;
    int varsta;

    // Atribut constant initializat la construire
    const int id;

    // Atribut STATIC: comun pentru toate obiectele, retine cate animale au fost create vreodata
    static int contor_id;

    // Functie virtuala pentru afisare polimorfica (tip interfață non-virtuală)
    virtual void afisare(std::ostream& os) const {
        os << "[ID: " << id << "] " << nume << " (Varsta: " << varsta << " ani)";
    }

public:
    Animal(std::string n, int v);

    // Destructor virtual obligatoriu
    virtual ~Animal() = default;

    // CONSTRUCTOR VIRTUAL (Clonare)
    virtual Animal* clone() const = 0;

    // Functie virtuala pura
    virtual void scoateSunet() const = 0;

    int getId() const { return id; }

    // Functie STATICĂ
    static int getContorId() { return contor_id; }

    // Interfata de afisare
    friend std::ostream& operator<<(std::ostream& os, const Animal& a) {
        a.afisare(os);
        return os;
    }
};