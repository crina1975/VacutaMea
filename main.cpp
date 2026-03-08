#include <iostream>
#include <string>
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
    std::string nume;
    Status foame;
    Status energie;
    int litriLapte;
    int bani;

public:
    explicit Vacuta(std::string nume_dat)
        : nume{std::move(nume_dat)},
          foame{"Foame", 100},
          energie{"Energie", 100},
          litriLapte{0},
          bani{10}
    {}

    friend std::ostream& operator<<(std::ostream& os, const Vacuta& v) {
        os << "\n--- Status " << v.nume << " ---\n"
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

    Vacuta v2 = v1;
    Vacuta v3{"Zuzu"};
    v3 = v1;

    return 0;
}