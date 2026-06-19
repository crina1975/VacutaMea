#pragma once

#include <vector>
#include <iostream>
#include <string>

template <typename T>
class Registru {
private:
    std::vector<T> inregistrari;

public:
    void adauga(const T& element) {
        inregistrari.push_back(element);
    }

    void afiseaza(std::ostream& os, const std::string& titlu) const {
        os << "--- Registru: " << titlu << " ---\n";
        for (size_t i = 0; i < inregistrari.size(); ++i) {
            os << "Ziua " << i + 1 << ": " << inregistrari[i] << "\n";
        }
    }
};