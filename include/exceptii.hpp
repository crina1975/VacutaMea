#pragma once
#include <stdexcept>
#include <string>

class EroareAplicatie : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class EroareParametru : public EroareAplicatie {
public:
    explicit EroareParametru(const std::string& msg) : EroareAplicatie(msg) {}
};

class EroareResurse : public EroareAplicatie {
public:
    explicit EroareResurse(const std::string& msg) : EroareAplicatie(msg) {}
};

class EroareLogica : public EroareAplicatie {
public:
    explicit EroareLogica(const std::string& msg) : EroareAplicatie(msg) {}
};