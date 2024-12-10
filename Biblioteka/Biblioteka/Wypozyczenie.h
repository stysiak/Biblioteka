#include "header.h"
#include "KontoCzytelnika.h"
#include "Egzemplarz.h"

class Wypozyczenie {
public:
	Wypozyczenie();
	void przypiszCzytelnika(KontoCzytelnika);
	void przypiszEgzemplarz(Egzemplarz);
};
