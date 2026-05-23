#include "ferma.h"
#include "animal.h"
#include "vacuta.h"
#include "gaina.h"
#include "exceptii.h"
#include <iostream>

int main() {
    std::cout << "--- SIMULARE FERMA TEMA 2 ---\n\n";

    // 1. Testare memorie si polimorfism
    {
        Ferma fermaMea("Ferma Vesela");
        fermaMea.adaugaAnimal(new Vacuta("Milka", 4, Sex::FEMELA));
        fermaMea.adaugaAnimal(new Gaina("Geta", 3, Sex::FEMELA));

        fermaMea.afisareDetalii();
        fermaMea.adunaResurse();

        Ferma fermaCopie = fermaMea; // Testam constructorul de copiere
        fermaCopie.afisareDetalii();
    } // Aici toate fermele si animalele se distrug curat din memorie

    // 2. Testare Excepție (Faliment)
    try {
        Ferma fermaSaraca("Ferma Saraca");
        fermaSaraca.plateste(600);
    } catch (const EroareFaliment& e) {
        std::cout << "\n[FALIMENT PRIN DE CATCH] " << e.what() << "\n";
    }

    // 3. Testare Excepție (Animal Invalid)
    // Alocam pe stiva (fara new) pentru a evita orice confuzie a lui Valgrind
    try {
        Vacuta vacaGresita("Eroare", -5, Sex::FEMELA);
    } catch (const EroareAnimalInvalid& e) {
        std::cout << "[ANIMAL INVALID PRINS DE CATCH] " << e.what() << "\n";
    }

    return 0;
}