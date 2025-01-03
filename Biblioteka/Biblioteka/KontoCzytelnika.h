#pragma once
#include "header.h"
#include "Ksiazka.h"

class KontoCzytelnika {
private:
	string pesel;
	string imie;
	string nazwisko;
	//vector<Ksiazka> listaWypozyczonych;
	//float kaucja;
	//int iloscKsiazek;
	//bool przekroczonoLimit;
public:
	KontoCzytelnika();
	KontoCzytelnika(const string& pesel, const string& imie, const string& nazwisko);
	KontoCzytelnika(const string& pesel);
	string getPesel() const;
	string getImie() const;
	string getNazwisko() const;
	friend class BazaCzytelnikow;
};