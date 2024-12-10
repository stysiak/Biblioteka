#include "header.h"

class Ksiazka {
private:
	string tytul;
	string nazwiskoAutora;
	int iloscEgzemplarzy;
	int rokWydania;
public:
	void wypiszDane();
	Ksiazka(string t, string n, int i, int r):tytul(t), nazwiskoAutora(n), iloscEgzemplarzy(i), rokWydania(r){}
};
