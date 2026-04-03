#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <random>
#include <stdexcept>
#include <map>

enum class Sex { FEMELA, MASCUL };
enum class StareCarne { NEFACUTA, PERFECTA, ARSA };
enum class TipVreme { INSORIT, PLOIOS, FURTUNA, CANICULA };
enum class StareSanatate { SANATOASA, BOLNAVA, CRITICA };

//exceptii custom
class FermaException : public std::runtime_error {
public:
    explicit FermaException(const std::string& msg) : std::runtime_error(msg) {}
};

//clasa 1
class Istoric {
    std::vector<std::string> loguri{};
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
class Vremea {
    TipVreme stadiuCurent = TipVreme::INSORIT;
    std::mt19937 generator{std::random_device{}()};
public:
    void schimbaVremea() {
        std::uniform_int_distribution<int> dist(0, 3);
        stadiuCurent = static_cast<TipVreme>(dist(generator));
    }
    [[nodiscard]] TipVreme getVremeCurenta() const { return stadiuCurent; }

    [[nodiscard]] std::string getNumeVreme() const {
        switch(stadiuCurent) {
            case TipVreme::INSORIT: return "Insorit";
            case TipVreme::PLOIOS: return "Ploios";
            case TipVreme::FURTUNA: return "Furtuna";
            case TipVreme::CANICULA: return "Canicula";
        }
        return "Necunoscut";
    }
};

//clasa 4
class SistemRealizari {
    bool primulPui = false;
    bool bogatie = false;
    bool maestruBucatar = false;
public:
    void verificaAvere(int bani, Istoric& jurnal) {
        if (bani >= 500 && !bogatie) {
            bogatie = true;
            jurnal.adaugaEveniment("🏆 REALIZARE DEBLOCATA: Fermier Bogat (Ai strans 500+ bani)!");
        }
    }
    void deblocheazaPui(Istoric& jurnal) {
        if (!primulPui) {
            primulPui = true;
            jurnal.adaugaEveniment("🏆 REALIZARE DEBLOCATA: Miracolul Vietii (Primul pui nascut)!");
        }
    }
    void deblocheazaBucatar(Istoric& jurnal) {
        if (!maestruBucatar) {
            maestruBucatar = true;
            jurnal.adaugaEveniment("🏆 REALIZARE DEBLOCATA: MasterChef (Ai gatit perfect un vitel)!");
        }
    }
};

//clasa 5
class Articol {
    std::string nume{"Nimic"};
    int pret{0};
    int putereSatietate{0};
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

//clasa 6
class Magazin {
    std::vector<Articol> catalog;
public:
    Magazin() {
        catalog.emplace_back("Iarba", 10, 20);
        catalog.emplace_back("Fan_Premium", 25, 50);
        catalog.emplace_back("Concentrate", 50, 100);
    }

    [[nodiscard]] const Articol& cautaArticol(const std::string& numeCautat) const {
        for (const auto& art : catalog) {
            if (art.getNume() == numeCautat) return art;
        }
        throw FermaException("Articolul " + numeCautat + " nu exista in magazin!");
    }

    void afiseazaCatalog() const {
        std::cout << "\n=== CATALOG MAGAZIN ===\n";
        for (const auto& art : catalog) {
            std::cout << " - " << art << " | Ofera " << art.getPutereSatietate() << " energie.\n";
        }
    }
};

//clasa 7
class Hambar {
    std::map<std::string, int> stocuri{};
public:
    void adauga(const std::string& numeArticol, int cantitate) {
        stocuri[numeArticol] += cantitate;
    }

    [[nodiscard]] bool consuma(const std::string& numeArticol) {
        if (stocuri.contains(numeArticol) && stocuri[numeArticol] > 0) {
            stocuri[numeArticol]--;
            return true;
        }
        return false;
    }

    void afiseazaStoc() const {
        std::cout << "\n=== STOC HAMBAR ===\n";
        if (stocuri.empty()) std::cout << " Hambarul este gol!\n";
        for (const auto& [nume, cantitate] : stocuri) {
            std::cout << " > " << nume << ": " << cantitate << " portii\n";
        }
    }
};

//clasa 8
class Status {
    std::string nume{"Parametru"};
    int valoare{100};
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

//clasa 9
class Angajat {
    std::string nume;
    int salariuZilnic{0};
    bool platitAzi{false};
public:
    Angajat(std::string n, int salariu) : nume{std::move(n)}, salariuZilnic{salariu} {}

