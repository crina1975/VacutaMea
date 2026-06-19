#include "animal_factory.hpp"
#include "vaca.hpp"
#include "gaina.hpp"
#include "../include/oaie.hpp"
#include "porc.hpp"
#include "exceptii.hpp"

std::unique_ptr<Animal> AnimalFactory::creazaAnimal(TipAnimal tip, const std::string& nume, int varsta, int parametruExtra) {
    switch (tip) {
        case TipAnimal::VACA:
            return std::make_unique<Vaca>(nume, varsta, parametruExtra > 0 ? parametruExtra : 10);
        case TipAnimal::GAINA:
            return std::make_unique<Gaina>(nume, varsta, parametruExtra > 0 ? parametruExtra : 1);
        case TipAnimal::OAIE:
            return std::make_unique<Oaie>(nume, varsta);
        case TipAnimal::PORC:
            return std::make_unique<Porc>(nume, varsta);
        default:
            throw EroareLogica("Tip de animal necunoscut in Factory!");
    }
}