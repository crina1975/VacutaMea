#ifndef UTILITARE_H
#define UTILITARE_H

#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <map>

enum class StareCarne { NEFACUTA, PERFECTA, ARSA };
enum class TipVreme { INSORIT, PLOIOS, FURTUNA, CANICULA };

class Istoric {
private:
    std::vector<std::string> loguri;
public:
    void adaugaEveniment(const std::string& eveniment);
    friend std::ostream& operator<<(std::ostream& os, const Istoric& istoric);
};

class Piata {
private:
    int pretLapte = 5;
    int pretCarne = 80;
    std::mt19937 generator;
public:
    Piata();
    void fluctueazaPreturi();
    int getPretLapte() const;
    int getPretCarne() const;
    friend std::ostream& operator<<(std::ostream& os, const Piata& p);
};

class Vremea {
private:
    TipVreme stadiuCurent = TipVreme::INSORIT;
    std::mt19937 generator;
public:
    Vremea();
    void schimbaVremea();
    TipVreme getVremeCurenta() const;
    std::string getNumeVreme() const;
    friend std::ostream& operator<<(std::ostream& os, const Vremea& v);
};

class SistemRealizari {
private:
    bool primulPui = false;
    bool bogatie = false;
    bool maestruBucatar = false;
public:
    void verificaAvere(int bani, Istoric& jurnal);
    void deblocheazaPui(Istoric& jurnal);
    void deblocheazaBucatar(Istoric& jurnal);
    friend std::ostream& operator<<(std::ostream& os, const SistemRealizari& s);
};

class Articol {
private:
    std::string nume;
    int pret;
    int putereSatietate;
public:
    explicit Articol(std::string n = "Nimic", int p = 0, int sat = 0);
    int getPret() const;
    int getPutereSatietate() const;
    const std::string& getNume() const;
    friend std::ostream& operator<<(std::ostream& os, const Articol& a);
};

class Magazin {
private:
    std::vector<Articol> catalog;
public:
    Magazin();
    ~Magazin();
    Magazin(const Magazin& other);
    Magazin& operator=(const Magazin& other);
    Articol cautaArticol(const std::string& numeCautat) const;
    friend std::ostream& operator<<(std::ostream& os, const Magazin& m);
};

class Hambar {
private:
    std::map<std::string, int> stocuri;
public:
    void adauga(const std::string& numeArticol, int cantitate);
    bool consuma(const std::string& numeArticol);
    friend std::ostream& operator<<(std::ostream& os, const Hambar& h);
};

class Status {
private:
    std::string nume;
    int valoare;
public:
    explicit Status(std::string n = "Parametru", int v = 100);
    void modifica(int delta);
    int getValoare() const;
    friend std::ostream& operator<<(std::ostream& os, const Status& s);
};

class Angajat {
private:
    std::string nume;
    int salariuZilnic;
    bool platitAzi = false;
public:
    explicit Angajat(std::string n, int salariu);
    int cerereSalariu() const;
    const std::string& getNume() const;
    void plateste();
    void reseteazaZiua();
    friend std::ostream& operator<<(std::ostream& os, const Angajat& a);
};

class Contract {
private:
    std::string companie;
    int necesarLapte;
    int lapteColectat = 0;
    int recompensaBani;
    int zileRamase;
    bool finalizat = false;
public:
    Contract(std::string comp, int necesar, int rec, int zile);
    bool esteFinalizat() const;
    bool esteExpirat() const;
    int getRecompensa() const;
    const std::string& getCompanie() const;
    int adaugaLapte(int cantitate);
    void treceZiua();
    friend std::ostream& operator<<(std::ostream& os, const Contract& c);
};

class CladireAuxiliara {
private:
    std::string nume;
    int bonusProductie;
    int costIntretinere;
public:
    CladireAuxiliara(std::string n, int bonus, int cost);
    int aplicaBonus(int productie) const;
    int getCost() const;
    const std::string& getNume() const;
    friend std::ostream& operator<<(std::ostream& os, const CladireAuxiliara& c);
};

class Gratar {
private:
    int timpGatireSecunde;
public:
    explicit Gratar(int timp = 0);
    StareCarne verificaStare() const;
    int vindeMancare(const std::string& tip, const Piata& piataCurenta, SistemRealizari& ach, Istoric& jurnal) const;
};

#endif