    [[nodiscard]] int cerereSalariu() const { return salariuZilnic; }
    [[nodiscard]] const std::string& getNume() const { return nume; }

    void plateste() { platitAzi = true; }
    void reseteazaZiua() { platitAzi = false; }
};

//clasa 10
class Vacuta {
    std::string nume;
    Status foame{"Foame", 30};
    Status energie{"Energie", 100};
    int varsta{0};
    Sex sex{Sex::FEMELA};
    StareSanatate sanatate{StareSanatate::SANATOASA};
    int contorEnergieMaxima{0};
    bool insarcinata{false};
    int zileSarcina{0};
    std::mt19937 generator{std::random_device{}()};

public:
    explicit Vacuta(std::string n, int v, Sex s)
        : nume{std::move(n)}, varsta{v}, sex{s} {}

    Vacuta(const Vacuta& other) = default;
    Vacuta& operator=(const Vacuta& other) = default;
    ~Vacuta() = default;

    [[nodiscard]] bool esteAdult() const { return varsta >= 3; }
    [[nodiscard]] Sex getSex() const { return sex; }
    [[nodiscard]] const std::string& getNume() const { return nume; }
    [[nodiscard]] bool vreaSaFuga() const { return foame.getValoare() >= 100; }
    [[nodiscard]] bool esteBolnava() const { return sanatate != StareSanatate::SANATOASA; }

    void ramaneInsarcinata() {
        if (sex == Sex::FEMELA && esteAdult() && !insarcinata && sanatate == StareSanatate::SANATOASA) {
            insarcinata = true;
            zileSarcina = 0;
        }
    }

    void vindeca() { sanatate = StareSanatate::SANATOASA; }

    void treceTimpul(TipVreme vremeCurenta) {
        int factorFoame = insarcinata ? 40 : 20;
        int factorEnergie = -10;

        if (vremeCurenta == TipVreme::CANICULA) factorFoame += 15;
        if (vremeCurenta == TipVreme::FURTUNA) factorEnergie -= 20;

        if (sanatate == StareSanatate::BOLNAVA) {
            factorEnergie -= 15;
            factorFoame += 10;
        }

        if (sanatate == StareSanatate::SANATOASA) {
            std::uniform_int_distribution<int> sansaBoala(1, 100);
            if (sansaBoala(generator) <= 10) sanatate = StareSanatate::BOLNAVA;
        }

        foame.modifica(factorFoame);
        energie.modifica(factorEnergie);

        if (energie.getValoare() == 100 && sanatate == StareSanatate::SANATOASA) contorEnergieMaxima++;
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
        if (sanatate != StareSanatate::SANATOASA) return 0;
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
        if (v.sanatate == StareSanatate::BOLNAVA) os << " [BOLNAVA]";
        return os;
    }
};

//clasa 11
class Veterinar {
    std::string numeClinica;
    int tarifTratament{40};
public:
    explicit Veterinar(std::string nume) : numeClinica{std::move(nume)} {}

    void trateazaCireada(std::vector<Vacuta>& cireada, int& baniFerma, Istoric& jurnal) const {
        for (auto& v : cireada) {
            if (v.esteBolnava()) {
                if (baniFerma >= tarifTratament) {
                    baniFerma -= tarifTratament;
                    v.vindeca();
                    jurnal.adaugaEveniment("Medic din " + numeClinica + ": " + v.getNume() + " a fost vindecata.");
                } else {
                    jurnal.adaugaEveniment("AVERTISMENT: Nu sunt bani pentru tratament: " + v.getNume());
                }
            }
        }
    }
};

//clasa 12
class Gratar {
    int timpGatireSecunde{0};
public:
    explicit Gratar(int timp = 0) : timpGatireSecunde{timp} {}

    [[nodiscard]] StareCarne verificaStare() const {
        if (timpGatireSecunde < 175) return StareCarne::NEFACUTA;
        if (timpGatireSecunde > 185) return StareCarne::ARSA;
        return StareCarne::PERFECTA;
    }

    [[nodiscard]] int vindeMancare(const std::string& tip, const Piata& piataCurenta, SistemRealizari& ach, Istoric& jurnal) const {
        StareCarne stare = verificaStare();
        if (stare == StareCarne::PERFECTA) {
            ach.deblocheazaBucatar(jurnal);
            return (tip == "ciorba") ? (piataCurenta.getPretCarne() / 2) : piataCurenta.getPretCarne();
        }
        std::cout << "[GRATAR] Atentie: Carnea este " << (stare == StareCarne::ARSA ? "ARSA" : "NEFACUTA") << "!\n";
        return 5;
    }
};

//clasa 13
class Contract {
    std::string companie;
    int necesarLapte;
    int lapteColectat{0};
    int recompensaBani;
    int zileRamase;
    bool finalizat{false};
public:
    Contract(std::string comp, int necesar, int rec, int zile)
        : companie{std::move(comp)}, necesarLapte{necesar}, recompensaBani{rec}, zileRamase{zile} {}

