#pragma once

#include <memory>
#include <string>
#include "animal.hpp"

enum class TipAnimal { VACA, GAINA, OAIE, PORC };

class AnimalFactory {
public:
    static std::unique_ptr<Animal> creazaAnimal(TipAnimal tip, const std::string& nume, int varsta, int parametruExtra = 0);
};