#include <iostream>
#include "../include/ferma.hpp"
#include "../include/vaca.hpp"
#include "../include/gaina.hpp"
#include "../include/oaie.hpp"
#include "../include/exceptii.hpp"

int main() {
    try {
        Ferma ferma("Ferma Vesela", 200);

        ferma.adaugaAnimal(std::make_unique<Vaca>("Milka", 3, 15));
        ferma.adaugaAnimal(std::make_unique<Gaina>("Cocuta", 1, 2));
        ferma.adaugaAnimal(std::make_unique<Oaie>("Miorita", 2));
        ferma.adaugaAnimal(std::make_unique<Oaie>("Bela", 4));

        std::cout << ferma << "\n";

        Articol iarba("Iarba Proaspata", 30);
        ferma.hranesteToateAnimalele(iarba);

        ferma.simuleazaZi(TipVreme::FURTUNA);
        ferma.strangeProductia();
        ferma.tundeOile();

        std::cout << "Dupa o zi de furtuna:\n" << ferma << "\n";

        ferma.cheamaVeterinar();

        std::cout << "Dupa tratament:\n" << ferma << "\n";

        Ferma fermaClonata = ferma;
        std::cout << "Ferma Clonata (Test Copy & Swap):\n" << fermaClonata << "\n";

    } catch (const EroareAplicatie& e) {
        std::cerr << "[Eroare Rulare] " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "[Eroare Critica] " << e.what() << "\n";
        return 1;
    }

    return 0;
}