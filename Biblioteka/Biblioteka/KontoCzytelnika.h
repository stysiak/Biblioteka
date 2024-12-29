#pragma once
#include "header.h"
#include "Ksiazka.h"

class KontoCzytelnika {
private:
	string imie;
	string nazwisko;
	int pesel;
	vector<Ksiazka> listaWypozyczonych;
	float kaucja;
	int iloscKsiazek;
	bool przekroczonoLimit;
public:
	float zwrotKaucji();
	KontoCzytelnika(string i, string n, int p): imie(i), nazwisko(n), pesel(p){}
	friend class BazaCzytelnikow;
};