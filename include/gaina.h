#pragma once
#include "animal.hpp"

class Gaina : public Animal {
private:
    int ouaZilnic;

protected:
    void afisare_(std::ostream& os) const override;
    void treceTimpul_(TipVreme vreme) override;
    int colecteazaProductie_() override;

public:
    Gaina(std::string n, int v, int oua);
    void hraneste(const Articol& a) override;
    [[nodiscard]] std::unique_ptr<Animal> clone() const override;
};