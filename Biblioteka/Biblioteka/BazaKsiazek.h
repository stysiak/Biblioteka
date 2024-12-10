#include "header.h"
#include "Egzemplarz.h"
#include "Ksiazka.h"

class BazaKsiazek {
private:
	float stawkaOplatyZaOpoznienie;
	vector<Ksiazka> listaKsiazek;
public:
	BazaKsiazek();
	void aktualizujStan();
	void aktualizujStanPoWypozyczeniu(Egzemplarz e);
};