#ifndef GAINA_H
#define GAINA_H

#include "Animal.h"

class Gaina : public Animal {
public:
    Gaina(std::string n, int v, Sex s);
    Animal* clone() const override;
    void scoateSunet() const override;
    int adunaOua();
    void afisare(std::ostream& os) const override;
};

#endif