#pragma once
#include "../../header.h"
//#include "Ksiazka.h"

class KontoCzytelnika {
private:
	string pesel;
	string imie;
	string nazwisko;
	float kaucja = 0.0;
	int iloscKsiazek = 0;
public:
	KontoCzytelnika(const string& pesel, const string& imie, const string& nazwisko, const float& kaucja, const int& iloscKsiazek);
	KontoCzytelnika(const string& pesel, const string& imie, const string& nazwisko);
	KontoCzytelnika(const string& pesel);
	string getPesel() const;
	string getImie() const;
	string getNazwisko() const;
	float getKaucja() const;
	int getIloscKsiazek() const;
};