    [[nodiscard]] bool esteFinalizat() const { return finalizat; }
    [[nodiscard]] bool esteExpirat() const { return zileRamase <= 0 && !finalizat; }
    [[nodiscard]] int getRecompensa() const { return recompensaBani; }
    [[nodiscard]] const std::string& getCompanie() const { return companie; }

    int adaugaLapte(int cantitate) {
        if (finalizat || esteExpirat()) return cantitate;
        int spatiu = necesarLapte - lapteColectat;
        if (cantitate >= spatiu) {
            lapteColectat += spatiu;
            finalizat = true;
            return cantitate - spatiu;
        }
        lapteColectat += cantitate;
        return 0;
    }

    void treceZiua() {
        if (!finalizat && zileRamase > 0) zileRamase--;
    }

    friend std::ostream& operator<<(std::ostream& os, const Contract& c) {
        os << "Contract " << c.companie << " [" << c.lapteColectat << "/" << c.necesarLapte << "L] ";
        if (c.finalizat) os << "- FINALIZAT";
        else if (c.esteExpirat()) os << "- EXPIRAT";
        else os << "- Zile: " << c.zileRamase;
        return os;
    }
};

//clasa 14
class CladireAuxiliara {
    std::string nume;
    int bonusProductie;
    int costIntretinere;
public:
    CladireAuxiliara(std::string n, int bonus, int cost)
        : nume{std::move(n)}, bonusProductie{bonus}, costIntretinere{cost} {}

    [[nodiscard]] int aplicaBonus(int productie) const { return productie + bonusProductie; }
    [[nodiscard]] int getCost() const { return costIntretinere; }
    [[nodiscard]] const std::string& getNume() const { return nume; }
};

//clasa 15
class Ferma {
    std::string numeF;
    std::string numeP;
    std::vector<Vacuta> cireada{};
    std::vector<Angajat> echipa{};
    std::vector<Contract> contracte{};
    std::vector<CladireAuxiliara> anexe{};

    Piata piataLocala{};
    Istoric jurnal{};
    Vremea meteo{};
    Veterinar doc{"Clinica VetHappy"};
    SistemRealizari trofee{};
    Hambar hambarCentral{};

    int bani{250};
    int stocLapte{0};
    int capacitateMaxima{5};
    int ziuaCurenta{1};
    std::mt19937 generator{std::random_device{}()};

public:
    Ferma(std::string nf, std::string np)
        : numeF{std::move(nf)}, numeP{std::move(np)} {}

    void inceputJoc() {
        cireada.emplace_back("Milka", 3, Sex::FEMELA);
        cireada.emplace_back("Milk", 4, Sex::MASCUL);
        jurnal.adaugaEveniment("Ferma a fost fondata.");
    }

    void angajeaza(const std::string& numeAngajat, int salariu) {
        echipa.emplace_back(numeAngajat, salariu);
    }

    void adaugaContract(const std::string& companie, int necesar, int recompensa, int zile) {
        contracte.emplace_back(companie, necesar, recompensa, zile);
        jurnal.adaugaEveniment("Contract semnat cu: " + companie);
    }

    void construiesteAnexa(const std::string& numeAnexa, int bonus, int intretinere, int pret) {
        if (bani >= pret) {
            bani -= pret;
            anexe.emplace_back(numeAnexa, bonus, intretinere);
            jurnal.adaugaEveniment("S-a construit: " + numeAnexa);
        } else {
            throw FermaException("Bani insuficienti pentru anexa " + numeAnexa);
        }
    }

    void cumparaProvizii(const Magazin& magazin, const std::string& numeProdus, int cantitate) {
        const Articol& produs = magazin.cautaArticol(numeProdus);
        int costTotal = produs.getPret() * cantitate;

        if (bani >= costTotal) {
            bani -= costTotal;
            hambarCentral.adauga(numeProdus, cantitate);
            jurnal.adaugaEveniment("Cumparat " + std::to_string(cantitate) + "x " + numeProdus);
        } else {
            throw FermaException("Fonduri insuficiente pentru a cumpara " + numeProdus);
        }
    }

