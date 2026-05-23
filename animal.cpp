#include "Animal.hpp"
#include "Exceptii.hpp"

// Initializarea atributului static (obligatoriu intr-un singur fisier .cpp)
int Animal::contor_id = 0;

Animal::Animal(std::string n, int v) : nume(std::move(n)), varsta(v), id(++contor_id) {
    // THROW IN CONSTRUCTOR - Validam datele; daca sunt gresite, obiectul nu se mai creeaza
    if (nume.empty()) {
        throw EroareParametru("Numele animalului nu poate fi gol!");
    }
    if (varsta < 0) {
        throw EroareParametru("Varsta nu poate fi negativa!");
    }
}