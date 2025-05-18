#pragma once
#include "../../header.h"

class ReaderAccount {
private:
	string pesel;
	string imie;
	string nazwisko;
	float kaucja = 0.0;
	int iloscKsiazek = 0;
public:
	ReaderAccount(const string& pesel, const string& imie, const string& nazwisko, const float& kaucja, const int& iloscKsiazek);
	ReaderAccount(const string& pesel, const string& imie, const string& nazwisko);
	ReaderAccount(const string& pesel);
	string getPesel() const;
	string getImie() const;
	string getNazwisko() const;
	float getKaucja() const;
	int getIloscKsiazek() const;
};