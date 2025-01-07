#include "Wypozyczenie.h"

Wypozyczenie::Wypozyczenie(int id, const Egzemplarz& e, const KontoCzytelnika& c, const std::string& data, const std::string& termin)
    : wypozyczenieID(id), egzemplarz(e), czytelnik(c), dataWypozyczenia(data), terminZwrotu(termin) {
}

int Wypozyczenie::getWypozyczenieID() const {
    return wypozyczenieID;
}

Egzemplarz Wypozyczenie::getEgzemplarz() const {
    return egzemplarz;
}

KontoCzytelnika Wypozyczenie::getCzytelnik() const {
    return czytelnik;
}

string Wypozyczenie::getTerminZwrotu() const {
    return terminZwrotu;
}
