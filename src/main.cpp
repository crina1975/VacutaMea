#include <iostream>
#include "ferma.hpp"
#include "vaca.hpp"
#include "gaina.hpp"
#include "oaie.hpp"
#include "exceptii.hpp"

int main() {
    try {
        std::cout << "--- START SIMULARE ---\n";
        Ferma ferma("Ferma Valea Verde", 300);

        ferma.adaugaAnimal(std::make_unique<Vaca>("Milka", 3, 15));
        ferma.adaugaAnimal(std::make_unique<Vaca>("Joiana", 5, 20));
        ferma.adaugaAnimal(std::make_unique<Gaina>("Cocuta", 1, 2));
        ferma.adaugaAnimal(std::make_unique<Oaie>("Miorita", 2));
        ferma.adaugaAnimal(std::make_unique<Oaie>("Bela", 4));

        std::cout << ferma;

        Articol iarba("Iarba Premium", 25);
        ferma.hranesteToateAnimalele(iarba);

        ferma.simuleazaZi();
        ferma.colecteazaTot();
        ferma.tundeOile();

        ferma.simuleazaZi();
        ferma.cheamaVeterinar();

        std::cout << ferma;

        std::cout << "\n[Test Copy-And-Swap Idiom]\n";
        Ferma fermaClonata = ferma;
        std::cout << fermaClonata;

    } catch (const EroareAplicatie& e) {
        std::cerr << "\n[Eroare Aplicatie]: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "\n[Eroare Standard C++]: " << e.what() << "\n";
        return 1;
    }

    std::cout << "\nSimulare incheiata cu succes. Total animale create: " << Animal::getTotalAnimale() << "\n";
    return 0;
}