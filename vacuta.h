#pragma once
#include "animal.h"

class Vacuta : public Animal {
private:
    int litriLapte;

protected:
    void afisare(std::ostream& os) const override;

public:
    Vacuta(std::string n, int v, int lapte);

    [[nodiscard]] Animal* clone() const override;
    void scoateSunet() const override;

    int mulge() const;
};