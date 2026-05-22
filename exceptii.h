#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <stdexcept>
#include <string>

class EroareFerma : public std::runtime_error {
public:
    explicit EroareFerma(const std::string& mesaj) : std::runtime_error(mesaj) {}
};

class EroareFaliment : public EroareFerma {
public:
    explicit EroareFaliment(const std::string& mesaj) : EroareFerma("Faliment: " + mesaj) {}
};

class EroareAnimalInvalid : public EroareFerma {
public:
    explicit EroareAnimalInvalid(const std::string& mesaj) : EroareFerma("Animal invalid: " + mesaj) {}
};

#endif