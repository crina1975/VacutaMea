#pragma once
#include "animal.h"

class Gaina : public Animal {
private:
    int oua;

protected:
    void afisare(std::ostream& os) const override;

public:
    Gaina(std::string n, int v, int oua_zilnic);

    [[nodiscard]] Animal* clone() const override;
    void scoateSunet() const override;

    int adunaOua() const;
};