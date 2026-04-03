#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>

//clasa 1
class Articol {
    std::string nume;
    int pret;
    int putereSatietate;
public:
    explicit Articol(std::string n = "Nimic", int p = 0, int sat = 0)
        : nume{std::move(n)}, pret{p}, putereSatietate{sat} {}

    [[nodiscard]] int getPret() const { return pret; }
    [[nodiscard]] int getPutereSatietate() const { return putereSatietate; }
    [[nodiscard]] const std::string& getNume() const { return nume; }

    friend std::ostream& operator<<(std::ostream& os, const Articol& a) {
        return os << a.nume << " (Pret: " << a.pret << ", Satietate: " << a.putereSatietate << ")";
    }
};

//clasa 2
class Status {
    std::string nume;
    int valoare;
public:
    explicit Status(std::string n = "Parametru", int v = 100)
        : nume{std::move(n)}, valoare{v} {}

    void modifica(int delta) {
        valoare = std::clamp(valoare + delta, 0, 100);
    }

    [[nodiscard]] int getValoare() const { return valoare; }

    friend std::ostream& operator<<(std::ostream& os, const Status& s) {
        return os << s.nume << ": " << s.valoare << "/100";
    }
};

//clasa 3
class Vacuta {
    std::string nume;
    Status foame;
    Status energie;
    int varsta;
public:
    explicit Vacuta(std::string nume_ = "Milka", int varsta_ = 3)
        : nume{std::move(nume_)}, foame{"Foame", 30}, energie{"Energie", 100}, varsta{varsta_} {}

    //regula celor 3
    Vacuta(const Vacuta& other)
        : nume{other.nume}, foame{other.foame}, energie{other.energie}, varsta{other.varsta} {
        std::cout << "";
    }

    Vacuta& operator=(const Vacuta& other) {
        if (this != &other) {
            nume = other.nume;
            foame = other.foame;
            energie = other.energie;
            varsta = other.varsta;
        }
        return *this;
    }

    ~Vacuta() = default;

    [[nodiscard]] bool esteAdult() const { return varsta >= 3; }
    [[nodiscard]] bool vreaSaFuga() const { return foame.getValoare() >= 100; }
    [[nodiscard]] const std::string& getNume() const { return nume; }

    void treceTimpul() {
        foame.modifica(20);
        energie.modifica(10);
    }

    int mulge() {
        if (esteAdult() && energie.getValoare() >= 20 && foame.getValoare() < 80) {
            energie.modifica(-20);
            return 5;
        }
        return 0;
    }

    void hraneste(const Articol& mancare) {
        foame.modifica(-mancare.getPutereSatietate());
        if (!esteAdult()) {
            varsta++;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Vacuta& v) {
        return os << "[" << (v.esteAdult() ? "Adult" : " Pui ") << "] " << v.nume
                  << " | " << v.foame << " | " << v.energie;
    }
};

//clasa 4
class Ferma {
    std::string numeFerma;
    std::string numeFermier;
    std::vector<Vacuta> cireada;
    int stocLapte;
    int bani;
public:
    explicit Ferma(std::string fermaNume, std::string fermier, int bugetInitial = 50)
        : numeFerma{std::move(fermaNume)}, numeFermier{std::move(fermier)}, stocLapte{0}, bani{bugetInitial} {}

    void cumparaPrimaVacuta() {
        if (cireada.empty() && bani >= 30) {
            bani -= 30;
            cireada.emplace_back("Milka", 3);
        }
    }

    void primestePui(const std::string& numePui) {
        cireada.emplace_back(numePui, 0);
    }

    void hranesteToate(const Articol& mancare) {
        for (auto& vacuta : cireada) {
            if (bani >= mancare.getPret()) {
                bani -= mancare.getPret();
                vacuta.hraneste(mancare);
            }
        }
    }

    void mulgeAdultii() {
        for (auto& vacuta : cireada) {
            stocLapte += vacuta.mulge();
        }
    }

    void vindeLapte() {
        if (stocLapte > 0) {
            bani += stocLapte * 4;
            stocLapte = 0;
        }
    }

    void treceZiua() {
        for (auto& vacuta : cireada) {
            vacuta.treceTimpul();
        }

        std::erase_if(cireada, [](const Vacuta& v) {
            return v.vreaSaFuga();
        });
    }

    friend std::ostream& operator<<(std::ostream& os, const Ferma& f) {
        os << "\n=== FERMA " << f.numeFerma << " (Proprietar: " << f.numeFermier << ") ===\n"
           << " Bani: " << f.bani << " | Lapte stocat: " << f.stocLapte << "L\n"
           << " Vacute (" << f.cireada.size() << "):\n";
        for (const auto& v : f.cireada) {
            os << "   " << v << "\n";
        }
        return os;
    }
};


int main() {
    Articol iarba("Iarba proaspata", 5, 30);

    std::string numeJucator, numeFerma;
    std::cout << "Introdu numele tau: ";
    std::getline(std::cin, numeJucator);
    std::cout << "Introdu numele fermei: ";
    std::getline(std::cin, numeFerma);

    Ferma ferma(numeFerma, numeJucator);
    ferma.cumparaPrimaVacuta();
    std::cout << ferma;

    ferma.mulgeAdultii();
    ferma.vindeLapte();
    ferma.treceZiua();

    std::string numeVitel;
    std::cout << "\nMilka a nascut! Cum numesti puiutul?  ";
    std::getline(std::cin, numeVitel);
    ferma.primestePui(numeVitel);

    ferma.hranesteToate(iarba);
    ferma.treceZiua();
    ferma.hranesteToate(iarba);
    ferma.treceZiua();
    ferma.hranesteToate(iarba); //puiutul devine adult

    std::cout << "\n--- Dupa cateva zile de hrana ---";
    std::cout << ferma;


    ferma.treceZiua();
    ferma.treceZiua();
    ferma.treceZiua();
    ferma.treceZiua();

    std::cout << "\n--- Dupa 4 zile de neglijenta ---";
    std::cout << ferma;

    return 0;
}