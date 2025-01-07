#pragma once
#include "header.h"
#include "KontoCzytelnika.h"
#include "Egzemplarz.h"

class Wypozyczenie {
private:
	int wypozyczenieID;
	Egzemplarz egzemplarz;
	KontoCzytelnika czytelnik;
	string dataWypozyczenia;
	string terminZwrotu;
public:
	Wypozyczenie(int id, const Egzemplarz& e, const KontoCzytelnika& c, const std::string& data, const std::string& termin);
	int getWypozyczenieID() const;
	Egzemplarz getEgzemplarz() const;
	KontoCzytelnika getCzytelnik() const;
	string getTerminZwrotu() const;
	Wypozyczenie();
	void przypiszCzytelnika(KontoCzytelnika);
	void przypiszEgzemplarz(Egzemplarz);
};
