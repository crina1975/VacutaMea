#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <random>
#include <exception>

enum class Sex { FEMELA, MASCUL };
enum class StareCarne { NEFACUTA, PERFECTA, ARSA };
enum class TipVreme { INSORIT, PLOIOS, FURTUNA, CANICULA };
enum class StareSanatate { SANATOASA, BOLNAVA, CRITICA };

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

//clasa 6
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

//clasa 7
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

//clasa 8
class Vacuta {
    std::string nume;
    Status foame;
    Status energie;
    int varsta;
    Sex sex;
    StareSanatate sanatate = StareSanatate::SANATOASA;
    int contorEnergieMaxima = 0;
    bool insarcinata = false;
    int zileSarcina = 0;
    std::mt19937 generator{std::random_device{}()};

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

        //influenta vremii
        if (vremeCurenta == TipVreme::CANICULA) factorFoame += 15;
        if (vremeCurenta == TipVreme::FURTUNA) factorEnergie -= 20;

        //influenta sanatatii
        if (sanatate == StareSanatate::BOLNAVA) {
            factorEnergie -= 15;
            factorFoame += 10;
        }

        //sansa de a se imbolnavi (10% sansa pe zi daca e sanatoasa)
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
        if (sanatate != StareSanatate::SANATOASA) return 0; //nu poti mulge o vaca bolnava
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

//clasa 9
class Veterinar {
    std::string numeClinica;
    int tarifTratament = 40;
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
                    jurnal.adaugaEveniment("AVERTISMENT: Nu sunt bani pentru a trata pe " + v.getNume() + "!");
                }
            }
        }
    }
};

//clasa 10
class Gratar {
    int timpGatireSecunde;
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

//clasa 11
class Ferma {
    std::string numeF;
    std::string numeP;
    std::vector<Vacuta> cireada;
    std::vector<Angajat> echipa;

    Piata piataLocala;
    Istoric jurnal;
    Vremea meteo;
    Veterinar doc;
    SistemRealizari trofee;

    int bani;
    int stocLapte;
    int nivelFerma;
    int capacitateMaxima;
    int ziuaCurenta;
    std::mt19937 generator{std::random_device{}()};

public:
    Ferma(std::string nf, std::string np)
        : numeF{std::move(nf)}, numeP{std::move(np)}, cireada{}, echipa{},
          piataLocala{}, jurnal{}, meteo{}, doc{"Clinica VetHappy"}, trofee{},
          bani{250}, stocLapte{0}, nivelFerma{1}, capacitateMaxima{5}, ziuaCurenta{1} {}

    void inceputJoc() {
        cireada.emplace_back("Milka", 3, Sex::FEMELA);
        cireada.emplace_back("Milk", 4, Sex::MASCUL);
        jurnal.adaugaEveniment("Ferma a fost fondata. Animale initiale adaugate.");
    }

    void angajeaza(const std::string& numeAngajat, int salariu) {
        echipa.emplace_back(numeAngajat, salariu);
        jurnal.adaugaEveniment("A fost angajat " + numeAngajat + " (Salariu: " + std::to_string(salariu) + ").");
    }

    void cheamaVeterinarul() {
        doc.trateazaCireada(cireada, bani, jurnal);
    }

    void platesteAngajati() {
        for (auto& angajat : echipa) {
            angajat.reseteazaZiua();
            if (bani >= angajat.cerereSalariu()) {
                bani -= angajat.cerereSalariu();
                angajat.plateste();
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
            std::cout << "[FERMA] Upgrade la nivelul " << nivelFerma << "!\n";
            jurnal.adaugaEveniment("Upgrade ferma la nivelul " + std::to_string(nivelFerma) + ".");
        } else {
            throw FermaException("Fonduri insuficiente sau capacitate maxima atinsa pentru upgrade!");
        }
    }

    void proceseazaBiologie() {
        ziuaCurenta++;
        piataLocala.fluctueazaPreturi();
        meteo.schimbaVremea();

        jurnal.adaugaEveniment("--- ZIUA " + std::to_string(ziuaCurenta) + " --- Vreme: " + meteo.getNumeVreme());

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
                jurnal.adaugaEveniment("TRAGEDIE: " + v.getNume() + " a fugit din cauza foamei!");
                return true;
            }
            return false;
        });

        trofee.verificaAvere(bani, jurnal);
    }

    void mulge() {
        int lapteObtinut = 0;
        for (auto& v : cireada) lapteObtinut += v.mulge();
        stocLapte += lapteObtinut;
    }

    void vindeLapte() {
        if (stocLapte > 0) {
            int profit = stocLapte * piataLocala.getPretLapte();
            bani += profit;
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

    friend std::ostream& operator<<(std::ostream& os, const Ferma& f) {
        os << "\n========================================\n"
           << " ZIUA " << f.ziuaCurenta << " | VREME: " << f.meteo.getNumeVreme() << "\n"
           << " FERMA: " << f.numeF << " | Proprietar: " << f.numeP
           << "\n Bani: " << f.bani << " | Nivel: " << f.nivelFerma
           << "\n Cireada (" << f.cireada.size() << "/" << f.capacitateMaxima << "):\n";
        for (const auto& v : f.cireada) os << "  " << v << "\n";
        return os << "========================================\n";
    }
};

int main() {
    Articol iarba("Iarba Standard", 10, 30);

    std::string np, nf;
    std::cout << "Bun venit! Nume proprietar: ";
    if (!(std::getline(std::cin, np))) return 0;
    std::cout << "Nume ferma: ";
    if (!(std::getline(std::cin, nf))) return 0;

    Ferma ferma(nf, np);
    ferma.inceputJoc();
    ferma.angajeaza("Gheorghe", 15);

    std::cout << "\n--- SIMULARE ZILE (Vreme, Boli, Achievements) ---";
    for(int i = 0; i < 5; ++i) {
        ferma.platesteAngajati();
        ferma.hranesteToate(iarba);
        ferma.cheamaVeterinarul();
        ferma.mulge();
        ferma.vindeLapte();
        ferma.proceseazaBiologie();
        std::cout << ferma;
    }

    std::cout << "\n--- TEST GRATAR (Realizare MasterChef) ---";
    try {
        ferma.gatesteVitel(2, 180);
    } catch (const FermaException&) {
        //ignoram eroarea in caz ca pe acea pozitie e femela sau un adult
    }

    ferma.afiseazaIstoric();

    return 0;
}