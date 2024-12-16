#include "header.h"
#include "Egzemplarz.h"

class Ksiazka {
private:
	string tytul;
	string nazwiskoAutora;
	int iloscEgzemplarzy;
	int rokWydania;
	int ID;
	vector<shared_ptr<Egzemplarz>> egzemplarze;
public:
	void wypiszDane();
	Ksiazka(int id, string t, string n, int i, int r):ID(id), tytul(t), nazwiskoAutora(n), iloscEgzemplarzy(i), rokWydania(r){}
	void dodajEgzemplarz(int egzID)
	{
		egzemplarze.push_back(make_shared<Egzemplarz>(egzID));
	}
};
