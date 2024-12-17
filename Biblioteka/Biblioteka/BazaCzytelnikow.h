#include "header.h"
#include "KontoCzytelnika.h"

class BazaCzytelnikow {
private:
	vector<KontoCzytelnika> listaCzytelnikow;
public:
	BazaCzytelnikow();
	void tworzenieKonta(KontoCzytelnika czytelnik) {
		if (!sprawdzenieKonta(czytelnik)) {
			listaCzytelnikow.push_back(czytelnik);
			cout << "Utworzono konto czytelnika\n";
		}
		else {
			cout << "Konto czytelnika juz istnieje\n";
		}
	}
	void usuniecieKonta(KontoCzytelnika czytelnik) {
		auto it = find(listaCzytelnikow.begin(), listaCzytelnikow.end(), czytelnik);

		if (it != listaCzytelnikow.end()) {
			listaCzytelnikow.erase(it);
			cout << "Usunieto konto czytelnika\n";
		}
		else {
			cout << "Nie ma takiego konta\n";
		}

	}
	bool sprawdzenieKonta(KontoCzytelnika czytelnik) {
		
	}
};