#ifndef VACUTA_H
#define VACUTA_H

#include "animal.h"

enum class StareSanatate { SANATOASA, BOLNAVA, CRITICA };

class Vacuta : public Animal {
private:
    int nivelFoame;
    int nivelEnergie;
    StareSanatate sanatate;

public:
    Vacuta(std::string n, int v, Sex s);
    Animal* clone() const override;
    void scoateSunet() const override;
    int mulge();
    void afisare(std::ostream& os) const override;
};

#endif