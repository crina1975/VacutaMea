#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <random>
#include <exception>

enum class Sex { FEMELA, MASCUL };
enum class StareCarne { NEFACUTA, PERFECTA, ARSA };

//exceptii custom
class FermaException : public std::exception {
    std::string mesaj;
public:
    explicit FermaException(std::string msg) : mesaj{std::move(msg)} {}
    [[nodiscard]] const char* what() const noexcept override { return mesaj.c_str(); }
};

//clasa 1
class Istoric {
    std::vector<std::string> loguri;
public:
    void adaugaEveniment(const std::string& eveniment) {
        loguri.push_back(eveniment);
    }
    void afiseazaIstoric() const {
        std::cout << "\n=== JURNAL FERMA ===\n";
        for (const auto& log : loguri) {
            std::cout << " > " << log << "\n";
        }
    }
};

//clasa 2
class Piata {
    int pretLapte = 5;
    int pretCarne = 80;
    std::mt19937 generator{std::random_device{}()};
public:
    void fluctueazaPreturi() {
        std::uniform_int_distribution<int> distLapte(3, 8);
        std::uniform_int_distribution<int> distCarne(50, 120);
        pretLapte = distLapte(generator);
        pretCarne = distCarne(generator);
    }
    [[nodiscard]] int getPretLapte() const { return pretLapte; }
    [[nodiscard]] int getPretCarne() const { return pretCarne; }
};

//clasa 3
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
        return os << a.nume << " (" << a.pret << " bani)";
    }
};

//clasa 4
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

//clasa 5
class Angajat {
    std::string nume;
    int salariuZilnic;
    bool platitAzi = false;
public:
    Angajat(std::string n, int salariu) : nume{std::move(n)}, salariuZilnic{salariu} {}

    [[nodiscard]] int cerereSalariu() const { return salariuZilnic; }
    [[nodiscard]] const std::string& getNume() const { return nume; }

    void plateste() { platitAzi = true; }
    void reseteazaZiua() { platitAzi = false; }
    [[nodiscard]] bool esteMultumit() const { return platitAzi; }
};

//clasa 6
class Vacuta {
    std::string nume;
    Status foame;
    Status energie;
    int varsta;
    Sex sex;
    int contorEnergieMaxima = 0;
    bool insarcinata = false;
    int zileSarcina = 0;

public:
    explicit Vacuta(std::string n, int v, Sex s)
        : nume{std::move(n)}, foame{"Foame", 30}, energie{"Energie", 100}, varsta{v}, sex{s} {}

    Vacuta(const Vacuta& other) = default;
    Vacuta& operator=(const Vacuta& other) = default;
    ~Vacuta() = default;

    [[nodiscard]] bool esteAdult() const { return varsta >= 3; }
    [[nodiscard]] Sex getSex() const { return sex; }
    [[nodiscard]] bool esteInsarcinata() const { return insarcinata; }
    [[nodiscard]] const std::string& getNume() const { return nume; }
    [[nodiscard]] bool vreaSaFuga() const { return foame.getValoare() >= 100; }

    void ramaneInsarcinata() {
        if (sex == Sex::FEMELA && esteAdult() && !insarcinata) {
            insarcinata = true;
            zileSarcina = 0;
        }
    }

    void treceTimpul() {
        int factorFoame = insarcinata ? 40 : 20;
        foame.modifica(factorFoame);
        energie.modifica(-10);
        if (energie.getValoare() == 100) contorEnergieMaxima++;
        if (insarcinata) zileSarcina++;
    }

    bool verificaNastere() {
        if (insarcinata && zileSarcina >= 3) {
            insarcinata = false;
            zileSarcina = 0;
            return true;
        }
        return false;
    }

    void hraneste(const Articol& m) {
        foame.modifica(-m.getPutereSatietate());
        energie.modifica(20);
        if (!esteAdult() && contorEnergieMaxima >= 5) {
            varsta = 3;
            std::cout << "[EVOLUTIE] " << nume << " a devenit adult!\n";
        }
    }

    int mulge() {
        if (esteAdult() && sex == Sex::FEMELA && energie.getValoare() >= 30) {
            energie.modifica(-30);
            return 10;
        }
        return 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vacuta& v) {
        os << "[" << (v.sex == Sex::FEMELA ? "F" : "M") << "] " << v.nume
           << " (V:" << v.varsta << ") | " << v.foame << " | " << v.energie;
        if (v.insarcinata) os << " [INS]";
        return os;
    }
};

