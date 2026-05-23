#pragma once
#include <stdexcept>
#include <string>

class EroareAplicatie : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class EroareFerma : public EroareAplicatie {
public:
    using EroareAplicatie::EroareAplicatie;
};

class EroareMagazin : public EroareAplicatie {
public:
    using EroareAplicatie::EroareAplicatie;
};

class EroareContract : public EroareAplicatie {
public:
    using EroareAplicatie::EroareAplicatie;
};