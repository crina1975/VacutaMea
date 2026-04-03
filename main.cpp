#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <random>

enum class Sex { FEMELA, MASCUL };
enum class StareCarne { NEFACUTA, PERFECTA, ARSA };

// --- CLASA 1: ARTICOL ---
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

// --- CLASA 2: STATUS ---
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

// --- CLASA 3: VACUTA ---
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

// --- CLASA 4: GRATAR ---
class Gratar {
    int timpGatireSecunde;
public:
    explicit Gratar(int timp = 0) : timpGatireSecunde{timp} {}

    [[nodiscard]] StareCarne verificaStare() const {
        if (timpGatireSecunde < 175) return StareCarne::NEFACUTA;
        if (timpGatireSecunde > 185) return StareCarne::ARSA;
        return StareCarne::PERFECTA;
    }

    [[nodiscard]] int vindeMancare(const std::string& tip) const {
        StareCarne stare = verificaStare();
        if (stare == StareCarne::PERFECTA) {
            return (tip == "ciorba") ? 50 : 80;
        }
        std::cout << "[GRATAR] Atentie: Carnea este " << (stare == StareCarne::ARSA ? "ARSA" : "NEFACUTA") << "!\n";
        return 5;
    }
};

// --- CLASA 5: FERMA ---
class Ferma {
    std::string numeF;
    std::string numeP;
    std::vector<Vacuta> cireada;
    int bani;
    int stocLapte;
    int nivelFerma;
    int capacitateMaxima;
    std::mt19937 generator{std::random_device{}()};

public:
    Ferma(std::string nf, std::string np)
        : numeF{std::move(nf)}, numeP{std::move(np)}, cireada{}, bani{100}, stocLapte{0}, nivelFerma{1}, capacitateMaxima{5} {}

    void inceputJoc() {
        cireada.emplace_back("Milka", 3, Sex::FEMELA);
        cireada.emplace_back("Milk", 4, Sex::MASCUL);
    }

    void upgradeFerma() {
        int cost = nivelFerma * 200;
        if (bani >= cost && capacitateMaxima < 10) {
            bani -= cost;
            nivelFerma++;
            capacitateMaxima += 2;
            std::cout << "[FERMA] Upgrade la nivelul " << nivelFerma << ". Capacitate: " << capacitateMaxima << "\n";
        }
    }

    void proceseazaBiologie() {
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
            }
        }
        for (auto& p : puiNoi) cireada.push_back(p);

        std::erase_if(cireada, [](const Vacuta& v) {
            if (v.vreaSaFuga()) {
                std::cout << "[FUGA] " << v.getNume() << " a fugit de foame!\n";
                return true;
            }
            return false;
        });
    }

    void mulge() {
        for (auto& v : cireada) stocLapte += v.mulge();
    }

    void vindeLapte() {
        if (stocLapte > 0) {
            int profit = stocLapte * 5;
            bani += profit;
            std::cout << "[PIATA] Vandut " << stocLapte << "L lapte pentru " << profit << " bani.\n";
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
    }

    void gatesteVitel(size_t index, int secunde) {
        if (index < cireada.size()) {
            if (!cireada[index].esteAdult() && cireada[index].getSex() == Sex::MASCUL) {
                Gratar g(secunde);
                int profit = g.vindeMancare("friptura");
                bani += profit;
                std::cout << "[GRATAR] " << cireada[index].getNume() << " a fost gatit. Profit: " << profit << "\n";
                cireada.erase(cireada.begin() + static_cast<std::ptrdiff_t>(index));
            } else {
                std::cout << "[GRATAR] Poti gati doar vitei masculi!\n";
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Ferma& f) {
        os << "\n========================================\n"
           << " FERMA: " << f.numeF << " | Proprietar: " << f.numeP
           << "\n Bani: " << f.bani << " | Nivel: " << f.nivelFerma
           << "\n Cireada:\n";
        for (const auto& v : f.cireada) os << "  " << v << "\n";
        return os << "========================================\n";
    }
};

int main() {
    Articol iarba("Iarba Standard", 10, 30);
    Articol fan("Fan Premium", 25, 60);

    std::string np, nf;
    std::cout << "Bun venit! Introdu numele proprietarului: ";
    if (!(std::getline(std::cin, np))) return 0;
    std::cout << "Introdu numele fermei: ";
    if (!(std::getline(std::cin, nf))) return 0;

    Ferma ferma(nf, np);
    ferma.inceputJoc();

    // TEST 1: Ciclu de muls si vanzare
    std::cout << "\n--- TEST 1: Productie Lapte ---";
    ferma.mulge();
    ferma.vindeLapte();
    std::cout << ferma;

    // TEST 2: Sarcina si Nastere (3 zile de procesare biologica)
    std::cout << "\n--- TEST 2: Biologie si Nastere ---";
    for(int i = 0; i < 3; ++i) {
        ferma.hranesteToate(fan);
        ferma.proceseazaBiologie();
    }
    std::cout << ferma;

    // TEST 3: Gratarul (Mascul vs Femela / Perfect vs Ars)
    std::cout << "\n--- TEST 3: Sectiunea Gratar ---";
    std::cout << "\nIncercam sa gatim vitelul de pe pozitia 2 (180 secunde - Perfect)...";
    ferma.gatesteVitel(2, 180);

    std::cout << "\nIncercam sa gatim vitelul de pe pozitia 2 (300 secunde - Ars)...";
    ferma.gatesteVitel(2, 300);

    // TEST 4: Upgrade Ferma
    std::cout << "\n--- TEST 4: Dezvoltare Ferma ---";
    ferma.upgradeFerma();

    std::cout << "\n--- STARE FINALA ---";
    std::cout << ferma;

    return 0;
}