//clasa 7
class Gratar {
    int timpGatireSecunde;
public:
    explicit Gratar(int timp = 0) : timpGatireSecunde{timp} {}

    [[nodiscard]] StareCarne verificaStare() const {
        if (timpGatireSecunde < 175) return StareCarne::NEFACUTA;
        if (timpGatireSecunde > 185) return StareCarne::ARSA;
        return StareCarne::PERFECTA;
    }

    [[nodiscard]] int vindeMancare(const std::string& tip, const Piata& piataCurenta) const {
        StareCarne stare = verificaStare();
        if (stare == StareCarne::PERFECTA) {
            return (tip == "ciorba") ? (piataCurenta.getPretCarne() / 2) : piataCurenta.getPretCarne();
        }
        std::cout << "[GRATAR] Atentie: Carnea este " << (stare == StareCarne::ARSA ? "ARSA" : "NEFACUTA") << "!\n";
        return 5;
    }
};

//clasa 8
class Ferma {
    std::string numeF;
    std::string numeP;
    std::vector<Vacuta> cireada;
    std::vector<Angajat> echipa;
    Piata piataLocala;
    Istoric jurnal;

    int bani;
    int stocLapte;
    int nivelFerma;
    int capacitateMaxima;
    int ziuaCurenta;
    std::mt19937 generator{std::random_device{}()};

public:
    Ferma(std::string nf, std::string np)
        : numeF{std::move(nf)}, numeP{std::move(np)}, cireada{}, echipa{}, bani{150}, stocLapte{0}, nivelFerma{1}, capacitateMaxima{5}, ziuaCurenta{1} {}

    void inceputJoc() {
        cireada.emplace_back("Milka", 3, Sex::FEMELA);
        cireada.emplace_back("Milk", 4, Sex::MASCUL);
        jurnal.adaugaEveniment("Ferma a fost fondata. Animale initiale adaugate.");
    }

    void angajeaza(const std::string& numeAngajat, int salariu) {
        echipa.emplace_back(numeAngajat, salariu);
        jurnal.adaugaEveniment("A fost angajat " + numeAngajat + " (Salariu: " + std::to_string(salariu) + ").");
    }

    void platesteAngajati() {
        for (auto& angajat : echipa) {
            angajat.reseteazaZiua();
            if (bani >= angajat.cerereSalariu()) {
                bani -= angajat.cerereSalariu();
                angajat.plateste();
                jurnal.adaugaEveniment("Platit salariu catre " + angajat.getNume() + ".");
            } else {
                jurnal.adaugaEveniment("AVERTISMENT: Nu am putut plati pe " + angajat.getNume() + "!");
            }
        }
    }

    void upgradeFerma() {
        int cost = nivelFerma * 200;
        if (bani >= cost && capacitateMaxima < 10) {
            bani -= cost;
            nivelFerma++;
            capacitateMaxima += 2;
            std::cout << "[FERMA] Upgrade la nivelul " << nivelFerma << ". Capacitate: " << capacitateMaxima << "\n";
            jurnal.adaugaEveniment("Upgrade ferma la nivelul " + std::to_string(nivelFerma) + " realizat.");
        } else {
            throw FermaException("Fonduri insuficiente sau capacitate maxima atinsa pentru upgrade!");
        }
    }

    void proceseazaBiologie() {
        ziuaCurenta++;
        piataLocala.fluctueazaPreturi();
        jurnal.adaugaEveniment("A inceput ziua " + std::to_string(ziuaCurenta) + ". Preturile pe piata s-au actualizat.");

        bool areTaur = std::ranges::any_of(cireada, [](const Vacuta& v){
            return v.getSex() == Sex::MASCUL && v.esteAdult();
        });

        std::vector<Vacuta> puiNoi;
        std::uniform_int_distribution<int> distribSex(0, 1);

        for (auto& v : cireada) {
            v.treceTimpul();
            if (areTaur && v.getSex() == Sex::FEMELA && v.esteAdult()) v.ramaneInsarcinata();

            if (v.verificaNastere() && cireada.size() + puiNoi.size() < static_cast<size_t>(capacitateMaxima)) {
                std::string numePui;
                std::cout << "\n[NASTERE] O vaca a nascut! Introdu nume pentru pui: ";
                std::cin >> numePui;
                Sex sexPui = (distribSex(generator) == 0) ? Sex::FEMELA : Sex::MASCUL;
                puiNoi.emplace_back(numePui, 0, sexPui);
                jurnal.adaugaEveniment("S-a nascut puiul " + numePui + ".");
            }
        }
        for (auto& p : puiNoi) cireada.push_back(p);

        std::erase_if(cireada, [&](const Vacuta& v) {
            if (v.vreaSaFuga()) {
                jurnal.adaugaEveniment("TRAGEDIE: Vaca " + v.getNume() + " a fugit din cauza foamei!");
                return true;
            }
            return false;
        });
    }

