#pragma once
#include <memory>
#include <string>
#include <random>
#include <iosfwd>
#include "exceptii.hpp"

// Enumerările necesare pentru întreaga ierarhie
enum class Sex { FEMELA, MASCUL };
enum class StareCarne { NEFACUTA, PERFECTA, ARSA };
enum class TipVreme { INSORIT, PLOIOS, FURTUNA, CANICULA };
enum class StareSanatate { SANATOASA, BOLNAVA, CRITICA };

// Forward declaration pentru a evita includerea circulară a Articolului
class Articol;

class Bovina {
public:
    // Destructor virtual esențial pentru orice clasă polimorfă
    virtual ~Bovina() = default;

    // --- INTERFAȚA PUBLICĂ (NVI Pattern) ---
    // Publicul apelează metodele non-virtuale, care deleagă către implementări private.
    void treceTimpul(TipVreme vremeCurenta, std::mt19937& gen) { treceTimpul_(vremeCurenta, gen); }
    void hraneste(const Articol& m) { hraneste_(m); }

    // Metode polimorfice publice
    virtual int mulge() { return 0; }
    virtual bool verificaNastere() { return false; }
    virtual void vindeca() = 0;
    virtual void ramaneInsarcinata() {}

    // Metadate obligatorii (interfață)
    [[nodiscard]] virtual bool esteAdult() const = 0;
    [[nodiscard]] virtual Sex getSex() const = 0;
    [[nodiscard]] virtual const std::string& getNume() const = 0;
    [[nodiscard]] virtual bool vreaSaFuga() const = 0;
    [[nodiscard]] virtual bool esteBolnava() const = 0;

    // Constructor virtual (esențial pentru "Copy Constructor" în vectori de pointeri)
    [[nodiscard]] virtual std::unique_ptr<Bovina> clone() const = 0;

    // Afișare polimorfă folosind operatorul <<
    friend std::ostream& operator<<(std::ostream& os, const Bovina& b) {
        b.afisare_(os);
        return os;
    }

protected:
    // Implementările specifice clasei derivate (detalii de implementare)
    virtual void treceTimpul_(TipVreme, std::mt19937&) = 0;
    virtual void hraneste_(const Articol&) = 0;
    virtual void afisare_(std::ostream& os) const = 0;
};