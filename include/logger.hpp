#pragma once

#include <iostream>
#include <string>
#include <vector>

class Logger {
private:
    std::vector<std::string> loguri;

    Logger() = default;

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstanta();

    void log(const std::string& mesaj);
    void afiseazaLoguri() const;
};