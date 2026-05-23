#include "ferma.h"
#include "animal.h"
#include "vacuta.h"
#include "gaina.h"
#include "exceptii.h"
#include "utilitare.h"
#include <iostream>

int main() {
    std::cout << "--- SIMULARE FERMA TEMA 2 ---\n\n";

    try {
        Ferma fermaMea("Ferma Vesela");

        fermaMea.adaugaAnimal(new Vacuta("Milka", 4, Sex::FEMELA));
        fermaMea.adaugaAnimal(new Gaina("Geta", 3, Sex::FEMELA));

        fermaMea.afisareDetalii();
        std::cout << "\n";

        fermaMea.adunaResurse();
        std::cout << "\n";

        Ferma fermaCopie = fermaMea;
        fermaCopie.afisareDetalii();

        fermaMea.plateste(600);

    } catch (const EroareFaliment& e) {
        std::cout << "[FALIMENT] " << e.what() << "\n";
    } catch (const EroareAnimalInvalid& e) {
        std::cout << "[ANIMAL INVALID] " << e.what() << "\n";
    } catch (const EroareFerma& e) {
        std::cout << "[EROARE] " << e.what() << "\n";
    }

    try {
        Animal* animalGresit = new Vacuta("VacaGresita", -5, Sex::FEMELA);
        delete animalGresit;
    } catch (const EroareAnimalInvalid& e) {
        std::cout << "\n[EXCEPTIE PRINSA CORRECT] " << e.what() << "\n";
    }

    return 0;
}