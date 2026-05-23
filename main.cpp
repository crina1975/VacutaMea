#include <iostream>
#include "ferma.hpp"

// Main-ul trebuie să fie foarte simplu pentru a evita erorile de compilare.
int main() {
    try {
        std::cout << "--- START SIMULARE TEMA 2 ---\n";

        // Inițializăm ferma (nume fermă, nume proprietar)
        Ferma ferma("Ferma Vesela", "Flavius");
        ferma.inceputJoc();
        Magazin magazinComunal;

        Ferma ferma("Ferma Vesela", "Flavius");
        ferma.inceputJoc();
        ferma.angajeaza("Vasile (Mulgator)", 10);
        // TEST 1: Angajari și Provizii
        ferma.angajeaza("Vasile (Mulgator)", 10);
        ferma.platesteCheltuieli();
        ferma.hranesteDinHambar(magazinComunal, "Iarba");
        // TEST 2: Simulare scurtă (Biologie + Vanzari)
        // Aici ferma apeleaza intern clasele derivate din Animal
        ferma.proceseazaBiologie();
        ferma.proceseazaVanzari();

        // Afișăm starea finală
        std::cout << ferma;
        std::cout << "\n>>> STATISTICI EXTRA <<<\n";
        std::cout << "Total animale inregistrate: " << Animal::getTotalAnimale() << "\n";
        std::cout << ferma.getHambar();
        std::cout << ferma.getPiata() << "\n";
        std::cout << ferma.getIstoric();
        std::cout << "\n--- SIMULARE ÎNCHEIATĂ CU SUCCES ---\n";

    } catch (const EroareAplicatie& e) {
        std::cerr << "[Eroare Aplicație]: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "[Eroare Standard]: " << e.what() << "\n";
        return 1;
    }

    return 0;
}