#include "grafica.hpp"
// cppcheck-suppress unusedFunction
void InterfataGrafica::curataEcranul() {
    for(int i = 0; i < 40; ++i) std::cout << "\n";
}
// cppcheck-suppress unusedFunction
void InterfataGrafica::afiseazaEcranIncarcare() {
    std::string logo = R"(
    ███████╗███████╗██████╗███╗   ███╗█████╗     ██╗  ██╗███████╗███████╗███████╗██╗     █████╗
    ██╔════╝██╔════╝██╔══██╗████╗████║██╔══██╗   ██║  ██║██╔════╝██╔════╝██╔════╝██║    ██╔══██╗
    █████╗  █████╗  ██████╔╝██╔████╔██║███████║   ██║  ██║█████╗  ███████╗█████╗  ██║    ███████║
    ██╔══╝  ██╔══╝  ██╔══██╗██║╚██╔╝██║██╔══██║   ╚██╗██╔╝██╔══╝  ╚════██║██╔══╝  ██║    ██╔══██║
    ██║     ███████╗██║  ██║██║╚═╝ ██║██║  ██║     ╚████╔╝███████╗███████║███████╗███████╗██║  ██║
    ╚═╝     ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝  ╚═╝      ╚═══╝  ╚══════╝╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝
    )";
    std::cout << logo << "\n";
}
// cppcheck-suppress unusedFunction
void InterfataGrafica::afiseazaFermaGrafica() {
    std::cout << R"(
         _.-^-._    .--.
      .-'   _   '-. |__|
     /     |_|     \ | |
    )" << "\n";
}
// cppcheck-suppress unusedFunction
void InterfataGrafica::afiseazaVacaGrafica() { 
    std::cout << R"(
          (__)
          (oo)
    /------\/
   / |    ||
  * /\---/\
     ~~   ~~
    )" << "\n"; 
}
// cppcheck-suppress unusedFunction
void InterfataGrafica::afiseazaGainaGrafica() { 
    std::cout << R"(
          //
        ('>
        /rr\
       *\/\/*
    )" << "\n"; 
}
// cppcheck-suppress unusedFunction
void InterfataGrafica::afiseazaOaieGrafica() { 
    std::cout << R"(
          __
        /    \
        | oo |
      /======\
      / |    | \
     * ||--||  *
    )" << "\n"; 
}
// cppcheck-suppress unusedFunction
void InterfataGrafica::afiseazaTractor() { 
    std::cout << R"(
        _|_|_
      /     \
      |      |___
     /___________\
      (O)     (O)
    )" << "\n"; 
}
// cppcheck-suppress unusedFunction
void InterfataGrafica::afiseazaManualJocMasiv() {
    std::cout << "\n[INFO] Manualul si regulamentul fermei au fost incarcate.\n";
}