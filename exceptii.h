#pragma once
#include <stdexcept>
#include <string>

// Ierarhie proprie derivată din std::runtime_error
class EroareFerma : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class EroareParametru : public EroareFerma {
public:
    explicit EroareParametru(const std::string& msg)
        : EroareFerma("Eroare parametru: " + msg) {}
};

class EroareLogica : public EroareFerma {
public:
    explicit EroareLogica(const std::string& msg)
        : EroareFerma("Eroare logica: " + msg) {}
};