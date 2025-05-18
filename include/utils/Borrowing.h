#pragma once
#include "../../header.h"
#include "../models/Book.h"

class Borrowing {
public:
	static string fileName;

	int wypozyczKsiazke(const Book& ksiazka);
};
