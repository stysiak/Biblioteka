#pragma once
#include "../../header.h"
#include "../models/Book.h"

class Return {
public:
	static string fileName;

	float returnBook(const Book& book);
};