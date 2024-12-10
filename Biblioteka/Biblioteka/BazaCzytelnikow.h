#include "header.h"
#include "KontoCzytelnika.h"

class BazaCzytelnikow {
private:
	vector<KontoCzytelnika> listaCzytelnikow;
public:
	BazaCzytelnikow();
	void tworzenieKonta(KontoCzytelnika czytelnik);
	void usuniecieKonta(KontoCzytelnika czytelnik);
	bool sprawdzenieKOnta(KontoCzytelnika czytelnik);
};