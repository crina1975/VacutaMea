#include "ferma.hpp"
#include "vacuta.hpp"

Ferma::Ferma(std::string nf, std::string np)
    : numeF{std::move(nf)}, numeP{std::move(np)} {}

Ferma::Ferma(const Ferma& other)
    : numeF(other.numeF), numeP(other.numeP),
      piataLocala(other.piataLocala), jurnal(other.jurnal),
      meteo(other.meteo), doc(other.doc), trofee(other.trofee),
      hambarCentral(other.hambarCentral), bani(other.bani),
      stocLapte(other.stocLapte), capacitateMaxima(other.capacitateMaxima),
      ziuaCurenta(other.ziuaCurenta), generator(std::random_device{}()) {

    cireada.reserve(other.cireada.size());
    for (const auto& b : other.cireada) {
        cireada.emplace_back(b->clone());
    }
    echipa = other.echipa;
    contracte = other.contracte;
    anexe = other.anexe;
}

Ferma& Ferma::operator=(Ferma other) {
    swap(*this, other);
    return *this;
}

void swap(Ferma& a, Ferma& b) {
    using std::swap;
    swap(a.numeF, b.numeF);
    swap(a.numeP, b.numeP);
    swap(a.cireada, b.cireada);
    swap(a.echipa, b.echipa);
    swap(a.contracte, b.contracte);
    swap(a.anexe, b.anexe);
    swap(a.piataLocala, b.piataLocala);
    swap(a.jurnal, b.jurnal);
    swap(a.meteo, b.meteo);
    swap(a.doc, b.doc);
    swap(a.trofee, b.trofee);
    swap(a.hambarCentral, b.hambarCentral);
    swap(a.bani, b.bani);
    swap(a.stocLapte, b.stocLapte);
    swap(a.capacitateMaxima, b.capacitateMaxima);
    swap(a.ziuaCurenta, b.ziuaCurenta);
}

void Ferma::inceputJoc() {
    cireada.emplace_back(std::make_unique<Vacuta>("Milka", 3, Sex::FEMELA));
    cireada.emplace_back(std::make_unique<Vacuta>("Milk", 4, Sex::MASCUL));
    jurnal.adaugaEveniment("Ferma a fost fondata.");
}

void Ferma::angajeaza(const std::string& numeAngajat, int salariu) {
    echipa.emplace_back(numeAngajat, salariu);
}

void Ferma::adaugaContract(const std::string& companie, int necesar, int recompensa, int zile) {
    contracte.emplace_back(companie, necesar, recompensa, zile);
    jurnal.adaugaEveniment("Contract semnat cu: " + companie);
}

void Ferma::construiesteAnexa(const std::string& numeAnexa, int bonus, int intretinere, int pret) {
    if (bani >= pret) {
        bani -= pret;
        anexe.emplace_back(numeAnexa, bonus, intretinere);
        jurnal.adaugaEveniment("S-a construit: " + numeAnexa);
    } else {
        std::cout << "\n[EROARE] Bani insuficienti pentru a construi " << numeAnexa << "!\n";
    }
}

void Ferma::cumparaProvizii(const Magazin& magazin, const std::string& numeProdus, int cantitate) {
    Articol produs = magazin.cautaArticol(numeProdus);
    if (produs.getNume() == "Eroare") return;

    int costTotal = produs.getPret() * cantitate;
    if (bani >= costTotal) {
        bani -= costTotal;
        hambarCentral.adauga(numeProdus, cantitate);
        jurnal.adaugaEveniment("Cumparat " + std::to_string(cantitate) + "x " + numeProdus);
    } else {
        std::cout << "\n[EROARE] Fonduri insuficiente pentru a cumpara " << cantitate << "x " << numeProdus << "!\n";
    }
}

void Ferma::cheamaVeterinarul() {
    doc.trateazaCireada(cireada, bani, jurnal);
}

