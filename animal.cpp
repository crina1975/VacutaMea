#include "animal.h"
#include "exceptii.hpp"

// Inițializarea atributului static (trebuie să existe în .cpp pentru a fi alocat în memorie)
int Animal::contor_animale = 0;

// Constructorul clasei de bază
Animal::Animal(std::string n, int v)
    : nume(std::move(n)), varsta(v), id(++contor_animale) {
    // Validarea se face aici. Dacă aruncă excepție, obiectul NU se construiește.
    if (nume.empty()) {
        throw EroareParametru("Numele animalului nu poate fi gol!");
    }
    if (varsta < 0) {
        throw EroareParametru("Varsta nu poate fi negativa!");
    }
}

// Implementarea funcției de afișare (NVI Pattern - metoda protejată)
// Aceasta este baza pe care clasele derivate (Vacuta/Gaina) o vor extinde
void Animal::afisare(std::ostream& os) const {
    os << "[ID: " << getId() << "] " << nume << " (Varsta: " << varsta << " ani, Energie: " << energie << "%)";
}

// Funcție statică pentru a accesa contorul global
int Animal::getTotalAnimale() {
    return contor_animale;
}

// Operatorul << delegă către metoda virtuală afisare
std::ostream& operator<<(std::ostream& os, const Animal& a) {
    a.afisare(os);
    return os;
}