#pragma once
#include "animal.hpp"

class Oaie : public Animal {
private:
    int lungimeLana;

protected:
    void afisare_(std::ostream& os) const override;
    void treceTimpul_(TipVreme vreme) override;
    int colecteazaProductie_() override;

public:
    Oaie(std::string n, int v);
    void hraneste(const Articol& a) override;
    [[nodiscard]] std::unique_ptr<Animal> clone() const override;
    void scoateSunet() const override;
    int tundeLana();
};