// cppcheck-suppress unusedFunction
void Ferma::platesteCheltuieli() {
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

void Ferma::proceseazaBiologie() {
    ziuaCurenta++;
    piataLocala.fluctueazaPreturi();
    meteo.schimbaVremea();

    jurnal.adaugaEveniment(std::string("--- ZIUA ") + std::to_string(ziuaCurenta) + " --- Vreme: " + meteo.getNumeVreme());
    for (auto& c : contracte) c.treceZiua();

    bool areTaur = std::any_of(cireada.begin(), cireada.end(), [](const std::unique_ptr<Bovina>& b){
        return b->getSex() == Sex::MASCUL && b->esteAdult();
    });

    std::vector<std::unique_ptr<Bovina>> puiNoi;
    std::uniform_int_distribution<int> distribSex(0, 1);
    std::uniform_int_distribution<int> distribNume(1, 999);

    for (auto& b : cireada) {
        b->treceTimpul(meteo.getVremeCurenta(), generator);

        if (areTaur) {
            if (auto* v = dynamic_cast<Vacuta*>(b.get())) {
                if (v->getSex() == Sex::FEMELA && v->esteAdult()) v->ramaneInsarcinata();
            }
        }

        if (b->verificaNastere() && cireada.size() + puiNoi.size() < static_cast<size_t>(capacitateMaxima)) {
            std::string numePui = "Vitelus_" + std::to_string(distribNume(generator));
            Sex sexPui = (distribSex(generator) == 0) ? Sex::FEMELA : Sex::MASCUL;
            puiNoi.emplace_back(std::make_unique<Vacuta>(numePui, 0, sexPui));
            trofee.deblocheazaPui(jurnal);
        }
    }

    for (auto& p : puiNoi) cireada.emplace_back(std::move(p));

    cireada.erase(std::remove_if(cireada.begin(), cireada.end(),
        [&](const std::unique_ptr<Bovina>& b){
            if (b->vreaSaFuga()) {
                jurnal.adaugaEveniment("TRAGEDIE: " + b->getNume() + " a fugit!");
                return true;
            }
            return false;
        }), cireada.end());

    trofee.verificaAvere(bani, jurnal);
}

void Ferma::mulge() {
    int lapteObtinut = 0;
    for (auto& b : cireada) lapteObtinut += b->mulge();
    if (lapteObtinut > 0) {
        for (const auto& anexa : anexe) {
            lapteObtinut = anexa.aplicaBonus(lapteObtinut);
        }
    }
    stocLapte += lapteObtinut;
}

void Ferma::proceseazaVanzari() {
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

    contracte.erase(std::remove_if(contracte.begin(), contracte.end(),
        [&](const Contract& c) {
            if (c.esteExpirat()) {
                jurnal.adaugaEveniment("Contract expirat (" + c.getCompanie() + ")! Penalizare 20 bani.");
                bani -= 20;
                return true;
            }
            return c.esteFinalizat();
        }), contracte.end());

    if (lapteRamas > 0) {
        int profit = lapteRamas * piataLocala.getPretLapte();
        bani += profit;
        lapteRamas = 0;
    }
    stocLapte = lapteRamas;
}
// cppcheck-suppress unusedFunction
void Ferma::hranesteDinHambar(const Magazin& magazin, const std::string& numeProdus) {
    Articol produs = magazin.cautaArticol(numeProdus);
    if (produs.getNume() == "Eroare") return;

    for (auto& b : cireada) {
        if (hambarCentral.consuma(numeProdus)) {
            b->hraneste(produs);
        } else {
            jurnal.adaugaEveniment("ATENTIE: Hambarul a ramas fara " + numeProdus + "!");
            break;
        }
    }
}

void Ferma::gatesteVitel(size_t index, int secunde) {
    if (index >= cireada.size()) {
        std::cout << "\n[EROARE] Nu exista nicio vacuta la indexul " << index << "!\n";
        return;
    }
    auto* v = dynamic_cast<Vacuta*>(cireada[index].get());
    if (!v) {
        std::cout << "\n[EROARE] Animalul de la index nu poate fi gatit!\n";
        return;
    }
    if (!v->esteAdult() && v->getSex() == Sex::MASCUL) {
        Gratar g(secunde);
        int profit = g.vindeMancare("friptura", piataLocala, trofee, jurnal);
        bani += profit;
        jurnal.adaugaEveniment("Vitel gatit. Profit: " + std::to_string(profit));
        cireada.erase(cireada.begin() + static_cast<std::ptrdiff_t>(index));
    } else {
        std::cout << "\n[EROARE] Poti gati doar vitei masculi care nu au ajuns la stadiul de adult!\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Ferma& f) {
    os << "\n========================================\n"
       << " ZIUA " << f.ziuaCurenta << " | VREME: " << f.meteo.getNumeVreme() << "\n"
       << " FERMA: " << f.numeF << " | Proprietar: " << f.numeP
       << "\n Bani: " << f.bani << " | Contracte Active: " << f.contracte.size()
       << "\n Cireada (" << f.cireada.size() << "/" << f.capacitateMaxima << "):\n";
    for (const auto& v : f.cireada) os << "  " << *v << "\n";
    os << "\n Angajati:\n";
    for (const auto& a : f.echipa) os << "  " << a << "\n";
    return os << "========================================\n";
}