    void mulge() {
        int lapteObtinut = 0;
        for (auto& v : cireada) lapteObtinut += v.mulge();
        stocLapte += lapteObtinut;
        jurnal.adaugaEveniment("S-au muls " + std::to_string(lapteObtinut) + "L de lapte azi.");
    }

    void vindeLapte() {
        if (stocLapte > 0) {
            int profit = stocLapte * piataLocala.getPretLapte();
            bani += profit;
            std::cout << "[PIATA] Vandut " << stocLapte << "L lapte pentru " << profit << " bani. (Pret: " << piataLocala.getPretLapte() << ")\n";
            jurnal.adaugaEveniment("Vandut lapte pentru " + std::to_string(profit) + " bani.");
            stocLapte = 0;
        }
    }

    void hranesteToate(const Articol& a) {
        for (auto& v : cireada) {
            if (bani >= a.getPret()) {
                bani -= a.getPret();
                v.hraneste(a);
            }
        }
        jurnal.adaugaEveniment("Cireada a fost hranita cu " + a.getNume() + ".");
    }

    void gatesteVitel(size_t index, int secunde) {
        if (index < cireada.size()) {
            if (!cireada[index].esteAdult() && cireada[index].getSex() == Sex::MASCUL) {
                Gratar g(secunde);
                int profit = g.vindeMancare("friptura", piataLocala);
                bani += profit;
                std::cout << "[GRATAR] " << cireada[index].getNume() << " gatit. Profit: " << profit << " (Pret piata: " << piataLocala.getPretCarne() << ")\n";
                jurnal.adaugaEveniment("Vitelul " + cireada[index].getNume() + " a fost preparat si vandut.");
                cireada.erase(cireada.begin() + static_cast<std::ptrdiff_t>(index));
            } else {
                throw FermaException("Poti gati doar vitei masculi non-adulti!");
            }
        }
    }

    void afiseazaIstoric() const { jurnal.afiseazaIstoric(); }

    friend std::ostream& operator<<(std::ostream& os, const Ferma& f) {
        os << "\n========================================\n"
           << " ZIUA " << f.ziuaCurenta << " | FERMA: " << f.numeF << " | Proprietar: " << f.numeP
           << "\n Bani: " << f.bani << " | Nivel: " << f.nivelFerma << " | Angajati: " << f.echipa.size()
           << "\n Cireada (" << f.cireada.size() << "/" << f.capacitateMaxima << "):\n";
        for (const auto& v : f.cireada) os << "  " << v << "\n";
        return os << "========================================\n";
    }
};

int main() {
    Articol fan("Fan Premium", 25, 60);

    std::string np, nf;
    std::cout << "Bun venit! Nume proprietar: ";
    if (!(std::getline(std::cin, np))) return 0;
    std::cout << "Nume ferma: ";
    if (!(std::getline(std::cin, nf))) return 0;

    Ferma ferma(nf, np);
    ferma.inceputJoc();
    ferma.angajeaza("Ion", 15);

    //test 1
    std::cout << "\n--- TEST 1: Tratam Exceptiile Custom ---";
    try {
        ferma.upgradeFerma(); //nu sunt destui bani
    } catch (const FermaException& e) {
        std::cerr << "\n[EROARE PRINSĂ] " << e.what() << "\n";
    }

    //test 2
    std::cout << "\n--- TEST 2: Biologie, Piata si Economie ---";
    for(int i = 0; i < 3; ++i) {
        ferma.platesteAngajati();
        ferma.hranesteToate(fan);
        ferma.mulge();
        ferma.vindeLapte();
        ferma.proceseazaBiologie();
    }
    std::cout << ferma;

    //test 3
    std::cout << "\n--- TEST 3: Gratar si Validare Erori ---";
    try {
        std::cout << "\nIncercam sa gatim taurul adult de pe pozitia 1 (ar trebui sa dea eroare)...";
        ferma.gatesteVitel(1, 180); //pe pozitia 1 este Milk (Adult), deci va arunca o exceptie
    } catch (const FermaException& e) {
        std::cerr << "\n[EROARE PRINSĂ] " << e.what() << "\n";
    }

    ferma.afiseazaIstoric();

    return 0;
}