    void cheamaVeterinarul() {
        doc.trateazaCireada(cireada, bani, jurnal);
    }

    void platesteCheltuieli() {
        for (auto& angajat : echipa) {
            angajat.reseteazaZiua();
            if (bani >= angajat.cerereSalariu()) {
                bani -= angajat.cerereSalariu();
                angajat.plateste();
            } else {
                jurnal.adaugaEveniment("AVERTISMENT: Nu am platit angajatul " + angajat.getNume());
            }
        }
        for (const auto& anexa : anexe) {
            if (bani >= anexa.getCost()) {
                bani -= anexa.getCost();
            } else {
                jurnal.adaugaEveniment("AVERTISMENT: Fara bani de mentenanta pt " + anexa.getNume());
            }
        }
    }

    void proceseazaBiologie() {
        ziuaCurenta++;
        piataLocala.fluctueazaPreturi();
        meteo.schimbaVremea();

        jurnal.adaugaEveniment("--- ZIUA " + std::to_string(ziuaCurenta) + " --- Vreme: " + meteo.getNumeVreme());

        for (auto& c : contracte) c.treceZiua();

        bool areTaur = std::ranges::any_of(cireada, [](const Vacuta& v){
            return v.getSex() == Sex::MASCUL && v.esteAdult();
        });

        std::vector<Vacuta> puiNoi;
        std::uniform_int_distribution<int> distribSex(0, 1);
        std::uniform_int_distribution<int> distribNume(1, 999);

        for (auto& v : cireada) {
            v.treceTimpul(meteo.getVremeCurenta());
            if (areTaur && v.getSex() == Sex::FEMELA && v.esteAdult()) v.ramaneInsarcinata();

            if (v.verificaNastere() && cireada.size() + puiNoi.size() < static_cast<size_t>(capacitateMaxima)) {
                std::string numePui = "Vitelus_" + std::to_string(distribNume(generator));
                Sex sexPui = (distribSex(generator) == 0) ? Sex::FEMELA : Sex::MASCUL;
                puiNoi.emplace_back(numePui, 0, sexPui);
                trofee.deblocheazaPui(jurnal);
            }
        }
        for (auto& p : puiNoi) cireada.push_back(p);

        std::erase_if(cireada, [&](const Vacuta& v) {
            if (v.vreaSaFuga()) {
                jurnal.adaugaEveniment("TRAGEDIE: " + v.getNume() + " a fugit!");
                return true;
            }
            return false;
        });

        trofee.verificaAvere(bani, jurnal);
    }

    void mulge() {
        int lapteObtinut = 0;
        for (auto& v : cireada) lapteObtinut += v.mulge();

        if (lapteObtinut > 0) {
            for (const auto& anexa : anexe) {
                lapteObtinut = anexa.aplicaBonus(lapteObtinut);
            }
        }
        stocLapte += lapteObtinut;
    }

    void proceseazaVanzari() {
        int lapteRamas = stocLapte;

        for (auto& c : contracte) {
            if (!c.esteFinalizat() && !c.esteExpirat()) {
                lapteRamas = c.adaugaLapte(lapteRamas);
                if (c.esteFinalizat()) {
                    bani += c.getRecompensa();
                    jurnal.adaugaEveniment("Contract indeplinit pt " + c.getCompanie() + "!");
                }
            }
        }

        std::erase_if(contracte, [&](const Contract& c) {
            if (c.esteExpirat()) {
                jurnal.adaugaEveniment("Contract expirat (" + c.getCompanie() + ")! Penalizare 20 bani.");
                bani -= 20;
                return true;
            }
            return c.esteFinalizat();
        });

        if (lapteRamas > 0) {
            int profit = lapteRamas * piataLocala.getPretLapte();
            bani += profit;
            lapteRamas = 0;
        }
        stocLapte = lapteRamas;
    }

    void hranesteDinHambar(const Magazin& magazin, const std::string& numeProdus) {
        const Articol& produs = magazin.cautaArticol(numeProdus);
        for (auto& v : cireada) {
            if (hambarCentral.consuma(numeProdus)) {
                v.hraneste(produs);
            } else {
                jurnal.adaugaEveniment("ATENTIE: Hambarul a ramas fara " + numeProdus + "!");
                break;
            }
        }
    }

