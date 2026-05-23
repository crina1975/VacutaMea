#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <utility>

// ==========================================
// 1. IERARHIE DE EXCEPȚII (Derivate din std::runtime_error)
// ==========================================
class EroareFerma : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class EroareParametru : public EroareFerma {
public:
    explicit EroareParametru(const std::string& msg)
        : EroareFerma("Eroare parametru: " + msg) {}
};

class EroareLogica : public EroareFerma {
public:
    explicit EroareLogica(const std::string& msg)
        : EroareFerma("Eroare logica: " + msg) {}
};

// ==========================================
// 2. CLASA DE BAZĂ ABSTRACTĂ (Interfață & Metode Statice)
// ==========================================
class Animal {
protected:
    std::string nume;
    int varsta;
    int energie;

    // Atribut constant initializat la construire
    const int id;

    // Atribut STATIC (comun pentru toate obiectele)
    static int contor_animale;

    // Functie virtuala protected (Interfata non-virtuala)
    virtual void afisare(std::ostream& os) const {
        os << "[ID: " << id << "] " << nume << " (Varsta: " << varsta << " ani, Energie: " << energie << "%)";
    }

public:
    Animal(std::string n, int v) : nume(std::move(n)), varsta(v), energie(100), id(++contor_animale) {
        // THROW IN CONSTRUCTOR - Validam datele; daca sunt gresite, evitam instantierea obiectului invalid
        if (nume.empty()) {
            throw EroareParametru("Numele animalului nu poate fi gol!");
        }
        if (varsta < 0) {
            throw EroareParametru("Varsta nu poate fi negativa!");
        }
    }

    virtual ~Animal() = default;

    // CONSTRUCTOR VIRTUAL (Clonare)
    virtual Animal* clone() const = 0;

    // Functie virtuala pura
    virtual void scoateSunet() const = 0;

    int getId() const { return id; }

    // Functie STATICĂ
    static int getTotalAnimale() { return contor_animale; }

    friend std::ostream& operator<<(std::ostream& os, const Animal& a) {
        a.afisare(os);
        return os;
    }
};

// Inițializare atribut static
int Animal::contor_animale = 0;

// ==========================================
// 3. CLASE DERIVATE
// ==========================================
class Vacuta : public Animal {
private:
    int litriLapteZilnic;

protected:
    void afisare(std::ostream& os) const override {
        os << "Vacuta ";
        Animal::afisare(os);
        os << " -> Ofera: " << litriLapteZilnic << "L lapte/zi";
    }

public:
    Vacuta(std::string n, int v, int lapte) : Animal(std::move(n), v), litriLapteZilnic(lapte) {}

    Animal* clone() const override {
        return new Vacuta(*this);
    }

    void scoateSunet() const override {
        std::cout << nume << " mugește: Muuuuu!\n";
    }

    int mulge() const {
        if (energie < 20) throw EroareLogica(nume + " este prea obosita pentru a da lapte.");
        return litriLapteZilnic;
    }
};

class Gaina : public Animal {
private:
    int ouaZilnic;

protected:
    void afisare(std::ostream& os) const override {
        os << "Gaina ";
        Animal::afisare(os);
        os << " -> Ofera: " << ouaZilnic << " oua/zi";
    }

public:
    Gaina(std::string n, int v, int oua) : Animal(std::move(n), v), ouaZilnic(oua) {}

    Animal* clone() const override {
        return new Gaina(*this);
    }

    void scoateSunet() const override {
        std::cout << nume << " cotcodaceste: Cotcodac!\n";
    }

    int adunaOua() const {
        return ouaZilnic;
    }
};

// ==========================================
// 4. GESTIONAREA RESURSELOR (Regula celor 3 - Copy and Swap)
// ==========================================
class Ferma {
private:
    std::string numeFerma;
    std::vector<Animal*> animale; // Gestioneaza pointeri polimorfici

public:
    explicit Ferma(std::string nume) : numeFerma(std::move(nume)) {
        if (numeFerma.empty()) throw EroareParametru("Numele fermei nu poate fi gol.");
    }

