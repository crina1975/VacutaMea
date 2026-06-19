#include "logger.hpp"

Logger& Logger::getInstanta() {
    static Logger instanta;
    return instanta;
}

void Logger::log(const std::string& mesaj) {
    loguri.push_back(mesaj);
    std::cout << "[LOGGER]: " << mesaj << "\n";
}

void Logger::afiseazaLoguri() const {
    std::cout << "\n=== ISTORIC EVENIMENTE ===\n";
    for (const auto& log : loguri) {
        std::cout << " - " << log << "\n";
    }
    std::cout << "==========================\n";
}