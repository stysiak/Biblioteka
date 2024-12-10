#include "header.h"

class Data {
private:
	int dzien, miesiac, rok;
public:
	Data(int d, int m, int r):dzien(d), miesiac(m), rok(r){}
	Data zwrocDate();
	void ustawDate(int d, int m, int r);
};
