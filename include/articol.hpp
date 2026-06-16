#pragma once
#include <string>
#include <iostream>

class Articol {
private:
    std::string nume;
    int putereSatietate;

public:
    Articol(std::string n, int sat);
    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] int getPutereSatietate() const;
    friend std::ostream& operator<<(std::ostream& os, const Articol& a);
};