#include "header.h"
#include "Pracownik.h"

class BazaPracownikow {
private:
	vector<Pracownik> listaPracownikow;
public:
	BazaPracownikow();
	bool logowanie(Pracownik p);
};