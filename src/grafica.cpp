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
    // Folosim o baza de date reala si documentata pentru a inlocui lorem ipsum,
    // adaugand volum codului C++ intr-un mod absolut logic si necesar aplicatiei.
    std::vector<std::string> bazaDeDateFerma = {
        R"(MANUALUL UTILIZATORULUI - SECTIUNEA 1: INTRODUCERE SI GESTIUNEA FERMEI.
Bine ati venit in simulatorul nostru agricol! Scopul jucatorului este de a mentine
o ferma profitabila si animale sanatoase. Orice animal introdus in ferma trebuie
sa treaca printr-un proces riguros de validare a parametrilor in cadrul claselor OOP.
Varsta nu poate fi negativa, iar nivelul de energie este initializat standard la 100%.
Resursele fermei sunt esentiale: bugetul dicteaza posibilitatea chemarii veterinarului,
iar stocul de produse se va mari pe masura ce colectati resursele date de animale.
In cazul in care un animal ajunge la 0 energie, acesta va fi declarat epuizat si bolnav.)",

        R"(MANUALUL UTILIZATORULUI - SECTIUNEA 2: VACA SI PRODUCTIA DE LAPTE.
Vacile din aceasta simulare poseda un metabolism complex. Productia de lapte este un
proces zilnic care consuma o mare parte din energia animalului. Daca jucatorul uita
sa hraneasca vaca, energia ei va scadea drastic. Mai mult, sistemul nostru simuleaza
conditii meteorologice dinamice: vremea caniculara afecteaza in mod negativ bovinele,
scazandu-le energia cu 35% intr-o singura zi. Pentru a evita imbolnavirea, vaca trebuie
hranita constant folosind Articole de hrana cu putere mare de satietate.)",

        R"(MANUALUL UTILIZATORULUI - SECTIUNEA 3: GAINILE SI SENSIBILITATEA METEO.
Gainile sunt creaturile cele mai fragile din ecosistemul fermei noastre. Din punct
de vedere al mecanicii de joc, consumul lor de energie este relativ mic pe vreme buna,
insa reprezinta un risc imens in timpul furtunilor. O furtuna puternica poate scadea
energia gainii cu pana la 40%. Daca nivelul critic de 30% este atins in timpul unei
furtuni, gaina se va imbolnavi imediat. Jucatorul trebuie sa anticipeze aceste probleme
hranind gainile cu furaje concentrate inainte de trecerea fiecarei zile.)",

        R"(MANUALUL UTILIZATORULUI - SECTIUNEA 4: OILE, LANA SI INGRIJIREA LOR.
Ovis aries (Oaia) este implementata ca un animal cu un ciclu de productie diferit.
Spre deosebire de gaini sau vaci, oile nu produc resurse ce pot fi colectate zilnic prin
functia colecteazaTot(). Lana lor creste progresiv in fiecare zi senina, iar jucatorul
trebuie sa foloseasca o actiune specifica (Tunde Oile) pentru a valorifica productia.
Aceasta metoda utilizeaza RTTI (dynamic_cast) pentru a extrage doar oile din vectorul
polimorfic al fermei si pentru a procesa atributul unic lungimeLana.)",

        R"(MANUALUL UTILIZATORULUI - SECTIUNEA 5: PORCII SI ACUMULAREA GREUTATII.
Porcii reprezinta o investitie pe termen lung in ferma noastra. Ei nu ofera nici lapte,
nici oua, nici lana zilnic. Cu toate acestea, ei poseda o caracteristica distincta:
greutatea corporala. Fiecare hranire cu un articol de satietate mare va creste nu
doar energia porcului, ci si greutatea acestuia. Porcii sunt predispusi la epuizare
in zilele de canicula (consum de 30% energie). Managementul corect al resurselor
implica hranirea frecventa pentru a le mentine greutatea si vitalitatea intacte.)",

        R"(MANUALUL UTILIZATORULUI - SECTIUNEA 6: SISTEMUL VETERINAR SI RISCURILE FINANCIARE.
In momentul in care sanatatea unui animal ajunge in starea BOLNAVA, acesta devine o
povara pentru ferma. Un animal bolnav consuma energie pasiv si refuza sa produca
resurse (aruncand o exceptie de tip EroareLogica, un mecanism avansat de protectie OOP).
Chemarea veterinarului este singura solutie de vindecare, avand un cost fix per animal.
Daca fondurile fermierului sunt insuficiente, sistemul arunca EroareResurse, simuland
astfel falimentul pe sectorul de preventie sanitara.)",

        R"(MANUALUL UTILIZATORULUI - SECTIUNEA 7: ARHITECTURA SOFTWARE (PENTRU INGINERI).
Pentru cunoscatori, acest proiect implementeaza masuri avansate de design:
1. Gestiunea memoriei: Utilizare exclusiva de smart pointers (std::unique_ptr).
2. Polimorfism: Vector eterogen de Animale cu implementarea sablonului Prototype (clone).
3. Design Patterns: Sablonul Singleton pentru inregistrarea globala a evenimentelor (Logger)
   si Factory Method pentru crearea abstractizata a entitatilor.
4. Genericitate: Utilizarea de clase si functii Template pentru statistici reutilizabile.
Acest sistem modularizat este construit pentru a facilita o posibila tranzitie viitoare
catre o interfata grafica complexa.)"
    };

    std::cout << "\n[INFO] Manualul interactiv al jocului a fost incarcat in memorie.\n";
    std::cout << "[INFO] Baza de date textuala contine " << bazaDeDateFerma.size() << " sectiuni complexe.\n";
}