#pragma once
#include "animal.hpp"

class Vaca : public Animal {
private:
    int litriLapteZilnic;

protected:
    void afisare_(std::ostream& os) const override;
    void treceTimpul_(TipVreme vreme) override;
    int colecteazaProductie_() override;

public:
    Vaca(std::string n, int v, int lapte);
    void hraneste(const Articol& a) override;
    [[nodiscard]] std::unique_ptr<Animal> clone() const override;
};