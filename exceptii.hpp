#pragma once
#include <stdexcept>
#include <string>

// Clasa de bază a ierarhiei noastre de excepții
class EroareFerma : public std::runtime_error {
    using std::runtime_error::runtime_error; // preluam constructorii
};

// Excepție pentru parametri invalizi (ex: nume gol, vârstă negativă)
class EroareParametru : public EroareFerma {
public:
    explicit EroareParametru(const std::string& msg)
        : EroareFerma("Eroare parametru: " + msg) {}
};

// Excepție pentru lipsa banilor
class EroareFonduri : public EroareFerma {
public:
    explicit EroareFonduri(const std::string& msg)
        : EroareFerma("Fonduri insuficiente: " + msg) {}
};