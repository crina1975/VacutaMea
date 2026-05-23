#include "vacuta.hpp"
#include <random>
#include <iostream>

// Constructorul apelează constructorul de bază și inițializează atributele specifice
Vacuta::Vacuta(std::string n, int v, Sex s)
    : Animal(std::move(n), v), sex{s} {}

// Implementări ale metodelor publice (NVI pattern - delegare către metodele virtuale private)
bool Vacuta::esteAdult() const { return varsta >= 3; }
Sex Vacuta::getSex() const { return sex; }
const std::string& Vacuta::getNume() const { return nume; }
bool Vacuta::vreaSaFuga() const { return foame.getValoare() >= 100; }
bool Vacuta::esteBolnava() const { return sanatate != StareSanatate::SANATOASA; }
void Vacuta::vindeca() { sanatate = StareSanatate::SANATOASA; }

void Vacuta::ramaneInsarcinata() {
    if (sex == Sex::FEMELA && esteAdult() && !insarcinata && sanatate == StareSanatate::SANATOASA) {
        insarcinata = true;
        zileSarcina = 0;
    }
}

// Implementări ale metodelor virtuale private (NVI protected)
void Vacuta::treceTimpul_(TipVreme vremeCurenta, std::mt19937& generatorRef) {
    int factorFoame = insarcinata ? 40 : 20;
    int factorEnergie = -10;

    if (vremeCurenta == TipVreme::CANICULA) factorFoame += 15;
    if (vremeCurenta == TipVreme::FURTUNA) factorEnergie -= 20;

    if (sanatate == StareSanatate::BOLNAVA) {
        factorEnergie -= 15;
        factorFoame += 10;
    }

    // Probabilitate de îmbolnăvire (10%)
    if (sanatate == StareSanatate::SANATOASA) {
        std::uniform_int_distribution<int> sansaBoala(1, 100);
        if (sansaBoala(generatorRef) <= 10) sanatate = StareSanatate::BOLNAVA;
    }

    foame.modifica(factorFoame);
    energie.modifica(factorEnergie);

    if (energie.getValoare() == 100 && sanatate == StareSanatate::SANATOASA) contorEnergieMaxima++;
    if (insarcinata) zileSarcina++;
}

void Vacuta::hraneste_(const Articol& m) {
    foame.modifica(-m.getPutereSatietate());
    energie.modifica(20);
    if (!esteAdult() && contorEnergieMaxima >= 5) {
        varsta = 3;
        std::cout << "[EVOLUTIE] " << nume << " a devenit adult!\n";
    }
}

int Vacuta::mulge() {
    if (sanatate != StareSanatate::SANATOASA) return 0;
    if (esteAdult() && sex == Sex::FEMELA && energie.getValoare() >= 30) {
        energie.modifica(-30);
        return 10;
    }
    return 0;
}

bool Vacuta::verificaNastere() {
    if (insarcinata && zileSarcina >= 3) {
        insarcinata = false;
        zileSarcina = 0;
        return true;
    }
    return false;
}

void Vacuta::afisare_(std::ostream& os) const {
    os << "[" << (sex == Sex::FEMELA ? "F" : "M") << "] " << nume
       << " (V:" << varsta << ") | " << foame << " | " << energie;
    if (insarcinata) os << " [INS]";
    if (sanatate == StareSanatate::BOLNAVA) os << " [BOLNAVA]";
}