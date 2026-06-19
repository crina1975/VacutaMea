#include <iostream>
#include <string>
#include <limits>
#include "ferma.hpp"
#include "vaca.hpp"
#include "gaina.hpp"
#include "../include/oaie.hpp"
#include "porc.hpp"
#include "exceptii.hpp"
#include "grafica.hpp"
#include "animal_factory.hpp"
#include "logger.hpp"

// Functie utilitara pentru a curata buffer-ul dupa un input gresit de la utilizator
void curataInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    try {
        // Grafica initiala
        InterfataGrafica::afiseazaEcranIncarcare();
        InterfataGrafica::afiseazaManualJocMasiv();

        std::cout << "=== CONFIGURARE INITIALA FERMA ===\n";
        std::string numeFerma;
        int bugetInitial;

        std::cout << "Introdu numele fermei (un singur cuvant, ex: ValeaVerde): ";
        std::cin >> numeFerma;

        std::cout << "Introdu bugetul initial (numar intreg pozitiv): ";
        while (!(std::cin >> bugetInitial) || bugetInitial < 0) {
            std::cout << "Buget invalid! Introdu un numar pozitiv: ";
            curataInput();
        }

        Ferma ferma(numeFerma, bugetInitial);
        InterfataGrafica::afiseazaFermaGrafica();
        std::cout << "\n[INFO] Ferma '" << numeFerma << "' a fost creata cu succes!\n";

        bool ruleaza = true;
        while (ruleaza) {
            std::cout << "\n=========================================\n";
            std::cout << "              MENIU FERMA\n";
            std::cout << "=========================================\n";
            std::cout << "1. Adauga un animal nou\n";
            std::cout << "2. Hraneste toate animalele\n";
            std::cout << "3. Simuleaza trecerea unei zile\n";
            std::cout << "4. Colecteaza productia (lapte/oua)\n";
            std::cout << "5. Tunde oile\n";
            std::cout << "6. Cheama veterinarul\n";
            std::cout << "7. Afiseaza starea fermei\n";
            std::cout << "8. Afiseaza statistici template (Tema 3)\n";
            std::cout << "9. Afiseaza logurile (Singleton)\n";
            std::cout << "0. Iesire\n";
            std::cout << "=========================================\n";
            std::cout << "Alege o optiune: ";

            int optiune;
            if (!(std::cin >> optiune)) {
                curataInput();
                std::cout << "[EROARE] Te rog introdu un numar valid!\n";
                continue;
            }

            switch (optiune) {
                case 1: {
                    std::cout << "\n--- ADAUGA ANIMAL ---\n";
                    std::cout << "1. Vaca | 2. Gaina | 3. Oaie | 4. Porc\nAlege tipul: ";
                    int tipAnim;
                    if (!(std::cin >> tipAnim)) {
                        curataInput();
                        std::cout << "[EROARE] Input invalid pentru tip!\n";
                        break;
                    }

                    std::string numeA;
                    int varstaA;

                    std::cout << "Nume: ";
                    std::cin >> numeA;
                    std::cout << "Varsta: ";
                    if (!(std::cin >> varstaA)) {
                        curataInput();
                        std::cout << "[EROARE] Varsta invalida!\n";
                        break;
                    }

                    try {
                        TipAnimal tipEnum;
                        if (tipAnim == 1) tipEnum = TipAnimal::VACA;
                        else if (tipAnim == 2) tipEnum = TipAnimal::GAINA;
                        else if (tipAnim == 3) tipEnum = TipAnimal::OAIE;
                        else if (tipAnim == 4) tipEnum = TipAnimal::PORC;
                        else {
                            std::cout << "[EROARE] Tip invalid!\n";
                            break;
                        }

                        ferma.adaugaAnimal(AnimalFactory::creazaAnimal(tipEnum, numeA, varstaA));

                        std::cout << "\n[SUCCES] Animalul '" << numeA << "' a fost adaugat!\n";

                        if (tipAnim == 1) InterfataGrafica::afiseazaVacaGrafica();
                        else if (tipAnim == 2) InterfataGrafica::afiseazaGainaGrafica();
                        else if (tipAnim == 3) InterfataGrafica::afiseazaOaieGrafica();

                    } catch (const EroareAplicatie& e) {
                        std::cerr << "[EROARE] " << e.what() << "\n";
                    }
                    break;
                }
                case 2: {
                    std::cout << "\n--- HRANESTE ANIMALE ---\n";
                    std::string numeHrana;
                    int putereSat;
                    std::cout << "Numele hranei (ex. Porumb, Fan): ";
                    std::cin >> numeHrana;
                    std::cout << "Putere satietate (numar > 0): ";
                    if (!(std::cin >> putereSat)) {
                        curataInput();
                        std::cout << "[EROARE] Input invalid!\n";
                        break;
                    }
                    try {
                        Articol hrana(numeHrana, putereSat);
                        ferma.hranesteToateAnimalele(hrana);
                    } catch (const EroareAplicatie& e) {
                        std::cerr << "[EROARE] " << e.what() << "\n";
                    }
                    break;
                }
                case 3:
                    InterfataGrafica::afiseazaTractor();
                    ferma.simuleazaZi();
                    break;
                case 4:
                    ferma.colecteazaTot();
                    std::cout << "[INFO] Productie colectata.\n";
                    break;
                case 5:
                    ferma.tundeOile();
                    break;
                case 6:
                    try {
                        ferma.cheamaVeterinar();
                    } catch (const EroareResurse& e) {
                        std::cout << "[EROARE FONDURI] " << e.what() << "\n";
                    }
                    break;
                case 7:
                    InterfataGrafica::afiseazaFermaGrafica();
                    std::cout << ferma;
                    break;
                case 8: {
                    std::cout << "\n=== STATISTICI TEMA 3 (TEMPLATE-URI) ===\n";
                    int numarVaci = ferma.numaraAnimaleDeTip<Vaca>();
                    int numarGaini = ferma.numaraAnimaleDeTip<Gaina>();
                    int numarOi = ferma.numaraAnimaleDeTip<Oaie>();

                    std::cout << "Numar total de Vaci in ferma: " << numarVaci << "\n";
                    std::cout << "Numar total de Gaini in ferma: " << numarGaini << "\n";
                    std::cout << "Numar total de Oi in ferma: " << numarOi << "\n\n";

                    ferma.afiseazaRegistre();
                    break;
                }
                case 9:
                    Logger::getInstanta().afiseazaLoguri();
                    break;
                case 0:
                    ruleaza = false;
                    std::cout << "Iesire din program...\n";
                    break;
                default:
                    std::cout << "[EROARE] Optiune invalida! Incearca din nou.\n";
                    break;
            }
        }

    } catch (const EroareAplicatie& e) {
        std::cerr << "\n[Eroare Aplicatie Critica]: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "\n[Eroare Standard C++]: " << e.what() << "\n";
        return 1;
    }

    std::cout << "\nSimulare incheiata cu succes. Total animale trecute prin ferma: " << Animal::getTotalAnimale() << "\n";
    return 0;
}