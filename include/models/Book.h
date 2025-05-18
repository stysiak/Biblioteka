#pragma once
#include "../../header.h"

class Book {
private:
    int ID;
    string tytul;
    string nazwiskoAutora;
    int rokWydania;
    string stan;
    string dataZwrotu;

public:
    Book();
    Book(int ID, const string& tytul, const string& nazwiskoAutora, int rokWydania, string stan);
    Book(int ID);
    int getID() const;
    string getTytul() const;
    string getNazwiskoAutora() const;
    int getRokWydania() const;
    string getStan() const;
  
};

