#include "header.h"
#include "KontoCzytelnika.h"
#include "Egzemplarz.h"

class Pracownik {
private:
	string imie;
	string nazwisko;
	float pensja;
public:
	Pracownik();
	void sprawdzenieKonta(KontoCzytelnika);
	void przyjmijKaucje(KontoCzytelnika, Egzemplarz);

};
