#include "header.h"
#include "Pracownik.h"

class BazaPracownikow {
private:
	vector<Pracownik> listaPracownikow;
public:
	BazaPracownikow();
	bool logowanie(Pracownik p) {
		string wpisanyLogin, wpisaneHaslo;

		cout << "Podaj login: ";
		cin >> wpisanyLogin;

		cout << "Podaj haslo: ";
		cin >> wpisaneHaslo;
		for (const auto& pracownik : listaPracownikow) {
			if (pracownik.getLogin() == wpisanyLogin && pracownik.getHaslo() == wpisaneHaslo) {
				cout << pracownik.getLogin() << ": logowanie pomyslne\n";
				return true;
			}
			cout << "Blad logowania!\n";
			return false;
		}
	}
	//dodajPracownika?
};