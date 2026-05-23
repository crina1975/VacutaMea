#pragma once
#include "animal.h" // Presupune că Animal este baza

class Gaina : public Animal {
private:
    int ouaZilnic;

protected:
    // Suprascriem metoda de afișare pentru a include specificul găinii
    void afisare(std::ostream& os) const override;

public:
    // Constructor
    Gaina(std::string n, int v, int oua);

    // Destructor virtual moștenit
    ~Gaina() override = default;

    // Metodă pentru clonare polimorfă
    [[nodiscard]] std::unique_ptr<Animal> clone() const override;

    // Metodă virtuală pură implementată
    void scoateSunet() const override;

    // Metodă specifică
    [[nodiscard]] int adunaOua() const;
};