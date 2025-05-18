#include "../../include/models/Book.h"

Book::Book() : ID(0), tytul(""), nazwiskoAutora(""), rokWydania(0), stan("") {} //konstruktor z warto�ciami domy�lnymi

Book::Book(int ID)
	: ID(ID) {
}

Book::Book(int ID, const string& tytul, const string& nazwiskoAutora, int rokWydania, string stan)
	: ID(ID), tytul(tytul), nazwiskoAutora(nazwiskoAutora), rokWydania(rokWydania), stan(stan) {
}

int Book::getID() const { 
	return ID; 
}

string Book::getTytul() const { 
	return tytul; 
}

string Book::getNazwiskoAutora() const { 
	return nazwiskoAutora; 
}

int Book::getRokWydania() const { 
	return rokWydania; 
}

string Book::getStan() const {
	return stan;
}