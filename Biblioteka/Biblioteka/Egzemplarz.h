#include "header.h"
#include "Data.h"

class Egzemplarz{
private:
	int ID;
	enum class Status{dostepna, niedostepna, wypozyczona, zniszczona};
	Data dataZwrotu;
	Data dataWypozyczenia;
public:
	Egzemplarz();
	void ustawStatus(Status s);
	Status zwrocStatus();
	Data zwrocDateZwrotu();
	Data zwrocDateWypozyczenia();
	void zmienDateZwrotu(Data d);
};
