#pragma once
#include <memory>
#include <string>
#include <random>
#include <iosfwd>
#include "exceptii.hpp"

enum class Sex { FEMELA, MASCUL };
enum class StareCarne { NEFACUTA, PERFECTA, ARSA };
enum class TipVreme { INSORIT, PLOIOS, FURTUNA, CANICULA };
enum class StareSanatate { SANATOASA, BOLNAVA, CRITICA };

class Articol;

class Bovina {
public:
    virtual ~Bovina() = default;

    // NVI: interfață non-virtuală care delegă la implementarea virtuală
    void treceTimpul(TipVreme vremeCurenta, std::mt19937& gen) { treceTimpul_(vremeCurenta, gen); }
    void hraneste(const Articol& m) { hraneste_(m); }

    // Virtuale publice
    virtual int mulge() { return 0; }
    virtual bool verificaNastere() { return false; }

    // Metadate obligatorii
    [[nodiscard]] virtual bool esteAdult() const = 0;
    [[nodiscard]] virtual Sex getSex() const = 0;
    [[nodiscard]] virtual const std::string& getNume() const = 0;
    [[nodiscard]] virtual bool vreaSaFuga() const = 0;
    [[nodiscard]] virtual bool esteBolnava() const = 0;
    virtual void vindeca() = 0;
    virtual void ramaneInsarcinata() {} // implicit nimic

    // Constructor virtual (deep copy polimorf)
    [[nodiscard]] virtual std::unique_ptr<Bovina> clone() const = 0;

    // Afișare polimorfă
    friend std::ostream& operator<<(std::ostream& os, const Bovina& b) {
        b.afisare_(os);
        return os;
    }

    // Exemplu de static
    static int urmator_id() { return ++gen_id; }

protected:
    virtual void treceTimpul_(TipVreme, std::mt19937&) = 0;
    virtual void hraneste_(const Articol&) = 0;
    virtual void afisare_(std::ostream& os) const = 0;

private:
    inline static int gen_id = 0;
};