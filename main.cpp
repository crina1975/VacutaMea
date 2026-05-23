#include <iostream>
#include "Ferma.hpp"
#include "Vacuta.hpp"
#include "Gaina.hpp"
#include "Exceptii.hpp"

int main() {
    std::cout << "--- START RULARE TEMA 2 ---\n\n";

    // TEST 1: Excepții (Throw în constructor + Try/Catch)
    try {
        std::cout << "[Test Excepție] Încercăm să creăm un animal invalid...\n";
        Vacuta v_invalida("", -2, 10); // Nume gol + Varsta negativa
    }
    catch (const EroareParametru& e) {
        std::cout << ">> EROARE PRINSĂ: " << e.what() << "\n\n";
    }

    // TEST 2: Fluxul principal (Polimorfism, Dynamic Cast, Copy and Swap)
    try {
        Ferma fermaMea("Ferma Vesela", 500);

        Vacuta v1("Milka", 4, 15);
        Gaina g1("Cocuta", 2, 2);
        Gaina g2("Geta", 1, 1);

        fermaMea.adaugaAnimal(v1);
        fermaMea.adaugaAnimal(g1);
        fermaMea.adaugaAnimal(g2);

        // Afisarea va face cast automat și va accesa functiile suprascrise
        fermaMea.afiseazaAnimale();

        // Productia apeleaza dynamic_cast pentru a verifica ce este animalul la rulare
        fermaMea.colecteazaProductia();

        // TEST 3: Metode și variabile statice
        std::cout << "\n[Test Static] Total animale trecute prin sistem vreodata: "
                  << Animal::getContorId() << "\n";

        // TEST 4: Copy and Swap (Testăm memoria pe copy constructor și assign operator)
        std::cout << "\n[Test Copy-And-Swap] Creem copii profunde ale fermei...\n";

        Ferma fermaCopie = fermaMea;           // CC (Constructor de copiere)
        Ferma fermaAtribuire("Temporar", 0);
        fermaAtribuire = fermaMea;             // OP= (Operatorul Copy and Swap)

        std::cout << "Ferma Copie colecteaza independent productia: ";
        fermaCopie.colecteazaProductia();

    }
    catch (const EroareFerma& e) {
        std::cout << "EROARE DE LOGICA A FERMEI: " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "EROARE GENERALA: " << e.what() << "\n";
    }

    return 0;
}