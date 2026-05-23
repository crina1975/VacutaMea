#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <utility>

// ==========================================
// 1. IERARHIE DE EXCEPȚII
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
// 2. CLASA DE BAZĂ ABSTRACTĂ
// ==========================================
class Animal {
protected:
    std::string nume;
    int varsta;
    int energie;
    const int id;
    static int contor_animale;

    virtual void afisare(std::ostream& os) const {
        os << "[ID: " << id << "] " << nume << " (V:" << varsta << " ani, E:" << energie << "%)";
    }

public:
    Animal(std::string n, int v) : nume(std::move(n)), varsta(v), energie(100), id(++contor_animale) {
        if (nume.empty()) throw EroareParametru("Nume gol!");
        if (varsta < 0) throw EroareParametru("Varsta negativa!");
    }

    virtual ~Animal() = default;
    virtual Animal* clone() const = 0;
    virtual void scoateSunet() const = 0;

    static int getTotalAnimale() { return contor_animale; }

    friend std::ostream& operator<<(std::ostream& os, const Animal& a) {
        a.afisare(os);
        return os;
    }
};

int Animal::contor_animale = 0;

// ==========================================
// 3. CLASE DERIVATE
// ==========================================
class Vacuta : public Animal {
private:
    int litriLapte;

protected:
    void afisare(std::ostream& os) const override {
        os << "Vacuta "; Animal::afisare(os); os << " -> Lapte: " << litriLapte << "L/zi";
    }

public:
    Vacuta(std::string n, int v, int lapte) : Animal(std::move(n), v), litriLapte(lapte) {}

    Animal* clone() const override { return new Vacuta(*this); }
    void scoateSunet() const override { std::cout << nume << " face: Muuuuu!\n"; }

    int mulge() const {
        if (energie < 20) throw EroareLogica(nume + " prea obosita.");
        return litriLapte;
    }
};

class Gaina : public Animal {
private:
    int oua;

protected:
    void afisare(std::ostream& os) const override {
        os << "Gaina "; Animal::afisare(os); os << " -> Oua: " << oua << "/zi";
    }

public:
    Gaina(std::string n, int v, int oua_zilnic) : Animal(std::move(n), v), oua(oua_zilnic) {}

    Animal* clone() const override { return new Gaina(*this); }
    void scoateSunet() const override { std::cout << nume << " face: Cotcodac!\n"; }
    int adunaOua() const { return oua; }
};

// ==========================================
// 4. MANAGEMENTUL RESURSELOR (Regula celor 3)
// ==========================================
class Ferma {
private:
    std::string numeFerma;
    std::vector<Animal*> animale;

public:
    explicit Ferma(std::string nume) : numeFerma(std::move(nume)) {
        if (numeFerma.empty()) throw EroareParametru("Nume ferma gol.");
    }

    Ferma(const Ferma& other) : numeFerma(other.numeFerma) {
        for (const auto* animal : other.animale) animale.push_back(animal->clone());
    }

    ~Ferma() {
        for (auto* animal : animale) delete animal;
        animale.clear();
    }

    Ferma& operator=(Ferma other) {
        std::swap(numeFerma, other.numeFerma);
        std::swap(animale, other.animale);
        return *this;
    }

    void adaugaAnimal(const Animal& a) {
        animale.push_back(a.clone());
    }

    void raporteazaProductia() const {
        int totalLapte = 0, totalOua = 0;
        std::cout << "\n=== Productie " << numeFerma << " ===\n";
        for (const auto* animal : animale) {
            if (const Vacuta* v = dynamic_cast<const Vacuta*>(animal)) totalLapte += v->mulge();
            else if (const Gaina* g = dynamic_cast<const Gaina*>(animal)) totalOua += g->adunaOua();
        }
        std::cout << " -> Lapte: " << totalLapte << " L\n -> Oua: " << totalOua << " buc\n";
    }

    void catalogAnimale() const {
        std::cout << "\n=== Catalog (" << numeFerma << ") ===\n";
        for (const auto* animal : animale) {
            std::cout << *animal << "\n";
            animal->scoateSunet();
        }
    }
};

// ==========================================
// 5. FUNCTIA MAIN
// ==========================================
int main() {
    try {
        std::cout << "[Test Excepție] Cream animal invalid...\n";
        Gaina g_eroare("Invalida", -1, 5);
    } catch (const EroareParametru& e) {
        std::cout << ">> Prins corect: " << e.what() << "\n\n";
    }

    try {
        Ferma ferma("Ferma De Test");
        Vacuta v1("Milka", 3, 12);
        Gaina g1("Porumbica", 2, 2);

        ferma.adaugaAnimal(v1);
        ferma.adaugaAnimal(g1);
        ferma.catalogAnimale();
        ferma.raporteazaProductia();

        std::cout << "\n[Statistici] Animale create in memorie: " << Animal::getTotalAnimale() << "\n";

        Ferma fermaCopie = ferma; // Test copy constructor
        std::cout << "\n[Test Copiere] Productie din copie:";
        fermaCopie.raporteazaProductia();

    } catch (const EroareFerma& e) {
        std::cerr << "Eroare: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Fatal: " << e.what() << "\n";
    }

    return 0;
}