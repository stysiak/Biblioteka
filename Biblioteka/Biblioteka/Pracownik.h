#include "header.h"
#include "KontoCzytelnika.h"
#include "Egzemplarz.h"

class Pracownik {
private:
	string imie;
	string nazwisko;
	float pensja;
	string login;
	string haslo;
public:
	Pracownik();
	void sprawdzenieKonta(KontoCzytelnika);
	void przyjmijKaucje(KontoCzytelnika, Egzemplarz);
	string getLogin() const;
	string getHaslo() const;

};
