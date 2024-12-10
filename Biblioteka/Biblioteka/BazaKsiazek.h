#include "header.h"
#include "Egzemplarz.h"
#include "Ksiazka.h"

class BazaKsiazek {
private:
	float stawkaOplatyZaOpoznienie; //to chyba mozna usunac
	vector<Ksiazka> listaKsiazek;
public:
	BazaKsiazek();
	void aktualizujStanDodaj(Ksiazka k);
	bool aktualizujStanUsun(Ksiazka k);
	bool aktualizujStanPoWypozyczeniu(Egzemplarz e);
};