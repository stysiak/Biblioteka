#include "Ksiazka.h"

Ksiazka::Ksiazka() : ID(0), tytul(""), nazwiskoAutora(""), rokWydania(0), stan("") {} //konstruktor z wartoœciami domyœlnymi

Ksiazka::Ksiazka(int ID)
	: ID(ID) {
}

Ksiazka::Ksiazka(int ID, const string& tytul, const string& nazwiskoAutora, int rokWydania, string stan = "dostepna")
	: ID(ID), tytul(tytul), nazwiskoAutora(nazwiskoAutora), rokWydania(rokWydania), stan(stan) {
}

int Ksiazka::getID() const { 
	return ID; 
}

string Ksiazka::getTytul() const { 
	return tytul; 
}

string Ksiazka::getNazwiskoAutora() const { 
	return nazwiskoAutora; 
}

int Ksiazka::getRokWydania() const { 
	return rokWydania; 
}

string Ksiazka::getStan() const {
	return stan;
}