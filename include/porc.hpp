#pragma once
#include "animal.hpp"

class Porc : public Animal {
private:
    int greutate;

protected:
    void afisare_(std::ostream& os) const override;
    void treceTimpul_(TipVreme vreme) override;
    int colecteazaProductie_() override;

public:
    Porc(std::string n, int v);
    void hraneste(const Articol& a) override;
    [[nodiscard]] std::unique_ptr<Animal> clone() const override;
    void scoateSunet() const override;
};