    void gatesteVitel(size_t index, int secunde) {
        if (index < cireada.size()) {
            if (!cireada[index].esteAdult() && cireada[index].getSex() == Sex::MASCUL) {
                Gratar g(secunde);
                int profit = g.vindeMancare("friptura", piataLocala, trofee, jurnal);
                bani += profit;
                jurnal.adaugaEveniment("Vitel gatit. Profit: " + std::to_string(profit));
                cireada.erase(cireada.begin() + static_cast<std::ptrdiff_t>(index));
            } else {
                throw FermaException("Poti gati doar vitei masculi non-adulti!");
            }
        }
    }

    void afiseazaIstoric() const { jurnal.afiseazaIstoric(); }
    void afiseazaHambar() const { hambarCentral.afiseazaStoc(); }

    friend std::ostream& operator<<(std::ostream& os, const Ferma& f) {
        os << "\n========================================\n"
           << " ZIUA " << f.ziuaCurenta << " | VREME: " << f.meteo.getNumeVreme() << "\n"
           << " FERMA: " << f.numeF << " | Proprietar: " << f.numeP
           << "\n Bani: " << f.bani << " | Contracte Active: " << f.contracte.size()
           << "\n Cireada (" << f.cireada.size() << "/" << f.capacitateMaxima << "):\n";
        for (const auto& v : f.cireada) os << "  " << v << "\n";
        return os << "========================================\n";
    }
};

int main() {
    std::cout << "--- START SIMULARE COMPLETA FERMA ---\n";
    Magazin magazinComunal;
    magazinComunal.afiseazaCatalog();

    std::string np, nf;
    std::cout << "Introdu numele proprietarului: ";
    if (!(std::getline(std::cin, np))) return 0;
    std::cout << "Introdu numele fermei: ";
    if (!(std::getline(std::cin, nf))) return 0;

    Ferma ferma(nf, np);
    ferma.inceputJoc();

    std::cout << "\n>>> TEST 1: Angajari, Cumparaturi si Cladiri <<<\n";
    ferma.angajeaza("Vasile (Mulgator)", 10);
    ferma.angajeaza("Ion (Ingrijitor)", 15);
    try {
        ferma.cumparaProvizii(magazinComunal, "Iarba", 30);
        ferma.cumparaProvizii(magazinComunal, "Fan_Premium", 15);
        ferma.construiesteAnexa("Sistem Automat Irigatii", 5, 5, 80);
        // Testam o eroare (nu mai avem bani pentru a 2-a cladire scumpa)
        ferma.construiesteAnexa("Tractor Nou", 10, 20, 500);
    } catch (const FermaException& ex) {
        std::cerr << " [EXCEPTIE ASTEPTATA] " << ex.what() << "\n";
    }

    std::cout << "\n>>> TEST 2: Contracte Economice <<<\n";
    ferma.adaugaContract("Lactate SA", 40, 200, 3); //contract scurt
    ferma.adaugaContract("Mega Image", 100, 600, 10); //contract pe termen lung

    std::cout << "\n>>> TEST 3: Simulare 7 Zile (Biologie, Vreme, Boli, Vanzari) <<<\n";
    for(int i = 1; i <= 7; ++i) {
        std::cout << "\n--- RULARE ZIUA " << i << " ---";
        ferma.platesteCheltuieli();

        //alternam mancarea pentru a testa hambarul
        if (i % 2 == 0) ferma.hranesteDinHambar(magazinComunal, "Fan_Premium");
        else ferma.hranesteDinHambar(magazinComunal, "Iarba");

        ferma.cheamaVeterinarul();
        ferma.mulge();
        ferma.proceseazaVanzari();
        ferma.proceseazaBiologie();
    }
    std::cout << ferma;

    std::cout << "\n>>> TEST 4: Modulul Gratar si Realizari <<<\n";
    //gatire gresita (adult)
    try {
        std::cout << " > Incerci sa gatesti un taur adult (Eroare)...";
        ferma.gatesteVitel(1, 180);
    } catch (const FermaException& ex) {
         std::cerr << "\n [EXCEPTIE] " << ex.what() << "\n";
    }
    //gatire vitel (daca s-a nascut macar unul in 7 zile) - Perfect
    try {
        std::cout << " > Incerci sa gatesti un vitel mascul PERFECT (180s)...";
        ferma.gatesteVitel(2, 180);
    } catch (const FermaException&) {} // prindem si ignoram in caz ca era femela
    //gatire Vitel - ars
    try {
        std::cout << "\n > Incerci sa gatesti alt vitel mascul ARS (300s)...";
        ferma.gatesteVitel(3, 300);
    } catch (const FermaException&) {}

    std::cout << "\n>>> REZUMAT FINAL <<<\n";
    ferma.afiseazaHambar();
    ferma.afiseazaIstoric();

    return 0;
}