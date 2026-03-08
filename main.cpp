#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <utility>

class Status {
private:
    std::string nume;
    int valoare;
public:
    explicit Status(std::string n, int v) : nume{std::move(n)}, valoare{v} {}
    void modifica(int delta) {
        valoare = std::clamp(valoare + delta, 0, 100);
    }
    int getValoare() const { return valoare; }
};

class Vacuta {
private:
    char* nume;
    Status foame;
    Status energie;
    int litriLapte;
    int bani;

public:
    explicit Vacuta(const char* nume_dat)
        : nume{nullptr},
          foame{"Foame", 100},
          energie{"Energie", 100},
          litriLapte{0},
          bani{10}
    {
        if (nume_dat) {
            size_t len = std::strlen(nume_dat) + 1;
            nume = new char[len];
            std::copy(nume_dat, nume_dat + len, nume);
        }
    }

    ~Vacuta() {
        delete[] nume;
    }

    Vacuta(const Vacuta& other)
        : nume{nullptr},
          foame{other.foame},
          energie{other.energie},
          litriLapte{other.litriLapte},
          bani{other.bani}
    {
        if (other.nume) {
            size_t len = std::strlen(other.nume) + 1;
            nume = new char[len];
            std::copy(other.nume, other.nume + len, nume);
        }
    }

    Vacuta& operator=(const Vacuta& other) {
        if (this != &other) {
            char* nume_nou = nullptr;
            if (other.nume) {
                size_t len = std::strlen(other.nume) + 1;
                nume_nou = new char[len];
                std::copy(other.nume, other.nume + len, nume_nou);
            }
            delete[] nume;
            nume = nume_nou;
            foame = other.foame;
            energie = other.energie;
            litriLapte = other.litriLapte;
            bani = other.bani;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vacuta& v) {
        os << "\n--- Status " << (v.nume ? v.nume : "Anonim") << " ---\n"
           << "Foame: " << v.foame.getValoare() << "/100\n"
           << "Energie: " << v.energie.getValoare() << "/100\n"
           << "Lapte: " << v.litriLapte << "L | Bani: " << v.bani << "\n";
        return os;
    }

    void treceTimpul(int ore) {
        foame.modifica(-10 * ore);
        energie.modifica(-5 * ore);
        if (foame.getValoare() < 20) {
            energie.modifica(-15 * ore);
        }
    }

    void mulge() {
        if (energie.getValoare() > 30 && foame.getValoare() > 20) {
            int bonus = foame.getValoare() / 25;
            litriLapte += (5 + bonus);
            energie.modifica(-35);
        }
    }

    void vindeLapte() {
        if (litriLapte > 0) {
            bani += litriLapte * 3;
            litriLapte = 0;
        }
    }
};

int main() {
    Vacuta v1{"Milka"};
    v1.treceTimpul(2);
    v1.mulge();
    v1.vindeLapte();
    std::cout << v1;
    Vacuta v2{v1};
    Vacuta v3{"Zuzu"};
    v3 = v1;
    return 0;
}