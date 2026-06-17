#include <iostream>
#include "ferma.hpp"
#include "vaca.hpp"
#include "gaina.hpp"
#include "oaie.hpp"
#include "porc.hpp"
#include "exceptii.hpp"
#include "grafica.hpp"

int main() {
    try {
        InterfataGrafica::afiseazaEcranIncarcare();
        InterfataGrafica::afiseazaFermaGrafica();
        InterfataGrafica::afiseazaManualJocMasiv();

        std::cout << "--- START SIMULARE ---\n";
        Ferma ferma("Ferma Valea Verde", 300);

        ferma.adaugaAnimal(std::make_unique<Vaca>("Milka", 3, 15));
        InterfataGrafica::afiseazaVacaGrafica();

        ferma.adaugaAnimal(std::make_unique<Gaina>("Cocuta", 1, 2));
        InterfataGrafica::afiseazaGainaGrafica();

        ferma.adaugaAnimal(std::make_unique<Oaie>("Miorita", 2));
        InterfataGrafica::afiseazaOaieGrafica();

        ferma.adaugaAnimal(std::make_unique<Porc>("Ghita", 1));

        std::cout << ferma;

        Articol iarba("Iarba Premium", 25);
        ferma.hranesteToateAnimalele(iarba);

        ferma.simuleazaZi();
        ferma.colecteazaTot();
        ferma.tundeOile();

        InterfataGrafica::afiseazaTractor();

        ferma.simuleazaZi();
        ferma.cheamaVeterinar();

        std::cout << ferma;

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