    // 1. Constructorul de Copiere (Deep Copy)
    Ferma(const Ferma& other) : numeFerma(other.numeFerma) {
        std::cout << "[Sistem] Apel Constructor Copiere Ferma\n";
        for (const auto* animal : other.animale) {
            animale.push_back(animal->clone());
        }
    }

    // 2. Destructorul
    ~Ferma() {
        for (auto* animal : animale) {
            delete animal;
        }
        animale.clear();
    }

    // Functie Custom Swap
    friend void swap(Ferma& f1, Ferma& f2) noexcept {
        using std::swap;
        swap(f1.numeFerma, f2.numeFerma);
        swap(f1.animale, f2.animale);
    }

    // 3. Operatorul de Atribuire (Copy-and-Swap idiom)
    Ferma& operator=(Ferma other) {
        std::cout << "[Sistem] Apel Operator= Ferma\n";
        swap(*this, other);
        return *this;
    }

    // Adaugare polimorfica
    void adaugaAnimal(const Animal& a) {
        animale.push_back(a.clone());
    }

    // DYNAMIC CAST
    void raporteazaProductia() const {
        int totalLapte = 0;
        int totalOua = 0;

        std::cout << "\n=== Productie Generata de " << numeFerma << " ===\n";

        for (const auto* animal : animale) {
            // Verificam la runtime ce tip de animal este pointerul curent
            if (const Vacuta* v = dynamic_cast<const Vacuta*>(animal)) {
                totalLapte += v->mulge();
            }
            else if (const Gaina* g = dynamic_cast<const Gaina*>(animal)) {
                totalOua += g->adunaOua();
            }
        }

        std::cout << " -> Lapte adunat: " << totalLapte << " L\n";
        std::cout << " -> Oua adunate: " << totalOua << " bucati\n";
    }

    void catalogAnimale() const {
        std::cout << "\n=== Catalog Animale (" << numeFerma << ") ===\n";
        for (const auto* animal : animale) {
            std::cout << *animal << "\n";
            animal->scoateSunet(); // Apel polimorfic
        }
    }
};

// ==========================================
// 5. FUNCTIA MAIN (TESTAREA COMPLETA)
// ==========================================
int main() {
    std::cout << "--- START SIMULARE TEMA 2 ---\n\n";

    // TEST 1: Exceptii
    try {
        std::cout << "[Test] Incercam sa creem un animal cu varsta negativa...\n";
        Gaina g_invalida("Eroare", -5, 1);
    }
    catch (const EroareParametru& e) {
        std::cout << ">> EROARE PRINSĂ CU SUCCES: " << e.what() << "\n\n";
    }

    try {
        Ferma ferma("Ferma Vesela");

        // TEST 2: Polimorfism si Adaugare Animale
        Vacuta v1("Milka", 4, 15);
        Gaina g1("Cocuta", 2, 2);
        Gaina g2("Geta", 1, 1);

        ferma.adaugaAnimal(v1);
        ferma.adaugaAnimal(g1);
        ferma.adaugaAnimal(g2);

        ferma.catalogAnimale();

        // TEST 3: Dynamic Cast
        ferma.raporteazaProductia();

        // TEST 4: Metode si variabile Statice
        std::cout << "\n[Statistică] Animale trecute prin sistem pana acum: "
                  << Animal::getTotalAnimale() << "\n";

        // TEST 5: Regula celor 3 (Copy & Swap Idiom)
        std::cout << "\n--- Testare Management Memorie (Deep Copy) ---\n";
        Ferma fermaCopie = ferma; // Apeleaza Constructorul de Copiere

        Ferma fermaGoala("Ferma Temporara");
        fermaGoala = ferma;       // Apeleaza Operatorul de Atribuire (Copy-and-Swap)

        std::cout << "Ferma copiata raporteaza aceeasi productie:";
        fermaCopie.raporteazaProductia();

    }
    catch (const EroareFerma& e) {
        std::cerr << "[EROARE FERMA]: " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "[EROARE FATALA]: " << e.what() << "\n";
    }

    std::cout << "\n--- SFARSIT SIMULARE ---\n";
    return 0;
}