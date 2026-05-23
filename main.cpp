#include <iostream>
#include "ferma.h"
#include "vacuta.h"
#include "gaina.h"
#include "exceptii.h"

int main() {
    std::cout << "--- RULARE TEMA 2 ---\n\n";

    // TEST 1: Excepții
    try {
        std::cout << "[Test Excepție] Animal invalid...\n";
        Gaina g_invalida("", -1, 1);
    } catch (const EroareFerma& e) {
        std::cout << ">> Prinsa corect: " << e.what() << "\n\n";
    }

    try {
        Ferma ferma("Ferma Vesela");

        // TEST 2: Polimorfism si Adaugare
        Vacuta v1("Milka", 4, 15);
        Gaina g1("Cocuta", 2, 2);

        ferma.adaugaAnimal(v1);
        ferma.adaugaAnimal(g1);
        ferma.catalog();

        // TEST 3: Dynamic Cast
        ferma.raporteazaProductia();

        // TEST 4: Atribute Statice
        std::cout << "\nTotal animale alocate istoric: " << Animal::getTotalAnimale() << "\n";

        // TEST 5: Regula celor 3 (Deep Copy verificat de Valgrind)
        std::cout << "\n[Test Copy-And-Swap]\n";
        Ferma fermaCopie = ferma; // Apeleaza Copy Constructor

        Ferma fermaAlocata("Test");
        fermaAlocata = ferma;     // Apeleaza Operator=

        std::cout << "Copie: ";
        fermaCopie.raporteazaProductia();

    } catch (const EroareFerma& e) {
        std::cerr << "Eroare logica ferma: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Eroare generala: " << e.what() << "\n";
    }

    return 0;
}