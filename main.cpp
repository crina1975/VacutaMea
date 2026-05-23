#include <iostream>
#include "ferma.hpp"

int main() {
    try {
        std::cout << "--- START SIMULARE COMPLETA FERMA ---\n";
        Magazin magazinComunal;
        std::cout << magazinComunal;

        std::string np = "Flavius";
        std::string nf = "Ferma Vesela";
        Ferma ferma(nf, np);
        ferma.inceputJoc();

        std::cout << "\n>>> TEST 1: Angajari, Cumparaturi si Cladiri <<<\n";
        ferma.angajeaza("Vasile (Mulgator)", 10);
        ferma.angajeaza("Ion (Ingrijitor)", 15);
        ferma.cumparaProvizii(magazinComunal, "Iarba", 30);
        ferma.cumparaProvizii(magazinComunal, "Fan_Premium", 15);
        ferma.construiesteAnexa("Sistem Automat Irigatii", 5, 5, 80);
        ferma.construiesteAnexa("Tractor Nou", 10, 20, 500);

        std::cout << "\n>>> TEST 2: Contracte Economice <<<\n";
        ferma.adaugaContract("Lactate SA", 40, 200, 3);
        ferma.adaugaContract("Mega Image", 100, 600, 10);

        std::cout << "\n>>> TEST 3: Simulare 7 Zile (Biologie, Vreme, Boli, Vanzari) <<<\n";
        for(int i = 1; i <= 7; ++i) {
            std::cout << "\n--- RULARE ZIUA " << i << " ---";
            ferma.platesteCheltuieli();
            if (i % 2 == 0) ferma.hranesteDinHambar(magazinComunal, "Fan_Premium");
            else ferma.hranesteDinHambar(magazinComunal, "Iarba");

            ferma.cheamaVeterinarul();
            ferma.mulge();
            ferma.proceseazaVanzari();
            ferma.proceseazaBiologie();
        }

        std::cout << ferma;

        std::cout << "\n>>> TEST 4: Modulul Gratar si Realizari <<<\n";
        std::cout << "\n > Incerci sa gatesti un taur adult (Va afisa Eroare)...";
        ferma.gatesteVitel(1, 180);

        std::cout << "\n > Incerci sa gatesti un vitel inexistent (Va afisa Eroare)...";
        ferma.gatesteVitel(100, 180);

        std::cout << "\n > Incerci sa gatesti un vitel mascul PERFECT (180s)...";
        ferma.gatesteVitel(2, 180);

        std::cout << "\n > Incerci sa gatesti alt vitel mascul ARS (300s)...";
        ferma.gatesteVitel(3, 300);

        std::cout << "\n\n>>> TEST 5: Regula celor 3 (Academic Requirement) <<<\n";
        Magazin magazinCopie = magazinComunal;
        Magazin altMagazin;
        altMagazin = magazinComunal;

        std::cout << "\n>>> REZUMAT FINAL <<<\n";
        std::cout << ferma.getHambar();
        std::cout << ferma.getPiata() << "\n";
        std::cout << ferma.getIstoric();

    } catch (const EroareAplicatie& e) {
        std::cout << "[Eroare aplicatie] " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "[Eroare std] " << e.what() << "\n";
    }

    return 0;
}