#ifndef FERMA_H
#define FERMA_H

#include <string>
#include <vector>
#include "animal.h"
#include "vacuta.h"
#include "gaina.h"

class Ferma {
private:
    std::string numeF;
    std::vector<Animal*> animale;
    int bani;

public:
    explicit Ferma(std::string nf);
    ~Ferma();
    Ferma(const Ferma& other);
    Ferma& operator=(Ferma other);
    friend void swap(Ferma& f1, Ferma& f2);

    void adaugaAnimal(Animal* animalNou);
    void adunaResurse();
    void plateste(int cost);
    void afisareDetalii() const;
};

#endif