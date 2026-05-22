#include "ferma.h"
#include "animal.h"
#include "vacuta.h"
#include "gaina.h"
#include "exceptii.h"
#include <iostream>

int main() {
    std::cout << "--- SIMULARE FERMA TEMA 2 ---\n\n";

    try {
        Ferma fermaMea("Ferma Vesela");

        fermaMea.adaugaAnimal(new Vacuta("Milka", 4, Sex::FEMELA));
        fermaMea.adaugaAnimal(new Gaina("Geta", 3, Sex::FEMELA));
        fermaMea.adaugaAnimal(new Vacuta("Bumbu", 1, Sex::MASCUL));

        std::cout << ">>> DETALII INITIALE FERMA <<<\n";
        fermaMea.afisareDetalii();
        std::cout << "\n";

        std::cout << ">>> COLECTARE RESURSE POLIMORFICA <<<\n";
        fermaMea.adunaResurse();
        std::cout << "\n";

        std::cout << ">>> TESTARE REGULA CELOR 3 (CONSTRUCTOR DE COPIERE) <<<\n";
        Ferma fermaCopie = fermaMea;
        std::cout << "Detalii ferma copiata:\n";
        fermaCopie.afisareDetalii();
        std::cout << "\n";

        std::cout << ">>> TESTARE OPERATOR DE ATRIBUIRE <<<\n";
        Ferma altaFerma("Ferma Noua");
        altaFerma = fermaMea;
        std::cout << "\n";

        std::cout << ">>> TESTARE EXCEPTIE: FONDURI INSUFICIENTE <<<\n";
        fermaMea.plateste(600);

    } catch (const EroareFaliment& e) {
        std::cout << "[CATCH FALIMENT] " << e.what() << "\n";
    } catch (const EroareAnimalInvalid& e) {
        std::cout << "[CATCH ANIMAL INVALID] " << e.what() << "\n";
    } catch (const EroareFerma& e) {
        std::cout << "[CATCH EROARE FERMA] " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "[CATCH EXCEPTIE STANDARD] " << e.what() << "\n";
    }

    std::cout << "\n>>> TESTARE EXCEPTIE: CONSTRUCTOR ANIMAL INVALID <<<\n";
    try {
        Animal* animalGresit = new Vacuta("VacaGresita", -5, Sex::FEMELA);
        delete animalGresit;
    } catch (const EroareAnimalInvalid& e) {
        std::cout << "[CATCH CONSTRUCTOR] " << e.what() << "\n";
    }

    return 0;
}