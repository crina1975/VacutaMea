#pragma once
#include <stdexcept>
#include <string>

// Clasa de bază pentru toate excepțiile din ferma ta
class EroareAplicatie : public std::runtime_error {
public:
    using std::runtime_error::runtime_error; // Moștenește constructorii de la std::runtime_error
};

// Excepție pentru parametri invalizi (ex: nume gol, vârstă negativă, buget negativ)
class EroareParametru : public EroareAplicatie {
public:
    explicit EroareParametru(const std::string& msg)
        : EroareAplicatie("Eroare parametru: " + msg) {}
};

// Excepție pentru erori de logică (ex: animal obosit, stoc epuizat)
class EroareLogica : public EroareAplicatie {
public:
    explicit EroareLogica(const std::string& msg)
        : EroareAplicatie("Eroare logica: " + msg) {}
};

// Excepție pentru contracte (ex: contracte invalide)
class EroareContract : public EroareAplicatie {
public:
    explicit EroareContract(const std::string& msg)
        : EroareAplicatie("Eroare contract: " + msg) {}
};
