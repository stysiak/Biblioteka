#include "header.h"
#include "Egzemplarz.h"
#include "Ksiazka.h"

class BazaKsiazek {
private:
	int ID = 0;
	int egzID = 100;
	//float stawkaOplatyZaOpoznienie; //to chyba mozna usunac
	unordered_map<int, shared_ptr<Ksiazka>> ksiazki;
	//vector<Ksiazka> listaKsiazek;
public:
	BazaKsiazek();
	int aktualizujStanDodaj(const string& tytul, const string& autor, int rok)
	{
		int id = ++ID;
		ksiazki[id] = make_shared<Ksiazka>(id, tytul, autor, rok);
		return id;
	}
	void dodajEgzemplarzDoKsiazki(int kID)
	{
		if (ksiazki.count(kID) > 0)
		{
			int eID = ++egzID;
			ksiazki.at(kID)->dodajEgzemplarz(egzID);
		}
		else
		{
			cout << "Podano bledne ID ksiazki" << endl;
		}
	}
	void aktualizujStanUsun(int kID)
	{
		if (ksiazki.count(kID) > 0)
		{
			ksiazki.erase(kID);
			cout << "Usunieto ksiazke" << endl;
		}
	}
	void usunEgzemplarzKsiazki(int eID)
	{
		
	}
	bool aktualizujStanPoWypozyczeniu(Egzemplarz e);
};